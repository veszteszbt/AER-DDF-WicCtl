#ifndef UDP_H
# define UDP_H

# include <cstdint>
# include <iostream>
# include <stdio.h>
# include <net/ipv4_address.h>
# include <string.h>

#ifdef __linux__

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <unistd.h>

#endif


#ifdef __MINGW32__

#include <winsock2.h>
#include <stdlib.h>
#include <Ws2tcpip.h>
#include <Wspiapi.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
#pragma comment (lib, "IPHLPAPI.lib")
#pragma comment (lib, "Psapi.lib")

#define PF_INET     AF_INET

#endif

namespace earpc
{
	class udp
	{
		struct sockaddr_in sock_in;
		int sock, sinlen;
		uint16_t local_port;
		uint16_t remote_port;
		WSADATA wsaData;
	public:
		udp(uint16_t lp, uint16_t rp)
			: local_port(lp)
			, remote_port(rp)
		{
			// udp server socket
			// localport = ezen a porton figyel a server socket
			// remote portarra a portra küldunk // destination ip
			// küldés, fogadás
			
			int yes = 1;
			int no = 0;

			struct timeval timeout;
			timeout.tv_sec = 0;
			timeout.tv_usec = 70000;

			sinlen = sizeof(struct sockaddr_in);
			memset(&sock_in, 0, sinlen);

			sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
			#ifdef __linux__
				
				setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

			#elif defined __MINGW32__
				// Initialize Winsock
				int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
				if (iResult != 0) {
					printf("WSAStartup failed: %d\n", iResult);
					return;
				}
				setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&timeout), sizeof(timeout));

			#endif

			sock_in.sin_addr.s_addr = htonl(INADDR_ANY);
			sock_in.sin_port = htons(lp);
			sock_in.sin_family = PF_INET;

			bind(sock, (struct sockaddr *)&sock_in, sinlen);

			sock_in.sin_family = PF_INET;
		}

		~udp()
		{
			#ifdef __linux__
				shutdown(sock, 2);
				close(sock);
			#elif defined __MINGW32__
				shutdown(sock, 2);
				closesocket(sock);
			#endif
		}

		int send(net::ipv4_address ip, uint16_t port, const void *buffer, uint16_t size)
		{
			
			sock_in.sin_addr.s_addr = htonl(ip);
			sock_in.sin_port = htons(port);
			#ifdef __linux__
				return sendto(sock, buffer, size, 0, (struct sockaddr*)&sock_in, sinlen);
			#elif defined __MINGW32__
				return sendto(sock, reinterpret_cast<const char*>(buffer), size, 0, (struct sockaddr*)&sock_in, sinlen);
			#endif

		}

		int recv(net::ipv4_address &ip, uint16_t &port, void *buffer,uint16_t size)
		{
			
			struct sockaddr_in x;

			unsigned l = sizeof(struct sockaddr_in);

			#ifdef __linux__
				const int rv = recvfrom(sock, buffer, size, 0, (struct sockaddr*)&x, &l);
			#elif defined __MINGW32__
				const int rv = recvfrom(sock, reinterpret_cast<char*>(buffer), size, 0, (struct sockaddr*)&x, reinterpret_cast<signed int*>(&l));
			#endif

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
