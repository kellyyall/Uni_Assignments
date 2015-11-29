#define MAXDATA 256

typedef struct _node{
	int key;
	struct _node *next;
}node;

typedef struct{
	int key;
	char val[MAXDATA];
}data_t;

int create_list(node *head,data_t alldata[],int n);
int re_comp(node *head,int searchkey);
int insert_sort_list(node *head);
void print_list(node *head);
void searchnode(node *head,data_t alldata[],int n,int searchkey);