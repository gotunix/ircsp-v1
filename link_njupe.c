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

NJupe	*addNJupe	(char *, char *);
NJupe	*findNJupe	(char *);
void	delNJupe	(char *);

///////////////////////////////////////////////////////////////////////////////
//

NJupe	*
addNJupe (nickname, reason)
char	*nickname;
char	*reason;
{
	NJupe	*nj;
	int	mFail = 0, mPass = 0;

	nj = (NJupe *)calloc(1, sizeof(NJupe));
	{
		if (!nj)
		{
			if (config->debug)
			{
				printf(
					"addNJupe(): calloc() of nj failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addNJupe(): calloc() of nj [%p] passed.\n",
					nj);
			}
			mPass++;
		}
	}
	nj->nickname = (char *)calloc(1, 256);
	{
		if (!nj->nickname)
		{
			if (config->debug)
			{
				printf(
					"addNJupe(): calloc() of nj->nickname failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addNJupe(): calloc() of nj->nickname [%p] passed.\n",
					nj->nickname);
			}
			mPass++;
		}
	}
	nj->reason = (char *)calloc(1, 1024);
	{
		if (!nj->reason)
		{
			if (config->debug)
			{
				printf(
		 			"addNJupe(): calloc() of nj->reason failed.\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addNJupe(): calloc()of nj->reason [%p] passed.\n",
					nj->reason);
			}
			mPass++;
		}
	}

	if (mFail)
	{
		if (config->debug)
		{
			printf(
				"addNJupe(): calloc() %d fail, %d pass\n",
				mFail, mPass);
		}
		return NULL;
	}

	strcpy(nj->nickname, nickname);
	strcpy(nj->reason, reason);

	printf(
		"addNJupe(): NN: %s    RES: %s\n",
		nj->nickname, nj->reason);

	if (!njupe)
	{
		njupe = nj;
		nj->next = NULL;
	}
	else
	{
		nj->next = njupe;
		njupe = nj;
	}
	return nj;
}

///////////////////////////////////////////////////////////////////////////////
//

NJupe	*
findNJupe (nickname)
char	*nickname;
{
	NJupe	*nj;

	nj = njupe;
	while (nj)
	{
		if (!strcasecmp(nj->nickname, nickname))
		{
			if (config->debug)
			{
				printf(
					"findNJupe(): %s [%p] found.\n",
					nj->nickname, nj->nickname);
			}
			return nj;
		}
		nj = nj->next;
	}
	if (config->debug)
	{
		printf(
			"findNJupe(): %s not found\n",
			nickname);
	}
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
//

void
delNJupe (nickname)
char	*nickname;
{
	NJupe	*nj, *next, *delete;

	for (nj = njupe; nj; nj = next)
	{
		next = nj->next;
		if (!strcasecmp(nj->nickname, nickname))
		{
			if (config->debug)
			{
				printf(
					"delNJupe(): %s [%p] found, removing.\n",
					nj->nickname, nj->nickname);
			}
			if (njupe == nj)
			{
				njupe = nj->next;
			}
			else
			{
				for (delete = njupe; (delete->next != nj) &&
					delete; delete = delete->next);
				delete->next = nj->next;
			}
			free(nj->nickname);
			free(nj->reason);
			free(nj);
			return;
		}
		if (config->debug)
		{
			printf(
				"delNJupe(): %s not found.\n",
				nickname);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//

