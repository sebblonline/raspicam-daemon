#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <array>

using namespace boost::asio;
using ip::tcp;

// TODO rename to "Session"
class ConnectionHandler : public boost::enable_shared_from_this<ConnectionHandler>
{
public:
  typedef boost::shared_ptr<ConnectionHandler> Pointer;
  ConnectionHandler(boost::asio::io_service& io_service);

// creating the pointer
  static Pointer create(boost::asio::io_service& io_service);

  //socket creation
  tcp::socket& socket()
  {
    return sock_;
  }

  void start();

  void handleRead(const boost::system::error_code& err, size_t bytes_transferred);

private:
  tcp::socket sock_;
  std::array<char,128> data_;

};

#endif // CONNECTIONHANDLER_H
