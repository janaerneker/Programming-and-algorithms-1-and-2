/* 
 * File:   main.c
 * Author: Jane
 *
 * Created on November 1, 2012, 2:05 PM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int main(int argc, char** argv)
{
   unsigned long long int x, rx=0, k=0, y=0;
   int ov, iterace=0;
   
   /*vstup*/
   printf("Zadejte cislo:\n");
   ov=scanf("%llu",&x);
   
   /*overeni vstupu*/
   if (ov!=1){
        printf("Nespravny vstup.\n");
        return 1;
        }
   y=x;
   
   do{
       x=y;
       rx=0;
       k=x;
       while (k != 0)
   {
      rx = rx * 10;
      rx = rx + k%10;
      k = k/10;
   }
        /*zadane jiz je palindrom*/
   
   if (rx==x){
       printf("Vypocteny palindrom: %llu (iteraci: %d)\n", x, iterace);
       break;
   } 
        /*zadane cislo neni palindrom - hledame ho*/
   
   y=x+rx;
   
   if (y<x){
       printf("Palindrom nenalezen.\n");
       break;
   }
        
        iterace++;
   } while(x!=rx);
   

 
    return (EXIT_SUCCESS);
}

