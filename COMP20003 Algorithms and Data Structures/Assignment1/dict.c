#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(int argc, char *argv[]){
	data_t alldata[MAXDATA];
	int n;
	data_t data;
	FILE *buildfile;
	if((buildfile=fopen(argv[1], "r"))==NULL){
		printf("No file\n");
	}  
	n = 0;
	while(fscanf(buildfile,"%d %s\n",&data.key,&data.val)==2){
		alldata[(n)++]=data;
	}
	fclose(buildfile);
	int searchkey;
	int search[MAXDATA];
	int i=0;
	while(scanf("%d\n",&searchkey)==1){
		search[i]=searchkey;
		i++;
	}
	int k,compar;	
	node *number;
	node *head;
	head=(node*)malloc(sizeof(node));
	if(NULL==head){
		return 1;
	}
	create_list(head,alldata,n);
	compar=insert_sort_list(head);
	print_list(head);
	printf(" %d\n",compar);
	for(k=0;k<i;k++){
	        searchnode(head,alldata,n,search[k]);
	}
	return 0;    
}