#ifndef _FTP_PROTO_H
#define _FTP_PROTO_H
#include "session.h"


void handle_child(session_t *sess);

void ftp_reply(session_t *sess, int status, const char *text);

#endif/*_FTP_PROTO_H_*/
