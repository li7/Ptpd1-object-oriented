/**
 * @file   net.c
 * @date   Tue Jul 20 16:17:49 2010
 * 
 * @brief  Functions to interact with the network sockets and NIC driver.
 * 
 * 
 */

#include "classes/ptpd.h"

Boolean 
lookupSubdomainAddress(Octet * subdomainName, Octet * subdomainAddress)
{
	UInteger32 h;

	/* set multicast group address based on subdomainName */
	if (!memcmp(subdomainName, DEFAULT_PTP_DOMAIN_NAME, PTP_SUBDOMAIN_NAME_LENGTH))
		memcpy(subdomainAddress, DEFAULT_PTP_DOMAIN_ADDRESS, NET_ADDRESS_LENGTH);
	else if (!memcmp(subdomainName, ALTERNATE_PTP_DOMAIN1_NAME, PTP_SUBDOMAIN_NAME_LENGTH))
		memcpy(subdomainAddress, ALTERNATE_PTP_DOMAIN1_ADDRESS, NET_ADDRESS_LENGTH);
	else if (!memcmp(subdomainName, ALTERNATE_PTP_DOMAIN2_NAME, PTP_SUBDOMAIN_NAME_LENGTH))
		memcpy(subdomainAddress, ALTERNATE_PTP_DOMAIN2_ADDRESS, NET_ADDRESS_LENGTH);
	else if (!memcmp(subdomainName, ALTERNATE_PTP_DOMAIN3_NAME, PTP_SUBDOMAIN_NAME_LENGTH))
		memcpy(subdomainAddress, ALTERNATE_PTP_DOMAIN3_ADDRESS, NET_ADDRESS_LENGTH);
	else {
		h = crc_algorithm(subdomainName, PTP_SUBDOMAIN_NAME_LENGTH) % 3;
		switch (h) {
		case 0:
			memcpy(subdomainAddress, ALTERNATE_PTP_DOMAIN1_ADDRESS, NET_ADDRESS_LENGTH);
			break;
		case 1:
			memcpy(subdomainAddress, ALTERNATE_PTP_DOMAIN2_ADDRESS, NET_ADDRESS_LENGTH);
			break;
		case 2:
			memcpy(subdomainAddress, ALTERNATE_PTP_DOMAIN3_ADDRESS, NET_ADDRESS_LENGTH);
			break;
		default:
			ERROR("handle out of range for '%s'!\n", subdomainName);
			return false;
		}
	}

	return true;
}

UInteger8 
lookupCommunicationTechnology(UInteger8 communicationTechnology)
{
#if defined(linux)

	switch (communicationTechnology) {
		case ARPHRD_ETHER:
		case ARPHRD_EETHER:
		case ARPHRD_IEEE802:
		return PTP_ETHER;

	default:
		break;
	}

#elif defined(BSD_INTERFACE_FUNCTIONS)

#endif

	return PTP_DEFAULT;
}

