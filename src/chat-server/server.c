#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    printf("------------------>   SERVER   <-----------------\n\n\n\n");

    int sd, cd;
    struct sockaddr_in sad, cad;
    char str[50];

    sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    sad.sin_family = AF_INET;
    sad.sin_addr.s_addr = inet_addr("127.0.0.1");
    sad.sin_port = htons(8080);

    bind(sd, (struct sockaddr *)&sad, sizeof(sad));
    listen(sd, 10);

    unsigned int cadl = sizeof(cad);
    cd = accept(sd, (struct sockaddr *)&cad, &cadl);

    do
    {
        memset(str, '\0', 100);
        printf("Enter message -> ");
        fflush(stdin);
        scanf("%s", str);
        send(cd, str, sizeof(str), 0);
        printf("\nClient IP address : %s\n", inet_ntoa(cad.sin_addr));
        recv(cd, str, sizeof(str), 0);
        printf("Received from Client -----> %s\n", str);
    } while (strcmp(str, "bye") != 0);

    close(cd);
    close(sd);
}