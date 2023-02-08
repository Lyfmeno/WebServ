/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:58:13 by avarnier          #+#    #+#             */
/*   Updated: 2023/02/08 17:36:24 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Server.hpp"

////////////////////////////////////////////////////////////////////////////////
//                             server constructor                             //
////////////////////////////////////////////////////////////////////////////////

ft::Server::Server() : sock(), addr()
{
}

ft::Server::Server(const Server &x) : sock(x.sock), addr(x.addr)
{
}

////////////////////////////////////////////////////////////////////////////////
//                        server assignement operator                         //
////////////////////////////////////////////////////////////////////////////////

ft::Server	&ft::Server::operator=(const Server &x)
{
	if (this != &x)
	{
	}
	return (*this);
}

////////////////////////////////////////////////////////////////////////////////
//                             server destructor                              //
////////////////////////////////////////////////////////////////////////////////

ft::Server::~Server()
{
}

////////////////////////////////////////////////////////////////////////////////
//                           server initialization                            //
////////////////////////////////////////////////////////////////////////////////

int	ft::Server::sockinit()
{
	this->sock = socket(AF_INET, SOCK_STREAM, 0);
	if (this->sock == -1)
		return (-1);

	if (bind(this->sock, (sockaddr *)&addr, sizeof(addr)) == -1)
		return (-1);

	return (0);
}
