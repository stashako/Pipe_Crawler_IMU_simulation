#include "IMU_server.h"

// con_handler::con_handler(boost::asio::io_service &io_service) : sock(io_service) {}
// socket creation
boost::asio::ip::tcp::socket &con_handler::socket()
{
  return sock;
}

void con_handler::read()
{
  sock.async_read_some(
      boost::asio::buffer(data, max_length),
      boost::bind(&con_handler::handle_read,
                  shared_from_this(),
                  boost::asio::placeholders::error,
                  boost::asio::placeholders::bytes_transferred));
}

void con_handler::write()
{

  for (int i = 0; i < 9; i++)
    msg[i] = data[i];

  sock.async_write_some(
      boost::asio::buffer(msg, max_length),
      boost::bind(&con_handler::handle_write,
                  shared_from_this(),
                  boost::asio::placeholders::error,
                  boost::asio::placeholders::bytes_transferred));
}

void con_handler::handle_read(const boost::system::error_code &err, size_t bytes_transferred)
{
  if (!err)
  {
    for (int i = 0; i < 9; i++)
    {
      std::cout << data[i] << "  ";
    }
    std::cout << std::endl;
  }
  else
  {
    std::cerr << "error: " << err.message() << std::endl;
    sock.close();
  }
  con_handler::write();
}
void con_handler::handle_write(const boost::system::error_code &err, size_t bytes_transferred)
{
  if (err)
  {
    std::cerr << "error: " << err.message() << std::endl;
    sock.close();
  }
}

void Server::start_accept()
{
  // socket
  std::shared_ptr<con_handler> con = std::make_shared<con_handler>(io_service);

  // asynchronous accept operation and wait for a new connection.
  acceptor_.async_accept(con->socket(),
                         boost::bind(&Server::handle_accept, this, con,
                                     boost::asio::placeholders::error));
}

// Server::Server(boost::asio::io_service &io_service, std::string address, unsigned int port) : acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address(address), port)), io_service(io_service)
// {
//   Server::start_accept();
// }
void Server::handle_accept(std::shared_ptr<con_handler> con, const boost::system::error_code &err)
{
  if (!err)
  {
    con->read();
  }
  Server::start_accept();
}
