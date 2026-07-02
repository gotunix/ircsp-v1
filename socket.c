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
#include "socket.h"

int	conn			();
int	sockread		(int, char *);

//////////////////////////////////////////////////////////////////////////////
//

int
conn ()
{
	struct	hostent		*hp;
	struct	sockaddr_in	sin;
	int			port;

	if ((hp = gethostbyname (config->server) ) == NULL) 
	{
		printf(
			"conn()  --  ERROR: Unknown hostname (%s)\n",
			config->server);

		exit(1);
	}
	if (( s = socket (AF_INET, SOCK_STREAM, 0) ) < 0) 
	{
		printf(
			"conn()  --  ERROR: Client: Socket\n");

		exit (1);
	}

	sin.sin_family = AF_INET;
	port = atoi (config->port);
	sin.sin_port = htons(port);
	bcopy (hp->h_addr, &sin.sin_addr, hp->h_length);

	if (connect(s, (struct sockaddr *)&sin, sizeof (sin) ) < 0) 
	{
		printf(
			"conn()  --  ERROR: Client: Connect\n");

		exit(1);
	}

	serv = fdopen(s, "a+");

	send_to_sock(s, 
		"PASS :%s\n", 
		config->password);

	send_to_sock(s, 
		"SERVER %s 1 %lu %lu P09 :%s\n",
		config->servname, time(NULL), time(NULL),
		config->servdesc);

	send_to_sock(s, 
		"NICK %s 1 0 %s %s %s :%s\n",
		config->unick, config->unick, 
		config->servname, config->servname, 
		config->udesc);

	send_to_sock(s, 
		"NICK %s 1 0 %s %s %s :%s\n",
		config->nnick, config->nnick, 
		config->servname, config->servname,
		config->ndesc);

	send_to_sock(s, 
		"NICK %s 1 0 %s %s %s :%s\n",
		config->scnick, config->scnick, 
		config->servname, config->servname, 
		config->scdesc);

	send_to_sock(s, 
		"NICK %s 1 0 %s %s %s :%s\n",
		config->hnick, config->hnick, 
		config->servname, config->servname, 
		config->hdesc);

	send_to_sock(s, 
		"NICK %s 1 0 %s %s %s :%s\n",
		config->wnick, config->wnick, 
		config->servname, config->servname, 
		config->wdesc);

	send_to_sock(s, 
		":%s MODE %s +o\n",
		config->unick, config->unick);

	send_to_sock(s, 
		":%s MODE %s +o\n",
		config->nnick, config->nnick);

	send_to_sock(s, 
		":%s JOIN %s\n",
		config->unick, config->clonechan);

	send_to_sock(s, 
		":%s JOIN %s\n",
		config->unick, config->statchan);

	send_to_sock(s, 
		"MODE %s +oiws %s\n",
		config->statchan, config->unick);

	send_to_sock(s, 
		"MODE %s +oiws %s\n",
		config->clonechan, config->unick);

	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//

int 
send_to_sock (int socket, const char *fmt, ...) 
{
	char	*string;
	va_list	args;

	string = malloc(MAXBUFLENGTH);

	va_start(args, fmt);
	vsnprintf(string, MAXBUFLENGTH, fmt, args);
	va_end(args);

	send(socket, string, strlen(string), 0);
	return(strlen(string));
}

//////////////////////////////////////////////////////////////////////////////
//

int
sockread(s,buf)
int	s;
char	*buf;
{
	char	inc;
	int	bufnum, n;
	fd_set	fds;
	struct	timeval	wait;

	bufnum = 0;

	if (s == -1)
	{
		return (-1);
	}

	wait.tv_sec  = 0L;
	wait.tv_usec = 2500L;
	FD_ZERO(&fds);
	FD_SET(s, &fds);

	if (select(s+1, &fds, NULL, 0, &wait) > 0)
	{
		do
		{
			n = read(s, &inc, 1);
			if (n == 0)
			{
				return -1;
			}
			if (bufnum < BUFFER_SIZE - 1 )
			{
				buf[bufnum++] = inc;
			}
		}
		while (inc != '\n');
		{
			buf[bufnum] = '\0';
		}
		brx += bufnum;
		return bufnum;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//


