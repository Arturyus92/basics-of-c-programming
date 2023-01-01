#include <stdio.h>
#include <unistd.h>
//#include <string.h>
#include <stdlib.h>
#include "temp_functions.h"

extern struct temperature month[13];

int main(int argc, char *argv[]) {

    int a, rez=0, months;
    int y,m,d,h,mi;
    float t, year[3];
    FILE *f;
    opterr=0;
    while((rez=getopt(argc,argv,"hf:ym:"))!=-1){
        switch(rez){

            case 'h':
                printf("This is the list directory:\n");
                printf("-h This help text\n-f Specify the file\n-y Statistics for the year\n-m Statistics for the specified month.\n");
                break;

            case 'f': 
                f = fopen(optarg, "r");
                while( (a = (fscanf(f, "%d;%d;%d;%d;%d;%f",&y,&m,&d,&h,&mi,&t)))!= EOF) {
                    if(a != 6){
                        char error[100] = {0};
                        fscanf(f,"%[^\n]",error);
                        printf("Error string: %s\n",error);
                    } 
                    else if((t < -99.0)||(t > 99.0)){
                        printf("Incorrect temperature %d.%d.%d %d hour %d min: %.1f grad\n",d,m,y,h,mi,t);
                    }
                    else {
                        month[m].sum += t;
                        month[m].count++;
                        
                        // тут логика поиска максимумов и минимумов по месяцам
                    
                        if((month[m].max.t < t)||(month[m].count==1)){
                            month[m].max.t = t;
                            month[m].max.day = d;
                            month[m].max.month = m;
                            month[m].max.hour = h;
                            month[m].max.minut = mi;
                        }
                        if((month[m].min.t > t)||(month[m].count==1)){
                            month[m].min.t = t;
                            month[m].min.day = d;
                            month[m].min.month = m;
                            month[m].min.hour = h;
                            month[m].min.minut = mi;
                        }
                    }
                }

                statistics_year(year);
                fclose(f);
                break;

            case 'y': 
                printf("Min_year=%.1f, max_year=%.1f, mean_year=%.1f.\n", year[0],year[1],year[2]);
                break;

            case 'm': 
                months = atoi(optarg);
                printf("Month %d: mean =%.1f, min = %.1f, max=%.1f.\n",months,mean_temp_month(month[months].sum, month[months].count),month[months].min.t,month[months].max.t);
                break;

            case '?':printf("Error found !\n"); break;
        };
    };
    return 0;
}