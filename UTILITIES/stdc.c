/*
                            
        -IMPORTANT C-FUNCTIONS USEFUL IN DATA STRUCTURES AND PROGRAM DESIGN COURSES IN C LANGUAGE
        (PLEASE ALSO FIND stdc.h file)
                PREPARED BY:    -ABDUL SATTAR MAPARA
                                 abdulsmapara.github.io
                                 abdulsmapara@gmail.com    
*/
#include "stdc.h"

/*
    %d-integer
    %c-character
    %f-float
    %s-string
    %u-unsigned int
    %lf-double
    %ld-long int
    %lld-long long int


    NOTE: USE strcmp() with appropriate arguments if ItemType is char*
*/
/*MAKE APPROPRIATE CHANGES IN THE FOLLOWING 5 FUNCTIONS ONLY IF YOU CHANGE ItemType*/
void printItem(ItemType data)
{
    printf("%d ",data);
    return;
}
void scanItem(ItemType* data)
{
    scanf("%d",data);
}
Bool areItemsEqual(ItemType data1,ItemType data2)
{
    return (data1==data2);
}
Bool isFirstItemGreater(ItemType data1,ItemType data2)
{
    return (data1>data2);
}
Bool isSecondItemGreater(ItemType data1,ItemType data2)
{
    return (data1<data2);
}
/*END FOR CHANGES IN FUNCTIONS DUE TO CHANGE IN ItemType*/


