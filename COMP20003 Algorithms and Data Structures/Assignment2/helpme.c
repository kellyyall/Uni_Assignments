//COMP20003 ASSIGNMENT 2, WRITTEN BY KELLY YANG, NO.566123
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING           1000 
#define MAX_VERTEX_NUMBER    1000                        
#define MAX_EDGE_NUMBER      1000                           
#define LARGE_NUMBER         1000000 
#define SMALLER_NUMBER       100000
                           
#define FALSE                0
#define TRUE                 1

                         
typedef struct _vertex {                        
    int id;
    struct _vertex *linklist[MAX_EDGE_NUMBER];    
    int Length[MAX_VERTEX_NUMBER];                    
    struct _vertex **next;                        
    int *minlength;        
}vertex;

typedef struct _node {                           
    int ID;
    struct _vertex *node;
    char name[MAX_STRING];
    char source_name[MAX_STRING];
}node;

int Dijkstra_Alg(node array[],int total_number);
	
int main(int argc, char *argv[]){
	int total_number;  
	
	node array[MAX_VERTEX_NUMBER];
	char enter_city[MAX_STRING];
	char enter_source[MAX_STRING];
	int shortestpath;	
	char buf[MAX_STRING];
	char *pos;
	int length;
	int i,n,m;
	int cityid;
	int tocityid;
	int linkpos;
	
	char *token;
	char *token1;
	
	int len=0;
	int ncity;
	
	int cityn;
	int nan;
	int sname;
	int number_city;
	
	char str[MAX_STRING];
	char connect[MAX_STRING];
	char connectpair[MAX_STRING];
	
	int realshort=SMALLER_NUMBER;
	int realstart;
	/* open a file*/
	FILE *file;
	if((file=fopen(argv[1], "r"))==NULL){
		printf("No file\n");
	}  
	/*just get the first cityid and set the memory for them*/
	while(NULL != fgets(buf, MAX_STRING, file)) {
		pos = strtok(buf, "|");
		cityid = atoi(pos);
		if(cityid < MAX_VERTEX_NUMBER) {
			array[cityid].ID = cityid;
			array[cityid].node = (vertex*)malloc(sizeof(vertex));
			memset(array[cityid].node, 0, sizeof(vertex));
			array[cityid].node->id = cityid;           
		}
	}
	/*'reopen' the file and read every details*/
	rewind(file);
	fscanf(file, "%d", &total_number);
	
    while(fscanf(file, "%s",str)!=EOF){
        /*read a new line, get rid of the | */
        token = strtok(str, "|");
       	i=0;
      	linkpos = 0; //use this to check how many edges each vertax has.
      	//start getting cityid,cityname,resource names.
       	while(token!= NULL){
       		if(i==0){
        		cityid=atoi(token);
       	 	}
       	 	if(i==1){
       	 		strcpy(array[cityid].name,token);
         	}
          	if(i==2){
       	 		strcpy(array[cityid].source_name,token);
       	 	}
       	 	//the fourth part contains the pairs, I got rid of the ','
       	 	//and use sscanf to 'rescan' each pair.
         	if(i==3){
         		strcpy(connect,token);
       	 		if(connect!=NULL){
        	 		token1=strtok(connect,",");
         	 		while(token1!=NULL){
         	 			strcpy(connectpair,token1);
       					sscanf(connectpair,"%d:%d",&tocityid,&length);   				
         	 			//set minmum length and the next node to NULL for further use.
         	 			array[tocityid].node->minlength = NULL;
         	 			array[cityid].node->next = NULL;
         	 			// I use linklist, link from one city to another
       					// and set the edges' length.
          				array[cityid].node->linklist[linkpos] = array[tocityid].node;
         	 			array[cityid].node->Length[tocityid] = length;
         	 			linkpos++;
         	 			token1 = strtok(NULL, ",");
         	 		}
         		}
       	 	}
       	 	i++;
       	 	token = strtok(NULL, "|");
       	}
    }
    // throw my array list to the main algorithm.
    Dijkstra_Alg(array,total_number);
       
    //start getting information.
    printf("Type your city please:");
	scanf("%s",&enter_city);
	
	//check each char in that city if/ifnot match the city in the file
	//need to check the length is the same as the city in the file as well
	//then we can say they are the same city.
	for(n=0;n<total_number;n++){
		for(m=0;m<strlen(array[n].name);m++){
			if(array[n].name[m]==enter_city[m]){
				len++;
			} 
		}
		if(len==strlen(enter_city)){
			ncity=n;
		}		
		len=0;			
	}
	//if the city name is wrong, close the program.
	if(ncity>SMALLER_NUMBER){
		printf("can't find the city\n");
		return 0;
	}	
	number_city=ncity;
	
	printf("\nType what you need:");	
	scanf("%s",&enter_source);
	   
	// check each enter_source one by one
	for(nan=0;nan<strlen(enter_source);nan++){
		ncity=number_city;
		realshort=LARGE_NUMBER;
		//just check all the cities in the file which has a source name
		//and compare their path, choose the shortest one to print.
		for(cityn=0;cityn<total_number;cityn++){
			for(sname=0;sname<strlen(array[cityn].source_name);sname++){
					vertex *temp = array[cityn].node;
	                shortestpath=temp->minlength[ncity];
	                //if the city already have the resource,
	                //it doesn't count.
	                if(shortestpath<realshort && shortestpath!=0){
	                    realshort=shortestpath;
	                    realstart=cityn;
	                }
	        }
	    }
	}
	//if the path is really large, means we can't get there
	if(realshort>SMALLER_NUMBER){
	    if(enter_source[nan]=='M'){
	        printf("sorry, can't get any medicine.\n\n");
	    }else if(enter_source[nan]=='B'){
	        printf("sorry, can't get any blankets.\n\n");
	    }else if(enter_source[nan]=='F'){
	        printf("sorry, can't get any food.\n\n");
	    }else if(enter_source[nan]=='W'){
	        printf("sorry, can't get any water.\n\n");
	    }else if(enter_source[nan]=='D'){
	        printf("sorry, can't get any digging equipments.\n\n");
	    }
	}else{
	    printf("%c   ",enter_source[nan]);
	    printf("%d    %s           %d hrs\n",realstart,array[realstart].name,realshort);
	    printf("        %d{%s)",ncity,enter_city);
	    //In the Dijkstra function, I store the 'route' backward
	    //so I print it backward, adding an arrow make it readable
		while(array[realstart].node->next[ncity]->id != realstart){
			ncity = array[realstart].node->next[ncity]->id;
	        printf("  <--- %d(%s)",ncity,array[ncity].name);
	    }
	        printf("  <--- %d(%s)",realstart,array[realstart].name);
	        printf("\n\n");                    
	}
	return 0;
}