UInteger32 
findIface(Octet * ifaceName, UInteger8 * communicationTechnology,
    Octet * uuid, NetPath * netPath)
{
#if defined(linux)

	/* depends on linux specific ioctls (see 'netdevice' man page) */
	int i, flags;
	struct ifconf data;
	struct ifreq device[IFCONF_LENGTH];

	data.ifc_len = sizeof(device);
	data.ifc_req = device;

	memset(data.ifc_buf, 0, data.ifc_len);

	flags = IFF_UP | IFF_RUNNING | IFF_MULTICAST;

	/* look for an interface if none specified */
	if (ifaceName[0] != '\0') {
		i = 0;
		memcpy(device[i].ifr_name, ifaceName, IFACE_NAME_LENGTH);

		if (ioctl(netPath->get_eventSock(), SIOCGIFHWADDR, &device[i]) < 0)
			DBGV("failed to get hardware address\n");
		else if ((*communicationTechnology = lookupCommunicationTechnology(device[i].ifr_hwaddr.sa_family)) == PTP_DEFAULT)
			DBGV("unsupported communication technology (%d)\n", *communicationTechnology);
		else
			memcpy(uuid, device[i].ifr_hwaddr.sa_data, PTP_UUID_LENGTH);
	} else {
		/* no iface specified */
		/* get list of network interfaces */
		if (ioctl(netPath->get_eventSock(), SIOCGIFCONF, &data) < 0) {
			PERROR("failed query network interfaces");
			return 0;
		}
		if (data.ifc_len >= sizeof(device))
			DBG("device list may exceed allocated space\n");

		/* search through interfaces */
		for (i = 0; i < data.ifc_len / sizeof(device[0]); ++i) {
			DBGV("%d %s %s\n", i, device[i].ifr_name, inet_ntoa(((struct sockaddr_in *)&device[i].ifr_addr)->sin_addr));

			if (ioctl(netPath->get_eventSock(), SIOCGIFFLAGS, &device[i]) < 0)
				DBGV("failed to get device flags\n");
			else if ((device[i].ifr_flags & flags) != flags)
				DBGV("does not meet requirements (%08x, %08x)\n", device[i].ifr_flags, flags);
			else if (ioctl(netPath->get_eventSock(), SIOCGIFHWADDR, &device[i]) < 0)
				DBGV("failed to get hardware address\n");
			else if ((*communicationTechnology = lookupCommunicationTechnology(device[i].ifr_hwaddr.sa_family)) == PTP_DEFAULT)
				DBGV("unsupported communication technology (%d)\n", *communicationTechnology);
			else {
				DBGV("found interface (%s)\n", device[i].ifr_name);

				memcpy(uuid, device[i].ifr_hwaddr.sa_data, PTP_UUID_LENGTH);
	printf("-uuid (findIface) = %d\n",*uuid);
				memcpy(ifaceName, device[i].ifr_name, IFACE_NAME_LENGTH);

				break;
			}
		}
	}

	if (ifaceName[0] == '\0') {
		ERROR("failed to find a usable interface\n");
		return 0;
	}
	if (ioctl(netPath->get_eventSock(), SIOCGIFADDR, &device[i]) < 0) {
		PERROR("failed to get ip address");
		return 0;
	}
	return ((struct sockaddr_in *)&device[i].ifr_addr)->sin_addr.s_addr;

#elif defined(BSD_INTERFACE_FUNCTIONS)

	struct ifaddrs *if_list, *ifv4, *ifh;

	if (getifaddrs(&if_list) < 0) {
		PERROR("getifaddrs() failed");
		return FALSE;
	}
	/* find an IPv4, multicast, UP interface, right name(if supplied) */
	for (ifv4 = if_list; ifv4 != NULL; ifv4 = ifv4->ifa_next) {
		if ((ifv4->ifa_flags & IFF_UP) == 0)
			continue;
		if ((ifv4->ifa_flags & IFF_RUNNING) == 0)
			continue;
		if ((ifv4->ifa_flags & IFF_LOOPBACK))
			continue;
		if ((ifv4->ifa_flags & IFF_MULTICAST) == 0)
			continue;
		if (ifv4->ifa_addr->sa_family != AF_INET)	/* must have IPv4
								 * address */
			continue;

		if (ifaceName[0] && strncmp(ifv4->ifa_name, ifaceName, IF_NAMESIZE) != 0)
			continue;

		break;
	}

	if (ifv4 == NULL) {
		if (ifaceName[0]) {
			ERROR("interface \"%s\" does not exist, or is not appropriate\n", ifaceName);
			return false;
		}
		ERROR("no suitable interfaces found!");
		return false;
	}
	/* find the AF_LINK info associated with the chosen interface */
	for (ifh = if_list; ifh != NULL; ifh = ifh->ifa_next) {
		if (ifh->ifa_addr->sa_family != AF_LINK)
			continue;
		if (strncmp(ifv4->ifa_name, ifh->ifa_name, IF_NAMESIZE) == 0)
			break;
	}

	if (ifh == NULL) {
		ERROR("could not get hardware address for interface \"%s\"\n", ifv4->ifa_name);
		return false;
	}
	/* check that the interface TYPE is OK */
	if (((struct sockaddr_dl *)ifh->ifa_addr)->sdl_type != IFT_ETHER) {
		ERROR("\"%s\" is not an ethernet interface!\n", ifh->ifa_name);
		return false;
	}

	DBG("==> %s %s %s\n", ifv4->ifa_name,
	    inet_ntoa(((struct sockaddr_in *)ifv4->ifa_addr)->sin_addr),
	    ether_ntoa((struct ether_addr *)
		       LLADDR((struct sockaddr_dl *)ifh->ifa_addr)));

	*communicationTechnology = PTP_ETHER;
	memcpy(ifaceName, ifh->ifa_name, IFACE_NAME_LENGTH);
	memcpy(uuid, LLADDR((struct sockaddr_dl *)ifh->ifa_addr), PTP_UUID_LENGTH);

	return ((struct sockaddr_in *)ifv4->ifa_addr)->sin_addr.s_addr;

#endif
}

