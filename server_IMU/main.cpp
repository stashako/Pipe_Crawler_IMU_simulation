#include "IMU_server.h"

int main(int argc, char *argv[])
{

  if (argc != 3)
  {
    std::cout << "Wrong parameter\n"
              << "Example usage ./async_server 127.0.0.1 1234" << std::endl;
    return -1;
  }

  std::string address = argv[1];
  unsigned int port = std::atoi(argv[2]);

  boost::asio::io_service io_service;
  Server server(io_service, address, port);
  io_service.run();

  return 0;
}