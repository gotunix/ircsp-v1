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

Admin *addAdmin (char *, int, char *, int, int, char *);
Admin *findAdmin (char *);
void delAdmin (char *);

//////////////////////////////////////////////////////////////////////////////
//

Admin *
addAdmin (nickname,level,hostname,flags,susp,password)
char  *nickname;
int   level;
char  *hostname;
int   flags;
int   susp;
char  *password;
{
	Admin *new;
	int mPass = 0, mFail = 0;
	new = (Admin *)calloc(1, sizeof(Admin));
	{
		if (!new)
		{
#ifdef DEBUG
			{
				printf(
					"addAdmin(): calloc() of new failed.\n");
			}
#endif
			mFail++;
		}
		else
		{
#ifdef DEBUG
			{
				printf(
					"addAdmin(): calloc() of new passed [%p].\n",
					new);
			}
#endif
			mPass++;
		}
	}
	new->nickname = (char *)calloc(1, 64);
	{
		if (!new->nickname)
		{
#ifdef DEBUG
			{
				printf(
					"addAdmin(): calloc() of new->nickname failed.\n");
			}
#endif
		}
		else
		{
#ifdef DEBUG
			{
				printf(
					"addAdmin(): calloc() of new->nickname passed [%p].\n",
					new->nickname);
			}
#endif
		}
	}
	new->hostname = (char *)calloc(1, 1024);
	{
		if (!new->hostname)
		{
#ifdef DEBUG
			{
				printf(
					"addAdmin(): calloc() of new->hostname failed.\n");
			}
#endif
		}
		else
		{
#ifdef DEBUG
			{
				printf(
					"addAdmin(): calloc() of new->hostname passed [%p].\n",
					new->hostname);
			}
#endif
		}
	}
	new->password = (char *)calloc(1, 256);
	{
		if (!new->password)
		{
#ifdef DEBUG
			{
				printf(
					"addAdmin(): calloc() of new->password failed.\n");
			}
#endif
		}
		else
		{
#ifdef DEBUG
			{
				printf(
					"addAdmin(): calloc() of new->password [%p].\n",
					new->password);
			}
#endif
		}
	}
	if (mFail)
	{
#ifdef DEBUG
		{
			printf(
				"addAdmin(): %d pass, %d fail\n",
				mPass, mFail);
		}
#endif
		return NULL;
	}
	strcpy(new->nickname, nickname);
	strcpy(new->hostname, hostname);
	strcpy(new->password, password);

	new->level = level;
	new->flags = flags;
	new->susp  = susp;

#ifdef DEBUG
	{
		printf(
			"addAdmin(): NN: %s   HN: %s   PW: %s   LVL: %d   FLG: %d  SUSP: %d\n",
			new->nickname, new->hostname, new->password, new->level,
			new->flags, new->susp);
	}
#endif

	if (!admin)
	{
		admin = new;
		new->next = NULL;
	}
	else
	{
		new->next = admin;
		admin = new;
	}
	return new;
}

//////////////////////////////////////////////////////////////////////////////
//

Admin *
findAdmin (nickname)
char  *nickname;
{
	Admin *temp;
	temp = admin;
	while (temp)
	{
		if (!strcasecmp(temp->nickname, nickname))
		{
#ifdef DEBUG
			{
				printf(
					"findAdmin(): %s found.\n", nickname);
			}
#endif
			return temp;
		}
		temp = temp->next;
	}
#ifdef DEBUG
	{
		printf(
			"findAdmin(): %s not found.\n", nickname);
	}
#endif
	return NULL;
}

//////////////////////////////////////////////////////////////////////////////
//

void
delAdmin (nickname)
char  *nickname;
{
	Admin *temp, *next, *delete;
	for (temp = admin; temp; temp = next)
	{
		next = temp->next;
		if (!strcasecmp(temp->nickname, nickname))
		{
#ifdef DEBUG
			{
				printf(
					"delAdmin(): %s found, deleting.\n",
					nickname);
			}
#endif
			if (admin == temp)
			{
				admin = temp->next;
			}
			else
			{
				for (delete = admin; (delete->next != temp) && delete;
					delete = delete->next)
					;
				delete->next = temp->next;
			}
			free(temp->nickname);
			free(temp->hostname);
			free(temp->password);
			free(temp);
			return;
		}
#ifdef DEBUG
		{
			printf(
				"delAdmin(): %s not found, unable to delete.\n",
				nickname);
		}
#endif
	}
}
