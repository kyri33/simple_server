#include "server.h"

int main(void)
{
    t_env   env;
    char    buffer[1024];
    env.recv_length = 1;
    env.yes = 1;
    if ((env.sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        printf("error\n");

    if (setsockopt(env.sockfd, SOL_SOCKET, SO_REUSEADDR, &(env.yes), sizeof(int)) == -1)
        printf("error\n");

    env.host_addr.sin_family = AF_INET; //Host byte order
    env.host_addr.sin_port = htons(PORT); //POrt to bind, convert byte order to network
    env.host_addr.sin_addr.s_addr = INADDR_ANY; //Set to 0 to define host ip as machine ip
    printf("Address is : %i\n", INADDR_ANY);
    memset(&(env.host_addr.sin_zero), '\0', 8); //Zero the rest of the struct

    if (bind(env.sockfd, (struct sockaddr *)&env.host_addr, sizeof(env.host_addr)) == -1)
        printf("Error binding\n"); //Bind socket to current ip address on port 7890

    if (listen(env.sockfd, 5) == -1)
        printf("Error listeneing\n"); //Listen for incoming connections

    while(1)
    {
        env.sin_size = sizeof(struct sockaddr_in);
        env.new_sockfd = accept(env.sockfd, (struct sockaddr *)&env.client_addr, &env.sin_size);
        if (env.new_sockfd == -1)
            printf("Error accepting connection\n");
        printf("Got connection from %s port %d\n", inet_ntoa(env.client_addr.sin_addr), ntohs(env.client_addr.sin_port));
        send(env.new_sockfd, "Hello World!\n", 13, 0);
        env.recv_length = recv(env.new_sockfd, &buffer, 1024, 0);
        while (env.recv_length > 0)
        {
            printf("RECV: %d bytes\n", env.recv_length);
            //dump(buffer, env.recv_length);
            printf(buffer);
            env.recv_length = recv(env.new_sockfd, &buffer, 1024, 0);
        }
        close(env.new_sockfd);
    }
    return (0);
}