/* start all of the UDP stuff */
/* must specify 'subdomainName', optionally 'ifaceName', if not then pass ifaceName == "" */
/* returns other args */
/* on socket options, see the 'socket(7)' and 'ip' man pages */
Boolean 
netInit(NetPath * netPath, RunTimeOpts * rtOpts, PtpClock * ptpClock)
{
	int temp, i;
	struct in_addr interfaceAddr, netAddr;
	struct sockaddr_in addr;
	struct ip_mreq imr;
	char addrStr[NET_ADDRESS_LENGTH];
	char *s;

	DBG("netInit\n");

	printf("listen3\n");
	/* open sockets */
	netPath->set_eventSock(socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP));
	printf("listen3.1\n");
	netPath->set_generalSock(socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP));
	if (netPath->get_eventSock() < 0
	    || netPath->get_generalSock() < 0) {
		PERROR("failed to initalize sockets");
		return false;
	}
	printf("listen3.2\n");
	/* find a network interface */
	if (!(interfaceAddr.s_addr = findIface(rtOpts->get_ifaceName(), &ptpClock->get_port_communication_technology(),
	    ptpClock->get_port_uuid_field(), netPath)))
		return false;
	printf("-port uuid field (findIface return) = %d\n",*ptpClock->get_port_uuid_field());

	printf("listen3.3\n");
	temp = 1;			/* allow address reuse */
	if (setsockopt(netPath->get_eventSock(), SOL_SOCKET, SO_REUSEADDR, &temp, sizeof(int)) < 0
	    || setsockopt(netPath->get_generalSock(), SOL_SOCKET, SO_REUSEADDR, &temp, sizeof(int)) < 0) {
		DBG("failed to set socket reuse\n");
	}
	/* bind sockets */
	/*
	 * need INADDR_ANY to allow receipt of multi-cast and uni-cast
	 * messages
	 */
	//printf("listen3.4\n");
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(PTP_EVENT_PORT);
	printf("listen3.5\n");
	if (bind(netPath->get_eventSock(), (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) < 0) {
		PERROR("failed to bind event socket");
		return false;
	}
	addr.sin_port = htons(PTP_GENERAL_PORT);
	printf("listen3.6\n");
	if (bind(netPath->get_generalSock(), (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) < 0) {
		PERROR("failed to bind general socket");
		return false;
	}
	printf("listen3.7\n");
	/* set general and port address */
	ptpClock->set_eventPortAddress(PTP_EVENT_PORT);
	ptpClock->set_generalPortAddress(PTP_GENERAL_PORT);
	//ptpClock->set_eventPortAddress(*(Integer16 *) PTP_EVENT_PORT);
	//ptpClock->set_generalPortAddress(*(Integer16 *) PTP_GENERAL_PORT);
	printf("%d\n",ptpClock->get_event_port_address());
	printf("%d\n",ptpClock->get_general_port_address());
printf("listen3.8\n");
	
	/* send a uni-cast address if specified (useful for testing) */
	if (rtOpts->get_unicastAddress(0)) {
		if (!inet_aton(rtOpts->get_unicastAddress(), &netAddr)) {
			ERROR("failed to encode uni-cast address: %s\n", rtOpts->get_unicastAddress());
			return false;
		}
		netPath->set_unicastAddr(netAddr.s_addr);
	} else
		netPath->set_unicastAddr(0);

	printf("listen3.9\n");
	/* resolve PTP subdomain */
	if (!lookupSubdomainAddress(rtOpts->get_subdomainName(), addrStr))
		return false;

	printf("listen3.10\n");
	if (!inet_aton(addrStr, &netAddr)) {
		ERROR("failed to encode multi-cast address: %s\n", addrStr);
		return false;
	}
	netPath->set_multicastAddr(netAddr.s_addr);

	printf("listen4\n");
	s = addrStr;
	for (i = 0; i < SUBDOMAIN_ADDRESS_LENGTH; ++i) {
		ptpClock->set_subdomainAddress(i,strtol(s, &s, 0));

		if (!s)
			break;

		++s;
	}

	/* multicast send only on specified interface */
	imr.imr_multiaddr.s_addr = netAddr.s_addr;
	imr.imr_interface.s_addr = interfaceAddr.s_addr;
	if (setsockopt(netPath->get_eventSock(), IPPROTO_IP, IP_MULTICAST_IF, &imr.imr_interface.s_addr, sizeof(struct in_addr)) < 0
	    || setsockopt(netPath->get_generalSock(), IPPROTO_IP, IP_MULTICAST_IF, &imr.imr_interface.s_addr, sizeof(struct in_addr)) < 0) {
		PERROR("failed to enable multi-cast on the interface");
		return false;
	}
	/* join multicast group (for receiving) on specified interface */
	if (setsockopt(netPath->get_eventSock(), IPPROTO_IP, IP_ADD_MEMBERSHIP, &imr, sizeof(struct ip_mreq)) < 0
	    || setsockopt(netPath->get_generalSock(), IPPROTO_IP, IP_ADD_MEMBERSHIP, &imr, sizeof(struct ip_mreq)) < 0) {
		PERROR("failed to join the multi-cast group");
		return false;
	}
	/* set socket time-to-live */
	if (setsockopt(netPath->get_eventSock(), IPPROTO_IP, IP_MULTICAST_TTL, &rtOpts->get_ttl(), sizeof(int)) < 0
	    || setsockopt(netPath->get_generalSock(), IPPROTO_IP, IP_MULTICAST_TTL, &rtOpts->get_ttl(), sizeof(int)) < 0) {
		PERROR("failed to set the multi-cast time-to-live");
		return false;
	}
	/* enable loopback */
	temp = 1;
	if (setsockopt(netPath->get_eventSock(), IPPROTO_IP, IP_MULTICAST_LOOP, &temp, sizeof(int)) < 0
	    || setsockopt(netPath->get_generalSock(), IPPROTO_IP, IP_MULTICAST_LOOP, &temp, sizeof(int)) < 0) {
		PERROR("failed to enable multi-cast loopback");
		return false;
	}
	/* make timestamps available through recvmsg() */

	temp = 1;
#if defined(linux)
	if (setsockopt(netPath->get_eventSock(), SOL_SOCKET, SO_TIMESTAMP, &temp, sizeof(int)) < 0
	    || setsockopt(netPath->get_generalSock(), SOL_SOCKET, SO_TIMESTAMP, &temp, sizeof(int)) < 0) {
#else /* BSD */
	if (setsockopt(netPath->get_eventSock(), SOL_SOCKET, SO_BINTIME, &temp, sizeof(int)) < 0
	    || setsockopt(netPath->get_generalSock(), SOL_SOCKET, SO_BINTIME, &temp, sizeof(int)) < 0) {
#endif /* linux or BSD */
		PERROR("failed to enable receive time stamps");
		return false;
	}

	printf("listen5, netInit done\n");
	return true;
}

/* shut down the UDP stuff */
Boolean 
netShutdown(NetPath * netPath)
{
	struct ip_mreq imr;

	imr.imr_multiaddr.s_addr = netPath->get_multicastAddr();
	imr.imr_interface.s_addr = htonl(INADDR_ANY);

	setsockopt(netPath->get_eventSock(), IPPROTO_IP, IP_DROP_MEMBERSHIP, &imr, sizeof(struct ip_mreq));
	setsockopt(netPath->get_generalSock(), IPPROTO_IP, IP_DROP_MEMBERSHIP, &imr, sizeof(struct ip_mreq));

	netPath->set_multicastAddr(0);
	netPath->set_unicastAddr(0);

	if (netPath->get_eventSock() > 0)
		close(netPath->get_eventSock());
	netPath->set_eventSock(-1);

	if (netPath->get_generalSock() > 0)
		close(netPath->get_generalSock());
	netPath->set_generalSock(-1);

	return true;
}

int 
netSelect(TimeInternal * timeout, NetPath * netPath)
{
	int ret, nfds;
	fd_set readfds;
	struct timeval tv, *tv_ptr;

	if (timeout < 0)//WHAT?
		return false;

	FD_ZERO(&readfds);
	FD_SET(netPath->get_eventSock(), &readfds);
	FD_SET(netPath->get_generalSock(), &readfds);

	if (timeout) {
		tv.tv_sec = timeout->get_seconds();
		tv.tv_usec = timeout->get_nanoseconds() / 1000;
		tv_ptr = &tv;
	} else
		tv_ptr = 0;

	if (netPath->get_eventSock() > netPath->get_generalSock())
		nfds = netPath->get_eventSock();
	else
		nfds = netPath->get_generalSock();

	ret = select(nfds + 1, &readfds, 0, 0, tv_ptr) > 0;
	if (ret < 0) {
		if (errno == EAGAIN || errno == EINTR)
			return 0;
	}
	return ret;
}

ssize_t 
netRecvEvent(Octet * buf, TimeInternal * time, NetPath * netPath)
{
	ssize_t ret;
	struct msghdr msg;
	struct iovec vec[1];
	struct sockaddr_in from_addr;
	union {
		struct cmsghdr cm;
		char	control[CMSG_SPACE(sizeof(struct timeval))];
	}     cmsg_un;
	struct cmsghdr *cmsg;
#if defined(linux)
	struct timeval *tv;
#else /* FreeBSD */
	struct timespec ts;
#endif /* FreeBSD or Linux */

	vec[0].iov_base = buf;
	vec[0].iov_len = PACKET_SIZE;

	memset(&msg, 0, sizeof(msg));
	memset(&from_addr, 0, sizeof(from_addr));
	memset(buf, 0, PACKET_SIZE);
	memset(&cmsg_un, 0, sizeof(cmsg_un));

	msg.msg_name = (caddr_t)&from_addr;
	msg.msg_namelen = sizeof(from_addr);
	msg.msg_iov = vec;
	msg.msg_iovlen = 1;
	msg.msg_control = cmsg_un.control;
	msg.msg_controllen = sizeof(cmsg_un.control);
	msg.msg_flags = 0;

	ret = recvmsg(netPath->get_eventSock(), &msg, MSG_DONTWAIT);
	if (ret <= 0) {
		if (errno == EAGAIN || errno == EINTR)
			return 0;

		return ret;
	}
	if (msg.msg_flags & MSG_TRUNC) {
		ERROR("received truncated message\n");
		return 0;
	}
	/* get time stamp of packet */
	if (!time) {
		ERROR("null receive time stamp argument\n");
		return 0;
	}
	if (msg.msg_flags & MSG_CTRUNC) {
		ERROR("received truncated ancillary data\n");
		return 0;
	}
	if (msg.msg_controllen < sizeof(cmsg_un.control)) {
		ERROR("received short ancillary data (%d/%d)\n",
		    msg.msg_controllen, (int)sizeof(cmsg_un.control));

		return 0;
	}

#if defined(linux)
	tv = 0;
	for (cmsg = CMSG_FIRSTHDR(&msg); cmsg != NULL; 
	     cmsg = CMSG_NXTHDR(&msg, cmsg)) 
		if (cmsg->cmsg_level == SOL_SOCKET && 
		    cmsg->cmsg_type == SCM_TIMESTAMP)
			tv = (struct timeval *)CMSG_DATA(cmsg);

	if (tv) {
		time->set_seconds(tv->tv_sec);
		time->set_nanoseconds(tv->tv_usec * 1000);
		DBGV("kernel recv time stamp %us %dns\n", time->get_seconds(), time->get_nanoseconds());
	} else {
		/*
		 * do not try to get by with recording the time here, better
		 * to fail because the time recorded could be well after the
		 * message receive, which would put a big spike in the
		 * offset signal sent to the clock servo
		 */
		DBG("no recieve time stamp\n");
		return 0;
	}
#else /* FreeBSD */
	bzero(&ts, sizeof(ts));
	for (cmsg = CMSG_FIRSTHDR(&msg); cmsg != NULL; 
	     cmsg = CMSG_NXTHDR(&msg, cmsg))
		if (cmsg->cmsg_level == SOL_SOCKET && 
		    cmsg->cmsg_type == SCM_BINTIME)
			bintime2timespec((struct bintime *)CMSG_DATA(cmsg),
					 &ts);

	if (ts.tv_sec != 0) {
		time->set_seconds(ts.tv_sec);
		time->set_nanoseconds(ts.tv_nsec);
		DBGV("kernel recv time stamp %us %dns\n", time->get_seconds(), time->get_nanoseconds());
	} else {
		/*
		 * do not try to get by with recording the time here, better
		 * to fail because the time recorded could be well after the
		 * message receive, which would put a big spike in the
		 * offset signal sent to the clock servo
		 */
		DBG("no recieve time stamp\n");
		return 0;
	}
#endif /* FreeBSD or Linux */

	return ret;
}

ssize_t 
netRecvGeneral(Octet * buf, NetPath * netPath)
{
	ssize_t ret;
	struct sockaddr_in addr;
	socklen_t addr_len = sizeof(struct sockaddr_in);

	ret = recvfrom(netPath->get_generalSock(), buf, PACKET_SIZE, MSG_DONTWAIT, (struct sockaddr *)&addr, &addr_len);
	if (ret <= 0) {
		if (errno == EAGAIN || errno == EINTR)
			return 0;

		return ret;
	}
	return ret;
}

ssize_t 
netSendEvent(Octet * buf, UInteger16 length, NetPath * netPath)
{
	ssize_t ret;
	struct sockaddr_in addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(PTP_EVENT_PORT);
	addr.sin_addr.s_addr = netPath->get_multicastAddr();

	ret = sendto(netPath->get_eventSock(), buf, length, 0, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
	if (ret <= 0)
		DBG("error sending multi-cast event message\n");

	if (netPath->get_unicastAddr()) {
		addr.sin_addr.s_addr = netPath->get_unicastAddr();

		ret = sendto(netPath->get_eventSock(), buf, length, 0, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
		if (ret <= 0)
			DBG("error sending uni-cast event message\n");
	}
	return ret;
}

ssize_t 
netSendGeneral(Octet * buf, UInteger16 length, NetPath * netPath)
{
	ssize_t ret;
	struct sockaddr_in addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(PTP_GENERAL_PORT);
	addr.sin_addr.s_addr = netPath->get_multicastAddr();

	ret = sendto(netPath->get_generalSock(), buf, length, 0, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
	if (ret <= 0)
		DBG("error sending multi-cast general message\n");

	if (netPath->get_unicastAddr()) {
		addr.sin_addr.s_addr = netPath->get_unicastAddr();

		ret = sendto(netPath->get_eventSock(), buf, length, 0, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
		if (ret <= 0)
			DBG("error sending uni-cast general message\n");
	}
	return ret;
}
