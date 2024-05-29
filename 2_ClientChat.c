#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
  int sd;
  struct sockaddr_in sad;
  char str[100];

  sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  sad.sin_family = AF_INET;
  sad.sin_port = htons(9995);
  sad.sin_addr.s_addr = inet_addr("127.0.0.1");

  connect(sd, (struct sockaddr *)&sad, sizeof(sad));

  while(strcmp(str,"bye")!=0){
    printf("Enter the string:");
    gets(str);
    send(sd,str,sizeof(str),0);
    recv(sd,str,sizeof(str),0);
    printf("Server says: %s\n",str);
  }

  close(sd);
}
