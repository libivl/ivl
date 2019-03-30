/* This file is part of the ivl C++ library <http://image.ntua.gr/ivl>.
   A C++ template library extending syntax towards mathematical notation.

   Copyright (C) 2012 Yannis Avrithis <iavr@image.ntua.gr>
   Copyright (C) 2012 Kimon Kontosis <kimonas@image.ntua.gr>

   ivl is free software; you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License
   version 3 as published by the Free Software Foundation.

   Alternatively, you can redistribute it and/or modify it under the terms
   of the GNU General Public License version 2 as published by the Free
   Software Foundation.

   ivl is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
   See the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   and a copy of the GNU Lesser General Public License along
   with ivl. If not, see <http://www.gnu.org/licenses/>. */

//-----------------------------------------------------------------------------

/** Sockets implementation in ivl **/
/* Note: This is not a complete socket API implementation. */
/* It only gives an interface to the basic operations */
/* of sending and receiving data of given sizes */
/* through socket connection. */

/* Note#2: KLUDGE: This file is temporary and not official.
 * It should be in an ivl module not in the main library,
 * plus it has implementation which needs separate compilation
 * plus it has no include guards.
 * */

//-----------------------------------------------------------------------------

#ifndef IVL_SYSTEM_SOCKET_HPP
#define IVL_SYSTEM_SOCKET_HPP

// standard C headers
#include <string.h>
#include <stdio.h>

