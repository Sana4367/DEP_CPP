#include "server.h"

int main() {
    WebServer server(8080, "html");
    server.start();
    return 0;
}
