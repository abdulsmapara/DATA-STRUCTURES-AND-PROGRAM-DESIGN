#include <stdio.h>
#include <stdlib.h>
#define ADD 1
typedef struct ListNodeTag
{
	struct ListNodeTag* next;
	int data;	
}node;
void PrintNum(node* head)
{
	node* h,*t,*mid,*trv;//t=tail h=head mid=middle trv=traverser
	h=head;
	mid=NULL;
	while(h!=NULL)
	{
		t=mid;
		mid=h;
		h=h->next;
		mid->next=t;

	}
	trv=mid;
	while(trv!=NULL)
	{
		printf("%d",trv->data);
		trv=trv->next;
	}
	return;
}
node* InsertAtEnd(node* lptr,int data)
{
	node* nptr=(node* )malloc(sizeof(node)),*ptr;
	if(nptr!=NULL)
	{
		nptr->data=data;
		nptr->next=NULL;
		if(lptr==NULL)
		{
			lptr=nptr;

		}
		else
		{
			ptr=lptr;
			while(ptr->next!=NULL)
			{
				ptr=ptr->next;
			}
			ptr->next=nptr;

		}
	}
	return lptr;
}
node* CreateNumberLL(int n)
{
	//create linked list for number n
	node* lptr=NULL;
	while(n>0)
	{
		lptr=InsertAtEnd(lptr,n%10);
		n=n/10;
	}
	return lptr;

}
node* add(node* lptr1,node* lptr2)
{
	node* ret=NULL,*p,*q,*prevP,*prevQ;
	p=lptr1;
	q=lptr2;
	int sum=0;
	while(p!=NULL&&q!=NULL)
	{
		sum=p->data+q->data+sum/10;
		//sum/10 for carry from previous addition
		ret=InsertAtEnd(ret,sum%10);
		prevP=p;
		prevQ=q;
		p=p->next;
		q=q->next;
	}
	if(sum/10&&p==NULL&&q==NULL)
	{
		
		ret=InsertAtEnd(ret,sum/10);
	}
	while(p!=NULL)
	{
		sum=p->data+sum/10;
		ret=InsertAtEnd(ret,sum);
		p=p->next;
	}

	while(q!=NULL)
	{
		sum=q->data+sum/10;
		ret=InsertAtEnd(ret,sum);
		q=q->next;
	}
	return ret;
}
int main()
{
	int n1,n2;
	node* lptr1,*lptr2,*addRes;
	printf("ENTER TWO NUMBERS\n");
	scanf("%d",&n1);
	scanf("%d",&n2);
	lptr1=CreateNumberLL(n1);
	lptr2=CreateNumberLL(n2);
	int choose;
	printf("\tMENU\n1] ADD THE TWO NUMBERS\n");
	scanf("%d",&choose);
	switch(choose)
	{
		case ADD:
			addRes=add(lptr1,lptr2);
			printf("ADDITION IS\t");
			PrintNum(addRes);
			break;
		default:
			printf("YOU ENTERED A CHOICE NOT AVAILABLE\n");
	}
	
	return 0;
}