// Using Dijkstra Algorithm find the shortest path and the route, put them in an array/linklist
int Dijkstra_Alg(node array[],int total_number){
	int i, j;
	vertex *start, *temp, *temp1;
	int *roadlength;
	int *checked;
	int cityidtemp;
	int mixcost = LARGE_NUMBER;
	
	roadlength = (int*)malloc(total_number * sizeof(int));
	checked = (int*)malloc(total_number * sizeof(int));
	
	for(i=0; array[i].node!=0; i++) {
		//set the length from all the other numbers to the starting point is 'infinite' 
		for(j=0; j<total_number; j++) {
			roadlength[j] = LARGE_NUMBER;
			checked[j] = 0;
		}
		start = array[i].node;
		start->next = (vertex**)malloc(total_number * sizeof(vertex*));
		start->minlength = (int*)malloc(total_number * sizeof(int));
		roadlength[i] = 0;
		checked[i] = 1;
		start->minlength[i] = 0;
		temp = start;

        while(1){
        	for(j=0; temp->linklist[j]!=0; j++) {
        		temp1 = temp->linklist[j];
        		//from the stating point to its next point
        		//update all the shortest edge length
        		if(roadlength[temp1->id] > roadlength[temp->id] + temp->Length[temp1->id] && checked[temp1->id] == 0) {
        			roadlength[temp1->id] = roadlength[temp->id] + temp->Length[temp1->id]; 
        			start->next[temp1->id] = temp;//recording the 'route'
                }
            }           
            mixcost = LARGE_NUMBER;
            //find the shortest path from one point to another after update
            for(j=0; j<total_number; j++) {
                if(checked[array[j].ID] != 1 && roadlength[array[j].ID] < mixcost && roadlength[array[j].ID] != 0) {               	
                	mixcost = roadlength[array[j].ID];
                	cityidtemp = array[j].ID;
                }
            }
            if(mixcost == LARGE_NUMBER) {
             	break;
            }
            //reset the current point
            temp = array[cityidtemp].node;
            start->minlength[cityidtemp] = mixcost;
            //this point has been checked, already know the shortest path,now the next one
            checked[cityidtemp] = 1;           
       	}
    }    
    //FREE
    free(checked);
    free(roadlength);
    return 1;
}