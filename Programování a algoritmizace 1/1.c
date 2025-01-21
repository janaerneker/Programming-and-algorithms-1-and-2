/* 
 * File:   main.c
 * Author: Jane
 *
 * Created on October 15, 2012, 9:50 PM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int main(int argc, char** argv) {
    /*deklarace promennych*/
    int ha1,ma1,ha2,ma2,hb1,mb1,hb2,mb2,hc1,mc1,hc2,mc2;
    int casa1,casa2,casb1,casb2,casc1,casc2;
    int oa1,oa2,ob1,ob2,oc1,oc2;
    int x=0,y=0,z=0;
    int casa1b=3000,casa2b=3000,casb1b=3000,casb2b=3000,casc1b=3000,casc2b=3000;
    /*ziskani hodnot od uzivatele a overeni spravnych vstupnich hodnot*/
       
    
    /*vlak A*/
    
       printf("Zadejte cas prijezdu vlaku A:\n");
       /*neplatny vstup*/
       oa1=scanf("%d:%d", &ha1, &ma1);
       if(oa1!=2 || ha1>23 || ma1>59 || ha1<0 || ma1<0)
       {
           printf("Nespravny vstup.\n");
           return 0;
       }
       
        printf("Zadejte cas odjezdu vlaku A:\n");
         /*neplatny vstup*/
       oa2=scanf("%d:%d", &ha2, &ma2);
       if(oa2!=2 || ha2>23 || ma2>59 || ha2<0 || ma2<0)
       {
           printf("Nespravny vstup.\n");
           return 0;
       }
   
     /*vlak B*/
       
       printf("Zadejte cas prijezdu vlaku B:\n");
         /*neplatny vstup*/
       ob1=scanf("%d:%d", &hb1, &mb1);
       if(ob1!=2 || hb1>23 || mb1>59 || hb1<0 || mb1<0)
       {
           printf("Nespravny vstup.\n");
           return 0;
       }
       
      
        printf("Zadejte cas odjezdu vlaku B:\n");
         /*neplatny vstup*/
       ob2=scanf("%d:%d", &hb2, &mb2);
       if(ob2!=2 || hb2>23 || mb2>59 || hb2<0 || mb2<0)
       {
           printf("Nespravny vstup.\n");
           return 0;
       }
        
     
      /*vlak C*/
       
        printf("Zadejte cas prijezdu vlaku C:\n");
         /*neplatny vstup*/
       oc1=scanf("%d:%d", &hc1, &mc1);
       if(oc1!=2 || hc1>23 || mc1>59 || hc1<0 || mc1<0)
       {
           printf("Nespravny vstup.\n");
           return 0;
       }
       
        printf("Zadejte cas odjezdu vlaku C:\n");
         /*neplatny vstup*/
       oc2=scanf("%d:%d", &hc2, &mc2);
       if(oc2!=2 || hc2>23 || mc2>59 || hc2<0 || mc2<0)
       {
           printf("Nespravny vstup.\n");
           return 0;
       }
 /*prevedeni na minuty*/
       casa1=ma1+(ha1*60);
       casa2=ma2+(ha2*60);
       casb1=mb1+(hb1*60);
       casb2=mb2+(hb2*60);
       casc1=mc1+(hc1*60);
       casc2=mc2+(hc2*60);
       
 /*prechod pulnoci:)*/
       if(casa1<180) {
       casa1b=casa1+1440;
       }
       if(casa2<180) {
       casa2b=casa2+1440;
       }
       if(casb1<180) {
       casb1b=casb1+1440;
       }
       if(casb2<180) {
       casb2b=casb2+1440;
       }
       if(casc1<180) {
       casc1b=casc1+1440;
       }
       if(casc2<180) {
       casc2b=casc2+1440;
       }
      
