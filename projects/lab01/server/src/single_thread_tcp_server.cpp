#include "single_thread_tcp_server.h"
#include <string>
using namespace std;

char caesar(char c);

void handle_connection(SOCKET socket, sockaddr_in* addr) {
    char* str_in_addr = inet_ntoa(addr->sin_addr);
    printf("[%s]>>%s\n", str_in_addr, "Establish new connection");

    while (true) {
        char buffer[256] = "";
        string output = "";
        int rc = recv(socket, buffer, sizeof(buffer), 0);
        if (rc > 0) {
            printf("[%s]: Received message - %s\n", str_in_addr, buffer);

            for (int x = 0; x < sizeof(buffer)/sizeof(int); x++)
            {
                output += caesar(buffer[x]);
            }

            printf("[%s]: Decoded message - %s\n", str_in_addr, output.c_str());
        }
        else {
            break;
        }
    }

    close_socket(socket);
    printf("[%s]>>%s", str_in_addr, "Close incomming connection\n");
}

char caesar(char c)
{
    if (isalpha(c))
    {
        c = toupper(c);
        c = (((c - 65) + 13) % 26) + 65;
    }
    return c;
}