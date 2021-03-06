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

#include "lwipopts.h"
#include "xlwipconfig.h"

#if !NO_SYS
#include "xmk.h"
#include "sys/process.h"
#endif

#include "lwip/mem.h"
#include "lwip/stats.h"
#include "lwip/sys.h"
#include "lwip/ip.h"
#include "lwip/tcp.h"
#include "lwip/udp.h"

#include "netif/etharp.h"
#include "netif/xadapter.h"

#ifdef XLWIP_CONFIG_INCLUDE_EMACLITE
#include "netif/xemacliteif.h"
#endif

#ifdef XLWIP_CONFIG_INCLUDE_TEMAC
#include "netif/xlltemacif.h"
#endif

#if !NO_SYS
#include "lwip/tcpip.h"
#endif

/* global lwip debug variable used for debugging */
int lwip_runtime_debug = 0;

void
lwip_raw_init()
{
	ip_init();	/* Doesn't do much, it should be called to handle future changes. */
#if LWIP_UDP
	udp_init();	/* Clears the UDP PCB list. */
#endif
#if LWIP_TCP
	tcp_init();	/* Clears the TCP PCB list and clears some internal TCP timers. */
			/* Note: you must call tcp_fasttmr() and tcp_slowtmr() at the */
			/* predefined regular intervals after this initialization. */
#endif
}

static enum xemac_types 
find_mac_type(unsigned base)
{
	int i;

	for (i = 0; i < xtopology_n_emacs; i++) {
		if (xtopology[i].emac_baseaddr == base)
			return xtopology[i].emac_type;
	}

	return xemac_type_unknown;
}

int 
xtopology_find_index(unsigned base)
{
	int i;

	for (i = 0; i < xtopology_n_emacs; i++) {
		if (xtopology[i].emac_baseaddr == base)
			return i;
	}

	return -1;
}

/* 
 * xemac_add: this is a wrapper around lwIP's netif_add function.
 * The objective is to provide portability between the different Xilinx MAC's
 * This function can be used to add both xps_ethernetlite and xps_ll_temac 
 * based interfaces
 */
struct netif *
xemac_add(struct netif *netif, 
	struct ip_addr *ipaddr, struct ip_addr *netmask, struct ip_addr *gw, 
	unsigned char *mac_ethernet_address,
  	unsigned mac_baseaddr)
{
	int i;

	/* set mac address */
	netif->hwaddr_len = 6;
	for (i = 0; i < 6; i++)
		netif->hwaddr[i] = mac_ethernet_address[i];

	/* initialize based on MAC type */
	switch (find_mac_type(mac_baseaddr)) {
		case xemac_type_xps_emaclite:
#ifdef XLWIP_CONFIG_INCLUDE_EMACLITE
			return netif_add(netif, ipaddr, netmask, gw,
				(void*)mac_baseaddr,
				xemacliteif_init, 
#if NO_SYS
				ethernet_input
#else
				tcpip_input
#endif
				);
#else
			return NULL;
#endif
		case xemac_type_xps_ll_temac:
#ifdef XLWIP_CONFIG_INCLUDE_TEMAC
			return netif_add(netif, ipaddr, netmask, gw,
				(void*)mac_baseaddr,
				xlltemacif_init, 
#if NO_SYS
				ethernet_input
#else
				tcpip_input
#endif
				);
#else
			return NULL;
#endif
		default:
			printf("unable to determine type of EMAC with baseaddress 0x%08x\n\r",
					mac_baseaddr);
			return NULL;
	}
}

#if !NO_SYS
void
xemacif_input_thread(struct netif *netif)
{
	while (1) {
		xemacif_input(netif);
		yield();
	}
}
#endif

void
xemacif_input(struct netif *netif)
{
	struct xemac_s *emac = (struct xemac_s *)netif->state;
	SYS_ARCH_DECL_PROTECT(lev);

	switch (emac->type) {
		case xemac_type_xps_emaclite:
#ifdef XLWIP_CONFIG_INCLUDE_EMACLITE
			SYS_ARCH_PROTECT(lev);
			xemacliteif_input(netif);
			SYS_ARCH_UNPROTECT(lev);
			break;
#else
			print("incorrect configuration: xps_ethernetlite drivers not present?");
			while(1);
			return;
#endif
		case xemac_type_xps_ll_temac:
#ifdef XLWIP_CONFIG_INCLUDE_TEMAC
			SYS_ARCH_PROTECT(lev);
			xlltemacif_input(netif);
			SYS_ARCH_UNPROTECT(lev);
			break;
#else
			print("incorrect configuration: xps_ll_temac drivers not present?");
			while(1);
			return;
#endif
		default:
			print("incorrect configuration: unknown temac type");
			while(1);
			return;
	}
}
