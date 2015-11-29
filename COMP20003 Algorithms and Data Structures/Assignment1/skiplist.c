/* Some parts of this program is refered to these websit: 
   http://en.literateprograms.org/index.php?
   title=Special:DownloadCode/Skip_list_(C)&oldid=18381
*/
   
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
 
#define P 0.5
#define MAX_LEVEL 10
#define MAXDATA 256
 
struct sn{
     int value;
     struct sn ** forward; 
};
typedef struct sn SkipNode;

typedef struct{
	SkipNode* header;
	int level;
}SkipSet;

typedef struct{
	int key;
	char val[MAXDATA];
}data_t;

float frand();
int random_level();
SkipNode* make_node(int level,int value);
SkipSet* make_skipset();
int insert(SkipSet* set, int value);
int seaerch_key(SkipSet* set, int searchkey);
 
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
	while(fscanf(buildfile,"%d %s\n",&data.key,&data.val)==2){
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
 
float frand(){
	return (float) rand() / RAND_MAX;
}

int random_level(){
	static int first = 1;
	int lvl = 0;
    	if(first){
    		srand( (unsigned)time( NULL ) );
    		first = 0;
    	}
    	while(frand() < P && lvl < MAX_LEVEL){
    		lvl++;
    	}
	return lvl;
} 

SkipNode* make_node(int level,int value){
	SkipNode* sn = (SkipNode*)malloc(sizeof(SkipNode));
	sn->forward = (SkipNode**)calloc(level + 1, sizeof(SkipNode *));
	sn->value = value;
	return sn;
}

SkipSet* make_skipset(){
	SkipSet* set=(SkipSet*)malloc(sizeof(SkipSet));
	set->header = make_node(MAX_LEVEL, 0);
	set->level = 0;
	return set;
}

/* insert the keys and print out the number of comparisons in insertion.*/
int insert(SkipSet* set, int value) {
	int i;
	int compar=0;
	SkipNode* x = set->header;	
	SkipNode* update[MAX_LEVEL + 1];
	memset(update, 0, MAX_LEVEL + 1);
	for(i =set->level; i >= 0; i--) {
		while(x->forward[i] != NULL && x->forward[i]->value < value) {
			x = x->forward[i];
			
		}
		update[i] = x; 
	}
	x = x->forward[0];
	if(x == NULL || x->value != value) {        
		int lvl = random_level() ;
		if(lvl > set->level) {
			for(i = set->level + 1; i <= lvl; i++) {
				update[i] = set->header;
			}
			set->level = lvl;
		}
		x = make_node(lvl, value);
		for(i = 0; i <= lvl; i++) {
			x->forward[i] = update[i]->forward[i];
			update[i]->forward[i] = x;
		}compar++;
	}
	return compar;
}

int search_key(SkipSet* set, int searchkey) {
	int i;
	SkipNode* x = set->header;
	for(i = set->level; i >= 0; i--) {
		while(x->forward[i] != NULL && x->forward[i]->value<searchkey){
			x = x->forward[i];
		}
	}
	x = x->forward[0];
	if(x != NULL && x->value == searchkey){
        return 1;
        }
        return 0;   
}
