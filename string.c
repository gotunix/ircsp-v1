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

///////////////////////////////////////////////////////////////////////////////
//

char *
token (tokenlist,index)
char	*tokenlist;
int	index;
{
	static		char	token[512];
	unsigned	int	curtok, curpos, tokenpos;

	curtok = 1;
	curpos = 0;
	tokenpos = 0;

	while (curtok < index)
	{
		if (tokenlist[curpos++] == ' ')
		{
			curtok++;
		}
		if (tokenlist[curpos] == '\n')
		{
			return NULL;
		}
	}
	while ((tokenlist[curpos] != ' ') &&
		(tokenlist[curpos] != '\r') &&
		(tokenlist[curpos] != '\n'))
	{
		token[tokenpos++] = tokenlist[curpos++];
	}
	token[tokenpos] = '\0';
	return (char *)token;
}

///////////////////////////////////////////////////////////////////////////////
//

char *
lrange (tokenlist,from)
char	*tokenlist;
int	from;
{
	static		char	token[1024];
	unsigned	int	curtok, tokenpos, curpos;

	curtok = 1;
	tokenpos = 0;
	curpos = 0;

	while (curtok < from)
	{
		if (tokenlist[curpos++] == ' ')
		{
			curtok++;
		}
		else if ((tokenlist[curpos] == '\n') || 
			(tokenlist[curpos] ==  '\0'))
		{
			return NULL;
		}
	}
	while ((tokenlist[curpos] != '\n') && 
		(tokenlist[curpos] != '\0') &&
		(tokenlist[curpos] != '\r'))
	{
		token[tokenpos++] = tokenlist[curpos++];
	}
	token[tokenpos] = '\0';
	return (char *)token;
}

///////////////////////////////////////////////////////////////////////////////
//

int
tokenize (inlist,sep)
char	*inlist;
char	sep;
{
	char	outlist[1024];
	int	pos, num;

	pos = 0;
	num = 1;

	while ((inlist[pos] != '\n') && (inlist[pos] != '\0'))
	{
		if (inlist[pos] == sep)
		{
			outlist[pos] = ' ';
			++num;
		}
		else
		{
			outlist[pos] = inlist[pos];
		}
		++pos;
	}
	strcpy(inlist, outlist);
	inlist[pos] = '\0';

	return num;
}

///////////////////////////////////////////////////////////////////////////////
//
 
char *
nocolon (line)
char	*line;
{
	int	pos;

	pos = -1;

	if (line[0] != ':') 
	{
		return 0;
	}
	while (line[++pos] != '\0')
	{
		line[pos] = line[pos+1];
	}
	return line;
}

///////////////////////////////////////////////////////////////////////////////
//

int 
numtokens (line)
char	*line;
{
	int	pos, num_tok;

	pos = 0;
	num_tok = 1;

	for (;pos<strlen(line); ++pos)
	{
		if (line[pos] == ' ')
		{
			num_tok += 1;
		}
	}
	return num_tok;
}

///////////////////////////////////////////////////////////////////////////////
//

char *
chop (chopme)
char	*chopme;
{
	int	x;

	x = strlen(chopme) - 1;

	if ((chopme[ x ] == '\n') || (chopme[ x ] == '\r'))
	{
		chopme[ x ] = '\0';
	}
	return chopme;
}

///////////////////////////////////////////////////////////////////////////////
//



