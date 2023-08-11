/*Programa que simula um jogo de criação de peixes, com várias funcionalidade
    Instruções:

    (:) Pedra: caso peixe se mova para pedra ele morre;
    (y) Alga broto;
    (Y) Alga crescida
    (@) Concha;
    (-) Larva;
    (x) Peixe jovem
    (X) Peixe adulto;

    Cultivar: Planta uma algo caso tenha saldo de alga;
    Fertilizar: Cresce uma alga caso tenha saldo de sais;
    Mover: Move peixes ou larvas, diferentes interações ocorrem dependendo de para onde se mover;
    Quebrar: Quebra conchas para gerar saldo de recursos aleatórios;
    Pescar: Pesca um peixe para gerar saldo de sais e larvas (caso adulto);
    Noite: Faz peixes e algas crescerem e uma chance de gerar concha;
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int larva=0;
int alga=1;
int sais=1;
int jogadas=1;
char tanque[25][50];
//imprime matriz tanque na tela
void imprime(){
    int i, j;
    printf("\n    00000000001111111111222222222233333333334444444444\n");
    printf("    01234567890123456789012345678901234567890123456789\n");
    for(i=0;i<25;i++){
        printf("[%2d]", i);
        for(j=0;j<50;j++){
            printf("%c", tanque[i][j]);
        }
        printf("\n");
    }

}
//inicializa tanque com varios simbolos
void inicializa(){
    int i, j, lin, col;
    //espaço
    for(i=0;i<25;i++){
        for(j=0;j<50;j++){
            tanque[i][j]=' ';
        }
    }
    //3 triangulos 1-3
    for(i=0;i<3;i++){
        lin=rand()%(25-1);
        col=rand()%(50-2);
        tanque[lin][col+1]=':';
        tanque[lin+1][col]=':';
        tanque[lin+1][col+1]=':';
        tanque[lin+1][col+2]=':';
    }
    //2 triangulos 1-3-5
    for(i=0;i<2;i++){
        lin=rand()%(25-2);
        col=rand()%(50-4);
        tanque[lin][col+2]=':';
        tanque[lin+1][col+1]=':';
        tanque[lin+1][col+2]=':';
        tanque[lin+1][col+3]=':';
        tanque[lin+2][col]=':';
        tanque[lin+2][col+1]=':';
        tanque[lin+2][col+2]=':';
        tanque[lin+2][col+3]=':';
        tanque[lin+2][col+4]=':';
    }
    //10 conchas
    for(i=0;i<10;i){
        lin=rand()%((25-2)+1);
        col=rand()%((50-2)+1);
        if(tanque[lin][col]==' '){
            tanque[lin][col]='@';
            i++;
        }
    }
    //5 brotos de alga
    for(i=0;i<5;i){
        lin=rand()%25;
        col=rand()%50;
        if(tanque[lin][col]==' '){
            tanque[lin][col]='y';
            i++;
        }
    }
    //peixe jovem
    for(i=0;i<3;i){
        lin=rand()%25;
        col=rand()%50;
        if(tanque[lin][col]==' '){
            tanque[lin][col]='x';
            i++;
        }
    }
}
//cultivar
void cultivar(){
    int lin, col;
    if(alga>0){
        printf("cultivar alga [linha] [coluna]: ");
        scanf("%d %d", &lin, &col);
        getchar();//capturar o enter
        if((lin>=0)&&(lin<=24)&&(col>=0)&&(lin<=49)){
            if(tanque[lin][col]==' '){
                tanque[lin][col]='y';
                alga--;
                jogadas++;
            }else{
                printf("coordenadas nao esta vazia");
            }
        }else{
            printf("coordenadas invalidas");
        }
    }else{
        printf("sem saldo de alga\n");
    }
}
//fertilizar
void fertilizar(){
     int lin, col;
    if(sais>0){
        printf("fertilizar alga [linha] [coluna]: ");
        scanf("%d %d", &lin, &col);
        getchar();//capturar o enter
        if((lin>=0)&&(lin<=24)&&(col>=0)&&(lin<=49)){
            if(tanque[lin][col]=='y'){
                tanque[lin][col]='Y';
                sais--;
                jogadas++;
            }else{
                printf("coordenadas sem broto de alga");
            }
        }else{
            printf("coordenadas invalidas");
        }
    }else{
        printf("sem saldo de sais\n");
    }
}
//mover
void mover(){
    int l1, c1, l2, c2;
    printf("Coordenada de origem [linha coluna]: ");
    scanf("%d %d", &l1, &c1);
    getchar();//captura enter
    if((l1>=0)&&(l1<=24)&&(c1>=0)&&(c1<=49)){
        if((tanque[l1][c1]=='-')||(tanque[l1][c1]=='x')||(tanque[l1][c1]=='X')){
            printf("Coordenada de destino [linha coluna]: ");
            scanf("%d %d", &l2, &c2);
            getchar();//captura enter
            if((l2>=0)&&(l2<=24)&&(c2>=0)&&(c2<=49)){
                if((l2-l1>=-1)&&(l2-l1<=1)&&(c2-c1>=-1)&&(c2-c1<=1)){//vizinho
                    if(tanque[l2][c2]==' '){//move
                        tanque[l2][c2]=tanque[l1][c1];
                        tanque[l1][c1]=' ';
                        jogadas++;
                    }
                    if((tanque[l2][c2]==':')||(tanque[l2][c2]=='@')){//morre
                        tanque[l1][c1]=' ';
                        jogadas++;
                    }
                    if((tanque[l1][c1]=='X')&&(tanque[l2][c2]=='x')){//reproduz
                        if(larva>0){
                            tanque[l1][c1]='-';
                            larva--;
                            jogadas++;
                        }else{
                            printf("Sem saldo de larvas\n");
                        }
                    }
                    if((tanque[l2][c2]=='y')||(tanque[l2][c2]=='Y')){//evolui
                        if(tanque[l1][c1]=='-'){
                            tanque[l2][c2]='x';
                            tanque[l1][c1]=' ';
                            jogadas++;
                        }
                        if(tanque[l1][c1]=='x'){
                            tanque[l2][c2]='X';
                            tanque[l1][c1]=' ';
                            jogadas++;
                        }
                        if(tanque[l1][c1]=='X'){
                            tanque[l2][c2]='X';
                            tanque[l1][c1]=' ';
                            jogadas++;
                        }
                    }
                }else{
                    printf("Desitino nao eh vizinho\n");
                }
            }else{
                printf("Coordenadas destino invalidas\n");
            }
        }else{
        printf("Coordenadas origem invalidas\n");
        }
    }else{
        printf("Coordenadas invalidas\n");
    }
}
//quebrar
void quebrar(){
    int lin, col;
    printf("quebrar concha [linha] [coluna]: ");
    scanf("%d %d", &lin, &col);
    getchar();//capturar o enter
    if((lin>=0)&&(lin<=24)&&(col>=0)&&(lin<=49)){
        if(tanque[lin][col]=='@'){
            tanque[lin][col]=' ';
            if(rand()%100<25){sais++;}
            if(rand()%100<25){larva++;}
            if(rand()%100<25){alga++;}
            if(rand()%100<10){sais+=2;}
            if(rand()%100<10){larva+=2;}
            if(rand()%100<5){alga+=2;}
            jogadas++;
        }else{
            printf("coordenada nao tem concha");
        }
    }else{
        printf("coordenadas invalidas");
    }
}
//pescar
void pescar(){
    int lin, col;
    printf("pescar peixe [linha] [coluna]: ");
    scanf("%d %d", &lin, &col);
    getchar();//capturar o enter
    if((lin>=0)&&(lin<=24)&&(col>=0)&&(lin<=49)){
        if(tanque[lin][col]=='x'){
            tanque[lin][col]=' ';
            sais++;
            jogadas++;
        }
        if(tanque[lin][col]=='X'){
            tanque[lin][col]=' ';
            sais+=2;
            larva++;
            jogadas++;
        }
    }else{
        printf("coordenadas invalidas");
    }
}
//noite
void noite(){
    int i,j;
    jogadas=1;
    for(i=0;i<25;i++){
        for(j=0;j<50;j++){
            if((tanque[i][j]=='-')&&(rand()%100<30)){
                tanque[i][j]='x';
            }
            if((tanque[i][j]=='y')&&(rand()%100<50)){
                tanque[i][j]='Y';
            }
            if((i!=0)&&(i!=24)&&(j!=0)&&(j!=49)&&(tanque[i][j]==' ')&&(rand()%1250==0)){
                tanque[i][j]='@';
            }
            if(tanque[i][j]=='@'){
                tanque[i-1][j-1]=' ';
                tanque[i-1][j]=' ';
                tanque[i-1][j+1]=' ';
                tanque[i][j-1]=' ';
                tanque[i][j+1]=' ';
                tanque[i+1][j-1]=' ';
                tanque[i+1][j]=' ';
                tanque[i+1][j+1]=' ';
            }
        }
    }
}
int main( int argc, char * argv[]){
    char op=' ';
    srand(time(NULL));
    //função inicializa
    inicializa();
    while(op != 's'){
        //funcao imprime
        imprime();
        printf("larva=%d alga=%d sais=%d\n", larva, alga, sais);
        printf("(c)ultivar / (f)ertilizar / (m)over / (q)uebrar / (p)escar / (n)oite / (s)air\n");
        printf("[Jogada %d] opcao: ", jogadas);
        op = getchar();
        switch(op){
            case 'c' :
                cultivar(); //cultivar
                break;
            case 'f' : //fertilizar
                fertilizar();
                break;
            case 'm' : //mover
                mover();
                break;
            case 'q' : //quebrar
                quebrar();
                break;
            case 'p' : //pescar
                pescar();
                break;
            case 'n' : //noite
                noite();
                break;
            case 's' :
                break;
            default:
                printf("[opcao invalida]\n");
        }
        if(jogadas > 7){
            imprime();
            noite();
        }
    }
    return 0;
}
