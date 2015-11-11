/*
 *      Author: Artur Waz
 *      Year: 2015
 */

#ifndef SOCKET_SERVER_H_
#define SOCKET_SERVER_H_


#include "Point2D.h"

#include <boost/array.hpp>
#include <boost/asio.hpp>



class Server {
public:

	Server();
	~Server();


	void sendPoint(Point2D const &p);


private:



};

#endif /* SOCKET_SERVER_H_ */
