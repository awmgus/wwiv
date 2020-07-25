/**************************************************************************/
/*                                                                        */
/*                          WWIV Version 5.x                              */
/*             Copyright (C)2015-2020, WWIV Software Services             */
/*                                                                        */
/*    Licensed  under the  Apache License, Version  2.0 (the "License");  */
/*    you may not use this  file  except in compliance with the License.  */
/*    You may obtain a copy of the License at                             */
/*                                                                        */
/*                http://www.apache.org/licenses/LICENSE-2.0              */
/*                                                                        */
/*    Unless  required  by  applicable  law  or agreed to  in  writing,   */
/*    software  distributed  under  the  License  is  distributed on an   */
/*    "AS IS"  BASIS, WITHOUT  WARRANTIES  OR  CONDITIONS OF ANY  KIND,   */
/*    either  express  or implied.  See  the  License for  the specific   */
/*    language governing permissions and limitations under the License.   */
/**************************************************************************/
#include "wwivutil/print/print.h"

#include "core/command_line.h"
#include "core/log.h"
#include "core/file.h"
#include "core/stl.h"
#include "core/strings.h"
#include "core/textfile.h"
#include "local_io/local_io_curses.h"
#include "local_io/local_io_win32.h"
#include "localui/curses_io.h"
#include "sdk/ansi/ansi.h"
#include "sdk/ansi/localio_screen.h"
#include "sdk/ansi/makeansi.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using wwiv::core::BooleanCommandLineArgument;
using namespace wwiv::core;
using namespace wwiv::sdk;
using namespace wwiv::sdk::ansi;
using namespace wwiv::strings;

namespace wwiv::wwivutil {

PrintCommand::PrintCommand() : UtilCommand("print", "prints a textfile") {}

std::string PrintCommand::GetUsage() const {
  std::ostringstream ss;
  ss << "Usage: " << std::endl << std::endl;
  ss << "  print : Prints a textfile." << std::endl;
  return ss.str();
}

 std::vector<int> colors = {7, 11, 14, 5, 31, 2, 12, 9, 6, 3};

 enum class pipe_state_t { text, pipe };
 static std::string PipeCodesToAnsi(const std::string & s) { 
   std::string out;
   out.reserve(s.size() + 1.1);
   auto state = pipe_state_t::text;
   std::string curpipe;
   int curatr = 0x07;
   for (auto it = std::begin(s); it != std::end(s); it++) {
     char c = *it;
     switch (state) {
     case pipe_state_t::text: {
       if (c == '|') {
         state = pipe_state_t::pipe;
         curpipe.push_back(c);
       } else {
         out.push_back(c);
       }
     } break;
     // grab first
     case pipe_state_t::pipe: {
       auto pipe_size = wwiv::stl::ssize(curpipe);
       if (std::isdigit(c) && pipe_size == 2) {
         curpipe.push_back(c);
         std::string ansitext;
         if (curpipe[1] == '#') {
           int color = colors.at(curpipe[2] - '0');
           ansitext = wwiv::sdk::ansi::makeansi(color, curatr);
           curatr = color;
         } else {
           int color = to_number<int>(curpipe.substr(1));
           ansitext = wwiv::sdk::ansi::makeansi(color, curatr);
           curatr = color;
         }
         out.append(ansitext);
         curpipe.clear();
         state = pipe_state_t::text;
       } else if ((std::isdigit(c) || c == '#') && pipe_size == 1) {
         curpipe.push_back(c);
       } else {
         state = pipe_state_t::text;
         out.append(curpipe);
         curpipe.clear();
       }
     } break;
     };
   } 
   out.shrink_to_fit();
   return out;
 }


int PrintCommand::Execute() {
  if (remaining().empty()) {
    std::cout << GetUsage() << GetHelp() << endl;
    return 2;
  }
  TextFile tf(remaining().front(), "rt");
  auto s = tf.ReadFileIntoString();

  if (s.find('|') != std::string::npos) {
    s = PipeCodesToAnsi(s);
  }

  bool need_pause = false;
  if (!barg("ansi")) {
    std::cout << s << std::endl;
  } else {
    std::unique_ptr<LocalIO> io;
    const auto io_type = sarg("io");
#ifdef _WIN32
    if (io_type == "win32") {
      io = std::make_unique<Win32ConsoleIO>();
    }
#endif
    if (!io) {
      need_pause = true;
      CursesIO::Init("wwivutil");
      // Use 25 lines (80x25) by default.
      // TODO(rushfan): We should try to inspect the screen size if possible
      // and use that instead.  Don't know how to do that on *NIX though.
      io = std::make_unique<CursesLocalIO>(25);
    }
    LocalIOScreen screen(io.get(), 80);
    AnsiCallbacks cb;
    cb.move_ = [](int x, int y) { VLOG(2) << "moved: x: " << x << "; y:" << y; };
    Ansi ansi(&screen, cb, 0x07);
    HeartCodeFilter heart(&ansi, {7, 11, 14, 5, 31, 2, 12, 9, 6, 3});

    screen.clear();
    for (const auto c : s) {
      heart.write(c);
    }
    if (need_pause) {
      io->GetChar();
    }
  }
  return 0;
}

bool PrintCommand::AddSubCommands() {
  add_argument(BooleanCommandLineArgument{"ansi", "Display the file as an ANSI file.", true});
  add_argument({"io", "What type of IO to use, win32 | curses",
#ifdef _WIN32
                "win32"});
#else
                "curses"});
#endif
  return true;
}

} // namespace wwiv
