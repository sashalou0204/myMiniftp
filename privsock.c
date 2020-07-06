#include "privsock.h"
#include "common.h"
#include "sysutil.h"
#include "session.h"

void priv_sock_init(session_t *sess)
{//init the commu-channel of inner process
	int sockfds[2];//this is exatly the commu-channel 
	if(socketpair(PF_UNIX, SOCK_STREAM, 0, sockfds) < 0)
		ERR_EXIT("socketpair error");
	
	sess->parent_fd = sockfds[0];
	sess->child_fd = sockfds[1];
}


void priv_sock_close(session_t *sess)
{//close the commu-channel , close parent sock as well as son sock
	if(sess->parent_fd != -1)
	{
		close(sess->parent_fd);
		sess->parent_fd = -1;
	}
	if(sess->child_fd != -1)
	{
		close(sess->child_fd);
		sess->child_fd = -1;
	}
	
}
void priv_sock_set_parent_context(session_t *sess)
{//set the environment of parent process
	if(sess->child_fd != -1)
	{
		close(sess->child_fd);
		sess->child_fd = -1;
	}
}
void priv_sock_set_child_context(session_t *sess)
{//set the eevironment of child process
	if(sess->parent_fd != -1)
	{
		close(sess->parent_fd);
		sess->parent_fd = -1;
	}
}

void priv_sock_send_cmd(int fd, char cmd)
{
	//ftp send command to nobody: one byte
	int ret;
	ret = writen(fd, &cmd, sizeof(cmd));//write commands
	if(ret != sizeof(cmd))
	{
		fprintf(stderr, "priv_sock_send_cmd error");
		exit(EXIT_FAILURE);
	}	

}
char priv_sock_get_cmd(int fd)
{
//nobody process receives command from ftp
	int ret;
	char res;
	ret = readn(fd,&res, sizeof(res));//read commands and give a feedback
	if(ret == 0)
	{
		printf("ftp process exit\n");
		exit(EXIT_SUCCESS);
	}
	if(ret != sizeof(res));
	{
		fprintf(stderr,"priv_sock_get_cmd error");
		exit(EXIT_FAILURE);
	}
	
	return res;	
}
void priv_sock_send_result(int fd, char res)
{//nobody send results of commands back to ftp process
	int ret;
	ret = writen(fd, &res, sizeof(res));//write answer
	if(ret != sizeof(res))
	{
		fprintf(stderr, "priv_sock_send_result error");
		exit(EXIT_FAILURE);
	}
}
char priv_sock_get_result(int fd)
{// the responds from ftp to nobody, like, ftp told nobody I got your messege
	char res;
	int ret;
	ret = readn(fd, &res, sizeof(res));//read answer and give a feedback
	if(ret != sizeof(res))
	{
		fprintf(stderr, "priv_sock_get_result error");
		exit(EXIT_FAILURE);
	}
	return res;
}



//ftp parse the command from client and send ip as well as port to nobody to connect the client

//1, port, ont byte
//send port
void priv_sock_send_int(int fd, int the_int)
{	
	int ret;
	ret = writen(fd, &the_int, sizeof(the_int));//write answer
	if(ret != sizeof(the_int))
	{
		fprintf(stderr, "priv_sock_send_the_int error");
		exit(EXIT_FAILURE);
	}
}
//receice port
int priv_sock_get_int(int fd)
{
	int the_int;
	int ret;
	ret = readn(fd, &the_int, sizeof(the_int));//read answer and give a feedback
	if(ret != sizeof(the_int))
	{
		fprintf(stderr, "priv_sock_get_int error");
		exit(EXIT_FAILURE);
	}
	return the_int;

}



//2, ip, a string with random length
//send ip : 1send the length of ip first ; 2 send the actual ip string
void priv_sock_send_buf(int fd, const char *buf, unsigned int len)
{
	priv_sock_send_int(fd, (int)len);
	int ret = writen(fd, buf, len);
	if(ret != (int)len)
	{
		fprintf(stderr, "priv_sock_send_buf error\n");
		exit(EXIT_FAILURE);
	}
}

//receive ip; RECEIVE THE LENGTH FIRST
void priv_sock_recv_buf(int fd, char *buf, unsigned int len)
{
	unsigned int recv_len = (unsigned int)priv_sock_get_int(fd);
	if(recv_len > len)
	{
		fprintf(stderr, "priv_sock_recv_buf error\n");
		exit(EXIT_FAILURE);
	}
	//read the string , the ip
	int ret = readn(fd, buf, recv_len);
	if(ret != (int)recv_len)
	{
		fprintf(stderr, "priv_sock_recv_buf error\n");
		exit(EXIT_FAILURE);
	}
	
}

void priv_sock_send_fd(int sock_fd, int fd)
{
	send_fd(sock_fd, fd);	
}

int priv_sock_recv_fd(int sock_fd)
{
	return recv_fd(sock_fd);
}
