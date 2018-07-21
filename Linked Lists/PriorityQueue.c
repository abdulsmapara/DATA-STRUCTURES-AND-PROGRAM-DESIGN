/*
		PRIORITY QUEUE CODE
		PREPARED BY:ABDUL SATTAR MAPARA
		DT:12th Feb,2018
*/
#include <stdio.h>
#include <stdlib.h>
//PREPROCESSOR DIRECTIVES
#define SIZE_PRIORITY_QUEUE 5		//FOR CONVENIENCE THIS VALUE IS SET TO 5.THIS VALUE CAN BE CHANGED AS PER REQUIREMENT
//PROGRAMMER DEFINED TYPES
typedef enum{FALSE,TRUE} Bool;
typedef enum{FAILURE,SUCCESS} Status;
typedef int ItemType;
//STRUCTURE FOR LINKED LIST's Node
typedef struct NodeTag
{
	ItemType data;
	struct NodeTag* next;
}Node;
//function for creating Nodes of a linked list
Node* MakeNode(ItemType data)
{
	Node* nptr=(Node*)malloc(sizeof(Node));
	if(nptr!=NULL)
	{
		nptr->data=data;
		nptr->next=NULL;
	}
	return nptr;
}
//STRUCTURE FOR queue
typedef struct QueueDSTag
{
	Node* front;
	Node* rear;
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
Status InsertInQueueDS(QueueDS* qptr,ItemType data)
{
	Status sc=SUCCESS;
	Node* ptr;
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
	Node* ptr;
	if(isQueueDSEmpty(qptr))
	{
		sc=FAILURE;
	}
	else
	{
		ptr=qptr->front;
		qptr->front=(qptr->front)->next;
		*dptr=ptr->data;
		free(ptr);
		if(qptr->front==NULL)
		{
			qptr->rear=NULL;
		}
	}
	return sc;
}
//structure for priorityqueue
typedef struct PriorityQueueTag
{
	QueueDS queue[SIZE_PRIORITY_QUEUE];
}PriorityQueue;
//functions for priority queue
void InitializePriorityQueue(PriorityQueue* pqptr,int size)
{
	int i;
	for(i=0;i<size;i++)
	{
		InitializeQueueDS(&(pqptr->queue[i]));
	}
	return;
}
Bool isPriorityQueueEmpty(PriorityQueue* pqptr,int size)
{
	int i=0;
	Bool retval=TRUE;
	for(i=0;i<size&&retval;i++)
	{
		retval=isQueueDSEmpty(&(pqptr->queue[i]));
	}
	return retval;
}
Bool isPriorityQueueFull(PriorityQueue* pqptr)
{
	return FALSE;
}
Status InsertInPriorityQueue(PriorityQueue* pqptr,int Priority,ItemType data,int size)
{
	//priority=0 means highest priority
	Status sc=SUCCESS;
	if(isPriorityQueueFull(pqptr))
	{
		sc=FAILURE;
	}
	else
	{
		if(Priority>=size||Priority<0)
		{
			sc=FAILURE;
		}
		else
		{
			sc=InsertInQueueDS(&(pqptr->queue[Priority]),data);
		}
	}
	return sc;
}
Status DeleteFromPriorityQueue(PriorityQueue* pqptr,int Priority,ItemType* dptr,int size)
{
	Status sc=SUCCESS;
	if(isPriorityQueueEmpty(pqptr,size))
	{
		sc=FAILURE;
	}
	else
	{
		if(Priority>=size||Priority<0)
		{
			sc=FAILURE;
		}
		else
		{
			sc=DeleteFromQueueDS(&(pqptr->queue[Priority]),dptr);
		}
	}
	return sc;
}
//main function-driver function here used to test all above functions
int main()
{
	PriorityQueue PQ_List;
	int i;
	ItemType data;
	Status sc=SUCCESS;
	InitializePriorityQueue(&PQ_List,SIZE_PRIORITY_QUEUE);
	//can insert in queue of same priority multiple times but here for the sake of testing above functions this facility is not shown apparently.Similar story goes for delete
	for(i=0;i<SIZE_PRIORITY_QUEUE&&sc;i++)
	{
		printf("DATA FOR PRIORITY %d\t",i);
		scanf("%d",&data);					//CHANGE HERE IF ITEMTYPE CHANGES
		sc=InsertInPriorityQueue(&PQ_List,i,data,SIZE_PRIORITY_QUEUE);
	}
	
	if(sc)
	{
		printf("INSERTED ALL DATA IN PRIORITY QUEUE SUCCESSFULLY\n");
	}
	else
	{
		printf("INSERT IN PRIORITY QUEUE FAILED\n");
	}
	for(i=0;i<SIZE_PRIORITY_QUEUE&&sc;i++)
	{
		sc=DeleteFromPriorityQueue(&PQ_List,i,&data,SIZE_PRIORITY_QUEUE);
		if(sc)
		{
			printf("DATA AT PRIORITY %d is \t%d\n",i,data);
		}
		else
		{
			printf("ERROR IN EXECUTION\nSORRY\n");
		}
	}
	
	return 0;
}
/*
IF YOU FIND ANYTHING INCORRECT PLEASE REPORT TO THE AUTHOR OF THIS CODE.
*/