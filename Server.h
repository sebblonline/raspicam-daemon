#ifndef SERVER_H
#define SERVER_H

#include "ConnectionHandler.h"
#include "ImageStreamer.h"

#include <boost/asio.hpp>

class Server
{
public:
    //constructor for accepting connection from client
    Server(boost::asio::io_service *ioService, unsigned short port);

    void handleAccept(ConnectionHandler::Pointer connection, const boost::system::error_code& err);

    void stop();

private:
    void startAccept();

    boost::asio::io_service *ioService_;
    boost::asio::ip::tcp::acceptor acceptor_;

    ImageStreamer imageStreamer_;

};

#endif // SERVER_H
