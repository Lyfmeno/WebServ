/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:17:09 by hlevi             #+#    #+#             */
/*   Updated: 2023/02/12 16:35:19 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Webserv.hpp"

namespace ft {
/////////////////////////////
// Coplien                 //
/////////////////////////////

Webserv::Webserv() : epfd(-1), servers()
{
	this->epinit();
}

Webserv::Webserv(const Webserv &cpy)
: epfd(cpy.epfd), servers(cpy.servers)
{
}

Webserv::~Webserv()
{
	this->close();
}

Webserv &Webserv::operator=(const Webserv &rhs)
{
	if (this != &rhs)
	{
		this->epfd = rhs.epfd;
		this->servers = rhs.servers;
	}
	return (*this);
}

/////////////////////////////
// Assignation contructors //
/////////////////////////////

/////////////////////////////
// Getters                 //
/////////////////////////////

/////////////////////////////
// Setters                 //
/////////////////////////////

/////////////////////////////
// Operators               //
/////////////////////////////

/////////////////////////////
// Methods                 //
/////////////////////////////

void	Webserv::epinit()
{
	size_t	server_nb = this->servers.size();

	this->epfd = epoll_create(server_nb);
	if (this->epfd == -1)
		throw std::runtime_error("Epoll initialization failed");

	for (std::vector<ft::Server> it = this->servers.begin();
	it != this->servers.end(); it++)
	{
		if (sockinit(it->addr) == -1)
		{
			this->close();
			throw std::runtime_error("Socket initialization failed");
		}
	}
}

int	Webserv::sockinit(sockaddr_in addr)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		return (-1);

	int flags = fcntl(sock, F_GETFL);
	if (flags == -1)
		return (-1);

	if (fcntl(sock, F_SETFL, flags | O_NONBLOCK) == -1)
		return (-1);

	if (bind(sock, (sockaddr *)addr, sizeof(addr)) == -1)
		return (-1);

	if (listen(sock, 128) == -1)
		return (-1);

	epoll_event	ev;
	ev.events = EPOLLIN | EPOLLET;
	if (epoll_ctl(this->epfd, EPOLL_CTL_ADD, sock, &ev) == -1)
		return (-1);

	this->sockets.push_back(sock);
	return (0);
}

int	Webserv::run()
{
	for (;;)
	{
		int n = epoll_wait(epoll_fd, this->epev, MAXEV, -1);
		if (n == -1)
			return (-1);
		for (int i = 0; i < n; i++)
		{
			if ((this->epev[i].events & EPOLLERR)
			|| (this->epev[i].events & EPOLLHUP)
			|| !(this->epev[i].events & EPOLLIN))
				::close(this->epev[i].data.fd);
			else if (this->isSock(this->epev[i].data.fd) == true)
			{		
			}
			else ()
			{
			}
		}
	}
}

void	Webserv::close()
{
	if (this->epfd != -1)
	{
		::close(this->epfd);
		this->epfd = -1;
	}
	while (this->sockets.size() != 0)
	{
		::close(*this->sockets.begin());
		this->sockets.erase(this->sockets.begin());
	}
}

bool	Webserv::isSock(int sock)
{
	for (std::vector<int>::const_iterator it = this->sockets.begin();
	it != this->sockets.end(); it++)
	{
		if (sock == *it)
			return (true);
	}
	return (false);
}

/////////////////////////////
// Exceptions              //
/////////////////////////////

}
