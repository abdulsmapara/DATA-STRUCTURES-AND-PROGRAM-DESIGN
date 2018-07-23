/*
		SPARSE MATRIX
		PREPARED BY:ABDUL SATTAR MAPARA
		DT:15th Feb,2018
		SPARSE MATRIX READING,TRAVERSING AND ADDING TWO SPARSE MATRICES
		IMPLEMENTED FOR +VE NUMBERS ONLY(SAME CAN BE EXTENDED FOR -ve NUMBERS but TERMINATING INPUTS  FROM USER HAS TO BE CHANGED IN THIS CODE & IN ADDITION IT'LL BECOME NECESSARY TO CHECK IF SUM!=0 BEFORE INSERTING INTO THE ADDITION MATRIX)
		NOTE:THE TYPEDEFs DOESNOT USE UNIONS.(THAT PART IS REMAINING)
*/
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 250
#define NEXT_ROW -1
#define END_INPUT -2
typedef int ItemType;
typedef enum{FALSE,TRUE} Bool;
typedef struct MatNodeTag
{
	ItemType val;
	int col;
	int row;
	struct MatNodeTag* next;
	struct MatNodeTag* down;
}MatNode;
typedef struct AddressNodeTag	//address node tag
{
	int address;				//either row or col
	struct AddressNodeTag* nextAddress;
	MatNode* rowList;
}AddressNode;
MatNode* MakeMatNode(ItemType val,int row,int col)
{
	MatNode* nptr;
	nptr=(MatNode*)malloc(sizeof(MatNode));
	if(nptr!=NULL)
	{
		nptr->val=val;
		nptr->col=col;
		nptr->row=row;
		nptr->next=NULL;
		nptr->down=NULL;
	}
	return nptr;
}
AddressNode* MakeAddressNode(int val_add,MatNode* nextRowList)
{
	AddressNode* nptr;
	nptr=(AddressNode*)malloc(sizeof(AddressNode));
	if(nptr!=NULL)
	{
		nptr->address=val_add;
		nptr->rowList=nextRowList;
		nptr->nextAddress=NULL;
	}
	return nptr;
}
void InsertAddressNode(AddressNode** finalHead,int add,MatNode* head,AddressNode** finalTail)
{
	AddressNode* nptr=MakeAddressNode(add,head);
	if(*finalHead==NULL)
	{
		*finalHead=nptr;
		*finalTail=nptr;
	}
	else
	{
		(*finalTail)->nextAddress=nptr;
		(*finalTail)=nptr;
	}
	nptr->nextAddress=NULL;
	return;
}
void InsertMatNode(MatNode** head,ItemType val,MatNode** tail,int rows,int cols)
{
	//can return status
	MatNode* nptr=MakeMatNode(val,rows,cols);
	nptr->next=NULL;
	nptr->down=NULL;
	if(*head==NULL)
	{
		*head=nptr;
		*tail=*head;
		
	}
	else
	{
		(*tail)->next=nptr;
		*tail=nptr;

	}
	return;
}
void TraverseMatrix(AddressNode* start)
{
	AddressNode* head=start;
	MatNode* mat;
	while(head!=NULL)
	{
		mat=head->rowList;
		while(mat!=NULL)
		{
			printf("%d ",mat->val);
			mat=mat->next;
		}
		head=head->nextAddress;
		printf("\n");
	}
	return;
}
AddressNode* Read()
{
	int element,rows,cols;
	Bool isEmpty;
	AddressNode* finalHead1=NULL,*finalTail1=NULL;
	AddressNode* finalHead2=NULL,*finalTail2=NULL;
	MatNode* head,*tail;
	printf("ENTER THE ELEMENTS(non-negative) IN THE MATRIX\nIF DONE ENTER -1 TO JUMP TO NEXT ROW AND -2 TO TERMINATE GIVING INPUTs\nENTER IN ROW MAJOR FORM\n");
	rows=0;
	cols=0;
	element=0;
	while(element!=END_INPUT)
	{
		head=NULL;
		tail=NULL;
		if(element==NEXT_ROW)
		{
			element=0;
		}
		isEmpty=TRUE;
		while(element!=NEXT_ROW && element!=END_INPUT)
		{
			scanf("%d",&element);
			if(element>0)
			{
				InsertMatNode(&head,element,&tail,rows,cols);
				if(rows==0)
				{
					InsertAddressNode(&finalHead2,cols,head,&finalTail2);
				}
				isEmpty=FALSE;
			}
			cols++;

			
		}
		if(!isEmpty)
		{
			InsertAddressNode(&finalHead1,rows,head,&finalTail1);
		}
		rows++;
	}
	printf("THE SPARSE MATRIX LOOKS LIKE:\n");
	TraverseMatrix(finalHead1);
	return finalHead1;
}
AddressNode* Addition(AddressNode* head1,AddressNode* head2)
{
	AddressNode* p=head1,*q=head2,*resultAdd,*resultAddTail;
	MatNode* mat1,*mat2,*resultMat,*resultMatTail;
	int sum;
	int rows,cols;
	rows=0;
	cols=0;
	resultAdd=NULL;
	resultAddTail=NULL;
	while(p!=NULL&&q!=NULL)
	{
		cols=0;
		mat1=p->rowList;
		mat2=q->rowList;
		resultMat=NULL;
		resultMatTail=NULL;
		while(mat1!=NULL&&mat2!=NULL)
		{
			sum=mat1->val+mat2->val;
			//insert only when sum!=0 but here we consider only +ve elements so we don't check the sum here
			InsertMatNode(&resultMat,sum,&resultMatTail,rows,cols);
			cols++;
			mat1=mat1->next;
			mat2=mat2->next;
		}
		while(mat1!=NULL)
		{
			InsertMatNode(&resultMat,mat1->val,&resultMatTail,rows,cols);
			cols++;
			mat1=mat1->next;
		}
		while(mat2!=NULL)
		{
			InsertMatNode(&resultMat,mat2->val,&resultMatTail,rows,cols);
			cols++;
			mat2=mat2->next;
		}
		InsertAddressNode(&resultAdd,rows,resultMat,&resultAddTail);
		rows++;
		p=p->nextAddress;
		q=q->nextAddress;
	}
	while(p!=NULL)
	{
		mat1=p->rowList;
		cols=0;
		while(mat1!=NULL)
		{
			InsertMatNode(&resultMat,mat1->val,&resultMatTail,rows,cols);
			cols++;
			mat1=mat1->next;
		}	
		rows++;
		p=p->nextAddress;
	}
	while(q!=NULL)
	{
		mat2=q->rowList;
		cols=0;		
		while(mat2!=NULL)
		{
			InsertMatNode(&resultMat,mat2->val,&resultMatTail,rows,cols);
			cols++;
			mat2=mat2->next;
		}	
		rows++;
		q=q->nextAddress;
	}
	printf("THE ADDIION LOOKS LIKE:\n");
	TraverseMatrix(resultAdd);
	return resultAdd;
}
int main()
{
	AddressNode* mat1,* mat2;
	mat1=Read();
	mat2=Read();
	Addition(mat1,mat2);
	return 0;
}
/*
IF YOU FIND ANYTHING INCORRECT,PLEASE REPORT TO THE AUTHOR OF THIS CODE 
*/
