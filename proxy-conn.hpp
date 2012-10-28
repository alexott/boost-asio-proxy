/**
 * @file   proxy-conn.hpp
 * @author Alex Ott <alexott@gmail.com>
 *
 * @brief
 *
 *
 */

#ifndef _PROXY_CONN_H
#define _PROXY_CONN_H 1

#include "common.h"
#include <map>

class connection : public boost::enable_shared_from_this<connection> {
public:
	typedef boost::shared_ptr<connection> pointer;

	static pointer create(ba::io_service& io_service) {
		return pointer(new connection(io_service));
	}

	ba::ip::tcp::socket& socket() {
		return bsocket_;
	}

	void start();

private:
	connection(ba::io_service& io_service);
	void handle_browser_write(const bs::error_code& err, size_t len);
	void handle_browser_read_headers(const bs::error_code& err, size_t len);
	void handle_server_write(const bs::error_code& err, size_t len);
	void handle_server_read_headers(const bs::error_code& err, size_t len);
	void handle_server_read_body(const bs::error_code& err, size_t len);
	void start_connect();
	void start_write_to_server();
	void shutdown();
	void handle_resolve(const boost::system::error_code& err,
									ba::ip::tcp::resolver::iterator endpoint_iterator);
	void handle_connect(const boost::system::error_code& err,
									ba::ip::tcp::resolver::iterator endpoint_iterator);

	ba::io_service& io_service_;
	ba::ip::tcp::socket bsocket_;
	ba::ip::tcp::socket ssocket_;
	ba::ip::tcp::resolver resolver_;
	bool proxy_closed;
	bool isPersistent;
	int32_t RespLen;
	int32_t RespReaded;

	boost::array<char, 8192> bbuffer;
	boost::array<char, 8192> sbuffer;

	std::string fURL;
	std::string fHeaders;
	std::string fNewURL;
	std::string fMethod;
	std::string fReqVersion;
	std::string fServer;
	std::string fPort;
	bool isOpened;

	std::string fReq;

	typedef std::map<std::string,std::string> headersMap;
	headersMap reqHeaders, respHeaders;

	void parseHeaders(const std::string& h, headersMap& hm);
};


#endif /* _PROXY-CONN_H */

