/* 
 * File:   main.c
 * Author: Jane
 *
 * Created on November 12, 2012, 5:57 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>



/*
 * 
 */
int main(int argc, char** argv) {
    int n, i, ov, ov1, h, m, l=0, m2, h2, k, s=0;
    unsigned int puv[21], in[21], fr[21], nsd, nsn, r, u, v;
    in[0]=1;
    printf("Zadejte pocet vlaku:\n");
    ov=scanf("%d",&n);
    
    if((ov!=1)||(n<1)||(n>20)){
        printf("Nespravny vstup.\n");
        return 0;
    } 
    
    for(i=1;i<=n;i++){
        printf("Interval vlaku %d:\n" , i);
        ov1=scanf("%d:%d", &h,&m);
        
        if((ov1!=2)||(h<0)||(m<0)||(m>59)||((h==0) && (m==0))){
        printf("Nespravny vstup.\n");
        return 0;
    } 
        puv[i]=in[i]=h*60+m; 
    }
    
    do{ 
    
        if (in[l] > (UINT_MAX / in[l+1])){
        printf("Vysledek mimo rozsah datoveho typu.\n");
        return 0;
        }
        
        if(in[l]>=in[l+1]){
            u=in[l];
            v=in[l+1];
        }else{
            v=in[l];
            u=in[l+1];
        }
        do{
            r=u%v;
            u=v;
            v=r;               
           }while(v!=0);
    nsd=u;
    in[l+1]=(in[l]*in[l+1])/nsd;
    nsn=in[l+1];
    l++;
    } while (l<n);
    
    m2=nsn%60;
    h2=(nsn-nsn%60)/60;
    if(m2==0){
        s=1;
    }
    switch(s){
        case 0:printf("Vsechny vlaky se potkaji za: %d:%d\nMezitim projede:\n",h2,m2);
        break;
        case 1:printf("Vsechny vlaky se potkaji za: %d:%d%d\nMezitim projede:\n",h2,m2,m2);
        break;
    }
    for(k=1;k<=n;k++){
        
        fr[k]=nsn/puv[k]-1;
      if(k<n-1){
        printf("* vlak %d: %dx,\n" , k, fr[k]);
        }
      if(k==n-1){
         printf("* vlak %d: %dx a\n" , k, fr[k]);
      }
      if(k==n){
         printf("* vlak %d: %dx.\n" , k, fr[k]);
      }
    }
    return (EXIT_SUCCESS);
}

