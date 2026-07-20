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

int	match		(const char *, const char *);

int 
match (mask, name)
const	char	*mask;
const	char	*name;
{
	const	char	*m, *n, *ma, *na;
	int		wild, q;

	m  = mask;
	n  = name;
	ma = mask;
	na = name;

	wild = 0;
	q = 0;

	while (1)
	{
		if (*m == '*')
		{
			while (*m == '*')
			{
				m++;
			}
			wild = 1;
			ma = m;
			na = n;
		}
		if (!*m)
		{
			if (!*n)
			{
				return 0;
			}
			for (m--; (m > mask) && (*m == '?'); m--);
			if ((*m == '*') && (m > mask) && (m[-1] != '\\'))
			{
				return 0;
			}
			if (!wild)
			{
				return 1;
			}
			m = ma;
			n = ++na;
		}
		else if (!*n)
		{
			while (*m == '*')
			{
				m++;
			}
			return (*m != 0);
		}
		if ((*m == '\\') && ((m[1] == '*') || (m[1] == '?')))
		{
			m++;
			q = 1;
		}
		else
		{
			q = 0;
		}
		if ((tolower(*m) != tolower(*n)) && ((*m != '?') || q))
		{
			if (!wild)
			{
				return 1;
			}
			m = ma;
			n = ++na;
		}
		else
		{
			if (*m)
			{
				m++;
			}
			if (*n)
			{
				n++;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//


