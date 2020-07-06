#include "session.h"
#include "common.h"
#include "ftpproto.h"
#include "privparent.h"
#include "privsock.h"
#include "sysutil.h"

void begin_session(session_t *sess)
{

/*	int sockfds[2];
	if(socketpair(PF_UNIX, SOCK_STREAM, 0, sockfds))//return a pairofsockets
	{
		ERR_EXIT("socketpair");
	}

*/
	activate_oobinline(sess->ctrl_fd);	
	priv_sock_init(sess);
	pid_t pid;
	pid = fork();
	if(pid < 0)
			ERR_EXIT("fork");

	if(pid == 0)//son
	{
		//ftp server process
/*		close(sockfds[0]);
		sess->child_fd = sockfds[1];*/

		priv_sock_set_child_context(sess);
		handle_child(sess);
	}
	else//father
	{
/*		struct passwd *pw = getpwnam("nobody");
		if(pw == NULL)
		return;
		if(setegid(pw->pw_gid)<0)
		ERR_EXIT("setegid");
		if(seteuid(pw->pw_uid)<0)
		ERR_EXIT("seteuid");
*/		
//nobody process
	/*	close(sockfds[1]);
		sess->parent_fd = sockfds[0]; */
		priv_sock_set_parent_context(sess);
		handle_parent(sess);

	}
}