//CHECK FOR GENERALIZATION OF BUBBLE SELECTION INSERTION SORTS-----AN EXPERIMENT
//!!!!!ARRAYS SORTED IN ASCENDING ORDER ONLY!!!!
/*A is the name for ARRAY
void BubbleSort(int A[],int low,int high);//low is the start from which sorting is to be started
void InsertionSort(int A[],int low,int high);//high is the index upto which sorting should be done
void SelectionSort(int A[],int low,int high);
void MergeSelf(int A[],int low,int upto,int high);
void MergeSort(int A[],int low,int high);
int partitionAlgo(int A[],int low,int high,int x);//partitions array about x and returns position upto which elements<=x
void QuickSort(int A[],int low,int high);//QuickSort Algorithm
*/
//BUBBLE SORT (n is ARRAY SIZE)
void BubbleSort(int A[],int low,int high)
{
   int i,j,temp,sorted=0,k=0;
    for(i=low;i<high&&sorted==0;i++,k++)
    {
        sorted=1;
        for(j=low;j<high-k;j++)
        {
            if(A[j]>A[j+1])
            {
                temp=A[j];
                A[j]=A[j+1];
                A[j+1]=temp;
                sorted=0;
            }
        }
    }
}
//INSERTION SORT
void InsertionSort(int A[], int low,int high)
{
    int i,min=A[low],pos=low,x,j;
    for(i=low+1;i<=high;i++)
    {
        if(A[i]<min)
        {
            min=A[i];
            pos=i;
        }

    }
    A[pos]=A[low];
    A[low]=min;//minimum stored at 0th index
    for(i=low+2;i<=high;i++)
    {

        j=i-1;
        x=A[i];
        while(x<A[j])
        {
            A[j+1]=A[j];
            j--;
        }
       A[j+1]=x;

    }
    return;
}
void SelectionSort(int A[], int low,int high)
{
    int i,j,min,pos;
    for(i=low;i<high+1;i++)
    {
        min=A[i];
        pos=i;
        for(j=i+1;j<high+1;j++)
        {
            if(A[j]<min)
            {
                min=A[j];
                pos=j;
            }
        }

        A[pos]=A[i];
        A[i]=min;
    }
    return;
}
//MERGE SELF
void MergeSelf(int A[],int low,int upto,int high)
{
    int i,j,k,*temp;
    temp=(int *)malloc(sizeof(int)*(high-low+1));
    i=low;
    j=upto+1;
    k=0;
    while(i<=upto&&j<=high)
    {
        if(A[i]<A[j])
        {
            temp[k++]=A[i++];
        }
        else
        {
            temp[k++]=A[j++];
        }
    }
    while(i<=upto)
    {
        temp[k++]=A[i++];
    }
    while(j<=high)
    {
        temp[k++]=A[j++];
    }
    k-=1;
    while(k>=0)
    {
        A[low+k]=temp[k];
        k--;
    }
    free(temp);
    temp=NULL;
    return;
}
//MERGE SORT
void MergeSort(int A[],int low,int high)
{
    int mid;
    if(low<high)
    {
        mid=(low+high)/2;
        MergeSort(A,low,mid);
        MergeSort(A,mid+1,high);
        MergeSelf(A,low,mid,high);
    }
    return;
}
int partitionAlgo(int A[], int low, int high, int x)
{
    int left=low,right=high,temp;
    while(left<=high&&A[left]<=x)
    {
        left++;
    }
    while(right>=low&&A[right]>x)
    {
        right--;
    }
    while(left<right)
    {
        temp=A[left];
        A[left]=A[right];
        A[right]=temp;
        while(A[left]<=x)
        {
            left++;
        }
        while(A[right]>x)
        {
            right--;
        }
    }
    return right;//or left-1
}
void QuickSort(int A[],int low,int high)
{
    int pos,temp;
    if(low<high)
    {
        pos=partitionAlgo(A,low,high,A[low]);
        temp=A[pos];
        A[pos]=A[low];
        A[low]=temp;
        QuickSort(A,low,pos-1);
        QuickSort(A,pos+1,high);

    }
    return;
}
/*
int LinearSearch(int A[],int low,int high,int searchThis);//low=index of element to start from;high=index of element to end at in an array
int BinarySearch(int A[],int low,int high,int searchThis);//low=index of element to start from;high=index of element to end at in a SORTED array
*/
int LinearSearch(int A[], int low,int high,int searchThis)//returns index of 1st occurence of the element being searched if found||||else returns -1(invalid)
{
    int ret_val=INDEX_INVALID,i;
    for(i=low;i<=high&&ret_val==INDEX_INVALID;i++)
    {
        if(A[i]==searchThis)
        {
            ret_val=i;
        }
    }
    return ret_val;
}
int BinarySearch(int A[], int low, int high,int searchThis)//A is required to be SORTED
{
    //!!!ForSorted ARRAY only!!!
    //returns index of an occurence of the element being searched(not necessarily 1st occurence) if found||||else returns -1(invalid)
    int ret_val=INDEX_INVALID,mid;
    while(low<=high&&ret_val==INDEX_INVALID)
    {
        mid=(low+high)/2;
        if(A[mid]==searchThis)
        {
            ret_val=mid;
        }
        else if(A[mid]<searchThis)
        {
            low=mid+1;
        }
        else    //A[mid]>searchThis
        {
            high=mid-1;
        }
    }
    return ret_val;

}
/*
float SqrtOf(float n);      //calculates square root of n(floating point number)
float Power(float base, unsigned int power);//calculates the value of (base float)to the power (power integer>=0)
float AbsoluteOf(float n);      //calculates absolute value of n and returns it
!!!SPECIAL NUMBERS!!!
int GetNthFib(int n,int fterm,int sterm);//Function to get nth fibonacci number (support for Wrapper Function NthFib(int n))
int NthFib(int n);          //nth fibonacci number n=1 fib=0 n=2 fib=1 and so on...
int max(int a,int b);           //maximum of a and b
int min(int a,int b);           //minimum of a and b
*/
float AbsoluteOf(float n)
{
    //calculates absolute value of n and returns it
    if(n<0)
    {
        n*=-1;
    }
    return n;
}
float SqrtOf(float n)
{
    float guess1,guess2;
    guess1=2.0;
    guess2=n;
    const float error=0.0001;
    do
    {
        guess1=guess2;
        guess2=(guess1+n/guess1)/2.0;

    }while(AbsoluteOf(guess1-guess2)>error);
    return guess2;
}
float Power(float base, unsigned int power)//calculates the value of (base float)to the power (power integer>=0)
{
    float retVal;
    if(power==0)
    {
        retVal=1.0;
    }
    else    //power>0
    {
        retVal=Power(base,power/2);
        retVal=retVal*retVal;
        if(power%2==1)
        {
            retVal*=base;
        }
    }
    return retVal;
}
int GetNthFib(int n,int fterm,int sterm)
{   //Function to get nth fibonacci number (support for Wrapper Function NthFib(int n))
    int retVal;
    if(n==1)
    {
        retVal=fterm;
    }
    else if(n==2)
    {
        retVal=sterm;
    }
    else
    {
        retVal=GetNthFib(n-1,sterm,fterm+sterm);
    }
    return retVal;
}
int NthFib(int n)   //nth fibonacci number n=1 fib=0 n=2 fib=1 and so on...     
{
    //WrapperFunction
    int fterm=0;
    int sterm=1;
    int retVal=GetNthFib(n,fterm,sterm);
    return retVal;

}
int max(int a,int b)
{
    int retVal=a;
    if(b>retVal)
    {
        retVal=b;
    }
    return retVal;
}
int min(int a,int b)
{
    int retVal=a;
    if(b<retVal)
    {
        retVal=b;
    }
    return retVal;

}
/*
                                    QUEUE-ABSTRACT DATA STRUCTURE
                                        FIRST IN FIRST OUT
                                    VALUES INSERTED AFTER INCREMENTING REAR POSITION
                                    VALUES DELETED AT FRONT POSITION
void InitializeQueue(Queue *qPtr);                  //Initializes rear,front variables in qPtr queue
Queue * CreateQueues(Queue *qPtr,int maxSize);      //creates a queue with data array of size=maxSize
Bool isQueueFull(Queue *qPtr);                      //returns true if queue is full else returns false
Bool isQueueEmpty(Queue *qPtr);                     //returns true if queue is empty else returns false
Status InsertInQueue(Queue *qPtr,ItemType val);     //inserts an element in queue if isQueueFull returns false
Status DeleteFromQueue(Queue *qPtr,ItemType *val);  //deletes an element in queue if isQueueEmpty returns false
*/
void InitializeQueue(Queue *qPtr)
{
//Initializes rear,front variables in qPtr queue
    qPtr->rear=-1;
    qPtr->front=0;
}
Queue* CreateQueues(Queue *qPtr,int maxSize)
{
//creates a queue with data array of size=maxSize
    qPtr=(Queue *)malloc(sizeof(Queue));
    InitializeQueue(qPtr);
    qPtr->maxSize=maxSize;
    qPtr->data=(ItemType *)malloc(sizeof(ItemType)*maxSize);
    return qPtr;
}
Bool isQueueFull(Queue *qPtr)
{
//returns true if queue is full else returns false
    return ((((qPtr->rear+1)%((qPtr->maxSize)))==qPtr->front)&&qPtr->rear!=-1);
}
Bool isQueueEmpty(Queue *qPtr)
{
//returns true if queue is empty else returns false
    return ((((qPtr->rear+1)%((qPtr->maxSize)))==qPtr->front)&&qPtr->rear==-1);

}
Status InsertInQueue(Queue *qPtr,ItemType val)
{
//inserts an element in queue if isQueueFull returns false
    Status retval=SUCCESS;
    if(isQueueFull(qPtr))
    {
        retval=FAILURE;
    }
    else
    {
        (qPtr->rear)++;

        qPtr->data[qPtr->rear]=val;

    }
    return retval;

}
Status DeleteFromQueue(Queue *qPtr,ItemType *val)
{
//deletes an element in queue if isQueueEmpty returns false
    Status retval=SUCCESS;
    if(isQueueEmpty(qPtr))
    {
        retval=FAILURE;
    }
    else
    {

        *val=qPtr->data[qPtr->front];
        (qPtr->front)--;

        if(((qPtr->rear+1)%(qPtr->maxSize))==qPtr->front)
        {
            InitializeQueue(qPtr);
        }
    }
    return retval;
}
/*
                    STACKS-ABSTRACT DATA STRUCTURE
                        FIRST-IN LAST-OUT
            VALUE INSERTED FIRST STORED AT BOTTOMMOST LOCATION
            VALUE INSERTED MOST RECENTLY STORED AT TOPMOST LOCATION
void InitializeStack(Stack *PointStack);//Initialize the stack top variable
Stack* CreateStacks(int size);//Implements  stack based on size given by user|||data structure on which it gets implemented is array currently.Can be changed by making changes in this file
Status PushOnStack(Stack *PointStack,ItemType val);//Push val on top of stack
Status PopFromStack(Stack *PointStack,ItemType *here);//Pop val from top of stack in 'here' variable
Bool isStackEmpty(Stack *PointStack);//returns true if stackisempty else returns false
Bool isStackFull(Stack *PointStack);//returns true if stackisfull else returns false
*/
void InitializeStack(Stack *PointStack)
{
    //INITIALIZING TOP VARIABLE OF STACKS 
    PointStack->top=-1;
    PointStack->size=0;
}
Stack* CreateStacks(int size)
{
//Implements stack based on size given by user|||data structure on which it gets implemented is array currently.Can be changed by making changes in this file
    Stack *PointStack=(Stack *)malloc(sizeof(Stack));
    InitializeStack(PointStack);
    PointStack->size=size;
    PointStack->array=(ItemType *)malloc(sizeof(ItemType)*size);
    return PointStack;
}
Bool isStackEmpty(Stack *PointStack)
{
//returns true if stackisempty else returns false
    /*Bool retval=FALSE;
    if(PointStack->top==-1)
    {
        retval=TRUE;
    }
    return retval;*/
    return ((PointStack->top)==-1);
}
Bool isStackFull(Stack *PointStack)
{
//returns true if stackisfull else returns false
    return ((PointStack->top)==((PointStack->size)-1));
}
Status PushOnStack(Stack *PointStack,ItemType val)
{
    //Push val on top of stack
    Status retval=SUCCESS;
    if(isStackFull(PointStack))
    {
        retval=FAILURE;
    }
    else
    {
        (PointStack->top)+=1;
        PointStack->array[PointStack->top]=val;
    }
    return retval;
}
Status PopFromStack(Stack *PointStack,ItemType *here)
{
//Pop val from top of stack in 'here' variable
    Status retval=SUCCESS;
    if(isStackEmpty(PointStack))
    {
        retval=FAILURE;
    }
    else
    {
        *here=PointStack->array[PointStack->top];
        (PointStack->top)-=1;
    }
    return retval;
}


