/*
        -IMPORTANT C-FUNCTIONS USEFUL IN DATA STRUCTURES AND PROGRAM DESIGN COURSES IN C LANGUAGE
        (PLEASE ALSO FIND stdc.c file)
                PREPARED BY:    -ABDUL SATTAR MAPARA
                                 abdulsmapara.github.io
                                 abdulsmapara@gmail.com    
*/
#ifndef STDC_LIBRARY_H_INCLUDED
#define STDC_LIBRARY_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#ifndef INDEX_INVALID
#define INDEX_INVALID -1
#endif
#ifndef SIZE_PRIORITY_QUEUE 
#define SIZE_PRIORITY_QUEUE 100
#endif

typedef enum{FAILURE=0,SUCCESS=1} Status;
typedef enum{FALSE=0,TRUE=1} Bool;
typedef int ItemType;
void printItem(ItemType data);
void scanItem(ItemType* data);
Bool areItemsEqual(ItemType data1,ItemType data2);
Bool isFirstItemGreater(ItemType data1,ItemType data2);
Bool isSecondItemGreater(ItemType data1,ItemType data2);
typedef ItemType KeyType;
typedef struct NodeTag
{
    ItemType data;
    struct NodeTag* next;
}Node;
typedef struct C_NodeTag    //FOR CIRCULAR LINKED LIST NODE
{
    ItemType data;
    struct C_NodeTag* next;
}CNode;
typedef struct D_NodeTag    //FOR DOUBLY LINKED LIST NODE
{
    ItemType data;
    struct D_NodeTag* next,*prev;
}DNode;
typedef struct QueueDSTag      //FOR QUEUE USING LINKED LISTS
{
    Node* front;
    Node* rear;
}QueueDS;

//structure for priorityqueue
typedef struct PriorityQueueTag
{
    QueueDS queue[SIZE_PRIORITY_QUEUE];
}PriorityQueue;
typedef struct TreeNodeTag
{
    ItemType data;
    struct TreeNodeTag* left;
    struct TreeNodeTag* right;
}TreeNode;
void BubbleSort(int A[],int low,int high);//low is the start from which sorting is to be started
void InsertionSort(int A[],int low,int high);//high is the index upto which sorting should be done
void SelectionSort(int A[],int low,int high);
void MergeSelf(int A[],int low,int upto,int high);
void MergeSort(int A[],int low,int high);
int partitionAlgo(int A[],int low,int high,int x);//partitions array about x and returns position upto which elements<=x
void QuickSort(int A[],int low,int high);//QuickSort Algorithm

int LinearSearch(int A[],int low,int high,int searchThis);//low=index of element to start from;high=index of element to end at in an array
int BinarySearch(int A[],int low,int high,int searchThis);//low=index of element to start from;high=index of element to end at in a SORTED array
//!!!BINARY SEARCH ForSorted ARRAY only!!!
int RemDuplicatesSortedArr(int A[],int low,int high);//returns index in the array upto which it has non-repeating elements(after removing duplicates)---TIME COMPLEXITY=O(n)
float SqrtOf(float n);      //calculates square root of n(floating point number)
float Power(float base, unsigned int power);//calculates the value of (base float)to the power (power integer>=0)
float AbsoluteOf(float n);      //calculates absolute value of n and returns it
//!!!SPECIAL NUMBERS!!!
int GetNthFib(int n,int fterm,int sterm);//Function to get nth fibonacci number (support for Wrapper Function NthFib(int n))
int NthFib(int n);          //nth fibonacci number n=1 fib=0 n=2 fib=1 and so on...
int max(int a,int b);           //maximum of a and b
int min(int a,int b);           //minimum of a and b
typedef struct                  //QUEUE USING ARRAYS

