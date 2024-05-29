#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(void){
  int sd,cd,cadl,dl,divl,i,j;
  struct sockaddr_in cad,sad;
  char data[100],div[100],data1[100];

  //socket
  sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
  printf("Socketing...\n");

  sad.sin_family=AF_INET;
  sad.sin_port=htons(9995);
  sad.sin_addr.s_addr=inet_addr("127.0.0.1");
  
  //bind
  bind(sd,(struct sockaddr*)&sad,sizeof(sad));
  printf("Binding....\n");
  
  //listen
  listen(sd,10);
  printf("listening...\n");

  //accept
  cadl=sizeof(cad);
  cd=accept(sd,(struct sockaddr*)&cad,&cadl);

  //receive
  recv(cd,data,sizeof(data),0);
  
  printf("received string: %s\n",data);
  dl=strlen(data);
  strcpy(data1,data);

  printf("Enter the divisor: ");
  gets(div);
  divl=strlen(div);
  
  //main logic
  for(i=0;i<dl;i++){
    if(data[i]=='1'){
      for(j=0;j<divl;j++){
        if(data[i+j]==div[j])
          data[i+j]='0';
        else
          data[i+j]='1';
      }
    }
  }
  int count=0;
  printf("%s\n",data);
  for(i=0;i<dl;i++){
    if(data[i]!='0')
        count++;
  }
  if(count==0){
    printf("Original data received...\n");
    printf("Actual data: ");
    for(i=0;i<dl-(divl-1);i++)
      printf("%c",data1[i]);
    printf("\n");
  }
  else
    printf("Wrong data received..");
  close(cd);
  close(sd);
}