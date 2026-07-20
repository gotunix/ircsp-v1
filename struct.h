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
typedef struct
{
   char  *server;
   char  *password;
   char  *port;
   char  *servname;
   char  *servdesc;
   char  *unick;
   char  *udesc;
   char  *hnick;
   char  *hdesc;
   char  *nnick;
   char  *ndesc;
   char  *scnick;
   char  *scdesc;
   char  *wnick;
   char  *wdesc;
   char  *clonechan;
   char  *statchan;
   int   debug;
   int   opergreet;
   int   usergreet;
   int   savecycle;
   int   glinecycle;
   int   nickcycle;
   int   chancycle;
}
   Config;

///////////////////////////////////////////////////////////////////////////////
//

typedef struct _nicklist
{
   char	   *nickname;
   char	   *userhost;
   char	   *server;
   char	   *realname;
   char	   *mode;
   int	   flags;
   int	   invs;
   int	   wall;
   int	   glob;
   time_t  ConnTime;
   int	   numClones;
   struct _nicklist  *next;
}
   Nick;

typedef struct _hosts
{
	char	*hostname;
	int	clones;
	int	numHosts;
	struct	_hosts *next;
} Hosts;

typedef struct _clones
{
	char	*username;
	char	*hostname;
	char	*nickname;
	struct _clones *next;
} Clones;

///////////////////////////////////////////////////////////////////////////////
//

struct aGline
{
   char	  *userhost;
   char	  *reason;
   time_t when;	
   time_t expire;
   struct aGline  *next;
};

///////////////////////////////////////////////////////////////////////////////
//

typedef struct _admin
{
   char  *nickname;
   char  *hostname;
   char  *password;
   int   level;	
   int   flags;
   int   susp;
   struct  _admin  *next;
}
   Admin;

///////////////////////////////////////////////////////////////////////////////
//

typedef struct _suspchan
{
   char	   *channel;
   char	   *reason;
   struct  _suspchan  *next; 
}
   SuspChan;

///////////////////////////////////////////////////////////////////////////////
//

typedef struct _nickservDB
{
   char	  *nickname;
   char	  *password;
   int	  authed;
   int    killprot;
   struct _nickservDB  *next;
}
   nickservDB;

///////////////////////////////////////////////////////////////////////////////
//

typedef struct _bans
{
   char   *host;
   char   *chan;
   char   *setby;
   struct _bans  *next;
}
   Bans;

///////////////////////////////////////////////////////////////////////////////
//

typedef struct _cadmin
{
   char   *nickname;
   char   *password;
   char   *channel;
   int    flags;
   int    level;
   struct _cadmin  *next;
}
   Cadmin;

///////////////////////////////////////////////////////////////////////////////
//

typedef struct _chanDB
{
   char   *channel;
   char   *password;
   char   *topic;
   char   *modes;
   char   *bot;
   struct _chanDB  *next;
}
   ChanDB;

///////////////////////////////////////////////////////////////////////////////
//

typedef struct _njupe
{
	char	*nickname;
	char	*reason;

	struct _njupe *next;
}	NJupe;

///////////////////////////////////////////////////////////////////////////////
//

typedef struct _jupe
{
	char *servername;
	char *reason;

	struct _jupe *next;
}	Jupe;

///////////////////////////////////////////////////////////////////////////////
//

Config		*config;
Nick		*nick;
Hosts		*hosts;
Clones		*clone;
struct aGline	*gline;
Admin		*admin;
SuspChan	*suspchan;
nickservDB	*nickservdb;
Bans		*bans;
Cadmin		*cadmin;
ChanDB		*chandb;
NJupe		*njupe;
Jupe		*jupe;
///////////////////////////////////////////////////////////////////////////////
//


