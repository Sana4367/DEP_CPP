#include "server.h"
#include <iostream>
#include <thread>
#include <vector>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <fstream>
#include <sstream>

#pragma comment(lib, "ws2_32.lib")

WebServer::WebServer(int port, const std::string& directory) : port(port), directory(directory) {}

void handle_client(SOCKET client_socket, const std::string& directory) {
    char buffer[1024];
    int bytes_received = recv(client_socket, buffer, 1024, 0);
    if (bytes_received > 0) {
        std::istringstream request(buffer);
        std::string method, path, version;
        request >> method >> path >> version;

        if (method == "GET") {
            std::string file_path = directory + path;
            if (path == "/") file_path += "index.html";

            std::ifstream file(file_path);
            if (file) {
                std::stringstream file_content;
                file_content << file.rdbuf();
                std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" + file_content.str();
                send(client_socket, response.c_str(), response.size(), 0);
            } else {
                std::string response = "HTTP/1.1 404 Not Found\r\n\r\n";
                send(client_socket, response.c_str(), response.size(), 0);
            }
        }
    }
    closesocket(client_socket);
}

void WebServer::start() {
    WSADATA wsa_data;
    WSAStartup(MAKEWORD(2, 2), &wsa_data);

    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    bind(server_socket, (sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_socket, SOMAXCONN);

    std::cout << "Server is running on port " << port << std::endl;

    while (true) {
        SOCKET client_socket = accept(server_socket, NULL, NULL);
        std::thread client_thread(handle_client, client_socket, directory);
        client_thread.detach();
    }

    WSACleanup();
}
