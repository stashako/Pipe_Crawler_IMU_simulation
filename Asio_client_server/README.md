1. sudo apt install libboost-dev
2. sudo apt install libboost-system-dev
3. sudo apt-get install libpthread-stubs0-dev (maybe)
4. sudo apt install libboost-thread-dev (maybe)


//g++ -lpthread -lboost_system server.cpp -o server    or    g++ main.cpp -o server -L /usr/lib -lpthread -lboost_system -lboost_thread