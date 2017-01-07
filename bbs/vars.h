/**************************************************************************/
/*                                                                        */
/*                              WWIV Version 5.x                          */
/*             Copyright (C)1998-2017, WWIV Software Services             */
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
#ifndef __INCLUDED_VARS_H__
#define __INCLUDED_VARS_H__

#include <ctime>

#include "bbs/conf.h"
#include "sdk/vardec.h"
#include "sdk/net.h"

///////////////////////////////////////////////////////////////////////////////

#ifdef _DEFINE_GLOBALS_
#define __EXTRN__
#else
#define __EXTRN__ extern
#endif

///////////////////////////////////////////////////////////////////////////////

__EXTRN__ char  ansistr[81],
          charbuffer[255],
          irt[81],
          irt_name[205],
          irt_sub[81],
          *quotes_ind;

__EXTRN__ unsigned char checksum;

__EXTRN__ int ansiptr,
bquote,
change_color,
charbufferpointer,
chatting,
defscreenbottom,
do_event,
equote;

__EXTRN__ bool  bChatLine,
          newline,
          forcescansub,
          guest_user,
          no_hangup,
          smwcheck,
          chatcall,
          chat_file,
          emchg,
          hangup,
          incom,
          outcom,
          okskey,
          okmacro,
          ok_modem_stuff;

// Chatroom additions
__EXTRN__ bool in_chatroom;

__EXTRN__ int modem_speed;

__EXTRN__ int curatr;
__EXTRN__ unsigned int
          dirconfnum,
          subconfnum;

__EXTRN__ time_t nscandate;


__EXTRN__ int
g_flags,
com_speed;

__EXTRN__ uint32_t
*qsc,
*qsc_n,
*qsc_q,
*qsc_p;

__EXTRN__ long extratimecall;

__EXTRN__ colorrec rescolor;
__EXTRN__ userconfrec *uconfsub, *uconfdir;
__EXTRN__ confrec *subconfs, *dirconfs;

#endif // __INCLUDED_VARS_H__

