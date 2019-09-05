#include "ConnectionHandler.h"
#include <iostream>
#include <boost/log/trivial.hpp>

ConnectionHandler::ConnectionHandler(boost::asio::io_service& io_service): sock_(io_service)
{
}

ConnectionHandler::Pointer ConnectionHandler::create(boost::asio::io_service& io_service)
{
    return Pointer(new ConnectionHandler(io_service));
}

void ConnectionHandler::start()
{
    BOOST_LOG_TRIVIAL(debug) << __PRETTY_FUNCTION__;

    sock_.async_receive(
                boost::asio::buffer(data_),
                boost::bind(&ConnectionHandler::handleRead,
                            shared_from_this(),
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));
}

void ConnectionHandler::handleRead(const boost::system::error_code& err, size_t bytes_transferred)
{
    BOOST_LOG_TRIVIAL(debug) << __PRETTY_FUNCTION__;

    if (!err)
    {
        BOOST_LOG_TRIVIAL(info) << "data: " << data_.data();
        // TODO remove this
        if (strcmp(data_.data(),"bye"))
        {
            sock_.close();
        }
    }
    else if ((boost::asio::error::eof == err) ||
             (boost::asio::error::connection_reset == err))
    {
        BOOST_LOG_TRIVIAL(info) << "ConnectionHandler: Client disconnected: " << err.message();
    }
    else
    {
        BOOST_LOG_TRIVIAL(error) << "ConnectionHandler error: " << err.message();
        sock_.close();
    }
}