Node* MakeNode(ItemType data)
{
    //MAKES A SINGLE Node and inserts data into it ..returns pointer to the newly made Node if MEMORY IS AVAILABLE ELSE RETURNS NULL
    Node* ptr;
    ptr=(Node*)malloc(sizeof(Node));
    if(ptr!=NULL)
    {
        ptr->data=data;
        ptr->next=NULL;         //initialize ptr->next with default value
    }
    return ptr;
}
void InitializeStackDS(StackDS *sptr)
{
    //INITIALIZES STACK TO DEFAULT VALUE
    sptr->top=NULL;
    return;
}
Bool isStackDSEmpty(StackDS *sptr)
{
    //returns true if stack is empty
    return ((sptr->top)==NULL);
}
Bool isStackDSFull(StackDS* sptr)
{
    //since LINKED LIST size is theoretically infinite,this function returns back FALSE always
    return FALSE;
}
Status PushOnStackDS(StackDS *sptr,ItemType data)
{
    //PUSH DATA ON STACKDS--returns SUCCESS when MEMORY NOT FULL ELSE RETURNS FAILURE
    Status sc=SUCCESS;
    Node* ptr;
    ptr=MakeNode(data);
    if(ptr==NULL||(isStackDSFull(sptr)))
    {
        sc=FAILURE;
    }
    else
    {
        ptr->next=(sptr->top);
        sptr->top=ptr;
    }
    return sc;
    //BASICALLY THIS FUNCTION RESEMBLES InsertAtStart() of LINKEDLIST
}
Status PopFromStackDS(StackDS *sptr,ItemType* dptr)
{
    //POPS DATA FROM STACKDS and PROVIDES DATA DELETED THROUGH dptr(if atall data was deleted)-----returns SUCCESS if Node is deleted else returns FAILURE(incase when stack is empty)
    Status sc=SUCCESS;
    Node* ptr;
    if(isStackDSEmpty(sptr))
    {
        sc=FAILURE;
    }
    else
    {
        //atleast a Node is present
        ptr=(sptr->top);
        (sptr->top)=ptr->next;
        *dptr=ptr->data;    //catch the data to be deleted
        free(ptr);
        ptr=NULL;
    }   
    return sc;
}

