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

Clones	*addClone	 (char *, char *, char *);
Clones  *findClone       (char *);
Clones  *findClonebyUser (char *);
void	delClone	 (char *);

///////////////////////////////////////////////////////////////////////////////
//

Clones *
addClone (username,nickname,hostname)
char	*username;
char	*nickname;
char	*hostname;
{
	Clones	*C;
	int	mFail = 0, mPass = 0;

	C = (Clones *)calloc(1, sizeof(Clones));
	{
		if (!C)
		{
			if (config->debug)
			{
				printf(
					"addClone(): calloc of C failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addClone(): calloc of C [%p] passed.\n",
					C);
			}
			mPass++;
		}
	}
	C->username = (char *)calloc(1, 256);
	{
		if (!C->username)
		{
			if (config->debug)
			{
				printf(
					"addClone(): calloc of C->username failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addClone(): calloc of C->username [%p] passed.\n",
					C->username);
			}
			mPass++;
		}
	}
	C->nickname = (char *)calloc(1, 256);
	{
		if (!C->nickname)
		{
			if (config->debug)
			{
				printf(
					"addClone(): calloc of C->nickname failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addClone(): calloc of C->nickname [%p] passed.\n",
					C->nickname);
			}
			mPass++;
		}
	}
	C->hostname = (char *)calloc(1, 1024);
	{
		if (!C->hostname)
		{
			if (config->debug)
			{
				printf(
					"addClone(): calloc of C->hostname failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addClone(): calloc of C->hostname [%p] passed.\n",
					C->hostname);
			}
			mPass++;
		}
	}

	if (mFail)
	{
		if (config->debug)
		{
			printf(
				"addClone(): calloc(): %d fail, %d pass\n",
				mFail, mPass);
		}
		return NULL;
	}

	strcpy(C->username, username);
	strcpy(C->nickname, nickname);
	strcpy(C->hostname, hostname);

	if (config->debug)
	{
		printf(
			"addClone(): UN: %s    NN: %s    HN: %s\n",
			C->username, C->nickname, C->hostname);
	}

	if (!clone)
	{
		clone = C;
		C->next = NULL;
	}
	else
	{
		C->next = clone;
		clone = C;
	}
	return C;
}

///////////////////////////////////////////////////////////////////////////////
//

Clones *
findClone (nickname)
char	*nickname;
{
	Clones	*c;

	c = clone;
	while (c)
	{
		if (!strcasecmp(c->nickname, nickname))
		{
			if (config->debug)
			{
				printf(
					"findClone(): %s [%p] found.\n",
					c->nickname, c->nickname);
			}
			return c;
		}
		c = c->next;
	}
	if (config->debug)
	{
		printf(
			"findClone(): %s not found.\n",
			nickname);
	}
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
//

Clones *
findClonebyUser (username)
char	*username;
{
	Clones	*c;

	c = clone;
	while (c)
	{
		if (!strcasecmp(c->username, username))
		{
			if (config->debug)
			{
				printf(
					"findClonebyUser(): %s [%p] found.\n",
					c->username, c->username);
			}
			return c;
		}
		c = c->next;
	}
	if (config->debug)
	{
		printf(
			"findClonebyUser(): %s not found.\n",
			username);
	}
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
//

void
delClone (nickname)
char	*nickname;
{
	Clones	*c, *next, *delete;

	for (c = clone; c; c = next)
	{
		next = c->next;
		if (!strcasecmp(c->nickname, nickname))
		{
			if (config->debug)
			{
				printf(
					"delClone(): %s [%s] found, removing.\n",
					c->nickname, c->nickname);
			}
			if (clone == c)
			{
				clone = c->next;
			}
			else
			{
				for (delete = clone; (delete->next != c) && 
					delete; delete = delete->next);
				delete->next = c->next;
			}
			free(c->username);
			free(c->nickname);
			free(c->hostname);
			free(c);
			return;
		}
		if (config->debug)
		{
			printf(
				"delClone(): %s not found.\n",
				nickname);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//

