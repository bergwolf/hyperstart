#ifndef _NET_H_
#define _NET_H_

#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/if.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>

#include "list.h"

struct rtnl_handle {
	int fd;
	struct sockaddr_nl local;
	struct sockaddr_nl peer;
	__u32 seq;
	__u32 dump;
};

struct hyper_ipaddress {
	struct list_head list;
	char *addr;
	char *mask;
};

struct hyper_interface {
	char		 *device;
	struct list_head  ipaddresses;
	char             *new_device_name;
	unsigned int      mtu;
};

struct hyper_route {
	char		*dst;
	char		*gw;
	char		*device;
};

struct hyper_pod;
int hyper_rescan(void);
void hyper_set_be32(uint8_t *buf, uint32_t val);
uint32_t hyper_get_be32(uint8_t *buf);
void hyper_set_be64(uint8_t *buf, uint64_t val);
uint64_t hyper_get_be64(uint8_t *buf);
int hyper_setup_network(struct hyper_pod *pod);
int hyper_cmd_setup_interface(char *json, int length, struct hyper_pod *pod);
int hyper_cmd_setup_route(char *json, int length, struct hyper_pod *pod);
int hyper_setup_dns(struct hyper_pod *pod);
int hyper_setup_hostname(struct hyper_pod *pod);
int hyper_send_data_block(int fd, uint8_t *data, uint32_t len);
int hyper_send_data(int fd, uint8_t *data, uint32_t len);
#endif