void swapNodesInLL(Node* ptr,Node* prev,Node** lpptr)
{
    Node* trv=*lpptr;
    if(prev!=*lpptr)
    {
        while(trv->next!=prev)
        {
            //find prev to prev
            trv=trv->next;
        }
        //begin swap
        trv->next=prev->next;
    }
    else
    {
        *lpptr=ptr;
        //printf("%d \n",ptr->data);
    }
    prev->next=ptr->next;
    ptr->next=prev;
    return;
}
Node* BubbleSortLL(Node* lptr)
{
    int i,j,sorted;
    Node* prev,*ptr,*copyPtr,*copyPrev,*prevBef,*temp,*storePtr;
    if(lptr!=NULL&&lptr->next!=NULL)    //atleast two Nodes should be present
    {   
        //INITIALIZE CONDITIONS--FOR LOOP(OUTER)
        prev=lptr;
        ptr=prev->next;
        i=0;
        sorted=0;
        copyPtr=ptr;
        copyPrev=prev;
        prevBef=NULL;
        storePtr=ptr;
        for (;!sorted;i++)
        {
            sorted=1;
            for(j=0,copyPtr=lptr->next,
        copyPrev=lptr;copyPtr!=prevBef;j++,copyPrev=copyPrev->next,copyPtr=copyPtr->next)
            {
                if(copyPtr->data < copyPrev->data)
                {
                    //swap
                    swapNodesInLL(copyPtr,copyPrev,&lptr);

                    temp=copyPtr;
                    copyPtr=copyPrev;
                    copyPrev=temp;
                    sorted=0;
                }
            }

            prevBef=copyPrev;
            
        }
    }
    return lptr;
}


