/******************************************************************************************
  Copyright 2013 Christian Roggia

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
******************************************************************************************/

#ifndef SOCKET_H
#define SOCKET_H

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>

#include "log.h"

#ifdef __cplusplus
extern "C" {
#endif

void socket_sndbuf(int fd, int optval);

/*const char *socket_block(int fd);*/

void socket_nonblock(int fd);
int socket_close(int fd);
int socket_keepalive(int fd);
int socket_reuse(int fd);

/*int socket_timeout(int arg, int a2, int a3);
int socket_rcvbuf(int arg, int optval);*/

int socket_lingeron(int fd);
int socket_lingeroff(int fd);

/*int socket_dontroute(int fd);
int socket_connect(char *arg, unsigned __int16 a2);*/

int socket_accept(int fd, struct sockaddr *addr);
int socket_bind(char *aIP, unsigned short sPort, int iType);
int socket_udp_bind(char *aIP, unsigned short sPort);
int socket_tcp_bind(char *aIP, unsigned short sPort);
ssize_t socket_write_tcp(int fd, const void *buf, size_t n);
int socket_write(int fd, const void *buf, size_t n);
ssize_t socket_read(int fd, void *buf, size_t n);
ssize_t socket_udp_read(int fd, void *buf, size_t n, struct sockaddr *addr, socklen_t *addr_len);

#ifdef __cplusplus
}
#endif

#endif // SOCKET_H
