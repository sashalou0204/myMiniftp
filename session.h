#ifndef _SESSION_H_
#define _SESSION_H_

#include "common.h"
//#include "privsock.h"
typedef struct session
{
		//about connection control
	uid_t uid;
	int ctrl_fd;
	char cmdline[MAX_COMMAND_LINE];
	char cmd[MAX_COMMAND];
	char arg[MAX_ARG];
		
//data connection
	struct sockaddr_in *port_addr;
	int pasv_listen_fd;//inited as -1
	int data_fd;
	int data_process;

//limiting rating
	unsigned int bw_upload_rate_max;
	unsigned int bw_download_rate_max;
	long bw_transfer_start_sec;
	long bw_transfer_start_usec;

// parent-child process channel
	int parent_fd;
	int child_fd;
//the state of FTP proto
	int is_ascii;
	long long restart_pos;//the position to restart
	char *rnfr_name;//rename
	int abor_received;//abortion

//limiting connection numbers
	unsigned int num_clients;
	unsigned int num_this_ip;
}session_t;

void begin_session(session_t *sess);

#endif/*_SESSION_H_*/
