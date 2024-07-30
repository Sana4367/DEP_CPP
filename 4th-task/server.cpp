#include <iostream>
#include <thread>
#include <vector>
#include <netinet/in.h>
#include <cstring>
#include <fstream>
#include <sstream>
#include <unistd.h>

const int PORT = 8080;
const int BUFFER_SIZE = 1024;

void handle_client(int client_socket);
std::string get_request_file_path(const std::string& request);
std::string read_file_content(const std::string& file_path);
std::string build_http_response(const std::string& file_content, bool file_found);

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        std::cerr << "Failed to create socket." << std::endl;
        return 1;
    }

    // Bind socket to address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Bind failed." << std::endl;
        close(server_socket);
        return 1;
    }

    // Listen for incoming connections
    if (listen(server_socket, 10) < 0) {
        std::cerr << "Listen failed." << std::endl;
        close(server_socket);
        return 1;
    }

    std::cout << "Server is listening on port " << PORT << std::endl;

    // Accept and handle client connections
    while (true) {
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);
        if (client_socket < 0) {
            std::cerr << "Failed to accept client connection." << std::endl;
            continue;
        }
        std::thread(handle_client, client_socket).detach();
    }

    close(server_socket);
    return 0;
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
    if (bytes_received < 0) {
        std::cerr << "recv failed." << std::endl;
        close(client_socket);
        return;
    }

    std::string request(buffer);
    std::cout << "Received request:\n" << request << std::endl;

    std::string file_path = get_request_file_path(request);
    std::string file_content = read_file_content(file_path);
    bool file_found = !file_content.empty();
    std::string response = build_http_response(file_content, file_found);

    send(client_socket, response.c_str(), response.size(), 0);
    close(client_socket);
}

std::string get_request_file_path(const std::string& request) {
    std::string file_path = "./static/index.html"; // Default file

    if (request.find("GET / ") == 0) {
        return file_path; // Serve index.html if root is requested
    }

    size_t pos = request.find("GET /");
    if (pos != std::string::npos) {
        size_t end_pos = request.find(" ", pos + 5);
        if (end_pos != std::string::npos) {
            file_path = "./static" + request.substr(pos + 5, end_pos - pos - 5);
        }
    }
    return file_path;
}

std::string read_file_content(const std::string& file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::string build_http_response(const std::string& file_content, bool file_found) {
    std::string response;
    if (file_found) {
        response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" + file_content;
    } else {
        response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n"
                   "<html><body><h1>404 Not Found</h1></body></html>";
    }
    return response;
}