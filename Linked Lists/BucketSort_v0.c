/*IMPLEMENTATION OF BUCKET SORT FOR STRINGS OF SAME LENGTH*/
/*
		BUCKET SORT or RADIX SORT CODE(for strings)
		PREPARED BY:ABDUL SATTAR MAPARA
		DT:14th Feb,2018
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPHABETS_ARRAY_SIZE 26
#define MAX_STRING_SIZE 100
typedef enum{FALSE,TRUE} Bool;
typedef enum{FAILURE,SUCCESS} Status;
typedef char ItemType;
//STRUCTURE FOR LINKED LIST's NODE
typedef struct NodeTag
{
	ItemType data[MAX_STRING_SIZE];
	struct NodeTag* next;
}node;
//function for creating nodes of a linked list
node* MakeNode(ItemType* data)
{
	node* nptr=(node*)malloc(sizeof(node));
	if(nptr!=NULL)
	{
		strcpy(nptr->data,data);
		nptr->next=NULL;
		//printf("\n%s\n",nptr->data);
	}
	return nptr;
}
//STRUCTURE FOR queue
typedef struct QueueDSTag
{
	node* front;
	node* rear;
}QueueDS;
//functions for Queue
void InitializeQueueDS(QueueDS* qptr)
{
	qptr->front=NULL;
	qptr->rear=NULL;
	return;
}
Bool isQueueDSFull(QueueDS* qptr)
{
	//depends on heap memory status;let this function always return false
	return FALSE;
}
Bool isQueueDSEmpty(QueueDS* qptr)
{
	return (qptr->front==NULL&&qptr->rear==NULL);
}
Status InsertInQueueDS(QueueDS* qptr,ItemType* data)
{
	Status sc=SUCCESS;
	node* ptr;
	if(isQueueDSFull(qptr))
	{
		sc=FAILURE;
	}
	else
	{
		ptr=MakeNode(data);
		if(ptr==NULL)
		{
			sc=FAILURE;
		}
		else
		{
			if(isQueueDSEmpty(qptr))
			{
				qptr->front=qptr->rear=ptr;
			}
			else
			{
				(qptr->rear)->next=ptr;
				
				qptr->rear=ptr;
			}
			ptr->next=NULL;
		}
	}
	return sc;
}
Status DeleteFromQueueDS(QueueDS* qptr,ItemType* dptr)
{
	Status sc=SUCCESS;
	node* ptr;
	if(isQueueDSEmpty(qptr))
	{
		sc=FAILURE;
	}
	else
	{
		ptr=qptr->front;
		qptr->front=(qptr->front)->next;
		strcpy(dptr,ptr->data);
		free(ptr);
		if(qptr->front==NULL)
		{
			qptr->rear=NULL;
		}
	}
	return sc;
}
typedef struct AlpahbetAccessTableTag
{
	QueueDS AccessAlphabet[ALPHABETS_ARRAY_SIZE];
}AlpahbetAccessTable;
void InitializeAlphabetAccessTable(AlpahbetAccessTable* accessptr,int size)
{
	int i;
	for(i=0;i<size;i++)
	{
		InitializeQueueDS(&(accessptr->AccessAlphabet[i]));
	}
	return;
}
Bool isAlphabetAccessTableEmpty(AlpahbetAccessTable* accessptr,int size)
{
	int i=0;
	Bool retval=TRUE;
	for(i=0;i<size&&retval;i++)
	{
		retval=isQueueDSEmpty(&(accessptr->AccessAlphabet[i]));
	}
	return retval;
}
Bool isAlphabetAccessTableFull(AlpahbetAccessTable* pqptr)
{
	return FALSE;
}
Status InsertInAccessTable(AlpahbetAccessTable* accessptr,int index,ItemType* data,int size)
{
	Status sc=SUCCESS;
	if(isAlphabetAccessTableFull(accessptr))
	{
		sc=FAILURE;
	}
	else
	{
		if(index>=size||index<0)
		{
			sc=FAILURE;
		}
		else
		{
			sc=InsertInQueueDS(&(accessptr->AccessAlphabet[index]),data);
			//DEBUG:printf("\nINSERTED %s at %d",data,index);
		}
	}
	return sc;
}
Status DeleteFromAccessTable(AlpahbetAccessTable* accessptr,ItemType* dptr,int size)
{
	Status sc=FAILURE;
	int i;
	if(isAlphabetAccessTableEmpty(accessptr,size))
	{
		;//sc=FAILURE;
	}
	else
	{
		i=0;
		while(sc==FAILURE&&i<size)
		{
			sc=DeleteFromQueueDS(&(accessptr->AccessAlphabet[i]),dptr);
			i++;
		}
		
	}
	return sc;
}
void OverwriteList(ItemType* data,node** tail)
{
	strcpy((*tail)->data,data);
	*tail=(*tail)->next;
}
node* BucketSort(node* head)
{
	node* lptr=head;
	node* tail;
	int len,i;
	char ret[MAX_STRING_SIZE];
	AlpahbetAccessTable AQ_List;
	InitializeAlphabetAccessTable(&AQ_List,ALPHABETS_ARRAY_SIZE);
	if(head==NULL||head->next==NULL)
	{
		;
	}
	else
	{
		len=strlen(lptr->data);//for same sized strings
		printf("LENGTH OF EACH STRING IS EXPECTED TO BE=%d\n",len);
		for(i=len-1;i>=0;i--)
		{
			lptr=head;
			tail=head;
			while(lptr!=NULL)
			{
				//DEBUG:printf("\nSHOULD INSERT %s\n",lptr->data);
				//DEBUG:printf("%d is index\n",lptr->data[i]-'a');
				InsertInAccessTable(&AQ_List,lptr->data[i]-'a',lptr->data,ALPHABETS_ARRAY_SIZE);
				lptr=lptr->next;
			}
			while(!(isAlphabetAccessTableEmpty(&AQ_List,ALPHABETS_ARRAY_SIZE)))
			{
				//tail = NULL will never occur
				DeleteFromAccessTable(&AQ_List,ret,ALPHABETS_ARRAY_SIZE);
				OverwriteList(ret,&tail);
			}
		}
	}
	return head;
}
node* InsertAtEnd(node* tail,ItemType* data,node** head)
{
	//CREATES a node AND PUTS IN data in its data field,PLACES the node at end of the linked list Returns tail to the caling function to help subsequent calls
	node* ptr,*lptr;
	ptr=MakeNode(data);
	if(*head==NULL)
	{
		*head=ptr;
		(*head)->next=NULL;
		tail=*head;
	}
	else
	{
		
		tail->next=ptr;
		tail=ptr;
		tail->next=NULL;
	}
	return tail;
}
void TraverseList(node* head)
{
	node* lptr=head;
	while(lptr!=NULL)
	{
		printf("%s\n",lptr->data);
		lptr=lptr->next;
	}
	return;
}
int main()
{
	int num_str,i;
	node* head=NULL;
	node* tail=NULL;
	printf("ENTER THE NUMBER OF STRINGS\n");
	scanf("%d",&num_str);
	char str[MAX_STRING_SIZE];
	i=0;
	while(i<num_str)
	{
		scanf("%s",str);
		tail=InsertAtEnd(tail,str,&head);
		i++;
	}
	tail->next=NULL;
	head=BucketSort(head);
	TraverseList(head);
	/*
	//DEBUG:
	AlpahbetAccessTable AQ;
	InitializeAlphabetAccessTable(&AQ,ALPHABETS_ARRAY_SIZE);
	char ret[MAX_STRING_SIZE];
	InsertInAccessTable(&AQ,0,"abcdef",ALPHABETS_ARRAY_SIZE);
	DeleteFromAccessTable(&AQ,ret,ALPHABETS_ARRAY_SIZE);
	printf("%s\n",ret );
	
	*/
	return 0;
}
/*
IF YOU FIND ANYTHING INCORRECT,PLEASE REPORT TO THE AUTHOR OF THIS CODE 
*/