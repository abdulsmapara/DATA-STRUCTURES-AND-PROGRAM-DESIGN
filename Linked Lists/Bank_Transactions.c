/*
			VISVESVARAYA NATIONAL INSTITUTE OF TECHNOLOGY,NAGPUR
				COMPUTER SCIENCE AND ENGINEERING DEPARTMENT
					DATA STRUCTURES AND PROGRAM DESIGN-II
						SEMESTER-4 ASSIGNMENT-1
								R3 BATCH
					TOPIC:LINKED LISTS and its APPLICATIONS
								 -ASSIGNMENT DONE BY:-
					   --ABDUL SATTAR MAPARA		--ROHAN SALVI
					  	 BT16CSE053					  BT16CSE077
					  				-GUIDED BY:-
					  		  	   RESPECTED R.B.KESKAR SIR 
					  		  	   RESPECTED Y.CHOPDE SIR
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define NOT_DONE -1
#define INVALID_BALANCE -1
#define LOW_AMOUNT_DEBIT "0"
#define START_TRANSACTION_ID 111
#define MAX_ACCOUNT_SIZE 10
#define ANSWER 4
#define DEBIT_CASE 1
#define CREDIT_CASE 2
#define END_FOR_k 3
#define ABORT_CASE 3
#define REVERT_CASE 4
#define FAILURE_CASE 5
#define EXIT 0
#define MIN_RATING 0
#define MAX_RATING 5
#define AVG_RATING 3

typedef enum{PARTIAL=-1,FAILED,COMPLETE} TransactionStatus;
//PARTIAL=DEBIT DONE,CREDIT PENDING
//FAILED=STATE WHEN REVERTED(AS REVERT CAN OCCUR ON COMPLETE/PARTIAL EXTRA STATUS REQUIRED TO PREVENT REVERT O REVERTED TRANSACTION)
//COMPLETE=DEBIT=DONE,CREDIT=DONE
typedef enum{FAILURE,SUCCESS} Status;
typedef enum{FALSE,TRUE} Bool;
typedef struct AccountTag
{
	char account_id[MAX_ACCOUNT_SIZE];
	int amount;
	struct AccountTag* next;
}Account;
typedef struct TransactionDetails
{
	/*<flags>*/
	int debit_flag;//stores node number at which debit occurs
	int credit_flag;//stores node number at which credit occurs
	/*</flags>*/
	int transactionId;
	int transaction_amount;
	char source[MAX_ACCOUNT_SIZE];
	char target[MAX_ACCOUNT_SIZE];
	TransactionStatus isDone;
	struct TransactionDetails* nextTransaction;
}Transaction;

