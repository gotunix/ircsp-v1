// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 1995-2026 The IRCSP authors
// =============================================================================================== //
//                                                                                                 //
//                         /$$$$$$ /$$$$$$$   /$$$$$$   /$$$$$$  /$$$$$$$                          //
//                        |_  $$_/| $$__  $$ /$$__  $$ /$$__  $$| $$__  $$                         //
//                          | $$  | $$  \ $$| $$  \__/| $$  \__/| $$  \ $$                         //
//                          | $$  | $$$$$$$/| $$      |  $$$$$$ | $$$$$$$/                         //
//                          | $$  | $$__  $$| $$       \____  $$| $$____/                          //
//                          | $$  | $$  \ $$| $$    $$ /$$  \ $$| $$                               //
//                         /$$$$$$| $$  | $$|  $$$$$$/|  $$$$$$/| $$                               //
//                        |______/|__/  |__/ \______/  \______/ |__/                               //
//                                                                                                 //
// =============================================================================================== //
//              This program is free software: you can redistribute it and/or modify               //
//              it under the terms of the GNU General Public License as published by               //
//              the Free Software Foundation, either version 3 of the License, or                  //
//              (at your option) any later version.                                                //
//                                                                                                 //
//              This program is distributed in the hope that it will be useful,                    //
//              but WITHOUT ANY WARRANTY; without even the implied warranty of                     //
//              MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                      //
//              GNU General Public License for more details.                                       //
//                                                                                                 //
//              You should have received a copy of the GNU General Public License                  //
//              along with this program.  If not, see <https://www.gnu.org/licenses/>.             //
// =============================================================================================== //
#include "services.h"

void SignalHUP (int num);
void SignalSEGV (int num);

//////////////////////////////////////////////////////////////////////////////
//

void
SignalHUP (num)
int	num;
{
	num = 0;

	send_to_sock(s, 
		"WALLOPS :Signal() --  HUP Receved.. Rehashing.\n");

	rehash_admin();
	rehash_bans();
	rehash_cadmin();
	rehash_config();
	rehash_channel();
	rehash_gline();
	/* rehash_nick(); this was not a smart idea =) --ice95 */
	rehash_suspchan(); 
}

//////////////////////////////////////////////////////////////////////////////
//

void
SignalSEGV (num)
int	num;
{
	num = 0;

	send_to_sock(s, 
		"WALLOPS :Signal() -- SEGV....\n");


//	system("/home/justin/code/irc-sp/ircsp");

	exit(1);
}

//////////////////////////////////////////////////////////////////////////////
//


