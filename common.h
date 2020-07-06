#ifndef _COMMON_H_
#define _COMMON_H_
#include<unistd.h>
#include<sys/wait.h>
#include<errno.h>
#include<shadow.h>
#include<linux/capability.h>
#include<crypt.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>//gethostbyname
#include<fcntl.h>//F_GETFL
#include<arpa/inet.h>//inet_ntoa
#include<sys/time.h>
#include<pwd.h>
#include<signal.h>
#include<sys/syscall.h>
#include<sys/sendfile.h>



#include<time.h>
#include<sys/stat.h>
#include<dirent.h>
#include<sys/time.h>

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


#define ERR_EXIT(m) \
	do \
	{ \
		perror(m); \
		exit(EXIT_FAILURE); \
	} \
	while(0)

#define MAX_COMMAND_LINE 1024
#define MAX_COMMAND 32
#define MAX_ARG 1024
#define MINIFTP_CONF "miniftpd.conf"


#endif /*_COMMON_H_*/
