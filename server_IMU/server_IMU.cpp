#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <memory>
#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

///////////////////////////////////////////////////////////////////
// simulation

void render();
void init();
void reshape(int w, int h);
void timer(int);

float shift = 4.0;
float roll1 = 0.0;
float pitch1 = 0.0;
float yaw1 = 0.0;

float roll2 = 0.0;
float pitch2 = 0.0;
float yaw2 = 0.0;

float roll3 = 0.0;
float pitch3 = 0.0;
float yaw3 = 0.0;

///////////////////////////////////////////////////////////////////
// Asio

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
    con_handler(boost::asio::io_service &io_service) : sock(io_service) {}
    //socket creation
    boost::asio::ip::tcp::socket &socket()
    {
        return sock;
    }

    void read()
    {
        sock.async_read_some(
            boost::asio::buffer(data, max_length),
            boost::bind(&con_handler::handle_read,
                        shared_from_this(),
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
    }

    void write()
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

    void handle_read(const boost::system::error_code &err, size_t bytes_transferred)
    {
        if (!err)
        {
            roll1 = data[0];
            pitch1 = data[1];
            yaw1 = data[2];

            roll2 = data[3];
            pitch2 = data[4];
            yaw2 = data[5];

            roll3 = data[6];
            pitch3 = data[7];
            yaw3 = data[8];
        }
        else
        {
            std::cerr << "error: " << err.message() << std::endl;
            sock.close();
        }
        write();
    }
    void handle_write(const boost::system::error_code &err, size_t bytes_transferred)
    {
        if (err)
        {
            std::cerr << "error: " << err.message() << std::endl;
            sock.close();
        }
    }
};

class Server
{
private:
    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::io_service &io_service;
    void start_accept()
    {
        // socket
        std::shared_ptr<con_handler> con = std::make_shared<con_handler>(io_service);

        // asynchronous accept operation and wait for a new connection.
        acceptor_.async_accept(con->socket(),
                               boost::bind(&Server::handle_accept, this, con,
                                           boost::asio::placeholders::error));
    }

public:
    //constructor for accepting connection from client
    Server(boost::asio::io_service &io_service, std::string address, unsigned int port) : acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address(address), port)), io_service(io_service)
    {
        start_accept();
    }
    void handle_accept(std::shared_ptr<con_handler> con, const boost::system::error_code &err)
    {
        if (!err)
        {
            con->read();
        }
        start_accept();
    }
};

////////////////////////////////////////////////////////////////////
// main

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

    return 0;
}

////////////////////////////////////////////////////////////////
// simulation functions
void init()
{

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
}

void render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0.0, 0.0, 30.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glRotatef(roll1, 1, 0, 0);
    glRotatef(pitch1, 0, 1, 0);
    glRotatef(yaw1, 0, 0, 1);

    GLUquadricObj *quadratic0;
    quadratic0 = gluNewQuadric();
    glColor3f(1.0, 0.0, 0.0);
    gluCylinder(quadratic0, 1.0f, 1.0f, 3.0f, 32, 2);

    glTranslatef(0, 0, shift);
    glRotatef(roll2 - roll1, 1, 0, 0);
    glRotatef(pitch2 - pitch1, 0, 1, 0);
    glRotatef(yaw2 - yaw1, 0, 0, 1);

    GLUquadricObj *quadratic1;
    quadratic1 = gluNewQuadric();
    glColor3f(0.0, 1.0, 0.0);
    gluCylinder(quadratic1, 1.0f, 1.0f, 3.0f, 32, 2);

    glTranslatef(0, 0, shift);
    glRotatef(roll3 - roll2 - roll1, 1, 0, 0);
    glRotatef(pitch3 - pitch2 - pitch1, 0, 1, 0);
    glRotatef(yaw3 - yaw2 - yaw1, 0, 0, 1);

    GLUquadricObj *quadratic2;
    quadratic2 = gluNewQuadric();
    glColor3f(0.0, 0.0, 1.0);
    gluCylinder(quadratic2, 1.0f, 1.0f, 3.0f, 32, 2);

    glutSwapBuffers();
}

void reshape(int w, int h)
{

    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 2.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);

    Server server(io_service, address, port);
    io_service.run();

    cout << "imu 1: " << roll1 << "," << pitch1 << "," << yaw1 << " imu 2: " << roll2 << "," << pitch2 << "," << yaw2 << " imu 3: " << roll3 << "," << pitch3 << "," << yaw3 << endl;
}