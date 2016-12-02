#include "server.h"

int main(void)
{
    t_env   env;
    //char    buffer[1024];

    env.recv_length = 1;
    env.yes = 1;

    if ((env.sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        printf("error");

    if (setsockopt(env.sockfd, SOL_SOCKET, SO_REUSEADDR, &(env.yes), sizeof(int)) == -1)
        printf("error");
}