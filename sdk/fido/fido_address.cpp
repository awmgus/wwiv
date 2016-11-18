/**************************************************************************/
/*                                                                        */
/*                          WWIV Version 5.x                              */
/*               Copyright (C)2016 WWIV Software Services                 */
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
#include "sdk/fido/fido_address.h"

#include <set>
#include <string>

#include <cereal/cereal.hpp>
#include <cereal/access.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/archives/json.hpp>

#include "core/file.h"
#include "core/log.h"
#include "core/stl.h"
#include "core/strings.h"
#include "sdk/datetime.h"
#include "sdk/filenames.h"

using std::string;
using namespace wwiv::core;
using namespace wwiv::strings;
using namespace wwiv::stl;

namespace wwiv {
namespace sdk {
namespace fido {

template <typename C, typename I>
int next_int(C& c, I& it, std::set<char> stop) {
  string s;
  while (it != std::end(c) && !contains(stop, *it)) {
    if (!std::isdigit(*it)) {
      throw bad_fidonet_address(StrCat("Missing Unexpected nondigit. address: ", c));
    }
    s.push_back(*it++);
  }
  if (it != std::end(c) && contains(stop, *it)) {
    // skip over last
    it++;
  }
  return StringToInt(s);
}

FidoAddress::FidoAddress(const std::string& address) {
  bool has_zone = contains(address, ':');
  bool has_net = contains(address, '/');
  bool has_point = contains(address, '.');
  bool has_domain = contains(address, '@');

  if (!has_net) {
    throw bad_fidonet_address(StrCat("Missing Net or Node. Unable to parse address: ", address));
  }
  auto it = std::begin(address);
  if (has_zone) {
    zone_ = next_int(address, it, {':'});
  } else {
    // per FSL-1002: "If 'ZZ:' is missing then assume 1 as the zone."
    // TODO(rushfan): Not sure if this is really what we expect though...
    zone_ = 1;
  }
  net_ = next_int(address, it, {'/'});
  node_ = next_int(address, it, {'@', '.'});
  if (has_point) {
    point_ = next_int(address, it, {'@'});
  }
  if (has_domain) {
    domain_ = string(it, std::end(address));
  }
}

std::string FidoAddress::as_string(bool include_domain) const {
  // start off with the minimal things we know.
  string s = StrCat(zone_, ":", net_, "/", node_);

  if (point_ > 0) {
    s += StrCat(".", point_);
  }

  if (include_domain && !domain_.empty()) {
    s += StrCat("@", domain_);
  }

  return s;
}

}
}  // namespace net
}  // namespace wwiv
