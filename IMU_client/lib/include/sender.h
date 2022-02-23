#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <unistd.h>
#include <vector>


int sending(char *addr, char *p, std::vector<float> msg);