Node* InsertNodeAtStart(Node* head,ItemType data)
{
    //CREATES a Node AND PUTS IN data in its data field..returns new head pointer
    Node* ptr;
    ptr=MakeNode(data);
    if(ptr!=NULL)
    {
        ptr->next=head;
    }
    head=ptr;
    return head;
}
Node* CreateList(int num)
{
    //CREATES num NUMBER OF NodeS and RETURNS HEAD TO THE START OF THE LINKED LIST
    Node *head;
    head=NULL;
    int i;
    ItemType d;
    for(i=0;i<num;i++)
    {
        printf("ENTER THE DATA\n");
        scanItem(&d);
        head=InsertNodeAtStart(head,d);
    }
    return head;
}
void TraverseList(Node* head)
{
    //TAKES in POINTER TO START OF THE LIST prints DATA PRESENT IN THE NodeS AND RETURNS
    Node* ptr=head;
    while(ptr!=NULL)
    {
        printItem(ptr->data);    //------!!CHANGE HERE IF ITEM TYPE CHANGES!!-------
        ptr=ptr->next;
    }
    return;
}
Status DeleteAtStart(Node** head,ItemType* dptr)
{
    //TAKES POINTER TO POINTER TO HEAD AND POINTER TO DATA AS INPUT and STORES DATA TO BE DELETED AND FREE UP THE LOACTION *head POINTS TO 
    Status sc=SUCCESS;
    Node* ptr=*head;
    if(ptr==NULL)
    {
        //CASE OF EMPTY LIST WHICH MEANS DELETING A Node IS IMPOSSIBLE
        sc=FAILURE;
    }
    else
    {
        //atleast a Node is present in the list
        *head=ptr->next;
        *dptr=ptr->data;
        free(ptr);
        ptr=NULL;
    }
    return sc;
}
void DeleteList(Node *head)
{                   
    //DELETES COMPLETE LIST
    Status sc;
    ItemType data;
    while(head!=NULL)
    {
        sc=DeleteAtStart(&head,&data);
        printf("DATA");
        printItem(data);
        printf(" JUST GOT DELETED FROM THE LIST\n");    //------!!CHANGE HERE IF ITEM TYPE CHANGES!!-------

    }
    return;
    //USER SHOULD TAKE CARE THAT AFTER THE LIST IS DELETED (after call to DeleteList())head should not be accessed OTHERWISE A CASE OF DANGLING POINTER WILL ARISE ACC TO THE WAY THE FUNCTION DELETELISTS IS WRITTEN
}
Bool MatchKeyData(ItemType data,KeyType key)
{
    //returns true if data and key matches
    //if data is large and key is value of element of data then changes can be made in this function 
    return (areItemsEqual(data,key));
}
Status SwapTwoNodes(Node** head,KeyType key1,KeyType key2)
{
    //swaps Nodes whose keys are given here
    //NOTE: Nodes are swapped by changing links as swapping data of Nodes may be expensive in many situations when data contains many fields
    Node *ptr1,*prev1,*ptr2,*prev2,*temp;
    ptr1=*head;
    ptr2=*head;
    prev1=NULL;
    prev2=NULL;
    Bool found1=FALSE;
    Bool found2=FALSE;
    Status sc=SUCCESS;
    while((ptr1!=NULL)&&(!found1)&&(ptr2!=NULL)&&(!found2))
    {
        if(MatchKeyData(ptr1->data,key1))
        {
            found1=TRUE;
        }
        else
        {
            prev1=ptr1;
            ptr1=ptr1->next;
        }
        if(MatchKeyData(ptr2->data,key2))
        {
            found2=TRUE;
        }
        else
        {
            prev2=ptr2;
            ptr2=ptr2->next;
        }
    }
    while((ptr1!=NULL)&&(!found1))
    {
        if(MatchKeyData(ptr1->data,key1))
        {
            found1=TRUE;
        }
        else
        {
            prev1=ptr1;
            ptr1=ptr1->next;
        }
    
    }
    while((ptr2!=NULL)&&(!found2))
    {
        if(MatchKeyData(ptr2->data,key2))
        {
            found2=TRUE;
        }
        else
        {
            prev2=ptr2;
            ptr2=ptr2->next;
        }
    }
    if((!found1)||(!found2))
    {
        sc=FAILURE;
    }
    else if(ptr1!=ptr2)
    {
        //if ptr1==ptr2 then swapping them doesnot make sense
        if(prev1==NULL)
        {
            *head=ptr2;
        }
        else
        {
            prev1->next=ptr2;
        }
        if(prev2==NULL)
        {
            *head=ptr1;
        }
        else
        {
            prev2->next=ptr1;
        }
        temp=ptr1->next;
        ptr1->next=ptr2->next;
        ptr2->next=temp;

    }
    return sc;

}
Status InsertBetween(Node* p,Node* q,Node* r,Node** headptr)
{
//assumes p and r are consecutive.inserts q between p and r
    Status sc=SUCCESS;
    if(q==NULL)
    {
        //the Node to insert is NULL itself ,therefore error case
        sc=FAILURE;
    }
    else
    {
        if(p==NULL)
        {
            //INSERT AT START
            if(r!=*headptr)
            {
                sc=FAILURE;
            }
            else
            {
                q->next=*headptr;
                *headptr=q;
            }
        }
        else
        {
            if(p->next!=r)
            {
                sc=FAILURE;
                //p and r are required to be consecutive.IN THIS CASE THEY ARE NOT-ERROR CASE
            }
            else
            {
                q->next=r;
                p->next=q;
            }
        }
    }
    return sc;
}
Node* ReverseLinkedList(Node* head)
{
//REVERSES LINKS OF THE LINKED LIST AND RETURNS POINTER TO THE MODIFIED 0TH Node
    Node* tail;
    Node* lptr=head;
    Node* middle;
    middle=NULL;
    while(lptr!=NULL)
    {
        tail=middle;
        middle=lptr;
        lptr=lptr->next;
        middle->next=tail;
    }
    return middle;
}


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
Status MakeTreeNode(ItemType data)
{
    Status sc=SUCCESS;
    TreeNode* nptr=(TreeNode*)malloc(sizeof(TreeNode));
    if(nptr != NULL)
    {
        nptr->data=data;
        nptr->left=NULL;
        nptr->right=NULL;
    }
    else //nptr == NULL
    {
        sc=FAILURE;
    }
    return sc;
}
void visit(TreeNode* node)
{
    printItem(node->data);       //!!!!!!!----CHANGE HERE IF ITEMTYPE CHANGES
    return;
}
Bool isLeaf(TreeNode* root)
{
    return (root->left == NULL && root->right == NULL);
}
void InOrder(TreeNode* root)
{
    if(root != NULL)
    {
        InOrder(root->left);
        visit(root);
        InOrder(root->right);
    }
    return;
}

