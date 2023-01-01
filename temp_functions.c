#include "temp_functions.h"

struct temperature month[13] = {0};

float mean_temp_month(float sum, int count){
    return sum/(count*1.0);
}

void statistics_year(float x[]){
    x[0]=1000.0;
    x[1]=-1000.0;
    x[2]=0.0;
    for(int i=1;i<13;i++){
        if(month[i].min.t<x[0]){x[0]=month[i].min.t;}
        if(month[i].max.t>x[1]){x[1]=month[i].max.t;}
        x[2]+=mean_temp_month(month[i].sum, month[i].count);

    }
    x[2] = x[2]/12;
}