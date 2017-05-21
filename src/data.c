#include "server.h"

int send_string(int sockfd, char *buffer)
{
    int sent;
    int toSend;

    toSend = strlen(buffer);
    while (toSend > 0)
    {
        sent = send(sockfd, buffer, toSend, 0);
        if (sent == -1)
            return (0);
        toSend -= sent;
        buffer += sent;
    }
    return (1);
}

int recv_line(int sockfd, char *buffer)
{
    char   *ptr;
    int             eol_match;

    eol_match = 0;
    ptr = buffer;
    while (recv(sockfd, ptr, 1, 0)) //Receive single byte
    {
        if (*ptr == EOL[eol_match])
        {
            eol_match++;
            if (eol_match == EOL_SIZE)
            {
                *(ptr + 1 - EOL_SIZE) = '\0'; //Terminate string
                return (strlen(buffer));
            }
        }
        else
            eol_match = 0;
        ptr++;
    }
    return (0);
}