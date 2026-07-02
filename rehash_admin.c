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

int	rehash_admin		();

///////////////////////////////////////////////////////////////////////////////
//

int
rehash_admin ()
{
	Admin	*a;

	a = admin;
	for (a = admin; a; a = a->next)
	{
		delAdmin(a->nickname);
	}
	load_admin();
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//


