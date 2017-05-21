#ifndef SERVER_H
# define SERVER_H

# define PORT 7890
# define EOL "\r\n"
# define EOL_SIZE 2

# include <stdio.h>
# include <sys/socket.h>
# include <stdlib.h>
# include <netinet/in.h>
# include <string.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <netdb.h>

typedef struct  s_env
{
    int                 sockfd;
    int                 new_sockfd;
    struct sockaddr_in  host_addr;
    struct sockaddr_in  client_addr;
    socklen_t           sin_size;
    int                 recv_length;
    int                 yes;
}               t_env;

int send_string(int sockfd, char *buffer);
int recv_line(int sockfd, char *buffer);

/*void    dump(char *data_buffer, int length)
{
    char    byte;
    int     i;
    int     j;

    i = 0;
    while (i < length)
    {
        byte = data_buffer[i];
        printf("%02x ", data_buffer[i]);
        if (i % 16 == 15 || i == length - 1)
        {
            j = 0;
            while (j < 15 - (i % 16))
            {
                printf("   ");
                j++;
            }
            printf("| ");
            j = i - (i % 16);
            while (j <= i)
            {
                byte = data_buffer[j];
                if (byte > 31 && byte < 127)
                    printf("%c", byte);
                else
                    printf(".");
                j++;
            }
            printf("\n");
        }
        i++;
    }
}*/

#endif
