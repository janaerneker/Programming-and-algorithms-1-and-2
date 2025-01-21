/* 
 * File:   main.c
 * Author: Jane
 *
 * Created on November 24, 2012, 6:31 PM
 */

#include <stdio.h>
#include <stdlib.h>
/*
 * 
 */
 int main(int argc, char** argv) {
    int sa, sb, i, j, m, y, z, kmax, vm, *pa, *pb, *vysl; 
    
    
    printf("Zadejte stupen polynomu A:\n");
    if((scanf("%d", &sa)!=1) || (sa<0)){
        printf("Nespravny vstup.\n");
        return 0;
    }
    
    pa = (int*)calloc((sa+2), sizeof (int));
    if (pa == NULL){
        printf("Pamet se nepodarilo alokovat, program bude ukoncen.\n");
        return 0;
    } 
      
    printf("Zadejte koeficienty polynomu A:\n");
       
    for(i=0;i<(sa+1);i++){
        if(scanf("%d", &pa[i]) != 1){
            printf("Nespravny vstup.\n");
            return 0;
        }
    }
    
    printf("Zadejte stupen polynomu B:\n");
    if((scanf("%d", &sb) != 1) || (sb<0)){
        printf("Nespravny vstup.\n");
        return 0;
    }
    
    pb =(int*)calloc ((sb+2), sizeof(int));
    if (pb == NULL){
        printf("Pamet se nepodarilo alokovat, program bude ukoncen.\n");
        return 0;
    }

    printf("Zadejte koeficienty polynomu B:\n");
    
    for(j=0;j<(sb+1);j++){
        if(scanf("%d", &pb[j]) != 1){
            printf("Nespravny vstup.\n");
            return 0;
        }
    }
    
    kmax=(sa+1)+(sb+1);
    
    vysl =(int*)calloc((kmax+1), sizeof (int));
    if (vysl == NULL){
         printf("Pamet se nepodarilo alokovat, program bude ukoncen.\n");
        return 0;
        }
     
    
     
        for (y=0;y<=(sa+1);++y)
        {
                for (z=0;z<=(sb+1);++z)
                {
                vysl[y+z]+=pa[y]*pb[z];
                }
        }
      
      
      free(pa);
      free(pb);
      
      vm=(sa+sb);
      if(vm>1){
      switch(vysl[0]){
          case 0:break;
          case 1:printf("x<sup>%d</sup>", vm);break;
          case -1:printf("-x<sup>%d</sup>", vm);break;
          default:printf("%dx<sup>%d</sup>", vysl[0], vm);
      }
       if((vysl[0]!=0) && (vysl[1]>0)){
              printf("+");
          } 
      }
      for(m=1;m<(vm-1);m++){
     
      switch(vysl[m]){
          case 0:break;
          case 1:printf("x<sup>%d</sup>", (vm-m));break;
          case -1:printf("-x<sup>%d</sup>", (vm-m));break;
          default:printf("%dx<sup>%d</sup>", vysl[m], (vm-m));
      }
          if(vysl[m+1]>0){
              printf("+");
          }
      }
      /*exponent s hodnotou jedna */
      if(vm>0){
      switch(vysl[vm-1]){
          case 0:break;
          case 1:printf("x");break;
          case -1:printf("-x");break;
          default:printf("%dx", vysl[vm-1]);
      }
      }
      if((vysl[vm]>0) && (vm>0)){
              printf("+");
          }
      
      /*vypsat posledni clen*/ 
      if((vm==0) && (vysl[vm]==0)){
          printf("0\n");
      }else{
      switch(vysl[vm]){
          case 0:printf("\n");break;
          default:printf("%d\n", vysl[vm]);
      }
      }
     
      free(vysl);
    
    return (EXIT_SUCCESS);
}

