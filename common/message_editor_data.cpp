/**************************************************************************/
/*                                                                        */
/*                              WWIV Version 5.x                          */
/*               Copyright (C)2018-2020, WWIV Software Services           */
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
/*                                                                        */
/**************************************************************************/
#include "common/message_editor_data.h"

#include "bbs/bbs.h"
#include "core/strings.h"
#include "sdk/names.h"
#include <string>

using std::string;
using namespace wwiv::bbs;
using namespace wwiv::strings;

wwiv::bbs::MessageEditorData::MessageEditorData() 
    : MessageEditorData(a()->names()->UserName(a()->usernum)) {}

MessageEditorData::MessageEditorData(std::string fn) : from_name(std::move(fn)) {}

bool MessageEditorData::is_email() const {
  return iequals(aux, "email");
}