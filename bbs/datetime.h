/**************************************************************************/
/*                                                                        */
/*                              WWIV Version 5.x                          */
/*             Copyright (C)1998-2016, WWIV Software Services             */
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
#ifndef __INCLUDED_DATETIME_H__
#define __INCLUDED_DATETIME_H__

#include <chrono>
#include <ctime>
#include <string>

char *date();
char *fulldate();
char *times();
time_t date_to_daten(const char *datet);
void filedate(const char *fpath, char *rtn);
long timer();
bool isleap(int nYear);
int dow();
char *ctim(float f);
char *ctim(double f);
char *ctim(long d);
std::string ctim2(long d);
int years_old(int nMonth, int nDay, int nYear);
std::chrono::system_clock::duration duration_since_midnight(std::chrono::system_clock::time_point now);
std::chrono::system_clock::time_point minutes_after_midnight(int minutes);

#endif // __INCLUDED_DATETIME_H__
