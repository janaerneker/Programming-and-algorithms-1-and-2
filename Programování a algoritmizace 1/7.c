/* 
 * File:   main.c
 * Author: Jane
 *
 * Created on December 4, 2012, 7:28 PM
 */

#include <stdio.h>
#include <stdlib.h>




void reallocate(int *priruba, int M){
    M=M+50;
    priruba=(int*)realloc(priruba, M*(sizeof(int)));
}

int load(int *priruba){
    int i=0, ov;
    
    printf("Zadejte pocty sroubu pro jednotlive priruby:\n");
    while((ov=scanf("%d", &priruba[i]))==1){
        if (priruba[i]<=0){
            printf("Nespravny vstup.\n");
            return 0;
        }
        i++;
        if(i%50==45){
            reallocate(priruba, 50);
        }
    }
    if(ov==0 || i<=1){
        printf("Nespravny vstup.\n");
        return 0;
    }
    return i;
}

int solve(int *priruba, int spodni, int horni, int **cost){
    int mincena=0, cena=0, k;
    
    if(horni-spodni>=2){
    
    for(k=spodni+1;k<horni;k++){
        if(k==0){
            k++;
        }
        if(cost[spodni][horni-1]==0 && horni-spodni>=2){
            
            solve(priruba, spodni, horni-1, cost);
        }
        if(cost[spodni+1][horni]==0 && horni-spodni>=2){
            
            solve(priruba, spodni+1, horni, cost);
            
        }
        /*vzorec*/
        
        cena=cost[spodni][k]+cost[k][horni]+(priruba[spodni]*priruba[horni]+priruba[k]);
        if(mincena==0){
            mincena=cena;
        }
        
        
        
        /*porovnavani*/
        if(cena<mincena && cena!=0){
            mincena=cena;
        }
        
    
    }
    
    cost[spodni][horni]=mincena;
 
    }else{
        return 0;
    }
    return 0;
}

/*
 * 
 */
int main(int argc, char** argv) {
    int *priruba, **cost, quantity, a;
    
    /*alokace poli*/
    cost=(int**)calloc(50, sizeof(int*));
    for(a=0;a<50;a++){
        cost[a]=(int*)calloc(50, sizeof(int));
    }
    priruba=(int*)calloc(50, sizeof(int));
    if((cost==NULL) || (priruba==NULL)){
        printf("Memory could not be allocated. The program will be terminated.\n");
        return 0;
    }
   
    
    
    /*nacteni hodnot a kontrola vstupu*/
    if ((quantity=load(priruba))==0){
        return 0;
    }
    
    
    /*rekurzivni funkce - reseni*/
    solve(priruba, 0, quantity-1, cost);
    
    /*vypsani vysledku*/
    printf("Cena: %d\n", cost[0][quantity-1]);
    
    
    
    /*uvolneni pameti*/
    for(a=0; a<50; a++){
    free(cost[a]);
    }
    free(cost);
    free(priruba);
    return (EXIT_SUCCESS);
}

