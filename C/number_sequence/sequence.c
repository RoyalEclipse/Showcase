#include <stdio.h>

/*pocita pocet cislic v cisle*/
int digitcounter(int number){
    int j=0;
    do {
        number /= 10;
        ++j;
    }while(number != 0);
    return j;
}
/*zjistuje co je na dane pozici za cislo, nevraci zadne informace o specificke cislici*/
int numgenerator(int pozice){
    int number = 10;
    int i = 10;

    while(i<=pozice){
        i+= digitcounter(number);
        ++number;
    }
    number -=1;
    return number;
}
/*zjistuje o kolik se musi posunout sipka aby ukazovala na spravnou pozici*/
int pointeroffset(int pozice, int number){
    int offset = 0;
    for(int i=0; numgenerator(pozice-i)>=number;i++){
        offset=i;
    }
    return offset;
}

int main(void){

    int pozice = -1;
    int soustava = -1;
    int number;
    printf("Pozice a soustava:\n");

    while(scanf("%d %d",&pozice,&soustava)==2){

    if(pozice < 0||soustava!=10){
        printf("Nespravny vstup.\n");
        return 1;
    }

/*hlavni proces pro zjisteni cisla, pozice pod 10 rovnou vraci dane cislo*/

    if(pozice<10){
        number = pozice;
    } else {
        number = numgenerator(pozice);
    }
    printf("%d\n",number);

    /*aplikace pointeroffset pro zjisteni kolik mezer je zapotrebi*/

    if (pozice <= 10) {
        printf("^\n");

    }else {
        switch (pointeroffset(pozice, number)) {
            default:
                printf("^\n");
                break;
            case 1:
                printf(" ^\n");
                break;
            case 2:
                printf("  ^\n");
                break;
            case 3:
                printf("   ^\n");
                break;
            case 4:
                printf("    ^\n");
                break;
            case 5:
                printf("     ^\n");
                break;
            case 6:
                printf("      ^\n");
                break;
            case 7:
                printf("       ^\n");
                break;
            case 8:
                printf("        ^\n");
                break;
            case 9:
                printf("         ^\n");
                break;
            case 10:
                printf("          ^\n");
                break;
            case 11:
                printf("           ^\n");
                break;
            case 12:
                printf("            ^\n");
                break;
        }
    }

    }
    if(pozice < 0||soustava!=10){
        printf("Nespravny vstup.\n");
        return 1;
    }
    return 0;
}