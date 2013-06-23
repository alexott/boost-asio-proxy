/**
 * @file   proxy-server.hpp
 * @author Alex Ott <alexott@gmail.com>
 * 
 * @brief  
 * 
 * 
 */

#ifndef _PROXY_SERVER_H
#define _PROXY_SERVER_H 1

#include "common.h"
#include "proxy-conn.hpp"

#include <deque>

typedef std::deque<io_service_ptr> ios_deque;

class server {
public:
	server(const ios_deque& io_services, int port=10001, std::string interface_address = "");

private:
	void start_accept();
	void handle_accept(connection::pointer new_connection, const bs::error_code& error);
	
	ios_deque io_services_;
	const ba::ip::tcp::endpoint endpoint_;   /**< object, that points to the connection endpoint */
	ba::ip::tcp::acceptor acceptor_;         /**< object, that accepts new connections */
};


#endif /* _PROXY-SERVER_H */