/*prestupovani mezi vlaky:)*/       
       
    /*prestupy z vlaku A*/
       if (((casa1+5<=casb2)&&(casb1-casa1<=180))
       || ((casa1+5<=casb2b)&&(casb1-casa1<=180)&&(casb2b<3000)) 
       || ((casa1+5<=casb2b)&&(casb1b-casa1<=180)&&(casb1b<3000)&&(casb2b<3000))
       || ((casa1b+5<=casb2b)&&(casb1-casa1b<=180)&&(casb1b<3000)&&(casc2b<3000)))
                {
           x=1;
           
                 }
              
                {
       if (((casa1+5<=casc2)&&(casc1-casa1<=180)) 
           || ((casa1+5<=casc2b)&&(casc1-casa1<=180)&&(casb2b<3000))
           || ((casa1+5<=casc2b)&&(casc1b-casa1<=180)&&(casc1b<3000)&&(casc2b<3000)) 
           || ((casa1b+5<=casc2b)&&(casc1-casa1b<=180)&&(casa1b<3000)&&(casc2b<3000)))
                {
           x=2;
           
                 }
                
       if ((((casa1+5<=casb2)&&(casb1-casa1<=180))
       || ((casa1+5<=casb2b)&&(casb1-casa1<=180)&&(casb2b<3000)) 
       || ((casa1+5<=casb2b)&&(casb1b-casa1<=180)&&(casb1b<3000)&&(casb2b<3000))
       || ((casa1b+5<=casb2b)&&(casb1-casa1b<=180)&&(casb1b<3000)&&(casc2b<3000)))
               && 
           (((casa1+5<=casc2)&&(casc1-casa1<=180)) 
           || ((casa1+5<=casc2b)&&(casc1-casa1<=180)&&(casb2b<3000))
           || ((casa1+5<=casc2b)&&(casc1b-casa1<=180)&&(casc1b<3000)&&(casc2b<3000)) 
           || ((casa1b+5<=casc2b)&&(casc1-casa1b<=180)&&(casa1b<3000)&&(casc2b<3000))))
                {
           x=3;
           
                 }
                
       switch(x){
case 0:
  printf("Z vlaku A nelze prestupovat.\n");
break;        
case 1:
  printf("Z vlaku A lze prestoupit na vlak B.\n");
break;
case 2:
  printf("Z vlaku A lze prestoupit na vlak C.\n");
break;
case 3:
  printf("Z vlaku A lze prestoupit na vlaky B a C.\n");
break;

}
       
/*prestupy z vlaku B*/
  
       if (((casb1+5<=casa2)&&(casa1-casb1<=180)) 
           || ((casb1+5<=casa2b)&&(casa1-casb1<=180)&&(casa2b<3000))
           || ((casb1+5<=casa2b)&&(casa1b-casb1<=180)&&(casa1b-casb1>=0)&&(casa1b<3000)&&(casa2b<3000)) 
           || ((casb1b+5<=casa2b)&&(casa1-casb1b<=180)&&(casa1-casb1b>=0)&&(casb1b<3000)&&(casc2b<3000)))
           {
           y=1;
                 }
                
       if (((casb1+5<=casc2)&&(casc1-casb1<=180)) 
           || ((casb1+5<=casc2b)&&(casc1-casb1<=180)&&(casc1-casb1>=0)&&(casc2b<3000)) 
           || ((casb1+5<=casc2b)&&(casc1b-casb1<=180)&&(casc1b-casb1>=0)&&(casc1b<3000)&&(casc2b<3000)) 
           || ((casb1b+5<=casc2b)&&(casc1-casb1b<=180)&&(casc1-casb1b>=0)&&(casb1b<3000)&&(casc2b<3000)))
                {
           y=2;
           
                 }
                
       if ((((casb1+5<=casa2)&&(casa1-casb1<=180)) 
           || ((casb1+5<=casa2b)&&(casa1-casb1<=180)&&(casa2b<3000))
           || ((casb1+5<=casa2b)&&(casa1b-casb1<=180)&&(casa1b-casb1>=0)&&(casa1b<3000)&&(casa2b<3000)) 
           || ((casb1b+5<=casa2b)&&(casa1-casb1b<=180)&&(casa1-casb1b>=0)&&(casb1b<3000)&&(casc2b<3000)))
               && 
               (((casb1+5<=casc2)&&(casc1-casb1<=180)) 
           || ((casb1+5<=casc2b)&&(casc1-casb1<=180)&&(casc1-casb1>=0)&&(casc2b<3000)) 
           || ((casb1+5<=casc2b)&&(casc1b-casb1<=180)&&(casc1b-casb1>=0)&&(casc1b<3000)&&(casc2b<3000)) 
           || ((casb1b+5<=casc2b)&&(casc1-casb1b<=180)&&(casc1-casb1b>=0)&&(casb1b<3000)&&(casc2b<3000))))
                {
           y=3;
           
                 }
                
       switch(y){
case 0:
  printf("Z vlaku B nelze prestupovat.\n");
break;        
case 1:
  printf("Z vlaku B lze prestoupit na vlak A.\n");
break;
case 2:
  printf("Z vlaku B lze prestoupit na vlak C.\n");
break;
case 3:
  printf("Z vlaku B lze prestoupit na vlaky A a C.\n");
break;

}
       
/*prestupy z vlaku C*/
  
       if (((casc1+5<=casa2)&&(casa1-casc1<=180))
       || ((casc1+5<=casa2b)&&(casa1-casc1<=180)&&(casa1-casc1>=0)&&(casa2b<3000))
       || ((casc1+5<=casa2b)&&(casa1b-casc1<=180)&&(casa1b-casc1>=0)&&(casa2b<3000)&&(casa1b<3000))
       || ((casc1b+5<=casa2b)&&(casa1-casc1b<=180)&&(casc1b<3000)&&(casa2b<3000)))
                {
           z=1;
           
                 }
                        
                        
       if (((casc1+5<=casb2)&&(casb1-casc1<=180)) 
        || ((casc1+5<=casb2b)&&(casb1-casc1<=180)&&(casb2b<3000))
        || ((casc1+5<=casb2b)&&(casb1b-casc1<=180)&&(casb1b<3000)&&(casb2b<3000))
        || ((casc1b+5<=casb2b)&&(casb1-casc1b<=180)&&(casc1b<3000)&&(casb2b<3000)))
                {
           z=2;
           
                 }
                
       if ((((casc1+5<=casa2)&&(casa1-casc1<=180))
       || ((casc1+5<=casa2b)&&(casa1-casc1<=180)&&(casa1-casc1>=0)&&(casa2b<3000))
       || ((casc1+5<=casa2b)&&(casa1b-casc1<=180)&&(casa1b-casc1>=0)&&(casa2b<3000)&&(casa1b<3000))
       || ((casc1b+5<=casa2b)&&(casa1-casc1b<=180)&&(casc1b<3000)&&(casa2b<3000)))
               && 
               (((casc1+5<=casb2)&&(casb1-casc1<=180)) 
        || ((casc1+5<=casb2b)&&(casb1-casc1<=180)&&(casb2b<3000))
        || ((casc1+5<=casb2b)&&(casb1b-casc1<=180)&&(casb1b<3000)&&(casb2b<3000))
        || ((casc1b+5<=casb2b)&&(casb1-casc1b<=180)&&(casc1b<3000)&&(casb2b<3000))))
                {
           z=3;
           
                 }
              
       switch(z){ 
case 0:
  printf("Z vlaku C nelze prestupovat.\n");
break;
case 1:
  printf("Z vlaku C lze prestoupit na vlak A.\n");
break;
case 2:
  printf("Z vlaku C lze prestoupit na vlak B.\n");
break;
case 3:
  printf("Z vlaku C lze prestoupit na vlaky A a B.\n");
break;
}
    return (EXIT_SUCCESS);
}
}
