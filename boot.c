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

int	boot_copyright		();
int	boot_help		();


//////////////////////////////////////////////////////////////////////////////
// 

int
boot_copyright ()
{
	FILE		*fp;
	char		read[512];

	fp = fopen("COPYRIGHT", "r");
	if (!fp)
	{
		printf("COPYRIGHT file missing. contact the author.\n");
		exit(1);
	}
	else
	{
		while (fgets(read, 256, fp) != NULL)
		{
			printf("%s", read); 
		}
		exit(1);
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//

int
boot_help ()
{
	printf("IRCSP Version %s\n", VERSION);
	printf("Copyright (C) 2000 Lostworld Development\n");
	printf("Written By: Justin Ovens (evilicey)\n");

	printf("\n\n");

	printf("----------------------------------------\n");
	printf("   -h  Displays this\n");
	printf("   -C  Displays Copyright file\n");
	printf("----------------------------------------\n");

	printf("End of help\n");
	printf("\n\nMore to come.\n\n");

	exit(1);
}

///////////////////////////////////////////////////////////////////////////////
//

