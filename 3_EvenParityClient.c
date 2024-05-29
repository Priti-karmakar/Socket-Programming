#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void generateParity(char *str){
  int i=0,count=0;
  while(str[i]!='\0'){
    if(str[i]=='1'){
      count++;
    }
    i++;
  }
  if(count%2==0){
    strcat(str,"0");
  }else{
    strcat(str,"1");
  }
  printf("Code word sent: %s\n",str);
}

int main() {
  int sd;
  struct sockaddr_in sad;
  char str[100];

  sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  sad.sin_family = AF_INET;
  sad.sin_port = htons(9995);
  sad.sin_addr.s_addr = inet_addr("127.0.0.1");

  connect(sd, (struct sockaddr *)&sad, sizeof(sad));

  printf("Enter the string:");
  gets(str);

  generateParity(&str);
  // printf("\n%s\n",str);
  send(sd,str,sizeof(str),0);

  close(sd);
}
