#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

int checkParity(char str[]){
  int i=0,count=0;
  while(str[i]!='\0'){
    if(str[i]=='1'){
      count++;
    } 
    i++;
  }
  // printf("%d",i);
  if(count%2==0){
    return 1;
  }else{
    return 0;
  }
}

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

  recv(cd,str,sizeof(str),0);

  printf("Code word received: %s\n",str);
  
  if(checkParity(str))
    printf("Correct data");
  else
    printf("Erronious data");
  
  close(cd);
  close(sd);
}