// include headers based on OS
#if defined WIN32
#include <winsock.h>  // WinSock subsystem
#elif defined __linux__
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#endif

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace net {

//-----------------------------------------------------------------------------

// redefine some types and constants based on OS
#if defined WIN32
typedef int socklen_t;  // Unix socket length
#elif defined __linux__
typedef int SOCKET;
enum { INVALID_SOCKET = -1 }; // WinSock invalid socket
enum { SOCKET_ERROR = -1 };   // basic WinSock error
// Unix uses file descriptors, WinSock doesn't...
template <class S> inline void closesocket(S& s) { close(s); }
#endif

struct socklib
{
	static void initialize(bool no_auto_destroy = false);
	static void no_initialize(bool no_auto_destroy = false);
	static void destroy();
	static bool status;
	static inline void ensure() { if(!status) initialize(); }
};

class sock
{
private:
    struct sockaddr_in addr;  // local address variable
    SOCKET   s;               // local socket
    int      r;               // will hold return values
    hostent* h;               // server host entry (holds IPs, etc)
    bool status;
    bool tcpcon_status;
	sockaddr_in client_addr;
	SOCKET   connected;

public:

	// TCP connection to host using port
	sock(const std::string& host, int port, bool listen = false, bool udp = false, int rcvbuf = 0, int sndbuf = 0);

	// send the data that is in the array and return true for success
	bool send(const array<char>& data);

	// receive data that fits the array and return true for success
	bool receive(array<char>& data);

	// receive data once into the array and return the size, else zero
	ptrdiff_t receive_once(array<char>& data);

	// receive data once into the array & resize the array downwards if necessary.
	void receive_resize(array<char>& data);

	~sock();

	sock& operator <<(const array<char>& data)
		{ if(!send(data)) throw ecomp(); return *this; }

	sock& operator >>(array<char>& data)
		{ if(!receive(data)) throw ecomp(); return *this; }

};

// ----------------------------------------------------
// implementations

void socklib::initialize(bool no_auto_destroy)
{
	if(status) return;
	status = true;
	#if defined WIN32
		WSADATA wsa_data;
		WSAStartup(MAKEWORD(1,1), &wsa_data);
		// networking on zombie threads is not automatically supported.
		// unless no_auto_destroy is specified, in which case
		// destruction is manual
		if(!no_auto_destroy)
			atexit(socklib::destroy);
	#endif
}

void socklib::no_initialize(bool no_auto_destroy)
{
	if(status) return;
	status = true;
	#if defined WIN32
		if(!no_auto_destroy)
		// networking on zombie threads is not automatically supported.
		// unless no_auto_destroy is specified, in which case
		// destruction is manual
			atexit(socklib::destroy);
	#endif
}

void socklib::destroy()
{
	if(!status) return;
	status = false;
    // cleanup WinSock in Windows
	#if defined WIN32
		WSACleanup();
	#endif
}

bool socklib::status = false;


// ----------------------------------------------------

sock::~sock()
{
	if(this->status)
		closesocket(s);
	if(this->tcpcon_status)
		closesocket(connected);
}

sock::sock(const std::string& host, int port, bool listen, bool udp, int rcvbuf, int sndbuf)
{
	socklib::ensure();
	this->status = false;
	this->tcpcon_status = false;

	if(host != std::string(""))
	{
		// get the server host entry
		memset((void*)&addr, 0, sizeof(addr));
		addr.sin_addr.s_addr = inet_addr(host.c_str());
		if(INADDR_NONE == addr.sin_addr.s_addr) {
			h = gethostbyname(host.c_str());
			if(NULL == h) {
				throw ecomp(); // something better here
				// perror("Could not get host by name");
			}
		} else {
			h = gethostbyaddr((const char*)&addr.sin_addr, sizeof(struct sockaddr_in), AF_INET);
			if(NULL == h) {
				throw ecomp(); // something better here
				// perror("Could not get host by address");
			}
		}
	    addr.sin_addr   = *((in_addr*)*h->h_addr_list);
	}
	else
	{
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
	}

    // create the local socket
	if(udp)
		s = socket(AF_INET, SOCK_DGRAM, 0);
	else
		s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(INVALID_SOCKET == s) {
		throw ecomp(); // something better here
        // perror("Could not create socket");
    }

    // setup the rest of our local address
    addr.sin_family = AF_INET;
    addr.sin_port   = htons(port);

	if(!listen)
		r = connect(s, (sockaddr*)&addr, sizeof(struct sockaddr));
	else
		r = bind(s, (sockaddr*)&addr, sizeof(struct sockaddr));

	if(listen && !udp)
	{
		if (::listen(s, 1) == -1) {
            //perror("Listen");
            throw ecomp(); // something better here
        }
		int sin_size;
		sin_size = sizeof(struct sockaddr_in);
		connected = accept(s, (struct sockaddr *)&client_addr,&sin_size);
		tcpcon_status = true;
		SOCKET tmp;
		tmp = connected; connected = s; s = tmp;
	}

    if(SOCKET_ERROR == r) {
        closesocket(s);
		throw ecomp(); // ...
        // perror("Cannot connect to server");
    }

	// set socket buffers to desired sizes
	for(int cnt = 0; cnt < 2; cnt++)
	{
		int newsize = !cnt ? rcvbuf : sndbuf;
		int opt = !cnt ? SO_RCVBUF : SO_SNDBUF;
		if(newsize)
		{
			int status = setsockopt(s, SOL_SOCKET, opt, (const char*)&rcvbuf, sizeof(int));
			if (status < 0)
			{
				closesocket(s);
				throw ecomp(); // ...
			}
			int resize=0;
			int getsize = sizeof(int);
			status = getsockopt(s, SOL_SOCKET, opt, (char*)&resize, &getsize);
			if (status < 0 || resize != rcvbuf)
			{
				closesocket(s);
				throw ecomp(); // ...
			}
		}
	}

	this->status = true;
}

// send the data that is in the array and return true for success
bool sock::send(const array<char>& data)
{
	// break to pieces and send
	size_t max_chunk = 1024*1024*32;
	size_t len = data.length();
	size_t off = 0;
	ptrdiff_t err;
	while(len > off) {
		size_t unit = std::min(len - off, max_chunk);
		err = ::send(s, data.c_ptr() + off, unit, 0);
		if(err <= 0)
			return false;
		off += err;
	}
	return true;
}

// receive data of size equal to array size and return true for success
bool sock::receive(array<char>& data)
{
	size_t max_chunk = 1024*1024*32;
	size_t len = data.length();
	size_t off = 0;
	ptrdiff_t err;

	while(len > off) {
		size_t unit = std::min(len - off, max_chunk);
		err = ::recv(s, data.c_ptr() + off, unit, 0);
		if(err <= 0)
			return false;
		off += err;
	}
	return true;
}

// receive data once into the array and return the size, else zero
ptrdiff_t sock::receive_once(array<char>& data)
{
	ptrdiff_t err = recv(s, data.c_ptr(), data.length(), 0);
	if(err < 0)
		err = 0;
	return err;
}

void sock::receive_resize(array<char>& data)
{
	ptrdiff_t err = this->receive_once(data);
	if(err < 0)
		throw ecomp();
	else
		data.resize(err);
}

//-----------------------------------------------------------------------------

}  // namespace net

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_SYSTEM_SOCKET_HPP