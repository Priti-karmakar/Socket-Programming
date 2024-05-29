#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(void){
    int sd,cd,cadl;
    struct sockaddr_in sad,cad;
    char str[100];

    //socket
    sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    sad.sin_family=AF_INET;
    sad.sin_port=htons(9995);
    sad.sin_addr.s_addr=inet_addr("127.0.0.1");

    //bind
    bind(sd,(struct sockaddr*)&sad,sizeof(sad));

    //listen
    listen(sd,10);

    //accept
    cadl=sizeof(cad);
    cd=accept(sd,(struct sockaddr*)&cad,&cadl);

    //read
    while(strcmp(str,"bye")!=0){
      recv(cd,str,sizeof(str),0);
      printf("Client says: %s\n",str);
      printf("Enter the string: ");
      gets(str);
      send(cd,str,sizeof(str),0);
    }
  
    //close
    close(cd);
    close(sd);
}