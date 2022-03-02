#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <memory>
#include <vector>

class con_handler : public std::enable_shared_from_this<con_handler>
{
private:
  boost::asio::ip::tcp::socket sock;
  float msg[9];
  enum
  {
    max_length = 40
  };
  float data[max_length];

public:
  con_handler(boost::asio::io_service &io_service) : sock(io_service) {};
  //socket creation
  boost::asio::ip::tcp::socket &socket();

  void read();


  void write();


  void handle_read(const boost::system::error_code &err, size_t bytes_transferred);

  void handle_write(const boost::system::error_code &err, size_t bytes_transferred);
};




class Server
{
private:
  boost::asio::ip::tcp::acceptor acceptor_;
  boost::asio::io_service &io_service;
  void start_accept();
public:
  //constructor for accepting connection from client
  Server(boost::asio::io_service &io_service, std::string address, unsigned int port) : acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address(address), port)), io_service(io_service)
  {
  Server::start_accept();
  }
  void handle_accept(std::shared_ptr<con_handler> con, const boost::system::error_code &err);
};