void Load(char* str)
{
	/*
	LOAD FUNCTION TO ANIMATE LOADING EFFECT ON CONSOLE
	*/
	int msec = 0;
    const int trigger = 500; // ms
    const int printWidth = 4;
    int counter = 0,i;
    clock_t before = clock();
    int timed=0;
    while (timed++<30000)
    {
        fputs(str, stdout);
        clock_t difference = clock() - before;
        msec = difference * 1000 / CLOCKS_PER_SEC;
        if (msec >= trigger)
        {
            counter++;
            msec = 0;
            before = clock();
        }
        for (i = 0; i < counter; ++i)
        {            
            fputc('.', stdout);
        }
        for (i = 0; i < printWidth - counter; ++i)
        {
            fputc(' ', stdout);
        }
        fputc('\r', stdout);
        fflush(stdout);

        if (counter == printWidth)
        {
            counter = 0;
        }
    }
    return;
}
Status InsertAtStart(Account** lpptr,Account* nptr)
{
	/*
	INSERTS ACCOUNT NODE AT START IN ACCOUNT LIST
	*/
	Status sc=SUCCESS;
	if(nptr==NULL)
	{
		sc=FAILURE;
	}
	else
	{
		if(*lpptr==NULL)
		{
			*lpptr=nptr;
			(*lpptr)->next=NULL;
		}
		else
		{
			nptr->next=*lpptr;
			(*lpptr)=nptr;
		}
	}
	return sc;
}
Account* LoadDataBase()
{
	/*
		CREATES ACCOUNT NODES AND ADDS TO THE LIST AND RETURNS HEAD POINTER TO THE LIST
	*/
	int i;
	Status sc=SUCCESS;
	char acc_id[MAX_ACCOUNT_SIZE];
	Account* head=NULL,*nptr;
	FILE* fp=NULL;
	fp=fopen("ACCOUNTS.txt","r");
	Load("LOADING ACCOUNT DATABASE FROM ACCOUNTS.txt");
	if(fp==NULL)
	{
		printf("SOMETHING WENT WRONG...");
	}
	else
	{
		while((fscanf(fp,"%s",acc_id) != EOF)&&sc)
		{
			nptr=(Account*)malloc(sizeof(Account));
			if(nptr != NULL)
			{
				strcpy(nptr->account_id,acc_id);
				fscanf(fp,"%d",&(nptr->amount));
				sc=InsertAtStart(&head,nptr);
			}
			else
			{
				sc=FAILURE;
			}
		}
		if(sc==SUCCESS)
		{
			printf("DATABASE LOADED SUCCESSFULLY\t\t\t\t\t\n");
		}
		else
		{
			printf("------!!!DATABASE LOADING FAILED!!!------\n");
		}

		fclose(fp);
		fp=NULL;
	}
	return head;
}
Status GenerateTransactionId(char* source,char* target,int amount,Transaction** transaction_head,Status sc,Transaction** transaction_tail,int numNode)
{
	/*
		Generates node of Transaction type when debit occurs
	*/
	 Status sc_local=FAILURE;
	 Transaction* transaction_generator;
	 static int idOfTransaction=START_TRANSACTION_ID;
	 idOfTransaction++;
	 transaction_generator=(Transaction*)malloc(sizeof(Transaction));
	 if(transaction_generator!=NULL)
	 {
	 	sc_local=SUCCESS;
	 	strcpy(transaction_generator->source,source);
		strcpy(transaction_generator->target,target);
		transaction_generator->transactionId=idOfTransaction;
		transaction_generator->transaction_amount=amount;
		transaction_generator->nextTransaction=NULL;
		transaction_generator->debit_flag=numNode;	//Transaction Node generated only during debit
		transaction_generator->credit_flag=NOT_DONE;//when transaction node generated initialize every other flag(other than debit flag as debit flag holds the value of sub-operation number on which transaction id was generated)
		
		if(sc==SUCCESS)
			transaction_generator->isDone=PARTIAL;	//when just transaction id generated and debit is success(no error for low amount-note:no node is created when low amount error occurs because we assume that low amount error means no transaction),transaction is said to be done partially
		else
			transaction_generator->isDone=FAILED;
		
		//INSERT AT END---WHY??? HEAD POINTS TO THE TRANSACTION OCCURED AT FIRST NOT RECENTLY THEREBY MAKING IT EASY TO CATCH kth SUB-OPERATION LIMITS--(needed in main function)
		//tail pointer kept to make insert at end O(1) as we need not traverse the whole list again
		 if(*transaction_head==NULL)
		 {
		 	*transaction_head=transaction_generator;
		 	*transaction_tail=*transaction_head;
		 	(*transaction_head)->nextTransaction=NULL;
		 }
		 else
		 {
		 	(*transaction_tail)->nextTransaction=transaction_generator;
		 	*transaction_tail=transaction_generator;
		 	(*transaction_tail)->nextTransaction=NULL;
		 }
	}
	return sc_local;	//return if at all id could be generated or not
}
Status Debit(Account* head,char* source,char* target,int* balance,int debit_amount,Transaction** headTransaction,Transaction** tailTransaction,int numNode)
{
	Status sc=SUCCESS;
	Status TransactionStatus;
	Bool found=FALSE;
	Account* lptr=head;
	char account_id[MAX_ACCOUNT_SIZE];
	time_t t;		//for timestamp
	//search node with acc no in ACCOUNT DATABASE--if at all such an acc_no exist
	while(lptr!=NULL&&!found)
	{
		if(!(strcmp(source,lptr->account_id)))
		{
			found=TRUE;
		}
		else
		{
			lptr=lptr->next;
		}
	}
	if(found)
	{
		if(lptr->amount >= debit_amount)
		{
			lptr->amount-=debit_amount;//success of debit
			if(debit_amount>0)
			{
				printf("CURRENT AMOUNT IN %s:\t%d\n",lptr->account_id,lptr->amount);
			}
			
		}
		else
		{
			sc=FAILURE;//amount low - failure
			printf("\n");
			debit_amount=0;
			printf("-------!!!!LOW AMOUNT IN YOUR ACCOUNT!!!!------\n",lptr->amount);
		}
		TransactionStatus=GenerateTransactionId(source,target,debit_amount,headTransaction,sc,tailTransaction,numNode);
			if(TransactionStatus==SUCCESS)
			{
				printf("TRANSACTION ID:\t%d\n",(*tailTransaction)->transactionId);//print transaction id of tail as transaction nodes are inserted at the end and the most recent node is at the last 
				time(&t);
				printf("TIMESTAMP: %s",ctime(&t));
				printf("SOURCE:\t%s\n",source);//source and (*tailTransaction)->source is one and the same thing ...similar thing goes for target and amount
				printf("TARGET:\t%s\n",target);
				printf("TRANSACTION AMOUNT:\t%d\n",debit_amount);
			
			}
			else
			{
				sc=FAILURE;//could not generate transaction id---------look into this later
			}
		*balance=lptr->amount;//send balance
	}
	else
	{
		sc=FAILURE;//not found-failure
		*balance=INVALID_BALANCE;//no account so no question of balance data so returning invalid balance data
	}
	return sc;
}
Status Credit(Account* head,Transaction* transaction_head,int transaction_id,int numNode)
{
	/*<var declarations>*/

	Status sc=SUCCESS;
	Transaction* lptr;
	Account* acc_trv;
	Bool found=FALSE;
	Bool caught;
	int nodeNum=0;
	char acc_credit_id[MAX_ACCOUNT_SIZE];

	/*</var declarations>*/
	//traverse list of transaction nodes and check if the transaction id specified really exists or not
	lptr=transaction_head;
	while(lptr!=NULL&&!found)
	{
		if(lptr->transactionId==transaction_id)
		{
			found=TRUE; 
		}
		else
		{
			lptr=lptr->nextTransaction;
		}
	}
	if(found)
	{	//given transaction id found and currently held by lptr
		if(lptr->isDone==PARTIAL)
		{	//if only debit done(meaning assigned to partial)
			lptr->isDone=SUCCESS;
			//debit paired successfully with credit hence isDone changed to success
			acc_trv=head;
			caught=FALSE;
			strcpy(acc_credit_id,lptr->target);
			while(acc_trv!=NULL&&!caught)
			{
				if(!strcmp(acc_trv->account_id,acc_credit_id))
				{
					caught=TRUE;
					acc_trv->amount+=lptr->transaction_amount;
					lptr->credit_flag=numNode;//do this if t_id exists and state is partial
					if(lptr->transaction_amount!=0)
					{
						printf("AMOUNT IN %s:\t%d\n",acc_trv->account_id,acc_trv->amount);
					}
				}
				else
				{
					acc_trv=acc_trv->next;
				}
			}
			//there can never be the case that caught will be false when acc_trv becomes null as if debit occurs then it occured because account existed)
		}
		else //lptr->isDone==FAILED or COMPLETE
		{
			//if lptr->isDone ==FAILED--AFTER REVERT OR ABORT this case may occur
			//else(lptr->isDone == SUCCESS)
				//it means credit already took place for this transaction id and this transaction id is now in consistent state and no more credits can be entertained
			sc=FAILURE;
		}
	}
	else
	{
		//if given transaction id is invalid
		sc=FAILURE;
	}
	return sc;
}
Status Abort(int t_id,Transaction* headTransaction,Account* headAccount)	//t_id=transaction id
{
	Status sc_abort=SUCCESS;
	Transaction* lptr=headTransaction;
	Account* lptrAcc=headAccount;
	Bool found=FALSE;
	Bool caught;
	//search for transaction id
	while(lptr!=NULL&&!found)
	{
		if(lptr->transactionId==t_id)
		{
			found=TRUE;
		}
		else
		{
			lptr=lptr->nextTransaction;
		}
	}
	if(found)
	{
		//t_id is a valid transaction id
		if(lptr->isDone==PARTIAL)
		{
			//if debit took place successfully but credit didn't take place
			caught=FALSE;
			while(lptrAcc!=NULL&&!caught)
			{
				if(!strcmp(lptrAcc->account_id,lptr->source))
				{
					caught=TRUE;
					lptrAcc->amount+=lptr->transaction_amount;//credit operation in debitted account
					lptr->isDone=FAILED;//REVERT OR CREDIT SHOULD NOT OCCUR AFTER ABORT--TRANSACTION ABORTED
				}
				else
				{
					lptrAcc=lptrAcc->next;
				}
			}
			//caught can't be false when lptrAcc becomes NULL
		}
		else
		{
			//if credit already took place for this transaction id
			sc_abort=FAILURE;
		}
	}
	else
	{
		//if invalid transaction id is encountered
		sc_abort=FAILURE;
	}
	return sc_abort;
}
Status Revert(int t_id,Transaction* headTransaction,Account* headAccount)	//t_id=transaction id
{
	Status sc_revert=SUCCESS;
	Transaction* lptr=headTransaction;
	Account* lptrAcc=headAccount;
	Bool found=FALSE;
	Bool caught;
	while(lptr!=NULL&&!found)
	{
		if(lptr->transactionId==t_id)
		{
			found=TRUE;
		}
		else
		{
			lptr=lptr->nextTransaction;
		}
	}
	if(found)
	{
		if(lptr->isDone==PARTIAL||lptr->isDone==SUCCESS)
		{
			caught=FALSE;
			if(lptr->isDone==SUCCESS)
			{
				caught=FALSE;
				lptrAcc=headAccount;
				while(lptrAcc!=NULL&&!caught)
				{
					if(!strcmp(lptrAcc->account_id,lptr->target))
					{
						caught=TRUE;
						if(lptrAcc->amount >= lptr->transaction_amount)
						{
							lptrAcc->amount-=lptr->transaction_amount;
						}
						else
						{
							sc_revert=FAILURE;
						}
					}
					else
					{
						lptrAcc=lptrAcc->next;
					}
				}
			}
			while(lptrAcc!=NULL&&!caught&&sc_revert)
			{
				if(!strcmp(lptrAcc->account_id,lptr->source))
				{
					caught=TRUE;
					lptrAcc->amount+=lptr->transaction_amount;					
				}
				else
				{
					lptrAcc=lptrAcc->next;
				}
			}
			lptr->isDone=FAILED;//no further reverts are possible on this transaction_id

		}
		else
		{
			sc_revert=FAILURE;
		}

	}
	else
	{
		sc_revert=FAILURE;
	}
	return sc_revert;
}
void FailureOfTransaction(Transaction* headTransaction,Account* head)
{
	Transaction* lptrTransaction=headTransaction;
	Account* lptrAcc=head;
	Status sc_abort;
	Bool caught;
	while(lptrTransaction!=NULL)
	{
		if(lptrTransaction->isDone==PARTIAL)
		{

			lptrAcc=head;
			caught=FALSE;
			//sc_abort=Abort(lptrTransaction->transactionId,headTransaction,head);
			while(lptrAcc!=NULL&&!caught)
			{
				if(!strcmp(lptrTransaction->source,lptrAcc->account_id))
				{
					caught=TRUE;
					lptrAcc->amount+=lptrTransaction->transaction_amount;
					lptrTransaction->isDone=FAILED;
				}
				else
				{
					lptrAcc=lptrAcc->next;
				}
			}
			
			printf("REVERTED TRANSACTION WITH ID= %d SUCCESSFULLY\n",lptrTransaction->transactionId);
		}
		lptrTransaction=lptrTransaction->nextTransaction;
	}
	return;
}
void AccountTraverse(Account* head)
{
	Account* lptr;
	lptr=head;
	FILE* fp=NULL;
	fp=fopen("ACCOUNTS.txt","w");
	if(fp != NULL)
	{
		while(lptr!=NULL)
		{
			fprintf(fp,"%s ",lptr->account_id);
			fprintf(fp,"%d",lptr->amount);
			if(lptr->next != NULL)
			{
				fprintf(fp,"\n");
			}
			printf("ACCOUNT ID:%s\t",lptr->account_id);
			printf("AMOUNT:%d\n",lptr->amount);
			lptr=lptr->next;
		}

	}
	return;
}
Bool CheckConsistent(Transaction* headTransaction,int k,Account* headAccount)
{
	int i;
	Status sc_revert=SUCCESS;
	Bool isConsistent=TRUE;
	Transaction* ptr=headTransaction;
	i=1;
	while(ptr!=NULL&&i<=k&&sc_revert)
	{
		if(ptr->isDone==FAILED)//failure in debit took place
		{
			i++;
			ptr=ptr->nextTransaction;
		}
		else//debit is successful
		{
			if(ptr->credit_flag > k || ptr->credit_flag == NOT_DONE)
			{
				isConsistent=FALSE;
				sc_revert=Revert(ptr->transactionId,headTransaction,headAccount);
				if(sc_revert)
				{
					printf("TRANSACTION FOR TRANSACTION ID=%d REVERTED SUCCESSFULLY\n",ptr->transactionId);
				}
				else
				{
					printf("SORRY FOR INCONVIENCE!SYSTEM CRASHED\n");
				}
				//(int t_id,Transaction* headTransaction,Account* headAccount)	//t_id=transaction id
			}
			
			else //if(ptr->credit_flag <= k&&ptr->credit_flag!=NOT_DONE)
			{
				i++;
			}
			i++;
			ptr=ptr->nextTransaction;
		}
	}
	return isConsistent;
}
void DeleteTransaction(Transaction** headTransaction)
{
	Transaction* head=*headTransaction;
	Transaction* prev;
	while(head!=NULL)
	{
		prev=head;
		head=head->nextTransaction;
		free(prev);
		
	}
	*headTransaction=NULL;//important
	return;
}
int main()
{
	int numNode,choice,balance,main_amount,main_t_id,flag,k,decrease;
	char main_source[MAX_ACCOUNT_SIZE],main_target[MAX_ACCOUNT_SIZE];
	Status sc_debit,sc_credit,sc_abort,sc_revert;
	Transaction* headTransaction,*tailTransaction,*ptr;
	FILE* fp=NULL;
	Account* acc_head=LoadDataBase();
	printf("\t\tMENU\n1]\tDEBIT\n2]\tCREDIT\n0]\tEXIT\n");
	decrease=0;
	headTransaction=NULL;
	tailTransaction=NULL;
	flag=1;
	numNode=0;
	fp=fopen("TRANSACTION_TYPE_1.txt","r");
	if(fp==NULL)
	{
		printf("SOMETHING WENT WRONG...\n");
	}
	else
	{
		Load("FETCHING INPUT FROM FILE");
		printf("\t\t\t\t\n");
		while((fscanf(fp,"%d",&choice)) != EOF)
		{
			switch(choice)
			{
				case DEBIT_CASE:
							numNode++;
							//printf("ENTER SOURCE ACCOUNT NUMBER:\t");
							fscanf(fp,"%s",main_source);
							//printf("ENTER TARGET ACCOUNT NUMBER:\t");
							fscanf(fp,"%s",main_target);
							//printf("ENTER TRANSACTION AMOUNT:\t");
							fscanf(fp,"%d",&main_amount);
							//Account* head,char* source,char* target,int* balance,int debit_amount,Transaction** headTransaction
							Load("DEBITING");
							printf("PROCESSING DONE\n");
							sc_debit=Debit(acc_head,main_source,main_target,&balance,main_amount,&headTransaction,&tailTransaction,numNode);
							if(sc_debit==FAILURE)
							{
								printf("DEBIT FAILED\nACCOUNT BALANCE:%d\n",balance);
							}
							break;
				case CREDIT_CASE:
							numNode++;
							//printf("ENTER TRANSACTION ID:\t");
							fscanf(fp,"%d",&main_t_id);
							Load("CREDITING");
							printf("PROCESSING DONE\n");
							sc_credit=Credit(acc_head,headTransaction,main_t_id,numNode);
							if(sc_credit)
							{
								printf("CREDIT SUCCESSFUL FOR TRANSACTION ID %d\n",main_t_id);
							}
							else
							{
								decrease--;
								printf("CREDIT OPERATION FOR TRANSACTION ID %d FAILED\n",main_t_id);
							}
							break;
				case END_FOR_k:
							Load("FETCHING THE VALUE OF k");
						 	printf("\t\t\t\t\t\n");
							fscanf(fp,"%d",&k);
							printf("THE VALUE OF k is %d\n",k);
							Bool consistent=CheckConsistent(headTransaction,k+decrease,acc_head);
							if(consistent)
							{
								printf("\nSYSTEM CONSISTENT\n");
							}
							else
							{
								printf("THE SYSTEM TILL GIVEN k=%d WAS INITIALLY INCONSISTENT BUT NOW EVERYTHING TILL k IS CONSISTENT\n",k);
							}
							break;
				default:	
							printf("INCORRECT CHOICE\nTRY AGAIN\n");
							break;
				}
				
		 }
		 
		fclose(fp);
		fp=NULL;
		AccountTraverse(acc_head);
	}
	//QUESTION 2
	DeleteTransaction(&headTransaction);
	numNode=0;
	printf("\t\tMENU\n1]\tDEBIT\n2]\tCREDIT\n3]\tABORT\n4]\tREVERT\n5]\tFAILURE\n");
	fp=fopen("TRANSACTION_TYPE_2.txt","r");
	if(fp == NULL)
	{
		printf("SOMETHING WENT WRONG...\n");
	}
	else
	{
		Load("FETCHING INPUT FROM FILE");
		printf("\t\t\t\t\t\t\t\n");
		while((fscanf(fp,"%d",&choice)) != EOF)
		{
			//printf("ENTER A SUB-OPERATION:\n");
			//scanf("%d",&choice);
			switch(choice)
			{
				case DEBIT_CASE:
							numNode++;
							//printf("ENTER SOURCE ACCOUNT NUMBER:\t");
							fscanf(fp,"%s",main_source);
							//printf("ENTER TARGET ACCOUNT NUMBER:\t");
							fscanf(fp,"%s",main_target);
							//printf("ENTER TRANSACTION AMOUNT:\t");
							fscanf(fp,"%d",&main_amount);
							//Account* head,char* source,char* target,int* balance,int debit_amount,Transaction** headTransaction
							Load("DEBITING");
							printf("PROCESSING DONE\n");
							sc_debit=Debit(acc_head,main_source,main_target,&balance,main_amount,&headTransaction,&tailTransaction,numNode);
							if(sc_debit==FAILURE)
							{
								printf("DEBIT FAILED\nACCOUNT BALANCE:%d\n",balance);
							}
							break;
				case CREDIT_CASE:
							numNode++;
							//printf("ENTER TRANSACTION ID:\t");
							fscanf(fp,"%d",&main_t_id);
							Load("CREDITING");
							printf("PROCESSING DONE\n");
							sc_credit=Credit(acc_head,headTransaction,main_t_id,numNode);
							if(sc_credit)
							{
								printf("CREDIT SUCCESSFUL FOR TRANSACTION ID %d\n",main_t_id);
							}
							else
							{
								printf("CREDIT OPERATION FOR TRANSACTION ID %d FAILED\n",main_t_id);
							}
							break;
				case ABORT_CASE:	
							numNode++;
							//printf("ENTER TRANSACTION ID:\t");
							fscanf(fp,"%d",&main_t_id);
							//int t_id,Transaction* headTransaction,Account* headAccount
							Load("ABORTING");
							sc_abort=Abort(main_t_id,headTransaction,acc_head);
							if(sc_abort)
							{
								printf("ABORT OPERATION SUCCESSFUL FOR TRANSACTION ID %d\n",main_t_id);
							}
							else
							{
								printf("ABORT OPERATION FOR TRANSACTION ID %d FAILED\n",main_t_id);
							}
							break;
				case REVERT_CASE:
							numNode++;
							//printf("ENTER TRANSACTION ID:\t");
							fscanf(fp,"%d",&main_t_id);
							Load("REVERTING");
							sc_revert=Revert(main_t_id,headTransaction,acc_head);
							if(sc_revert)
							{
								printf("REVERT OPERATION SUCCESSFUL FOR TRANSACTION ID %d\n",main_t_id);
							}
							else
							{
								printf("REVERT OPERATION FOR TRANSACTION ID %d FAILED\n",main_t_id);
							}
							break;
				case FAILURE_CASE:
							numNode++;
							FailureOfTransaction(headTransaction,acc_head);
							break;
				default:	
							printf("INCORRECT CHOICE\nTRY AGAIN\n");
							break;
			}
		}
		fclose(fp);
		fp=NULL;
		ptr=headTransaction;
		Status abortSc=SUCCESS;
		Bool consistency=TRUE;
		while(ptr!=NULL&&abortSc)
		{
			if(ptr->isDone==PARTIAL)
			{
				consistency=FALSE;
				abortSc=Abort(ptr->transactionId,headTransaction,acc_head);
				if(abortSc)
				{
					printf("TRANSACTION WITH TRANSACTION ID=%d REVERTED SUCCESSFULLY\n",ptr->transactionId);
				}
				else
				{
					printf("SYSTEM CRASHED\n");
				}
			}
			ptr=ptr->nextTransaction;
		}
		if((!consistency)&&abortSc)
		{
			printf("INCONSISTENT STATE OF THE SYSTEM WAS ENCOUNTERED BUT WE REVERTED IT SUCCESSFULLY\n");
		}
		else if(abortSc)
		{
			printf("\nCONSISTENT SYSTEM\n");
		}
	}
	AccountTraverse(acc_head);

	printf("---------THANK YOU FOR USING OUR PROGRAM------------\n");
	printf("WE WOULD LIKE YOU TO RATE US(out of 5)---\n");	//MAX_RATING=5
	int rating;
	scanf("%d",&rating);
	while(rating<MIN_RATING||rating>MAX_RATING)
	{
		  if(rating>MAX_RATING)
		  {
		  	printf("WE KNOW YOU LOVE US BUT WE WOULD LIKE TO STAY DOWN TO EARTH\n");
		  }
		  else
		  {
		  	printf("AS INDIANS WE WOULD LIKE OUR MINIMUM RATING TO BE 0\n");//MIN_RATING=0
		  }
		  scanf("%d",&rating);
	}
	if(rating<AVG_RATING)
	{
		printf("WE ASSURE YOU THAT WE WILL BETTER OUR PROGRAM NEXT TIME!");
	}
	else if(rating<MAX_RATING)
	{
		printf("THANK YOU FOR YOUR RATING\nWE WOULD TRY GETTING 5 STARS THE NEXT TIME\n");
	}
	else
	{
		printf("WE ARE PROUD TO EARN THE 5 STARS! SPECIAL THANKS TO RESPECTED R.B.KESKAR SIR AND RESPECTED Y.CHOPDE SIR FOR MOTIVATING US BY THEIR OWN EXAMPLES.\n");
	}
	return 0;
}
