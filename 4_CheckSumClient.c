#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
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
  int sd,dl,sl,i,j,k,t,sum[100],c;
  struct sockaddr_in sad;
  char data[100],data1[100];

  //socket
  sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
  printf("Socket created\n");

  sad.sin_family=AF_INET;
  sad.sin_port=htons(9995);
  sad.sin_addr.s_addr=inet_addr("127.0.0.1");
  
  //connect
  connect(sd,(struct sockaddr*)&sad,sizeof(sad));
  printf("Connnected\n");

  //logic
  printf("Enter the data: ");
  gets(data);
  dl=strlen(data);
  
  /*segment length must be power of 2*/
  while(1){
    printf("\nEnter the segment length: ");
    scanf("%d",&sl);
    if(powTwo(sl)==0)
      printf("\nSegment length must be power of 2");
    else
      break;
  }

  printf("\nOut %d %d",dl,sl);
  /*if data length is not divisible by segment length add 0 at front*/
  if((dl%sl)!=0){
    i=sl-(dl%sl);
    for(j=0;j<i;j++)
      data1[j]='0';
    strcat(data1,data);
    strcpy(data,data1);
    dl=dl+i;
  }
  
  printf("\nData length:%d ",dl);
  
  //main logic
  for(i=dl;i>0;i=i-sl){
    c=0;
    k=sl-1;
    for(j=i-1;j>=i-sl;j--){
      t=(sum[k]+(data[j]-48)+c);
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

  printf("\n main logic executed...");
  
  printf("\nChecksum: ");
  for(i=0;i<sl;i++){
    if(sum[i]==0)
        sum[i]=1;
    else
        sum[i]=0;
    printf("%d",sum[i]);
    data[dl+i]=sum[i]+48;
  }
  data[dl+i]='\0';
  printf("\nCodeword sent: %s",data);
    
  //send
  send(sd,data,sizeof(data),0);
  
  close(sd);
}