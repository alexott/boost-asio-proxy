/**
 * @file   proxy-server.cpp
 * @author Alex Ott <alexott@gmail.com>
 * 
 * @brief  
 * 
 * 
 */

#include "proxy-server.hpp"

server::server(const ios_deque& io_services, int port, std::string interface_address)
	: io_services_(io_services),
	  endpoint_(interface_address.empty()?	
				(ba::ip::tcp::endpoint(ba::ip::tcp::v4(), port)): // INADDR_ANY for v4 (in6addr_any if the fix to v6)
				ba::ip::tcp::endpoint(ba::ip::address().from_string(interface_address), port) ),	// specified ip address
	  acceptor_(*io_services.front(), endpoint_)	// By default set option to reuse the address (i.e. SO_REUSEADDR)
{
	std::cout << endpoint_.address().to_string() << ":" << endpoint_.port() << std::endl;
//	std::cout << "server::server" << std::endl;
	start_accept();
}

void server::start_accept() {
//	std::cout << "server::start_accept" << std::endl;
	// Round robin.
	io_services_.push_back(io_services_.front());
	io_services_.pop_front();
	connection::pointer new_connection = connection::create(*io_services_.front());

	acceptor_.async_accept(new_connection->socket(),
						   boost::bind(&server::handle_accept, this, new_connection,
									   ba::placeholders::error));
}

void server::handle_accept(connection::pointer new_connection, const bs::error_code& error) {
//	std::cout << "server::handle_accept" << std::endl;
	if (!error) {
		new_connection->start();
		start_accept();
	}
}
