#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int create_list(node *head,data_t alldata[],int n){
	int i;
	node *p,*q;
	p=head;
	for(i=0;i<n;i++){
		q=(node*)malloc(sizeof(node));
		if(NULL==q){
			return 1;
		}
		q->next=NULL;
		q->key=alldata[i].key;
		p->next=q;
		p=q;
	}
	return 0;
}

int re_comp(node *head, int searchkey){
	int j;
	node *p;
	p=head->next; 
	j=1;
	while(p->next&&p->key<searchkey){
		p=p->next;
		j++;
	}
	return j;
}

/*then return the number of comparison in insertions*/
int insert_sort_list(node *head){
	node *p,*q,*t,*r;
	int calcompar=0;
	p=head->next;
	head->next=NULL;
	while(NULL!=p){
		t=head;
		q=t->next; 
	        while((NULL!=q)&&(q->key <= p->key)){
			t=q;
			q=q->next;			
		}
		r=p->next;
		t->next=p;
		calcompar+=re_comp(head,p->key);
		p->next=q;
		p=r;        
	}
	if(p=NULL){
		calcompar+=1;
	}
	return calcompar;
}

void print_list(node *head){
	node *p;
	p=head->next;
	int n=0;
	while(p){
		p=p->next;
		n++;
	}
	printf("%d Insertions",n);
} 


/*search the key and print the number of comparison in searching.*/
void searchnode(node *head,data_t alldata[],int n,int searchkey){
	int j,k;
	node *p;
	p=head->next; 
	j=1;
	while(p->next&&p->key<searchkey){
		p=p->next;
		j++;
	}
	if(searchkey==p->key){
		printf("%d ",p->key);
		for(k=0;k<n;k++){
			if(alldata[k].key==p->key){
				printf("%s ",alldata[k].val);
			}
		}
	}
	else{
		printf("%d NOTFOUND ",searchkey);
	}
	printf("%d\n",j);
}

node* free_list(node *head){
	node *p=head;
	node *q=head;
	while(q) {
		p=q;
		q=p->next;
		free(p);
	}       
	return head;
}

node* insert(node* head,int number){
    node *temp,*p,*q;
    temp=(node*)malloc(sizeof(node));
    temp->key=number;
    temp->next=NULL;
    if(!head){
		head=temp;
	}else{
		p=NULL;
		q=head;
		while((q)&&(q->data<=number)){
			p=q;
			q=q->next;
		}
		if(!q){
			p->next=temp;
		}else{
			if(p){
			temp->next=p->next;
			p->next=temp;
			}else{temp->next=head;
					head=temp;
			}            
		}   
	}
	return head;
}

node* delete(node* head,int x){
	node *p,*q;                  
	p=head->next;
	while(p->key!=x){   
		q=p; 
		p=p->next;
	}
	q->next=p->next;          
	free(p);
	return head;
} 
   
