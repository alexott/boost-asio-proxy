/**
 * @file   proxy.cpp
 * @author Alex Ott <alexott@gmail.com>
 * 
 * @brief  
 * 
 * 
 */

#include "proxy-server.hpp"

int main(int argc, char** argv) {
	try {
		int thread_num=2;
		if(argc > 1)
			thread_num=boost::lexical_cast<int>(argv[1]);
		ios_deque io_services;
		std::deque<ba::io_service::work> io_service_work;
		
		boost::thread_group thr_grp;
		
		for (int i = 0; i < thread_num; ++i) {
			io_service_ptr ios(new ba::io_service);
			io_services.push_back(ios);
			io_service_work.push_back(ba::io_service::work(*ios));
			thr_grp.create_thread(boost::bind(&ba::io_service::run, ios));
		}
		server server(io_services);
		thr_grp.join_all();
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}


	return 0;
}

