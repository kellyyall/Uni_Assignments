#define P 0.5
#define MAX_LEVEL 10
#define MAXDATA 256
 
struct sn{
     int value;
     struct sn ** forward; /* pointer to array of pointers */
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
int search_key(SkipSet* set, int searchkey);