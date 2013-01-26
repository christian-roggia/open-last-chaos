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

#include "socket.h"

void socket_sndbuf(int fd, int optval)
{
    socklen_t optlen; // [sp+2Ch] [bp-Ch]@1

    optlen = 4;

    if(setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &optval, 4) < 0)
    {
        sys_err(__FUNCTION__, __LINE__, "setsockopt: sndbuf: %s", strerror(errno));
        return;
    }

    optval = 0;
    optlen = 4;

    if(getsockopt(fd, SOL_SOCKET, SO_SNDBUF, &optval, &optlen) < 0)
    {
        sys_err(__FUNCTION__, __LINE__, "getsockopt: sndbuf: %s", strerror(errno));
        return;
    }

    sys_log(1, "SYSTEM: %d: send buffer changed to %d", fd, optval);
}

/*const char *socket_block(int fd)
{
    int v1; // eax@1
    const char *result; // eax@1
    int *v3; // eax@2
    char *v4; // eax@2

    v1 = fcntl(fd, 3, 0);
    result = (const char *)fcntl(fd, 4, v1 & 0xFFFFFFFB);
    if((signed int)result < 0)
    {
        v3 = (int *)__error();
        v4 = strerror(*v3);
        result = sys_err((int)"socket_block", 325, "fcntl: nonblock: %s", v4);
    }
    return result;
}*/

void socket_nonblock(int fd)
{
    if(fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK) < 0)
        sys_err(__FUNCTION__, __LINE__, "fcntl: nonblock: %s", strerror(errno));
}

int socket_close(int fd)
{
    return close(fd);
}

int socket_keepalive(int fd)
{
    int result; // eax@1
    int optval; // [sp+20h] [bp-8h]@1

    optval = 1;
    result = setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &optval, 4);
    if(result < 0)
    {
        perror("setsockopt: keepalive");
        result = socket_close(fd);
    }
    return result;
}

int socket_reuse(int fd)
{
    int result; // eax@1
    int optval; // [sp+20h] [bp-8h]@1

    optval = 1;
    result = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &optval, 4);

    if(result < 0)
    {
        sys_err(__FUNCTION__, __LINE__, "setsockopt: reuse: %s", strerror(errno));
        result = socket_close(fd);
    }

    return result;
}

/*int socket_timeout(int arg, int a2, int a3)
{
    int result; // eax@5
    int *v4; // eax@6
    char *v5; // eax@6
    int *v6; // eax@7
    char *v7; // eax@7
    int *v8; // eax@8
    char *v9; // eax@8
    int *v10; // eax@9
    char *v11; // eax@9
    int v12; // [sp+28h] [bp-20h]@1
    int v13; // [sp+2Ch] [bp-1Ch]@1
    int optval; // [sp+30h] [bp-18h]@1
    int v15; // [sp+34h] [bp-14h]@1
    socklen_t optlen; // [sp+38h] [bp-10h]@1

    optlen = 8;
    v12 = a2;
    optval = a2;
    v13 = a3;
    v15 = a3;
    if(setsockopt(arg, 65535, 4102, &optval, 8u) < 0)
    {
        v4 = (int *)__error();
        v5 = strerror(*v4);
        sys_err((int)"socket_timeout", 460, "setsockopt: timeout: %s", v5);
        result = socket_close(arg);
    }
    else
    {
        if(getsockopt(arg, 65535, 4102, &optval, &optlen) < 0)
        {
            v8 = (int *)__error();
            v9 = strerror(*v8);
            sys_err((int)"socket_timeout", 467, "getsockopt: timeout: %s", v9);
            result = socket_close(arg);
        }
        else
        {
            optlen = 8;
            if(setsockopt(arg, 65535, 4101, &v12, 8u) < 0)
            {
                v6 = (int *)__error();
                v7 = strerror(*v6);
                sys_err((int)"socket_timeout", 476, "setsockopt: timeout: %s", v7);
                result = socket_close(arg);
            }
            else
            {
                if(getsockopt(arg, 65535, 4101, &v12, &optlen) < 0)
                {
                    v10 = (int *)__error();
                    v11 = strerror(*v10);
                    sys_err((int)"socket_timeout", 483, "getsockopt: timeout: %s", v11);
                    result = socket_close(arg);
                }
                else
                {
                    result = sys_log(1, "SYSTEM: %d: TIMEOUT RCV: %d.%d, SND: %d.%d", arg, optval, v15, v12, v13);
                }
            }
        }
    }
    return result;
}

int socket_rcvbuf(int arg, int optval)
{
    int result; // eax@3
    int *v3; // eax@4
    char *v4; // eax@4
    int *v5; // eax@5
    char *v6; // eax@5
    socklen_t optlen; // [sp+2Ch] [bp-Ch]@1

    optlen = 4;
    if(setsockopt(arg, 65535, 4098, &optval, 4u) < 0)
    {
        v3 = (int *)__error();
        v4 = strerror(*v3);
        sys_err((int)"socket_rcvbuf", 401, "setsockopt: rcvbuf: %s", v4);
        result = socket_close(arg);
    }
    else
    {
        optval = 0;
        optlen = 4;
        if(getsockopt(arg, 65535, 4098, &optval, &optlen) < 0)
        {
            v5 = (int *)__error();
            v6 = strerror(*v5);
            sys_err((int)"socket_rcvbuf", 411, "getsockopt: rcvbuf: %s", v6);
            result = socket_close(arg);
        }
        else
        {
            result = sys_log(1, "SYSTEM: %d: receive buffer changed to %d", arg, optval);
        }
    }
    return result;
}*/

