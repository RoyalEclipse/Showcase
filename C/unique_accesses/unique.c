#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){

printf("Pozadavky:\n");
char command;
char newuser ='+';
char unique ='?';
int allInputs[1000000];
int uidcount[100000];
int uniqueuidindex[100000];
int inputPos=0;
int newlogfromuid;
int input=-69;
int from=-1;
int to=-1;
int diff;
int uniquecnt = 0;

for(int i = 0; i<1000000; i++) {allInputs[i]=0;}
for(int i = 0; i<100000; i++) {uidcount[i]=0;}
for(int i = 0; i<100000; i++) {uniqueuidindex[i]=0;}

while( 1 ){
    if(scanf(" %c ",&command)==-1) return 0;

    if (command!=newuser && command!=unique){
        printf("Nespravny vstup.\n");
        return 1;
    }else if(command==EOF) {
        return 0;
    }else if(command==newuser){

        if(scanf(" %d",&input) !=1 || input < 0 || input > 99999){
            printf("Nespravny vstup.\n");
            return 1;

        } else if(input == EOF) return 0;

        allInputs[inputPos] = input;
        newlogfromuid=allInputs[inputPos];
        uidcount[newlogfromuid]+=1;

            if(inputPos>=1000000){
        printf("Nespravny vstup.\n");
        return 1;}

        if(uidcount[newlogfromuid]==1)
            printf("> prvni navsteva\n");
        else printf("> navsteva #%d\n",uidcount[newlogfromuid]);
        inputPos++;
        

    }else if(command==unique){

        
        
        if(scanf("%d %d",&from,&to)==-1) return 0;
         if( from < 0 || from > to || to > inputPos-1 ){
            printf("Nespravny vstup.\n");
            return 1;
        }
        diff = to - from + 1;
        
        for(int i = from; i <= to; i++){
            uniqueuidindex[allInputs[i]] += 1;
        }
        for(int i=0; i<100000; i++){
            if(uniqueuidindex[i] != 0)
                uniquecnt+=1;
        }
        printf("> %d / %d\n", uniquecnt, diff);

        uniquecnt = 0;
        for(int i = 0; i < 100000; i++){
            uniqueuidindex[allInputs[i]] = 0;
        }

    }

    }
return 0;
}