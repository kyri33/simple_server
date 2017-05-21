#include "server.h"

int perform_lookup(int for_sockfd, char *host_name)
{
    int                 sockfd;
    struct hostent      *host_info;
    struct sockaddr_in  address;
    char                buffer[4096];

    printf("Trying %s\n", host_name);
    if ((host_info = gethostbyname(host_name)) == NULL)
        return (send_string(for_sockfd, "Could not find host\n"));
    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        return (send_string(for_sockfd, "Fatal socket\n"));
    address.sin_family = AF_INET;
    address.sin_port = htons(80);
    address.sin_addr = *((struct in_addr *)host_info->h_addr);
    memset(&(address.sin_zero), '\0', 8);
    if (connect(sockfd, (struct sockaddr *)&address, sizeof(struct sockaddr)) == -1)
        return (send_string(for_sockfd, "Unable to connect\n"));
    send_string(sockfd, "HEAD / HTTP/1.0\r\n\r\n");
    while (recv_line(sockfd, buffer))
    {
        send_string(for_sockfd, buffer);
        send_string(for_sockfd, "\n");
    }
    return (1);
}

int main(void)
{
    t_env   env;
    char    buffer[1024];
    env.recv_length = 1;
    env.yes = 1;
    if ((env.sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) // Protocol: IP, Type: stream, always 0
        printf("error\n");

    if (setsockopt(env.sockfd, SOL_SOCKET, SO_REUSEADDR, &(env.yes), sizeof(int)) == -1)
        printf("error\n");

    env.host_addr.sin_family = AF_INET; //Host byte order
    env.host_addr.sin_port = htons(PORT); //POrt to bind, convert byte order to network
    env.host_addr.sin_addr.s_addr = INADDR_ANY; //Set to 0 to define host ip as machine ip
    printf("Address is : %i\n", INADDR_ANY);
    memset(&(env.host_addr.sin_zero), '\0', 8); //Zero the rest of the struct 'padding'

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
        send_string(env.new_sockfd, "Hello World!\n");
        env.recv_length = recv_line(env.new_sockfd, buffer);
        printf("Received %s\n", buffer);
        perform_lookup(env.new_sockfd, buffer);
        close(env.new_sockfd);
    }
    return (0);
}
