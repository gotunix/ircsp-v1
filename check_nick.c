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

void	checknick		(void);

///////////////////////////////////////////////////////////////////////////////
//

void
checknick (void)
{
	Nick		*n;
	nickservDB	*ns;

	n = nick;
	ns = nickservdb;

	while (ns)
	{
		//////////////////////////////////////////////////////////////
		// check if temp->nickname is registered.
		//

		n = findNick(ns->nickname);
		if (!n)
		{
			//////////////////////////////////////////////////////
			// temp->nickname is not a registered nickname, 
			// so don't do anything.
			//
		}
		else
		{
			if (!IsNSAuth(ns))
			{
				//////////////////////////////////////////////
				// make sure temp->nickname is not already 
				// authorized.

				if (IsNSKillProt(ns))
				{

					///////////////////////////////////////////////////////
					// temp->nickname has kill protection on, if he does,
					// give him 2 minutes to authorize, and if he don't
					// remove him from the network.
					//

					if ((time(NULL) - n->ConnTime) > 120)
					{ 
						//////////////////////////////////////////////////
						// user has faild to authorize, so remove him/her
						// from the network.
						//
						send_to_sock(s, 
							":%s KILL %s :%s\n",
							config->nnick, ns->nickname,
							"User faild to authorize with NS.");
						delNick(ns->nickname);
					}
					else
					{
						send_to_sock(s, 
							":%s NOTICE %s :%s\n",
							config->nnick, ns->nickname,
							"You're using a registered nickname, please authorize.");
						send_to_sock(s, 
							":%s NOTICE %s :\2/msg %s AUTH %s <password>\n",
							config->nnick, ns->nickname, 
							config->nnick, ns->nickname);
					}
				}
				else
				{
					////////////////////////////////////////////////////////
					// temp->nickname doesn't have kill protection on,
					// so keep sending please auth yourself messages.
					//

					send_to_sock(s, 
						":%s NOTICE %s :%s\n",
						config->nnick, ns->nickname,
						"You're using a registered nickname, please authorize.");
					send_to_sock(s, 
						":%s NOTICE %s :\2/msg %s AUTH %s <password>\n",
						config->nnick, ns->nickname, 
						config->nnick, ns->nickname);
				}
			}
		}
         
		////////////////////////////////////////////////////////////////////
		// move to the next nickname in our nick list.
		//

		ns = ns->next;
	}
}

///////////////////////////////////////////////////////////////////////////////
//


