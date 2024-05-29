#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<math.h>

int main(void){
    int sd;
    struct sockaddr_in sad;
    char data[100],str[100];

    //socket
    sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    printf("Socketing....\n");
    
    sad.sin_family=AF_INET;
    sad.sin_port=htons(9995);
    sad.sin_addr.s_addr=inet_addr("127.0.0.1");

    //connect
    connect(sd,(struct sockaddr*)&sad,sizeof(sad));
    printf("Connecting....\n");

    int r=0,data1[100],codeword[100],i,j,k,dl,z,c;
    printf("Enter the data: ");
    gets(data);
    dl=strlen(data);
    printf("length: %d",dl);

    while(pow(2,r)<(dl+r+1)){
        // printf("in");
        r++;
    }
    // printf("out: %d",r);
    printf("\nNumber of redundant bits: %d\n",r);

    //storing data array in an integer array
    for(i=0;i<dl;i++){
        data1[i]=data[i]-'0';
    }


    //placing the parity and data bits
    printf("Data stored in the array: ");
    k=0;
    for(i=1,j=dl-1;i<=dl+r;i++){
        if(i==pow(2,k)){
            codeword[i]=999;
            k++;
        }
        else
            codeword[i]=data1[j--];
        printf("%d ",codeword[i]);
    }

    //main logic
    for(i=0;i<r;i++){
        z=pow(2,i);
        c=0;
        for(j=z;j<=dl+r;j=k+z){
            for(k=j;k<j+z;k++){
                if(k<=dl+r){
                    if(codeword[k]!=999)
                        c+=codeword[k];
                    // printf("\n%d",c);
                }
            }
        }
        codeword[z]=c%2;
    }
    printf("\nGenerated codeword: ");
    for(i=dl+r;i>=1;i--)
        printf("%d ",codeword[i]);
    printf("\n");

    j=0;
    for(i=dl+r;i>=1;i--){
        str[j++]=codeword[i]+'0';
    }
    str[j]='\0';
    // gets(str);
    send(sd,str,sizeof(str),0);

    close(sd);
}