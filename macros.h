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
#define SetOper(x)		((x)->flags |= OPER_FLAG)
#define DelOper(x)		((x)->flags &= ~OPER_FLAG)
#define SetAdmin(x)		((x)->flags |= ADMIN_FLAG)
#define DelAdmin(x)		((x)->flags &= ~ADMIN_FLAG)
#define SetNSAuth(x)		((x)->authed |= NSAUTH_FLAG)
#define DelNSAuth(x)		((x)->authed &= ~NSAUTH_FLAG)
#define SetNSKillProt(x)	((x)->killprot |= NS_KILLPROT_FLAG)
#define DelNSKillProt(x)	((x)->killprot &= ~NS_KILLPROT_FLAG)
#define SetCAdmin(x)		((x)->flags |= CADMIN_FLAG)
#define DelCAdmin(x)		((x)->flags &= ~CADMIN_FLAG)

#define IsOper(x)		((x)->flags & OPER_FLAG)
#define IsAdmin(x)		((x)->flags & ADMIN_FLAG)
#define IsSusp(x)		((x)->susp & SUSP_FLAG)
#define IsNSAuth(x)		((x)->authed & NSAUTH_FLAG)
#define IsNSKillProt(x)		((x)->killprot & NS_KILLPROT_FLAG)

/**** Channel Services Crap ****/

#define IsCAdmin(x)		((x)->flags & CADMIN_FLAG)


#define IsChanOwner(x)		(((x)->flags & CADMIN_FLAG) &&  \
				((x)->level == CHAN_OWNER))

#define IsChanAdmin(x)		(((x)->flags & CADMIN_FLAG) && \
				((x)->level == CHAN_ADMIN))

#define IsChanOper(x)		(((x)->flags & CADMIN_FLAG) && \
				((x)->level == CHAN_OPER))

#define IsChanVoice(x)		(((x)->flags & CADMIN_FLAG) && \
				((x)->level == CHAN_VOIC))

/***** Usermode stuff *****/

#define SetInv(x)		((x)->invs |= USER_INVS)
#define DelInv(x)		((x)->invs &= ~USER_INVS)
#define SetWall(x)		((x)->wall |= USER_WALLOPS)
#define DelWall(x)		((x)->wall &= ~USER_WALLOPS)
#define SetGlob(x)		((x)->glob |= USER_GLOBOPS)
#define DelGlob(x)		((x)->glob &= ~USER_GLOBOPS)

#define IsInvisible(x)		((x)->invs & USER_INVS)
#define IsWallops(x)		((x)->wall & USER_WALLOPS)
#define IsGlobops(x)		((x)->glob & USER_GLOBOPS)

///////////////////////////////////////////////////////////////////////////////
//