{
    int rear;
    int front;
    int maxSize;                                    //for dynamic size of data array
    ItemType *data;
}Queue;
void InitializeQueue(Queue *qPtr);                  //Initializes rear,front variables in qptr queue
Queue * CreateQueues(Queue *qptr,int maxSize);      //creates a queue with data array of size=maxSize
Bool isQueueFull(Queue *qptr);                      //returns true if queue is full else returns false
Bool isQueueEmpty(Queue *qptr);                     //returns true if queue is empty else returns false
Status InsertInQueue(Queue *qptr,ItemType val);     //inserts an element in queue if isQueueFull returns false
Status DeleteFromQueue(Queue *qptr,ItemType *val);  //deletes an element in queue if isQueueEmpty returns false
//STACK USING ARRAYS
typedef struct 
{
    int top;
    int size;
    ItemType *array;
}Stack;
void InitializeStack(Stack *PointStack);//Initialize the stack top variable
Stack* CreateStacks(int size);//Implements  stack based on size given by user|||data structure on which it gets implemented is array currently.Can be changed by making changes in this file
Status PushOnStack(Stack *PointStack,ItemType val);//Push val on top of stack
Status PopFromStack(Stack *PointStack,ItemType *here);//Pop val from top of stack in 'here' variable
Bool isStackEmpty(Stack *PointStack);//returns true if stackisempty else returns false
Bool isStackFull(Stack *PointStack);//returns true if stackisfull else returns false
//STACKS USING LINKED LISTS
//WRAPPER FOR INFORMATION HIDING AND ABSTRCTION
typedef struct StackLinkedListTag
{
    Node* top;
}StackDS;   //STACK DATA STRUCTURE BASED ON LINKED LIST--important for the case described--#include "Stacks.h" #include "StacksLinkedLists.h"---same name would cause problem
Node* MakeNode(ItemType data);                      //MAKES A SINGLE Node and inserts data into it ..returns pointer to the newly made Node if MEMORY IS AVAILABLE ELSE RETURNS NULL
void InitializeStackDS(StackDS *sptr);              //INITIALIZES STACK TO DEFAULT VALUE
Bool isStackDSEmpty(StackDS *sptr);                 //returns true if stack is empty
Bool isStackDSFull(StackDS* sptr);                  //since LINKED LIST size is theoretically infinite,this function returns back FALSE always
Status PushOnStackDS(StackDS *sptr,ItemType data);  //PUSH DATA ON STACKDS
Status PopFromStackDS(StackDS *sptr,ItemType* dptr);    //POPS DATA FROM STACKDS and PROVIDES DATA DELETED THROUGH dptr(if atall data was deleted)-----returns SUCCESS if Node is deleted else returns FAILURE(incase when stack is empty)
void swapNodesInLL(Node* ptr,Node* prev,Node** lpptr);

Node* BubbleSortLL(Node* lptr);
Node* InsertNodeAtStart(Node* head,ItemType data);  //CREATES a Node AND PUTS IN data in its data field..returns new head pointer
Node* CreateList(int num);                          //CREATES num NUMBER OF NodeS and RETURNS HEAD TO THE START OF THE LINKED LIST
void TraverseList(Node* head);                      //TAKES in POINTER TO START OF THE LIST prints DATA PRESENT IN THE NodeS AND RETURNS
Status DeleteAtStart(Node** head,ItemType* dptr);   //TAKES POINTER TO POINTER TO HEAD AND POINTER TO DATA AS INPUT and STORES DATA TO BE DELETED AND FREE UP THE LOACTION *head POINTS TO 
void DeleteList(Node *head);                    //DELETES COMPLETE LIST
Bool MatchKeyData(ItemType data,KeyType key);   //returns true if data and key matches
    //if data is large and key is value of element of data then changes can be made in this function 
Status SwapTwoNodes(Node** head,KeyType key1,KeyType key2);//swaps Nodes whose keys are given here
    //NOTE: Nodes are swapped by changing links as swapping data of Nodes may be expensive in many situations when data contains many fields
Status InsertBetween(Node* p,Node* q,Node* r,Node** headptr);//assumes p and r are consecutive.inserts q between p and r
Node* ReverseLinkedList(Node* head);//REVERSES LINKS OF THE LINKED LIST AND RETURNS POINTER TO THE MODIFIED 0TH Node

//QUEUE USING LINKED LISTS
void InitializeQueueDS(QueueDS* qptr);
Bool isQueueDSFull(QueueDS* qptr);
Bool isQueueDSEmpty(QueueDS* qptr);
Status InsertInQueueDS(QueueDS* qptr,ItemType data);
Status DeleteFromQueueDS(QueueDS* qptr,ItemType* dptr);

void InitializePriorityQueue(PriorityQueue* pqptr,int size);
Bool isPriorityQueueEmpty(PriorityQueue* pqptr,int size);
Bool isPriorityQueueFull(PriorityQueue* pqptr);
Status InsertInPriorityQueue(PriorityQueue* pqptr,int Priority,ItemType data,int size);
Status DeleteFromPriorityQueue(PriorityQueue* pqptr,int Priority,ItemType* dptr,int size);
//TREE DATA STRUCTURE
Status MakeTreeNode(ItemType data);
void visit(TreeNode* node);
Bool isLeaf(TreeNode* root);
void InOrder(TreeNode* root);
void PreOrder(TreeNode* root);
void PostOrder(TreeNode* root);
TreeNode* InsertTreeNode(TreeNode* root,TreeNode* nptr);
void DeleteTreeNodeFunction(TreeNode** node);
TreeNode* DeleteTreeNode(TreeNode* root,int key);
TreeNode* SearchBST(TreeNode* root,ItemType key);
void MirrorImg(TreeNode* root);
#endif
/*
IF YOU FIND ANYTHING INCORRECT PLEASE REPORT TO THE AUTHOR OF THIS CODE
*/
