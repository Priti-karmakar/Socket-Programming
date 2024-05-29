#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<math.h>

int main(void){
    int sd,cd,cadl;
    struct sockaddr_in sad,cad;
    char codeword[100];

    //socket
    sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    printf("Socketing....\n");

    sad.sin_family=AF_INET;
    sad.sin_port=htons(9995);
    sad.sin_addr.s_addr=inet_addr("127.0.0.1");

    //bind
    bind(sd,(struct sockaddr*)&sad,sizeof(sad));
    printf("Binding....\n");

    //listen
    listen(sd,10);
    printf("Listening....\n");

    //accept
    cadl=sizeof(cad);
    cd=accept(sd,(struct sockaddr*)&cad,&cadl);

    recv(cd,codeword,sizeof(codeword),0);

    printf("Received string: %s\n",codeword);

    int dl,r=0,data[100],i,j,k,z,c,count=0,error[100],l=1;
    dl=strlen(codeword);
    printf("data length: %d\n",dl);
    while(pow(2,r)<(dl+1)){
        r++;
    }
    printf("Number of parity bits: %d",r);

    for(i=1,j=dl-1;i<=dl;i++){
        data[i]=codeword[j--]-'0';
    }

    //checking
    for(i=0;i<r;i++){
        z=pow(2,i);
        c=0;
        for(j=z;j<=dl;j=k+z){
            for(k=j;k<j+z;k++){
                if(k<=dl){
                    c+=data[k];
                }
            }
        }
        error[l]=c%2;
        count+=error[l];
        l++;
    }

    if(count==0){
        printf("\nActual data received...");
    }else{
        printf("\nWromg data received...");
        int index=0;
        for(i=r;i>=1;i--){
            if(error[i]==1){
                index+=pow(2,(i-1));
            }
        }
        printf("\nError bit: %d",index);
        if(data[index]==0)
            data[index]=1;
        else
            data[index]=0;
        printf("\nCorrected data: ");
        for(i=dl;i>=1;i--)
            printf("%d ",data[i]);
        printf("\n");
    }

    close(cd);
    close(sd);

}