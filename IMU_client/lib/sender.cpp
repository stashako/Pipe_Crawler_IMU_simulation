#include "sender.h"

using namespace std;

int sending(char *addr, char *p, std::vector<float> msg)
{

    auto const address = boost::asio::ip::make_address(addr);
    auto const port = std::atoi(p);
    boost::asio::io_service io_service;
    //socket creation
    boost::asio::ip::tcp::socket socket(io_service);
    //connection
    boost::system::error_code ec;
    socket.connect(boost::asio::ip::tcp::endpoint(address, port), ec);
    if (ec)
    {
        std::cout << ec.message() << std::endl;
        return 1;
    }
    // request/message from client
    //const string msg = "Hello from Client!\n";
    boost::system::error_code error;
    boost::asio::write(socket, boost::asio::buffer(msg), error);
    if (error)
    {
        std::cout << "send failed: " << error.message() << std::endl;
    }
    // getting response from server
    boost::asio::streambuf receive_buffer;
    boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error);
    if (error && error != boost::asio::error::eof)
    {
        std::cout << "receive failed: " << error.message() << std::endl;
    }
    else
    {
        const float *data = boost::asio::buffer_cast<const float *>(receive_buffer.data());
        //std::cout << data << std::endl;
    }
}