#include "Server.h"
#include <boost/bind.hpp>
#include <boost/log/trivial.hpp>

using namespace boost::asio;
using ip::tcp;

Server::Server(boost::asio::io_service *ioService, unsigned short port):
    ioService_(ioService),
    acceptor_(*ioService, tcp::endpoint(tcp::v4(), port))
{
    BOOST_LOG_TRIVIAL(debug) << __PRETTY_FUNCTION__;
    startAccept();
}

void Server::handleAccept(ConnectionHandler::Pointer connection, const boost::system::error_code& err)
{
    BOOST_LOG_TRIVIAL(debug) << __PRETTY_FUNCTION__;
    if (err)
    {
        BOOST_LOG_TRIVIAL(error) << __PRETTY_FUNCTION__ << "error code: " << err.message();
        return;
    }

    connection->start();
    imageStreamer_.addClient(connection->socket().remote_endpoint().address().to_string());
    startAccept();
}

void Server::stop()
{
    BOOST_LOG_TRIVIAL(debug) << __PRETTY_FUNCTION__;

    imageStreamer_.stop();
    ioService_->stop();
}

void Server::startAccept()
{
    BOOST_LOG_TRIVIAL(debug) << __PRETTY_FUNCTION__;

    // socket
    ConnectionHandler::Pointer connection = ConnectionHandler::create(acceptor_.get_io_service());

    // asynchronous accept operation and wait for a new connection.
    acceptor_.async_accept(connection->socket(),
                           boost::bind(&Server::handleAccept, this, connection,
                                       boost::asio::placeholders::error));
}
