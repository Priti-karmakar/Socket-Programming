#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(void){
    int sd;
    struct sockaddr_in sad;
    char str[50];

    //socket
    sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    sad.sin_family=AF_INET;
    sad.sin_port=htons(9995);
    sad.sin_addr.s_addr=inet_addr("127.0.0.1");

    //connect
    connect(sd,(struct sockaddr*)sad,sizeof(sad));

    //write
    printf("Enter your msg: ");
    scanf("%[^\n]s",str);

    send(sd,str,sizeof(str),0);

    close(sd);

    //read
    //close

}