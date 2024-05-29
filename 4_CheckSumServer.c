#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<math.h>

int powTwo(int n){
  for(int i=1;i<=n/2;i++){
    if(pow(2,i)==n){
      return 1;
    }
  }
  return 0;
}

int main(void){
  int sd,cd,cadl,dl,sl,c,i,j,k,t,sum[100];
  struct sockaddr_in sad,cad;
  char data[100];

  //socket
  sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
  printf("Socket created\n");

  sad.sin_family=AF_INET;
  sad.sin_port=htons(9995);
  sad.sin_addr.s_addr=inet_addr("127.0.0.1");
  
  //bind
  bind(sd,(struct sockaddr*)&sad,sizeof(sad));
  printf("Binding done\n");
  
  //listen
  listen(sd,10);
  printf("Listening\n");
  
  //accept
  cadl=sizeof(cad);
  cd=accept(sd,(struct sockaddr*)&cad,&cadl);
  
  //receive
  recv(cd,data,sizeof(data),0);

  printf("Received string: %s\n",data);

  //logic
  dl=strlen(data);

  while(1){
    printf("Enter segment length:");
    scanf("%d",&sl);
    if(pow(2,sl)==0)
      printf("\nSegement length is power of 2");
    else
      break;
  }

  //main logic
  for(i=dl;i>0;i=i-sl){
    c=0;
    k=sl-1;
    for(j=i-1;j>=i-sl;j--){
       t=sum[k]+(data[j]-48)+c;
       sum[k]=t%2;
       c=t/2;
       k--;
    } 
    if(c==1){
      for(j=sl-1;j>=0;j--){
        t=sum[j]+c;
        sum[j]=t%2;
        c=t/2;
      }
    }
  }

  //checking
  int count=0;
  for(j=0;j<sl;j++){
    if(sum[j]!=1){
      count++;
      break;
    }
  }

  if(count!=0){
    printf("Error in transmission....");
  }
  else{
    printf("Data received in correct: ");
    for(i=0;i<dl-sl;i++)
      printf("%c",data[i]);
    printf("\n");
  }
  
  close(cd);
  close(sd);
}