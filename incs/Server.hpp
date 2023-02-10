/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:08:45 by avarnier          #+#    #+#             */
/*   Updated: 2023/02/10 19:05:32 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <netinet/ip.h>
#include <string>
#include "../incs/Location.hpp"

namespace ft {

struct Server
{
	// hlevi
	std::string				server_name;
	std::string				listen;
	std::vector<Location>	location;
	// avarnier
	int			sock;
	sockaddr_in	addr;
	epoll_event	epev;
};
}
