/* COMP20005 Engineering Computation - Assignment 2
   Written by Kelly Yang*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>

#define MAXDATA 100
#define Data_per_line 3
#define Tower_height 8.25
#define pi 3.1415926
#define points 5929

typedef struct {
	double x, y, l;
}data_t;

typedef struct {
	double x,y;
}location_t;

void read_data(data_t allpoles[], int* npoles, location_t all_location[],int* nlocation);

double cal_illuminance(double x, double y, double l);
double cal_illuminance_location(double xl, double yl, double x, double y, double l);
double cal_percent(double unacc_p);

void stage_one(data_t allpoles[], int npoles);
void stage_two(data_t allpoles[], int npoles, location_t all_location[],int nlocation);
void stage_three(data_t allpoles[], int npoles);



int main(int argc, char **argv){
	data_t allpoles[MAXDATA];
	location_t all_location[MAXDATA];
	int npoles;
	int nlocation;
	read_data(allpoles, &npoles, all_location,&nlocation);
	if(npoles<1){
		printf("Need more than one input line\n");
		exit(EXIT_FAILURE);
	}
	stage_one(allpoles, npoles);
	stage_two(allpoles, npoles, all_location, nlocation);
	stage_three(allpoles, npoles);
	return 0;
}

/* read all the input data into array */
void read_data(data_t allpoles[], int* npoles, location_t all_location[],int* nlocation){
	data_t pole;
	location_t location;
	int head_letter;
	*npoles = 0;
	*nlocation=0;

	while((head_letter=getchar())!=EOF){
		if(head_letter == 'P'){
			while(scanf("%lf %lf %lf\n",&pole.x,&pole.y,&pole.l)== Data_per_line){			
				if(*npoles==100){
					printf("Too much input data\n");
					exit(EXIT_FAILURE);
				}                       
				allpoles[(*npoles)++]=pole;
			}			 
		}
		
		if(head_letter == 'L'){
			scanf("%lf %lf\n",&location.x,&location.y);
			if(*nlocation==100){
				printf("Too much input data\n");
				exit(EXIT_FAILURE);
			}
			all_location[(*nlocation)++]=location;
		}
	}
}	 

void stage_one(data_t allpoles[], int npoles){
	double illuminance; double total_illuminance=0;
	int i;
	
	for(i=0;i<npoles;i++){
		illuminance = cal_illuminance(allpoles[i].x, allpoles[i].y, allpoles[i].l);
		total_illuminance += illuminance;
	}
	/* now the output*/
	printf("Stage 1\n=========\n");
	printf("Number of light poles: %d\n", npoles);
	printf("Illuminance at ( 0.0, 0.0): %.2f lux\n\n",total_illuminance);
}

void stage_two(data_t allpoles[], int npoles, location_t all_location[],int nlocation){
    int r, k;
    double illuminance_location;
    double total_illuminance_location=0;
    int line_L=1;
    for(r=0;r<nlocation;r++){
        for(k=0;k<npoles;k++){
          	illuminance_location= cal_illuminance_location(all_location[r].x,all_location[r].y, allpoles[k].x,allpoles[k].y,allpoles[k].l);
          	total_illuminance_location+=illuminance_location;
          	}
          	if((illuminance_location) && (line_L==1)){
          	  	printf("Stage 2\n=========\n");	  
          	}
          	printf("Illuminance at (%.1f,%.1f): %.2f lux\n", all_location[r].x,all_location[r].y, total_illuminance_location);
          	total_illuminance_location=0;
          	line_L=0;
        }
        printf("\n");
}

void stage_three(data_t allpoles[], int npoles){
	int i;
    double x_point, y_point;
    double percent;
    double unaccepetable_point=0;
    double stage3_lux, total_stage3_lux=0;
    for((x_point)=1;(x_point)<78;(x_point)++){
        for((y_point)=1;(y_point)<78;(y_point)++){
     	  	for(i=0;i<npoles;i++){
       	  		stage3_lux = cal_illuminance_location(allpoles[i].x,allpoles[i].y, x_point,y_point,allpoles[i].l);
          	  	total_stage3_lux+=stage3_lux;
          	}
            if(total_stage3_lux<1.0){
            	unaccepetable_point+=1;
          		}
          	    total_stage3_lux=0;
        }
    }
    percent = cal_percent(unaccepetable_point);
    printf("Stage 3\n=========\n");
    printf("With %d poles in use and 5929 points sampled, %.0f point\n", npoles, unaccepetable_point);
    printf("(%.1f%%) have illuminance below the 1.0 lux acceptable level.", percent);
    printf("\n");
}

double cal_illuminance(double x, double y, double l){	
	return l/((pow(x,2)+pow(y,2)+pow(Tower_height,2))*4.0*pi);
}

double cal_illuminance_location(double xl, double yl, double x, double y, double l){
	double ill_location;
	double base;
	base=(pow((xl-x),2)+pow((yl-y),2)+pow(Tower_height,2))*4.0*pi;
	ill_location = l/base;
	return ill_location;
}

double cal_percent(double unacc_p){
	return (unacc_p*100.0)/(points);
}
