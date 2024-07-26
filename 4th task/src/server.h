#ifndef SERVER_H
#define SERVER_H

#include <string>

class WebServer {
public:
    WebServer(int port, const std::string& directory);
    void start();
private:
    int port;
    std::string directory;
};

#endif // SERVER_H
