/* Some parts of this program is refered to these websit: 
   http://en.literateprograms.org/index.php?
   title=Special:DownloadCode/Skip_list_(C)&oldid=18381
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "skiplist.h"

int main(int argc, char *argv[]) {
	data_t alldata[MAXDATA];
	int i,l,k;
	int n;
	int c=0;
	data_t data;
	/* open a buildfile */
	FILE *buildfile;
	if((buildfile=fopen(argv[1], "r"))==NULL){
		printf("No file\n");
	}  
	n = 0;
	while(fscanf(buildfile,"%d %s\n",&data.key,data.val)==2){
		alldata[(n)++]=data;
	}
	fclose(buildfile);
	
	int searchkey;
	int search[MAXDATA];
	int m=0;
	while(scanf("%d\n",&searchkey)==1){
		search[m]=searchkey;
		m++;
	}	
	SkipSet* set = make_skipset();    
     	for(i=0;i<n;i++){
     		c+=insert(set, alldata[i].key);
     	}
     	printf("%d Insertions %d\n",n,c);
     	for(l=0;l<m;l++){
     		if(search_key(set, search[l])) {
     			printf("%d ",search[l]);
     			for(k=0;k<n;k++){
     				if(search[l]==alldata[k].key){   	     	     
     					printf("%s %d\n",alldata[k].val,l);
     				}
     			}
     		}
     		else{
     			printf("%d NOTFOUND %d\n",search[l],l);
     		}
     	} 
     	return 0;
}