int socket_lingeron(int fd)
{
    int result; // eax@1
    struct linger optval; // [sp+1Ch] [bp-Ch]@1

    optval.l_onoff = 1;
    optval.l_linger = 0;

    result = setsockopt(fd, SOL_SOCKET, SO_LINGER, &optval, 8u);

    if(result < 0)
    {
        sys_err(__FUNCTION__, __LINE__, "setsockopt: linger: %s", strerror(errno));
        result = socket_close(fd);
    }
    return result;
}

int socket_lingeroff(int fd)
{
    int result; // eax@1
    struct linger optval; // [sp+1Ch] [bp-Ch]@1

    optval.l_onoff = 0;
    optval.l_linger = 0;

    result = setsockopt(fd, SOL_SOCKET, SO_LINGER, &optval, 8);

    if(result < 0)
    {
        sys_err(__FUNCTION__, __LINE__, "setsockopt: linger: %s", strerror(errno));
        result = socket_close(fd);
    }

    return result;
}

/*int socket_dontroute(int fd)
{
    int result; // eax@1
    int *v2; // eax@2
    char *v3; // eax@2
    char optval; // [sp+20h] [bp-8h]@1

    result = setsockopt(fd, 65535, 16, &optval, 4u);
    if(result < 0)
    {
        v2 = (int *)__error();
        v3 = strerror(*v2);
        sys_err((int)"socket_dontroute", 349, "setsockopt: dontroute: %s", v3);
        result = socket_close(fd);
    }
    return result;
}

int socket_connect(char *arg, unsigned __int16 a2)
{
    int v2; // eax@1
    int v3; // ecx@3
    __int16 v4; // bx@5
    int v5; // eax@5
    int v6; // esi@5
    int v7; // ebx@6
    int v9; // [sp+18h] [bp-20h]@4
    struct sockaddr addr; // [sp+1Ch] [bp-1Ch]@1

    *(_DWORD *)&addr.sa_family = 0;
    *(_DWORD *)&addr.sa_data[2] = 0;
    *(_DWORD *)&addr.sa_data[6] = 0;
    *(_DWORD *)&addr.sa_data[10] = 0;
    v2 = *arg;
    if(!(v2 & 0xFFFFFF80) && DefaultRuneLocale__FBSD_1_0[4 * v2 + 53] & 4)
    {
        *(_DWORD *)&addr.sa_data[2] = __inet_addr(arg);
        v9 = a2;
    }
    else
    {
        if(!gethostbyname(arg))
        {
            v6 = -1;
            sys_err((int)"socket_connect", 229, "socket_connect(): can not connect to %s:%d", arg, a2);
            return v6;
        }
        thecore_memcpy(v3);
        v9 = a2;
    }
    LOBYTE(v4) = HIBYTE(a2);
    HIBYTE(v4) = a2;
    HIBYTE(addr.sa_family) = 2;
    *(_WORD *)&addr.sa_data[0] = v4;
    v5 = socket(2, 1, 0);
    v6 = v5;
    if(v5 < 0)
    {
        v6 = -1;
        perror("socket");
    }
    else
    {
        socket_keepalive(v5);
        socket_sndbuf(v6, 233016);
        socket_rcvbuf(v6, 233016);
        socket_timeout(v6, 10, 0);
        socket_lingeron(v6);
        v7 = connect(v6, &addr, 0x10u);
        if(v7 < 0)
        {
            socket_close(v6);
            switch(v7)
            {
                case 51:
                    sys_err((int)"socket_connect", 281, "HOST %s:%d is not reachable from this host.", arg, v9);
                    break;
                case 61:
                    sys_err((int)"socket_connect", 274, "HOST %s:%d port is not opened. connection refused.", arg, v9);
                    break;
                case 4:
                    sys_err((int)"socket_connect", 267, "HOST %s:%d connection timeout.", arg, v9);
                    break;
                default:
                    sys_err((int)"socket_connect", 285, "HOST %s:%d, could not connect.", arg, v9);
                    break;
            }
            v6 = -1;
            perror("connect");
        }
    }
    return v6;
}*/

