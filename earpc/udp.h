#ifndef UDP_H
# define UDP_H
# include <cstdint>
# include <iostream>
# include <stdio.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <stdint.h>
# include <string.h>
# include <unistd.h>
# include <net/ipv4_address.h>

namespace earpc
{
	class udp
	{
		struct sockaddr_in sock_in;
		int sock, sinlen;
		uint16_t local_port;
		uint16_t remote_port;
	public:
		udp(uint16_t lp, uint16_t rp)
			: local_port(lp)
			, remote_port(rp)
		{
			int yes = 1;
			int no = 0;

			struct timeval timeout;
			timeout.tv_sec = 0;
			timeout.tv_usec = 70000;

			sinlen = sizeof(struct sockaddr_in);
			memset(&sock_in, 0, sinlen);

			sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
			setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

			sock_in.sin_addr.s_addr = htonl(INADDR_ANY);
			sock_in.sin_port = htons(lp);
			sock_in.sin_family = PF_INET;

			bind(sock, (struct sockaddr *)&sock_in, sinlen);

			sock_in.sin_family = PF_INET;
		}

		~udp()
		{
			shutdown(sock, 2);
			close(sock);
		}

		int send(net::ipv4_address ip, uint16_t port, const void *buffer, uint16_t size)
		{
			sock_in.sin_addr.s_addr = htonl(ip);
			sock_in.sin_port = htons(port);
			return sendto(sock, buffer, size, 0, (struct sockaddr*)&sock_in, sinlen);
		}

		int recv(net::ipv4_address &ip, uint16_t &port, void *buffer,uint16_t size)
		{
			struct sockaddr_in x;

			unsigned l = sizeof(struct sockaddr_in);

			const int rv = recvfrom(sock, buffer, size, 0, (struct sockaddr*)&x, &l);

			ip = htonl(x.sin_addr.s_addr);

			port = htons(x.sin_port);
			
			return rv;

		}

	/*	int recv(void *buffer,uint16_t size, uint64_t timeout)
		{
			struct timeval timeout;
			
			return recvfrom(sock, buffer, size, 0, 0, 0);
		}
	*/
	};
}
#endif
