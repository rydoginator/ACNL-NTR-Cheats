#pragma once

#include <errno.h>
#include <string.h>
#include <sys/iosupport.h>
#include "socket.h"
#include "../../types.h"
#include "../svc.h"
#include "../srv.h"
#include "../services/soc.h"

#define SYNC_ERROR ENODEV

//int __alloc_handle(size_t size);
__handle *__get_handle(int fd);
void __release_handle(int fd);

extern Handle	SOCU_handle;
extern Handle	socMemhandle;

static inline int
soc_get_fd(int fd)
{
	__handle *handle = __get_handle(fd);
	if(handle == NULL)
		return -ENODEV;
	if(strcmp(devoptab_list[handle->device]->name, "soc") != 0)
		return -ENOTSOCK;
	return *(Handle*)handle->fileStruct;
}

s32 _net_convert_error(s32 sock_retval);

ssize_t soc_recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);

ssize_t soc_sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);