int socket_accept(int fd, struct sockaddr *addr)
{
    int v3; // ebx@1
    socklen_t addr_len; // [sp+2Ch] [bp-Ch]@1

    addr_len = 16;
    v3 = accept(fd, addr, &addr_len);

    if(v3 == -1)
    {
        sys_err(__FUNCTION__, __LINE__, "accept: %s (fd %d)", strerror(errno), fd);
        return v3;
    }

    if(v3 > 65499)
    {
        sys_err(__FUNCTION__, __LINE__, "SOCKET FD 65500 LIMIT! %d", v3);
        socket_close(fd);

        return -1;
    }

    socket_nonblock(v3);
    socket_lingeroff(v3);

    return v3;
}

int socket_bind(char *aIP, unsigned short sPort, int iType)
{
    int v3; // eax@1
    struct sockaddr_in addr; // [sp+1Ch] [bp-1Ch]@2

    v3 = socket(AF_INET, iType, 0);

    if(v3 < 0)
    {
        sys_err(__FUNCTION__, __LINE__, "socket: %s", strerror(errno));
        return v3;
    }

    socket_reuse(v3);
    socket_lingeroff(v3);

    /*addr.sin_family = 0;
    addr.sin_port   = 0;
    addr.sin_addr   = 0;
    addr.sin_zero   = 0;*/
    memset(&addr, 0, 16);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(sPort);
    addr.sin_addr.s_addr = inet_addr(aIP);

    if(bind(v3, (struct sockaddr *)&addr, 16) < 0)
    {
        sys_err(__FUNCTION__, __LINE__, "bind: %s", strerror(errno));
        return -1;
    }

    socket_nonblock(v3);

    if(iType != 1)
    {
        sys_log(0, "SYSTEM: BINDING UDP PORT ON [%d]", sPort);
        return v3;
    }

    sys_log(0, "SYSTEM: BINDING TCP PORT ON [%d]", sPort);
    listen(v3, 128);

    return v3;
}

int socket_udp_bind(char *aIP, unsigned short sPort)
{
    return socket_bind(aIP, sPort, SOCK_DGRAM);
}

int socket_tcp_bind(char *aIP, unsigned short sPort)
{
    return socket_bind(aIP, sPort, SOCK_STREAM);
}

ssize_t socket_write_tcp(int fd, const void *buf, size_t n)
{
    ssize_t result; // eax@1

    result = send(fd, buf, n, 0);
    if(result <= 0)
    {
        if(!result)
            return -1;

        if(errno != 35 && errno != 35 && errno != 11)
            return -1;

        return 0;
    }

    return result;
}

int socket_write(int fd, const void *buf, size_t n)
{
    const void *v3; // esi@1
    size_t v4; // ebx@1
    ssize_t v5; // eax@3

    v3 = buf;
    v4 = n;

    while(1)
    {
        v5 = socket_write_tcp(fd, v3, v4);

        if(v5 < 0)
            break;

        v4 -= v5;

        if(!v4)
            return 0;

        v3 = (char *)v3 + v5;
    }

    if(errno == 35)
        errno = 35;

    if(errno == 35)
    {
        sys_err(__FUNCTION__, __LINE__, "socket write would block, about to close!");
        return -1;
    }
    else
    {
        sys_err(__FUNCTION__, __LINE__, "write to desc error");
        return -1;
    }
}

ssize_t socket_read(int fd, void *buf, size_t n)
{
    ssize_t result; // eax@1

    result = recv(fd, buf, n, 0);
    if(result <= 0)
    {
        if(!result)
            return -1;

        if(errno != 4 && errno != 35 && errno != 35 && errno != 11)
        {
            sys_err(__FUNCTION__, __LINE__, "about to lose connection");
            return -1;
        }

        return 0;
    }

    return result;
}

ssize_t socket_udp_read(int fd, void *buf, size_t n, struct sockaddr *addr, socklen_t *addr_len)
{
    return recvfrom(fd, buf, n, 0, addr, addr_len);
}
