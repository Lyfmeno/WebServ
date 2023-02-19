#include "../incs/Webserv.hpp"

namespace ft {

////////////////////////////////////////////////////////////////////////////////
//                                constructor                                 //
////////////////////////////////////////////////////////////////////////////////

Webserv::Webserv()
{
	// --> parsing
	for (std::vector<Server>::const_iterator it = this->servers.begin();
	it != this->servers.end(); it++)
	{
		this->manager.addServer(it->addr);
	}
}

Webserv::~Webserv()
{
}

////////////////////////////////////////////////////////////////////////////////
//                                  methods                                   //
////////////////////////////////////////////////////////////////////////////////

<<<<<<< HEAD
void	Webserv::run()
{
	for (;;)
	{
		int	n = epoll_wait(this->ep.fd, this->ep.ev, MAXEV, -1);
		if (n == -1)
			throw std::runtime_error("System error: epoll_wait failed");
		for (int i = 0; i < n; i++)
		{
			if ((this->ep.ev[i].events & EPOLLERR)
			|| (this->ep.ev[i].events & EPOLLHUP)
			|| (this->ep.ev[i].events & EPOLLIN))
			{
				::close(this->ep.ev[i].data.fd);
				std::cerr << "Webserv: epoll_wait bad event returned" << '\n';
			}
			else if (this->isSock(this->ep.ev[i].data.fd) == true)
			{
				ft::Socket	newClient;
				socklen_t	len = sizeof(sockaddr_in);
				newClient.fd = accept(this->ep.ev[i].data.fd,
				reinterpret_cast<sockaddr *>(&newClient.addr), &len);
				if (newClient.fd == -1)
				{
					if (errno != EAGAIN && errno != EWOULDBLOCK)
						throw std::runtime_error("System error: accept failed");
				}
				else
				{
					newClient.set(newClient.addr);
					this->ep.add(newClient.fd);
					this->clients.push_back(newClient);
				}
			}
			else
			{
				char	buff[BUFFSIZE + 1];
				ssize_t	bytes = recv(this->ep.ev[i].data.fd, buff, BUFFSIZE, 0);
				buff[bytes] = '\0';
				if (bytes == -1)
					std:: cout << "recv error" << std::endl;
				else if (bytes == 0)
					close(this->ep.ev[i].data.fd);
				else
					std::cout << buff << '\n';
			}
		}
	}
}

bool	Webserv::isSock(const int &fd)
{
	for (std::vector<ft::Socket>::const_iterator it = this->clients.begin();
	it != this->clients.end(); it++)
	{
		if (it->fd == fd)
			return (true);
	}
	return (false);
}

=======
>>>>>>> main
}