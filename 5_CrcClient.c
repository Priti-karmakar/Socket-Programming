#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(void){
  int sd,dl,divl,i,j,k;
  struct sockaddr_in sad;
  char data[100],div[100],data1[100];

  sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
  printf("Socket done\n");

  sad.sin_family=AF_INET;
  sad.sin_port=htons(9995);
  sad.sin_addr.s_addr=inet_addr("127.0.0.1");

  connect(sd,(struct sockaddr*)&sad,sizeof(sad));
  printf("Connecting....\n");

  //main logic
  printf("Enter the dividend:");
  gets(data);

  printf("Enter the divisor: ");
  gets(div);

  dl=strlen(data);
  divl=strlen(div);

  //appending n-1 zeroes 
  for(i=0;i<divl-1;i++){
    data[dl+i]='0';
  }
  strcpy(data1,data);

  //main logic
  for(i=0;i<dl;i++){
    if(data1[i]=='1'){
      for(j=0;j<divl;j++){
        if(data1[i+j]==div[j])
          data1[i+j]='0';
        else
          data1[i+j]='1';
      }
    }
  }

  for(i=dl;i<dl+divl-1;i++){
    data[i]=data1[i];
  }
  printf("%s\n",data);
  send(sd,data,sizeof(data),0);

  close(sd);
  
}