void PreOrder(TreeNode* root)
{
    if(root != NULL)
    {
        visit(root);
        PreOrder(root->left);
        PreOrder(root->right);
    }
    return;
}

void PostOrder(TreeNode* root)
{
    if(root != NULL)
    {
        PostOrder(root->left);
        PostOrder(root->right);
        visit(root);

    }
    return;
}
TreeNode* InsertTreeNode(TreeNode* root,TreeNode* nptr)
{
    TreeNode* p=root;
    Bool done=FALSE;
    if(root == NULL)
    {
        root = nptr;
    }
    else
    {
        while(!done)
        {
            if(isFirstItemGreater(p->data,nptr->data))
            {
                if(p->left == NULL)
                {
                    done=TRUE;
                    p->left=nptr;
                }
                else
                {
                    p=p->left;
                }
            }
            else if(isSecondItemGreater(p->data,nptr->data))
            {
                if(p->right == NULL)
                {
                    done=TRUE;
                    p->right=nptr;
                }
                else
                {
                    p=p->right;
                }
            }
            else
            {
                printf("ERROR!\n");
                done=TRUE;
            }
        }
    }
    return root;
}
void DeleteTreeNodeFunction(TreeNode** node)
{
    TreeNode* p,*q;
    if((*node) == NULL)
    {
        ;
    }
    else
    {
        if((*node)->right == NULL)
        {
            p=*node;
            *node=(*node)->left;
            printf("DELETED ");
            printItem(p->data);
            printf("\n");
            free(p);
        }
        else if((*node)->left == NULL)
        {
            p=*node;
            printf("DELETED ");
            printItem(p->data);
            printf("\n");
            free(p);
        }
        else        // neither left child nor right child of the node to be deleted is NULL
        {
            //IN THIS APPROACH EITHER THE HEIGHT OF THE TREE REMAINS THE SAME OR DECREASES--SO THIS IS QUIET AN EFFIECIENT APPROACH
            p=NULL;
            for(q=(*node)->left;q->right != NULL;)
            {
                p=q;
                q=q->right;
            }
            // p can never be NULL here(THINK WHY?)
            p->right=q->left;//q need not be a leaf node although it is the rightmost node in the subtree
            q->left=(*node)->left;
            q->right=(*node)->right;
            //p's job done now p can be used for some other purpose
            p=*node;
            *node=q;
            printf("DELETED ");
            printItem(p->data);
            printf("\n");
            free(p);
            p=NULL;

        }
    }
    return;
}
TreeNode* DeleteTreeNode(TreeNode* root,int key)
{
    TreeNode* p=root,*prev=NULL;
    Status sc=SUCCESS;
    while(p!=NULL && !areItemsEqual(p->data,key))
    {
        if(p->data > key)
        {
            prev=p;
            p=p->left;
        }
        else                                //p->data < key
        {
            prev=p;
            p=p->right;
        }
    }
    if(p == NULL)
    {
        sc=FAILURE;
        printf("NOT FOUND\n");
    }
    else
    {
        if(p == root)
        {
            DeleteTreeNodeFunction(&root);
        }
        else
        {
            if(p == prev->left)
            {
                DeleteTreeNodeFunction(&(prev->left));
            }
            else    // p == prev->right(why else if(p==prev->right) is not necessary--DOUBT???)
            {
                DeleteTreeNodeFunction(&(prev->right));
            }
        }
    }
    return root;
}
TreeNode* SearchBST(TreeNode* root,ItemType key)
{
    TreeNode* p=root;
    while(p != NULL && !areItemsEqual(p->data,key))
    {
        if(isFirstItemGreater(p->data,key))
        {
            p=p->left;
        }
        else //if(p->data < key)
        {
            p=p->right;
        }
    }
    return p;
}
void MirrorImg(TreeNode* root)
{
    TreeNode* temp;
    if(root == NULL || isLeaf(root))
    {
        ;
    }
    else    //root != NULL
    {
        temp=root->left;
        root->left=root->right;
        root->right=temp;
        MirrorImg(root->left);
        MirrorImg(root->right);
    }
    return;
}
/*
    IF YOU FIND ANYTHING INCORRECT PLEASE REPORT TO THE AUTHOR OF THIS CODE
    
*/
