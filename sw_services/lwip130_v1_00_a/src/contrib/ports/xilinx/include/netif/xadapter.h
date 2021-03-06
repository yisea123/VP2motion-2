/*
 * Copyright (c) 2007 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef __XADAPTER_H_
#define __XADAPTER_H_

#ifdef __cplusplus
extern "C" { 
#endif

#include "lwip/netif.h"
#include "lwip/ip.h"

#include "netif/xtopology.h"

struct xemac_s {
	enum xemac_types type;
	int  topology_index;
	void *state;
};

void 		lwip_raw_init();
void 		xemacif_input(struct netif *netif);
void 		xemacif_input_thread(struct netif *netif);
struct netif *	xemac_add(struct netif *netif, 
	struct ip_addr *ipaddr, struct ip_addr *netmask, struct ip_addr *gw,
	unsigned char *mac_ethernet_address,
  	unsigned mac_baseaddr);

/* global lwip debug variable used for debugging */
extern int lwip_runtime_debug;

#ifdef __cplusplus
}
#endif

#endif
