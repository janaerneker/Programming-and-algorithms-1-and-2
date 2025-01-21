/* 
 * File:   main.c
 * Author: Jane
 *
 * Created on November 3, 2012, 7:07 PM
 */
#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#endif /*__PROGTEST__*/

int clipLine(double rx1, double ry1, double rx2, double ry2, double *ax, double *ay, double *bx, double *by){
    double xmin,xmax,ymin,ymax;
    int boda=0,bodb=0;
    
    /*ohraniceni obdelnika*/
        if (rx1<=rx2){
            xmin=rx1;
            xmax=rx2;
        }else{
            xmin=rx2;
            xmax=rx1;
        }
        
         if (ry1<=ry2){
            ymin=ry1;
            ymax=ry2;
        }else{
            ymin=ry2;
            ymax=ry1;
        }
    /*kodovani krajnich bodu primky podle Cohen-Sutherlandova algoritmu*/
        if (*ax<xmin){
            boda=boda+1;
        } 
        if (*ax>xmax){
            boda=boda+2;
        } 
        if (*bx<xmin){
            bodb=bodb+1;
        } 
        if (*bx>xmax){
            bodb=bodb+2;
        } 
        if (*ay<ymin){
            boda=boda+4;
        } 
        if (*ay>ymax){
            boda=boda+8;
        } 
        if (*by<ymin){
            bodb=bodb+4;
        } 
        if (*by>ymax){
            bodb=bodb+8;
        } 
    /*primka lezi cela v obdelniku*/
        if ((boda==0)&&(bodb==0)){
            return 1;
        }
        if((boda&bodb)!=0){
            return 0;
        }
        
        /*orezavani - bod A*/
        if ((boda&1)!=0 && (*ax!=*bx)){
            *ay=((*by-*ay)*(xmin-*ax))/(*bx-*ax)+*ay;
            *ax=xmin;
            boda=boda-1;
        }
        if ((boda&2)!=0 && (*ax!=*bx)){
            *ay=((*by-*ay)*(xmax-*ax))/(*bx-*ax)+*ay;
            *ax=xmax;
            boda=boda-2;
        }
        if ((boda&4)!=0 && (*ay!=*by)){
            *ax=((*bx-*ax)*(ymin-*ay))/(*by-*ay)+*ax;
            *ay=ymin;
            boda=boda-4;
        }
        if ((boda&8)!=0 && (*ay!=*by)){
            *ax=((*bx-*ax)*(ymax-*ay))/(*by-*ay)+*ax;
            *ay=ymax;
            boda=boda-8;
        } 
        /*orezavani - bod B*/
        if ((bodb&1)!=0 && (*ax!=*bx)){
            *by=((*ay-*by)*(xmin-*bx))/(*ax-*bx)+*by;
            *bx=xmin;
            bodb=bodb-1;
        }
        if ((bodb&2)!=0 && (*ax!=*bx)){
            *by=((*ay-*by)*(xmax-*bx))/(*ax-*bx)+*by;
            *bx=xmax;
            bodb=bodb-2;
        }
        if ((bodb&4)!=0 && (*ay!=*by)){
            *bx=((*ax-*bx)*(ymin-*by))/(*ay-*by)+*bx;
            *by=ymin;
            bodb=bodb-4;
        }
        if ((bodb&8)!=0 && (*ay!=*by)){
            *bx=((*ax-*bx)*(ymax-*by))/(*ay-*by)+*bx;
            *by=ymax;
            bodb=bodb-8;
        }
        
        if((*ax<xmin)||(*ax>xmax)||(*ay<ymin)||(*ay>ymax)||(*bx<xmin)||(*bx>xmax)||(*by<ymin)||(*by>ymax)){
            return 0;
        }
return 1;
}
/*
 * 
 */
#ifndef __PROGTEST__
int main(int argc, char** argv) {
    double rx1,ry1,rx2,ry2;
    int res;
    double x1,y1,x2,y2;
    x1=0.000000;
    y1=2.000000;
    x2=-10.000000;
    y2=-11.000000;
    res=clipLine(0.000000,0.000000,4.000000,5.000000, &x1, &y1, &x2, &y2);
    printf("res=%d\nx1=%lf\ny1=%lf\nx2=%lf\ny2=%lf\n",res,x1,y1,x2,y2);
    return (EXIT_SUCCESS);
}
#endif /*__PROGTEST__*/