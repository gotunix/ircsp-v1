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

Hosts	*addHost		(char *);
Hosts	*findHost		(char *);
void	delHost			(char *);

///////////////////////////////////////////////////////////////////////////////
//

Hosts *
addHost (hostname)
char	*hostname;
{
	Hosts	*h;
	int	mFail = 0, mPass = 0;

	h = (Hosts *)calloc(1, sizeof(Hosts));
	{
		if (!h)
		{
			if (config->debug)
			{
				printf(
					"addHost(): calloc() of h failed\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addHost(): calloc() of h [%p] passed.\n",
					h);
			}
			mPass++;
		}
	}
	h->hostname = (char *)calloc(1, 1024);
	{
		if (!h->hostname)
		{
			if (config->debug)
			{
				printf(
					"addHost(): calloc() of h->hostname failed\n");
			}
			mFail++;
		}
		else
		{
			if (config->debug)
			{
				printf(
					"addHost(): calloc() of h->hostname [%p] passed.\n",
					h->hostname);
			}
			mPass++;
		}
	}


	strcpy(h->hostname, hostname);
	h->numHosts++;

	if (config->debug)
	{
		printf(
			"addHost(): HST: %s\n",
			h->hostname);
	}

	if (!hosts)
	{
		hosts = h;
		h->next = NULL;
	}
	else
	{
		h->next = hosts;
		hosts = h;
	}
	return h;
}

///////////////////////////////////////////////////////////////////////////////
//

Hosts *
findHost (hostname)
char	*hostname;
{
	Hosts	*h;
	h = hosts;

	while (h)
	{
		if (!strcasecmp(h->hostname, hostname))
		{
			if (config->debug)
			{
				printf(
					"findHost(): %s [%p] found.\n",
					h->hostname, h->hostname);
			}
			return h;
		}
		h = h->next;
	}
	if (config->debug)
	{
		printf(
			"findHost(): %s not found\n",
			hostname);
	}
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
//

void
delHost (hostname)
char	*hostname;
{
	Hosts	*h, *next, *delete;

	for (h = hosts; h; h = next)
	{
		next = h->next;
		if (!strcasecmp(h->hostname, hostname))
		{
			if (config->debug)
			{
				printf(
					"delHost(): %s [%p] found, removing.\n",
					h->hostname, h->hostname);
			}
			if (hosts == h)
			{
				hosts = h->next;
			}
			else
			{
				for (delete = hosts; (delete->next != h) && delete; delete = delete->next);
				delete->next = h->next;
			}
			free (h->hostname);
			free (h);
			return ;
		}
		if (config->debug)
		{
			printf(
				"delHost(): %s not found\n",
				hostname);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//

