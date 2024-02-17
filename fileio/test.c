/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2023.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Listing 4-1 */

/* copy.c

   Copy the file named argv[1] to a new file named in argv[2].
*/
#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

#ifndef BUF_SIZE        /* Allow "cc -D" to override definition */
#define BUF_SIZE 1024
#endif

#ifndef MAX_READ 20
#define MAX_READ 20
#endif

int
main(int argc, char *argv[])
{
    char buffer[MAX_READ + 1];
    ssize_t numRead;
    
    while((numRead = read(STDIN_FILENO, buffer, MAX_READ))>0)
    {
    	buffer[numRead] = '\0';
    	printf("The input data was: %s\n", buffer);
    }
    printf("read");
}
