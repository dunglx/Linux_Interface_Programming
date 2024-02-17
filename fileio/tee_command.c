/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2023.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* tee

  tee command đọc nội standard input cho tới EOF, sau đó ghi 1 bản copy input tới standard output và tới file được đặt tên trong arg của command line. Mặc định tee ghi đè  bất cứ file đang tồn tại nào với tên đã cho trước.
  tee -a file sẽ append text tới EOF của 1 file nếu nó đã tồn tại trước đó

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
    int outputFd, openFlags;
    mode_t filePerms;
    char buffer[MAX_READ + 1];
    ssize_t numRead;
    
    int opt, append = 0;
    
    while ((opt = getopt(argc, argv, "-ah")) != -1)
    {
    	switch(opt)
    	{
    		case 'a':
    			printf("run with option append\n");
    			append = 1;
    			break;
    		case 'h':
    			printf("Run with help option\n");
    			break;
    	}
    }
 
    if (append == 1) openFlags = O_CREAT | O_WRONLY | O_TRUNC | O_APPEND;
   	else openFlags = O_CREAT | O_WRONLY | O_TRUNC;
   	
   	//openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH;
                
    
    if (outputFd == -1)
    	errExit("opening file %s", argv[1]);
    	
	if (append == 1) {
		printf("Ghi kieu append\n");
		outputFd = open(argv[2], openFlags, filePerms);
		lseek(outputFd, 0, SEEK_END);
 	}
 	else {
 		printf("Khong ghi kieu append\n");
 		outputFd = open(argv[1], openFlags, filePerms);
 	}
 
    while((numRead = read(STDIN_FILENO, buffer, MAX_READ))>0)
    {
    	buffer[numRead] = '\0';
    	printf("%s", buffer);
    	if (write(outputFd, buffer, numRead) != numRead)
    		fatal("write() returned error or partial write occurred");
    }
    
    if (close(outputFd) == -1)
    	errExit("close output");
}
