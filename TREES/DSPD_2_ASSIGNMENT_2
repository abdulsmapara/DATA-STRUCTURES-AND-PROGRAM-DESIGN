/*
				VISVSESVARAYA NATIONAL INSTITUTE OF TECHNOLOGY,NAGPUR
					COMPUTER SCIENCE and ENGINEERING DEPARTMENT
									2016-2020
						DATA STRUCTURES AND PROGRAM DESIGN-II
								    R3 BATCH
					ASSIGNMENT-2-IMPLEMENTING TREES(FAMILY TREES)
								:::AUTHORS OF THE CODE:::
					-ABDUL SATTAR MAPARA			-ROHAN SALVI
					 BT16CSE053						 BT16CSE077
					 			  :::DATE(s) OF CREATION:::
					 		  24th MARCH,2018 - 01st APRIL,2018
					 				 :::GUIDED BY:::
					 -RESPECTED R.B.KESKAR SIR		-RESPECTED Y.CHOPDE SIR
					  VNIT,NAGPUR					 VNIT,NAGPUR
					  				   :::VERSION:::
					  				   FINAL STABLE 1
									   :::BUGS:::
										UNKNOWN
*/
/*
	EXPECTED FILE FORMAT:
START OF A FAMILY:	
		[SURNAME] FAMILY
START OF A NODE:
	[MARITAL STATUS] [GENDER] [NAME] [AGE] [EARNINGS] [EDUCATIONAL QUALIFICATION WEIGHTAGE] [ACTIVE STATUS] [UID]
	(MALE FIRST IF MALE EXISTS)
END OF A NODE
	[NUMBER OF CHILDREN/CHILD]
START OF A CHILD:(PERSON WHO IS SOMEONE'S CHILD)
	CHILD
	SAME AS ANY NODE

	FOR EXAMPLE PLEASE VIEW FAMILY.txt
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MAX_NAME_LENGTH 50												//MAX_NAME_LENGTH
#define MAX_UID_LENGTH 13												//UID LENGTH
#define MAX_FAMILY_LENGTH 7
#define ref(x) (*(x))
#define DATA_SOURCE "FAMILY.txt"										//SOURCE FOR READING DATA
#define READ_MODE "r"
#define WRITE_MODE "w"
#define HASH_TABLE_SIZE 13												//HASH TABLE SIZE-PRIME
#define MAX_KEY_LENGTH_TO_BE_HASHED 5
#define INSERT 1
#define DEATH 2
#define SAME_FAMILY_CHECK 3
#define GET_SAVING_CAPACITY_OF_A_NODE 4
#define HIGHEST_LOWEST_SAVINGS_EDUCATION 5
#define HIGHEST_LOWEST_HEAD 6
#define PER_PERSON_SPENDING_AVG_EDUCATION 7
#define PER_PERSON_SPENDING_AT_A_LEVEL 8
#define DISPLAY_A_FAMILY 9
#define EXIT 0
#define BIRTH 1
#define MARRIAGE 2
#define SAVINGS 1
#define EDUCATION 2
#define DATA_SOURCE_UPDATE "FAMILY.txt"
#define REPORT_SUCCESS_TO_CRE 0
typedef enum {FALSE,TRUE} Bool;	
typedef enum{FAILURE,SUCCESS} Status;
typedef enum{MALE,FEMALE} Gender;
typedef enum{INIT_MAX=0,ILLITERATE=0,TENTH=1,TWELFTH,GRADUATE,INIT_MIN=7} Education_Qualification;
typedef enum{UNMARRIED,MARRIED} Marital_Status;
typedef enum{DEAD,LIVE} Active_Status;
typedef float Money;
typedef struct MemberNodeTag MemberNode;
typedef char* Key;
typedef MemberNode* ItemType;
typedef struct InfoTag
{
   char first_name[MAX_NAME_LENGTH];
   int age;
   Gender gender;
   Money earning;
   Education_Qualification education_qualification;
   Marital_Status marital_status;
   Active_Status active_status;
   char UID[MAX_UID_LENGTH];

}Person;//PERSON INFORMATION
typedef struct MemberNodeTag
{
	Person person_male,person_female;
	MemberNode** child;
	int num_child;
	Money saving_capacity;
}MemberNode;//MEMBER OF A FAMILY
typedef struct LinkedListNodeTag
{
	ItemType data;
	int level;
	struct LinkedListNodeTag* next;	
}Node;//NODE TO IMPLEMENT QUEUE
typedef struct QueueDSTag
{
	Node* front;
	Node* rear;
}QueueDS;//QUEUE AS DATA STRUCTURE--INFORMATION HIDING AVAILED
typedef struct ListNodeTag
{
	Key surname;
	MemberNode* root_family;
	struct ListNodeTag* next;
}Node_Identifier;//LINKED LIST NODE FOR IMPLEMENTING A HASH TABLE(BUCKETING)
typedef struct HashTableTag
{
	Node_Identifier* HashTable[HASH_TABLE_SIZE];
}Family_Identity;//TO AVAIL INFORMATION HIDING HASH TABLE THROUGH BUCKETING HIDDEN IN FAMILY_IDENTITY
int getHeight(MemberNode* member_identity)
{
	/*
		A UTILITY FUNCTION TO DETERMINE HEIGHT OF ANY TREE BELONGING TO THE FOREST
		NOTE THAT HEIGHT OF NULL NODE=-1
	*/
	int height,count,max_height_internal=-1,val_height;
	if(member_identity==NULL)
	{
		height=-1;
	}
	else if(member_identity->num_child==0)
	{
		height=0;
	}
	else
	{
		for(count = 0;count < member_identity->num_child ; count++)
		{
			val_height=getHeight(member_identity->child[count]);
			if(max_height_internal < val_height)
			{
				max_height_internal=val_height;
			}
		}
		height=1+max_height_internal;
	}
	return height;
}
Family_Identity* Initialize_Family_Identity(Family_Identity* fptr)
{
	/*
		INITIALIZATION FUNCTION FOR HASH TABLE THAT STORES POINTERS TO THE TREES IN THE FOREST
	*/
	int i;
	if(fptr!=NULL)
	{
		for(i=0;i<HASH_TABLE_SIZE;i++)
		{
			fptr->HashTable[i]=NULL;
		}
	}
	return fptr;
}
int HashFunction(Key surname)
{
	/*
		A SIMPLE HASH FUNCTION THAT ADDS THE ASCII VALUES OF SOME OF THE CHARACTERS OF SURNAME AND RETURNS A LOCATION IN THE HASH TABLE
	*/
	int value=0,upto=0;
	if(surname!=NULL)
	{
		while((upto)<MAX_KEY_LENGTH_TO_BE_HASHED && surname[upto]!='\0')
		{
			value += surname[upto];
			upto++;
		}
	}
	if(value < 0)
	{
		value=-1*value;
	}
	return (value % HASH_TABLE_SIZE);
}
Status InsertNewFamily(Family_Identity* fptr,Key surname,MemberNode* member_identity)
{
	/*
		INSERT A NEW FAMILY IN HASH TABLE(POINTER TO THE FAMILY TREE TO BE AVAILABLE IN YHE FOREST)
		RETURNS FAILURE IF DUPLICATE ENTRY FOUND
	*/
	int location=HashFunction(surname);
	Node_Identifier* head,*nptr;
	Status sc=SUCCESS;
	if(fptr==NULL||member_identity==NULL)
	{
		/*
			HASH TABLE SHOULD NOT BE NULL
			and NULL MEMBER NEED NOT BE ADDED
		*/
		sc=FAILURE;
		printf("ERROR IN HASH TABLE INSERTION\n");
	}
	else
	{
		head=fptr->HashTable[location];
		while(head!=NULL && sc)
		{
			/*
				THIS LOOP CHECKS FOR DUPLICATE ENTRIES
			*/
			if(strcmp(head->surname,surname)==0)
			{
				sc=FAILURE;
				printf("OUR PROGRAM DOES NOT APPRECIATE DUPLICATE SURNAMES\n");
			}
			else
			{
				head=head->next;
			}
		}
		if(sc)
		{
			/*
				REACH HERE IF DUPLICATES NOT FOUND
			*/
			nptr=(Node_Identifier*)malloc(sizeof(Node_Identifier));
			nptr->next=NULL;
			if(nptr!=NULL)
			{
				nptr->root_family=member_identity;
				nptr->surname=(Key)malloc(sizeof(char)*MAX_NAME_LENGTH);
				strcpy(nptr->surname,surname);
				nptr->next=fptr->HashTable[location];
				fptr->HashTable[location]=nptr;
			}
			else
			{
				sc=FAILURE;
				printf("MEMORY INSUFFICIENT\n");
			}
		}
	}
	return sc;
}
Node* MakeNode(ItemType data)
{
	/*
		MAKE A NODE OF A LINKED LIST (FOR IMPLEMENTATION OF A QUEUE)
	*/
	Node* ret=(Node*)malloc(sizeof(Node));
	if(ret!=NULL)
	{
		ret->level=0;
		ret->data=data;
		ret->next=NULL;
	}
	return ret;
}
void InitializeQueueDS(QueueDS* qptr)
{
	/*
		INITIALIZATION FUNCTION FOR QUEUE
	*/
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
	/*
		CHECKS IF A QUEUE IS EMPTY OR NOT
	*/
    return (qptr->front==NULL&&qptr->rear==NULL);
}
Status InsertInQueueDS(QueueDS* qptr,ItemType data)
{
	/*
		ENQUEUE IN QUEUE
	*/
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
	/*
		DEQUEUE FROM QUEUE
	*/
    Status sc=SUCCESS;
    Node* ptr;

    if(isQueueDSEmpty(qptr))
    {
        sc=FAILURE;
        *dptr=NULL;
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
MemberNode* new_MemberNode()
{
	/*
		MAKES A NODE FOR THE FAMILY TREE AND INITIALIZES IT WITH APPROPRIATE VALUES.
		DEPENDENT ON THIS INITIALIZATION ALL OTHER FUNCTIONS WORK PROPERLY SO THIS INITIALIZATION PLAYS AN IMPORTANT ROLE FOR THIS PROGRAM AND SHOULD NEVER BE TAKEN LIGHTLY.
	*/
	MemberNode* new_member=(MemberNode*)malloc(sizeof(MemberNode));
	if(new_member!=NULL)
	{
		(new_member->child)=NULL;
		new_member->num_child=0;
		new_member->person_male.first_name[0]='\0';
		new_member->person_male.age=0;
		new_member->person_male.gender=MALE;
		new_member->person_male.earning=0;
		new_member->person_male.education_qualification=ILLITERATE;
		new_member->person_male.marital_status=UNMARRIED;
		new_member->person_male.active_status=DEAD;
		new_member->person_male.UID[0]='\0';
		new_member->saving_capacity=0.0;
		new_member->person_female.first_name[0]='\0';
		new_member->person_female.age=0;
		new_member->person_female.gender=FEMALE;
		new_member->person_female.earning=0;
		new_member->person_female.education_qualification=ILLITERATE;
		new_member->person_female.marital_status=UNMARRIED;
		new_member->person_female.active_status=DEAD;
		new_member->person_female.UID[0]='\0';
	}
	return new_member;
}
MemberNode* FillHeadNode(MemberNode* head,FILE* fp)
{
	/*
		READS DATA FROM FILE FOR A NODE (1/2 MEMBERS)IN FAMILY TREE
	*/
	Marital_Status marital_status;
	Gender gender;
	fscanf(fp,"%d",&marital_status);
	if(head==NULL||fp==NULL)
	{
		printf("ERROR!\n");
	}
	else
	{
		switch(marital_status)
		{
			case MARRIED:
											head->person_male.marital_status=MARRIED;
											fscanf(fp,"%d",&head->person_male.gender);
											fscanf(fp,"%s",head->person_male.first_name);
											fscanf(fp,"%d",&head->person_male.age);
											fscanf(fp,"%f",&head->person_male.earning);
											fscanf(fp,"%d",&head->person_male.education_qualification);
											fscanf(fp,"%d",&head->person_male.active_status);
											fscanf(fp,"%s",head->person_male.UID);
											fscanf(fp,"%d",&head->person_female.marital_status);
											fscanf(fp,"%d",&head->person_female.gender);
											fscanf(fp,"%s",head->person_female.first_name);
											fscanf(fp,"%d",&head->person_female.age);
											fscanf(fp,"%f",&head->person_female.earning);
											fscanf(fp,"%d",&head->person_female.education_qualification);
											fscanf(fp,"%d",&head->person_female.active_status);
											fscanf(fp,"%s",head->person_female.UID);
											break;
							
			case UNMARRIED:

											fscanf(fp,"%d",&(gender));
											switch(gender)
											{
												case MALE:
															head->person_male.marital_status=UNMARRIED;
															head->person_male.gender=gender;
															fscanf(fp,"%s",head->person_male.first_name);
															fscanf(fp,"%d",&(head->person_male.age));
															fscanf(fp,"%f",&(head->person_male.earning));
															fscanf(fp,"%d",&(head->person_male.education_qualification));
															fscanf(fp,"%d",&(head->person_male.active_status));
															fscanf(fp,"%s",head->person_male.UID);
															break;
												case FEMALE:
															head->person_female.marital_status=UNMARRIED;
															head->person_female.gender=gender;
															fscanf(fp,"%s",head->person_female.first_name);
															fscanf(fp,"%d",&(head->person_female.age));
															fscanf(fp,"%f",&(head->person_female.earning));
															fscanf(fp,"%d",&(head->person_female.education_qualification));
															fscanf(fp,"%d",&(head->person_female.active_status));
															fscanf(fp,"%s",head->person_female.UID);
															break;
											}
											break;
		}
		fscanf(fp,"%d",&(head->num_child));
	}
	return head;
}
MemberNode* FindPerson(MemberNode* root_family,char* name)
{
	/*
		FIND IF A NODE WITH ONE MEMBER'S NAME 'name' EXISTS IN THE TREE ROOTED AT root
		IF YES RETURNS POINTER TO THAT NODE
		ELSE RETURNS A NULL POINTER
	*/
	MemberNode* ret=NULL;
	int count;
	if(root_family==NULL)
	{
		;
	}
	else
	{
		if(strcmp(root_family->person_male.first_name,name)==0 || strcmp(root_family->person_female.first_name,name)==0)
		{
			//BASE CASE
			ret=root_family;
		}
		for(count=0;count< root_family->num_child && ret==NULL;count++)
		{
			ret=FindPerson(root_family->child[count],name);
		}
	}
	return ret;
}
MemberNode* FindParentToAChild(MemberNode* root_family,char* name)
{
	/*
		'name'-NAME OF A CHILD
		RETURNS POINTER TO THE PARENT NODE ON SUCCESS
		ELSE RETURNS NULL POINTER
	*/
	MemberNode* ret=NULL;
	int count;
	if(root_family == NULL)
	{
		;
	}
	else
	{
		for(count=0;count < root_family->num_child && ret==NULL ; count++)
		{
			if(strcmp(root_family->child[count]->person_male.first_name,name)==0 || strcmp(root_family->child[count]->person_female.first_name,name)==0)
			{
				ret=root_family;
			}
		}
		for(count=0;count < root_family->num_child && ret==NULL ; count++)
		{
			ret=FindParentToAChild(root_family->child[count],name);
		}
	}
	return ret;
}
MemberNode* isClashed(Family_Identity* fptr,MemberNode* head)
{
	MemberNode* ret=NULL,*root=NULL;
	int i;
	Node_Identifier* node_identifier;
	Family_Identity* trv=fptr;
	
		for(i = 0;i < HASH_TABLE_SIZE && ret==NULL;i++)
		{
			node_identifier=trv->HashTable[i];
			while(node_identifier != NULL && ret==NULL)
			{
				 root = node_identifier->root_family;
				 ret = FindPerson(root,head->person_female.first_name);
				 if(ret != NULL && strcmp(ret->person_female.UID,head->person_female.UID) != 0)
				 {
				 	ret=NULL;
				 }
				 else
				 {

				 	ret=FindPerson(root,head->person_male.first_name);
				 	if(ret != NULL && strcmp(ret->person_female.UID,head->person_female.UID) != 0)
				 	{
				 		ret=NULL;
					}
				 }
				 
				node_identifier=node_identifier->next;
			}
		}
	
	return ret;
}
void MakeForestOfFamily(Family_Identity* fptr,MemberNode** root,FILE* fp)
{
	/*
		PROBABLY THE MOST IMPORTANT FUNCTION TO BRING THE INFORMATION FROM FILE TO THE PROGRAM FOR THE DATA TO BE ACCESSIBLE IN THIS PROGRAM.THIS IS A RECURSIVE CODE!
	*/
	MemberNode* head=NULL;
	MemberNode* clashed=NULL;
	/*EACH  NEW NODE IS POINTED TO BY head(initially NULL)*/
	int i;
	char identifier[MAX_FAMILY_LENGTH];
	char surname[MAX_NAME_LENGTH];
	if(fp==NULL)
	{
		/*IF FILE HANDLE IS IMPROPERLY SENT-JUST PRINT THE ERROR AND RETURN*/
		printf("ERROR IN OPENING FILE!\n");
	}
	else
	{

		if(fscanf(fp,"%s",identifier)==EOF)
		{
			printf("\n\n");
			/*
			BASE CASE(NOT EXACTLY--THIS IS JUST A SAFE CONDITION CHECK)-END OF READING OF FILE
			--ACCORDING TO THE FILE FORMAT,identifier=EITHER FAMILY(i.e. this function is just invoked) OR CHILD(this function still needs to continue to add children_nodes to parent_nodes previously made through this function(in this single invokation)) OR ITS THE END_OF_FILE CONDITION(in worst possible situation,for instance ---.txt file CONTAINING ONLY SURNAME(THAT IS ALREADY READ IN MAIN FUNCTION AND THERE IS NOTHING TO BE READ HERE))
			*/
		}
		else
		{
			/*REACH HERE IF THE CONTENTS OF THE FILE ARE STILL TO BE READ*/
			head=new_MemberNode();
			/*
				MAKE A NEW MEMBER NODE(WITH INITIALIZATION) 
			*/
			head=FillHeadNode(head,fp);
			/*
				READ A NODE'S DATA(i.e EITHER MALE+FEMALE DATA OR ONLY MALE/FEMALE DATA(IN CASE OF UNMARRIED))
			*/
			clashed = isClashed(fptr,head);
			if(clashed == NULL)
			{
				;
			}
			else
			{
				*root=clashed;
				free(head);
				head=clashed;
			}
			if((*root)==NULL)
			{
				/*IF FAMILY ROOT IS NULL LET THE FAMILY ROOT BE SET TO HEAD JUST CREATED*/
				*root=head;
			}
			if(head == NULL)
			{
				;//BASE CASE TO LEAVE AND RECUR BACK(IF IN SUCH A SITUATION)
				/*
					THIS IS THE BASE CASE TO STOP THE RECURSION i.e STOP IF A PARTICULAR NODE HAS NO CHILD AND COMPLETE THE PENDING TASKS IN THE PREVIOUS RECURSIVE CALLS(if they are made) BY UNFOLDING(THE UNFOLDING OF RECURSION STARTS)
				*/
			}
			else if( head->num_child==0)
			{
				;
			}
			else
			{
				/*NUMBER OF CHILDREN !=0 i.e WE NEED TO PEEP INTO THE FILE FURTHER--HERE WE MAKE THE USE OF THE SAME FUNCTION*/
				
					(head)->child=(MemberNode**)realloc((head->child),sizeof(MemberNode*)*(head->num_child));
					/*
						child(declared as MemberNode** child)
						is being pointed to an array of size=num_child
					*/
					if((head)->child==NULL)
					{
						printf("SORRY...MEMORY PROBLEM IN YOUR PC!PLEASE CONTACT THE AUTHOR\n");
					}
					else
					{

						for(i=0;i<(head->num_child);i++)
						{
							/*continue the process to attach the child nodes to their parents*/
							head->child[i]=NULL;
							MakeForestOfFamily(fptr,&(head->child[i]),fp);
						}
					}
				
				
			}
		}
	}

	return;
}
void DisplayFamilyMembers(MemberNode* root)
{	
	/*
		A UTILITY FUNCTION TO DISPLAY ALL FAMILY MEMBERS OF A FAMILY(LEVEL WISE)
	*/
	QueueDS q1;
	QueueDS* qptr=&q1;
	InitializeQueueDS(qptr);
	int count,level=0;
	MemberNode* p=root;
	
	while(p != NULL)
	{
		printf("LEVEL %d PERSON MALE: %s \tPERSON FEMALE: %s\n",level,p->person_male.first_name,p->person_female.first_name);
		for(count=0;count < p->num_child;count++)
		{
			InsertInQueueDS(qptr,p->child[count]);
			qptr->rear->level=level+1;
		}
		if(!isQueueDSEmpty(qptr))
		{
			level=qptr->front->level;
		}
		DeleteFromQueueDS(qptr,&p);
	}
	return;
}
Status DeleteTreeForFamily(MemberNode** root)
{
	/*
		UTILITY FUNCTION FOR DELETING A TREE FORMED FOR A FAMILY WHOSE SURNAME IS A DUPLICATE
	*/
	Status sc=SUCCESS;
	int count;
	if((*root) == NULL)
	{
		sc=FAILURE;
	}
	else
	{
		for(count=0;count < (*root)->num_child;count++)
		{
			DeleteTreeForFamily(&((*root)->child[count]));
		}
		free(*root);
		*root=NULL;
	}
	return sc;
}
MemberNode* SearchFamily(Family_Identity* fptr,Key surname)
{
	/*	
		HASH TABLE SEARCH FUNCTION
		SEARCHES IF A TREE EXISTS FOR A GIVEN SURNAME(FAMILY)
		RETURNS NULL (IF NOT FOUND) OR RETURNS POINTER TO THE ROOT OF THE FAMILY TREE(OF THE FAMILY BEING SEARCHED)
	*/
	int location=HashFunction(surname);
	Node_Identifier* ptr=fptr->HashTable[location];
	MemberNode* ret=NULL;
	while(ptr!=NULL && strcmp(ptr->surname,surname)!=0)
	{
		ptr=ptr->next;
	}
	if(ptr!=NULL)
	{
		ret=ptr->root_family;
	}
	return ret;
}
MemberNode* FindParent(MemberNode* root_family,char* name)
{
	//FIND A PERSON WHO IS ALSO A PARENT--NAME IS THE NAME OF THE PARENT(NOT CHILD)
	//SEARCH FUNCTION
	MemberNode* ret=NULL;
	int count;
	if(root_family == NULL)
	{
		;
	}
	else
	{
		if( strcmp(root_family->person_male.first_name,name)==0|| strcmp(root_family->person_female.first_name,name)==0)
		{
			if(root_family->person_male.marital_status==MARRIED)
			{
				ret=root_family;
			}
		}
		else
		{
			for(count=0;count<root_family->num_child && ret==NULL;count++)
			{
				ret=FindParent(root_family->child[count],name);
			}
		}
	}
	return ret;
}
Person* HeadMember(MemberNode* root,QueueDS* qptr,Bool* done,int* level)
{
	/*
		FUNCTION TO DETERMINE HEAD OF A FAMILY(IDENTIFIED BY ROOT POINTER)
		INPUT:QUEUE POINTER(SHOULD POINT TO A QUEUE),BOOL POINTER(SHOULD BE INITIALLY FALSE),LEVEL(INITIALLY 0-THIS IS REQUIRED BY ONE FUNCTION THAT USES THIS FUNCTION,OTHER FUNCTION(s) CAN PASS APPROPRIATE VALUE TO MEET THEIR NEEDS)
	*/
		MemberNode* p=root;
		Person* head=NULL;
		*done=FALSE;
		int count;
		InitializeQueueDS(qptr);
		while(p!=NULL && !(*done))
		{
			if(p->person_male.active_status==LIVE || p->person_female.active_status==LIVE)
			{
				if(p->person_male.active_status==LIVE)
				{
					printf("ALIVE NODE:\n");
					printf("HEAD(MALE):%s\t at LEVEL:%d Active_Status:%d\n",p->person_male.first_name,*level,p->person_male.active_status);
					*done=TRUE;
					head=&(p->person_male);
					printf("PERSON FEMALE:%s Active_Status:%d\n",p->person_female.first_name,p->person_female.active_status);
					

				}
				else
				{
					printf("ALIVE NODE:\n");
					printf("PERSON MALE: %s Active_Status:%d\n",p->person_male.first_name,p->person_male.active_status);
					printf("HEAD(FEMALE):%s\t at LEVEL %d Active_Status:%d\n",p->person_female.first_name,*level,p->person_female.active_status);
					*done=TRUE;
					head=&(p->person_female);
				}
			}
			else
			{
				for(count=0;count<p->num_child;count++)
				{
					InsertInQueueDS(qptr,p->child[count]);
					qptr->rear->level=(*level)+1;
				}
				if(!isQueueDSEmpty(qptr))
				{
					*level=qptr->front->level;
				}
				DeleteFromQueueDS(qptr,&p);
			}
		}
		return head;
}
Status Birth(Family_Identity* fptr)
{
	/*
		FUNCTION TO UPDATE A FAMILY'S TREE TO INSERT A NEW MEMBER DUE TO BIRTH
	*/
	Status sc=SUCCESS;
	char name[MAX_NAME_LENGTH];
	char surname[MAX_NAME_LENGTH];
	char UID[MAX_UID_LENGTH];
	Gender gender;
	MemberNode* root_family,*parent,*child_node=NULL;
	printf("ENTER SURNAME OF THE FAMILY IN WHICH THE CHILD IS BORN.ENTER IN CAPITALS TO AVOID ANY ERRORS!\n");
	scanf("%s",surname);
	root_family=SearchFamily(fptr,surname);
	if(root_family!=NULL)
	{
		/*
			IF PROVIDED FAMILY EXISTS REACH HERE
		*/
		printf("ENTER THE NAME OF ANY ONE PARENT\n");
		scanf("%s",name);
		parent=FindParent(root_family,name);
		if(parent != NULL && parent->person_male.active_status==LIVE && parent->person_female.active_status==LIVE)
		{
			/*
				IF PARENT NODE TO THE NEW MEMBER FOUND REACH HERE
			*/
			parent->child=(MemberNode**)realloc(parent->child,sizeof(MemberNode*)*(parent->num_child+1));
			if(parent->child==NULL)
			{
				sc=FAILURE;
				printf("MEMORY FAILURE\n");
			}
			else
			{
					(parent->num_child)++;
					printf("ENTER THE MANDATORY DETAILS:\n");
					printf("NAME:\t");
					scanf("%s",name);
					printf("GENDER\n0-MALE\t1-FEMALE\n");
					scanf("%d",&gender);
					printf("ENTER UID \n");
					scanf("%s",UID);
					while(strlen(UID) != (MAX_UID_LENGTH-1))
					{
						printf("UID SHOULD BE 12 DIGITS LONG.PLEASE ENTER CORRECT UID!\n");
						scanf("%s",UID);
					}
					child_node=new_MemberNode();
					if(child_node==NULL)
					{
						sc=FAILURE;
						printf("MEMORY FAILURE ON YOUR PC!\n");
					}
					else
					{
						switch(gender)
						{
							case MALE:
										strcpy(child_node->person_male.first_name,name);
										child_node->person_male.gender=gender;
										strcpy(child_node->person_male.UID,UID);
										child_node->person_male.active_status=LIVE;
										break;
							case FEMALE:
										strcpy(child_node->person_female.first_name,name);
										child_node->person_female.gender=gender;
										strcpy(child_node->person_female.UID,UID);
										child_node->person_female.active_status=LIVE;
										break;
						}
						parent->child[parent->num_child-1]=child_node;
					}
			}
		}
		else
		{
			sc=FAILURE;
			printf("PARENT NOT FOUND...\n");
		}
	}
	else
	{
			sc=FAILURE;
			printf("NO SUCH FAMILY EXISTS...\n");
	}		
		
	return sc;
}
Status Marriage(Family_Identity* fptr)
{
	/*
		FUNCTION TO UPDATE TWO FAMILY TREES DUE TO MARRIAGE
	*/
	char name[MAX_NAME_LENGTH];
	char name_male[MAX_NAME_LENGTH];
	Status sc=SUCCESS;
	Bool possible;
	int count;
	Node_Identifier* wife_ptr;
	char surname1[MAX_NAME_LENGTH];
	char surname2[MAX_NAME_LENGTH];
	MemberNode* husband,*wife,*family_male,*family_female,*parent_wife;
	wife=NULL;
	printf("HUSBAND INFO:\n");
	printf("FIRST NAME:\t");
	scanf("%s",name_male);
	printf("SURNAME:   \t");
	scanf("%s",surname1);
	family_male=SearchFamily(fptr,surname1);//SEARCH FOR MALE'S FAMILY
	if(family_male==NULL)
	{
		sc=FAILURE;
		printf("NO SUCH FAMILY EXISTS...\n");
	}
	else
	{
		husband=FindPerson(family_male,name_male);
		if(husband==NULL||(husband->person_male.active_status==DEAD)||(husband->person_male.marital_status==MARRIED)||(husband->person_female.first_name[0] != '\0'))
		{
			sc=FAILURE;
			printf("MARRIAGE IMPOSSIBLE HERE...\n");
		}
		else
		{
			printf("WIFE INFO:\n");
			printf("FIRST NAME\t");
			scanf("%s",name);
			printf("SURNAME   \t");
			scanf("%s",surname2);			
			family_female=SearchFamily(fptr,surname2);
			if(family_female==NULL)
			{
				printf("NOT POSSIBLE...FAMILY NOT FOUND\n");
				sc=FAILURE;
			}
			else if(strcmp(surname1,surname2)==0)
			{
				printf("THIS CASE IS NOT HANDLED BY THIS VERSION OF THE PROGRAM...\n");
				sc=FAILURE;
			}
			else
			{

				parent_wife=FindParentToAChild(family_female,name);
				/*FIND PARENT TO THE WIFE*/
				if(parent_wife != NULL)
				{
					//IF PARENT TO WIFE EXISTS REACH HERE
					for(count=0;count < parent_wife->num_child && wife == NULL;)
					{
						//GET POINTER TO THE WIFE HERE IN THE LOOP
						if(strcmp(parent_wife->child[count]->person_female.first_name,name)==0)
						{
							wife=parent_wife->child[count];
						}
						count++;
					}
					if(wife == NULL)
					{
						/*
							SOME KIND OF ERROR AS PARENT TO CHILD EXISTED BUT HERE CHILD IS NOT FOUND
							THIS CASE IS HANDLED FOR SAFETY AND WILL MOSTLY NEVER ARISE
							!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						*/
						sc=FAILURE;
						printf("IMPOSSIBLE CASE...\n");
					}
					else
					{
						if((wife->person_female.active_status==DEAD)||(wife->person_female.marital_status==MARRIED)||(wife->person_male.first_name[0] != '\0'))
						{
							sc=FAILURE;
							printf("NOT POSSIBLE...\n");
						}
						else
						{
							//SUCCESS-PART 1
							strcpy(husband->person_female.first_name,name);
							husband->person_female.age=wife->person_female.age;
							husband->person_female.education_qualification=wife->person_female.education_qualification;
							husband->person_female.earning=wife->person_female.earning;
							husband->person_male.marital_status=husband->person_female.marital_status=wife->person_female.marital_status=MARRIED;
							strcpy(husband->person_female.UID,wife->person_female.UID);
							parent_wife->child[count-1]=husband;
							free(wife);
							wife=NULL;
						}
					}
				}
				else	//NO PARENT TO WIFE
				{
					//i.e WIFE IS ROOT OF HER FAMILY TREE
					wife=family_female;
					if((wife->person_female.active_status==DEAD)||(wife->person_female.marital_status==MARRIED)||(wife->person_male.first_name[0] != '\0'))
					{
							sc=FAILURE;
							printf("NOT POSSIBLE\n");
					}
					else
					{
						//SUCCESS-PART 2
						strcpy(husband->person_female.first_name,name);
						husband->person_female.age=wife->person_female.age;
						husband->person_female.education_qualification=wife->person_female.education_qualification;
						husband->person_female.earning=wife->person_female.earning;
						husband->person_male.marital_status=husband->person_female.marital_status=wife->person_female.marital_status=MARRIED;
						strcpy(husband->person_female.UID,wife->person_female.UID);
						free(family_female);//delete the tree
						family_female=NULL;
						family_female=husband;//WIFE'S TREE IS NOW A PART OF HUSBAND'S FAMILY TREE
						//UPDATION IN HASH TABLE INFORMATION OF SURNAME2(FEMALE'S SURNAME)
						//FEMALE'S SURNAME IS STILL EXIXTENT BUT IT POINTS TO THE TREE INSIDE THE HUSBAND'S FAMILY TREE
						wife_ptr=fptr->HashTable[HashFunction(surname2)];
						while(wife_ptr!=NULL && strcmp(wife_ptr->surname,surname2)!=0)
						{
							wife_ptr=wife_ptr->next;						
						}
						//FAILURE NOT POSSIBLE
						wife_ptr->root_family=husband;
					}
						
				}

			}
			
		}
	}
	return sc;
}
Status Death(Family_Identity* fptr)
{
	/*
		FUNCTION TO UPDATE THE TREE DUE TO DEATH OF A MEMBER
	*/
	int count;
	int num_live;
	Money distribute;
	int trivial_level=0;
	QueueDS* qptr,q1;
	qptr=&q1;
	Status sc=SUCCESS;
	Bool done;
	char name[MAX_NAME_LENGTH],surname[MAX_NAME_LENGTH];
	MemberNode* person,*family;
	Person* head=NULL;
	printf("ENTER NAME:\t");
	scanf("%s",name);
	printf("SURNAME:   \t");
	scanf("%s",surname);
	family=SearchFamily(fptr,surname);//SEARCH FOR THE FAMILY
	if(family == NULL)
	{
		sc=FAILURE;
		printf("FAMILY NOT FOUND...\n");
	}
	else
	{
		person=FindPerson(family,name);
		//FIND THE PERSON WHO DIED
		if(person==NULL)
		{
			sc=FAILURE;
			printf("PERSON NOT FOUND\n");
		}
		else
		{
			if(strcmp(person->person_male.first_name,name)==0)
			{
				//IF MALE PERSON DIED(ACC. TO USER INFO) REACH HERE
				if(person->person_male.active_status==DEAD)
				{
					//CHECK IF ALREADY DEAD
					sc=FAILURE;
					printf("PERSON ALREADY INACTIVE\n");
				}
				else
				{
					//UPDATE IN NODE HERE
					person->person_male.active_status=DEAD;
					if(person->person_female.active_status==LIVE)
					{
						//IF FEMALE IS ALIVE GIVE AWAY ALL THE EARNINGS OF THE MALE PERSON TO THE FEMALE
						person->person_female.earning += person->person_male.earning;
					}
					else
					{
						//NODE BECAME INACTIVE HERE
						if(person->num_child==0)
						{
							//IF NUM_CHILD==0 REACH HERE AND GIVE AWAY EARNINGS TO THE HEAD OF THE FAMILY
							done=FALSE;
							head=HeadMember(family,qptr,&done,&trivial_level);//GET THE HEAD MEMBER
							if(head != NULL)
							{
								//IF HEAD TO THE FAMILY EXISTS(i.e THE FAMILY HAS ATLEAST ONE ALIVE MEMBER)
								head->earning += person->person_male.earning;

							}
						}
						else
						{
							//CHILDREN TO THE DEAD PERSON EXISTS AND SO GIVE AWAY EARNINGS TO THE CHILDREN(DISTRIBUTION SHOULD BE UNIFORM AND EQUAL)
							for(count=0,num_live=0;count < person->num_child;count++)
							{
								//CALCULATE THE NUMBER OF LIVE CHILDREN NODES TO THE DEAD PERSON
								if(person->child[count]->person_male.active_status==LIVE || person->child[count]->person_female.active_status==LIVE)
								{
									num_live++;
								}
							}
							if(num_live==0)
							{
								//IF NONE OF HIS CHILD NODES ARE ACTIVE AGAIN PASS ON THE EARNINGS TO THE HEAD OF THE FAMILY
								done=FALSE;
								head=HeadMember(family,qptr,&done,&trivial_level);
								if(head != NULL)
								{
									head->earning += person->person_male.earning;
								}
							}
							else
							{
								//IF LIVING CHILD NODES ARE PRESENT
								distribute=person->person_male.earning/(float)num_live;//MAKE EQUAL DISTRIBUTION--HERE WE NEGLECT ANY FRACTIONAL AMOUNT OF MONEY
								for(count=0;count < person->num_child;count++)
								{
									if(person->child[count]->person_male.active_status==LIVE && person->child[count]->person_female.active_status==LIVE)
									{
										//IF BOTH MEMBERS OF THE CHILD NODE ARE ALIVE THEN DISTRIBUTE AMONG THEM EQUALLY FURTHER
										person->child[count]->person_male.earning += distribute/2.0;
										person->child[count]->person_female.earning += distribute/2.0;
										
									}
									else if(person->child[count]->person_male.active_status==LIVE)
									{
										//ONLY MALE PERSON ALIVE
										person->child[count]->person_male.earning += (Money)distribute;

									}
									else if(person->child[count]->person_female.active_status==LIVE)
									{
										//ONLY FEMALE PERSON ALIVE
										person->child[count]->person_female.earning += (Money)distribute;

									}

								}
							}
						}
						
					}
					person->person_male.earning=0.0;
					//MAKE EARNINGS OF THE DEAD PERSON 0
					if(person->person_female.active_status==DEAD)
					{
						//IF FEMALE MEMBER ALSO DEAD THEN NODE BECOMES INACTIVE SO MAKE SAVING CAPACITY OF THE NODE=0
						person->saving_capacity=0.0;
					}
				}
			}
			else
			{
				//REPEAT WHOLE PROCESS FOR FEMALE-----COULD HAVE BEEN DONE THROUGH ONE FUNCTION AND TWO CALLS TO IT
				if(person->person_female.active_status==DEAD)
				{
					sc=FAILURE;
					printf("PERSON ALREADY INACTIVE\n");
				}
				else
				{
					person->person_female.active_status=DEAD;
					if(person->person_male.active_status==LIVE)
					{
						person->person_male.earning += person->person_female.earning;
					}
					else
					{
						if(person->num_child==0)
						{
							done=FALSE;
							head=HeadMember(family,qptr,&done,&trivial_level);
							if(head != NULL)
							{
								head->earning += person->person_female.earning;
							}
						}
						else
						{
							for(count=0,num_live=0;count < person->num_child;count++)
							{
								if(person->child[count]->person_male.active_status==LIVE || person->child[count]->person_female.active_status==LIVE)
								{
									num_live++;
								}
							}
							if(num_live==0)
							{
								done=FALSE;
								head=HeadMember(family,qptr,&done,&trivial_level);
								if(head != NULL)
								{
									head->earning += person->person_female.earning;
								}
							}
							else
							{
								distribute=person->person_female.earning/(float)num_live;
								for(count=0;count < person->num_child;count++)
								{
									if(person->child[count]->person_male.active_status==LIVE && person->child[count]->person_female.active_status==LIVE)
									{
										person->child[count]->person_male.earning += distribute/2.0;
										person->child[count]->person_female.earning += distribute/2.0;
										
									}
									else if(person->child[count]->person_male.active_status==LIVE)
									{
										person->child[count]->person_male.earning += (Money)distribute;

									}
									else if(person->child[count]->person_female.active_status==LIVE)
									{
										person->child[count]->person_female.earning += (Money)distribute;

									}

								}
							}
						}
						
					}
					person->person_female.earning=0.0;
					if(person->person_male.active_status==DEAD)
					{
						person->saving_capacity=0.0;
					}				
				}
			
			}
		}
	}
	return sc;
}
void CheckInSameFamily(MemberNode* root,MemberNode** person1,MemberNode** person2,char* name1,char* name2)
{
	/*
		DETERMINES IF TWO NODES BELONG TO THIS FAMILY(IDENTIFIED BY root) OR NOT
		A NODE IS SELECTED BASED ON THE FIRST NAMEs
	*/
	int count;
	if(root == NULL)
	{
		printf("!!!ERROR!!!\n");;//ERROR CONDITION---SINCE THIS FUNCTION IS CALLED INTERNALLY THIS FUNCTION DOES NOT RETURNS STATUS
	}
	else
	{
		if(strcmp(root->person_male.first_name,name1)==0 || strcmp(root->person_female.first_name,name1)==0)
		{
			*person1=root;
		}
	    if(strcmp(root->person_male.first_name,name2)==0 || strcmp(root->person_female.first_name,name2)==0)
		{
			*person2=root;
		}
		
		for(count=0;count< root->num_child && (*person1 == NULL || *person2 == NULL);count++ )
		{
			CheckInSameFamily(root->child[count],person1,person2,name1,name2);//RECURSIVE CALL
		}
		
	}
	return;
}
Bool TwoInSameFamily(Family_Identity* fptr)
{
	//FUNCTION TO CHECK IF TWO NODES BELONG TO THE SAME FAMILY OR NOT
	MemberNode* person1,*person2;
	person1=person2=NULL;
	int count;
	Node_Identifier* nptr;
	char name1[MAX_NAME_LENGTH],name2[MAX_NAME_LENGTH];
	printf("TO DETERMINE THE FIRST NODE. ENTER NAME OF A MEMBER:\t");
	scanf("%s",name1);
	printf("TO DETERMINE THE SECOND NODE. ENTER NAME OF A MEMBER:\t");
	scanf("%s",name2);
	for(count=0 ; count < HASH_TABLE_SIZE && (person1==NULL || person2==NULL);)
	{
		for(nptr=fptr->HashTable[count];nptr!=NULL && (person1==NULL || person2==NULL);nptr=nptr->next)
		{
			person1=person2=NULL;
			CheckInSameFamily(nptr->root_family,&person1,&person2,name1,name2);
		}
		count++;
	}
	return (person1 != NULL && person2 != NULL);//RETURNS TRUE OR FALSE APPROPRIATELY
}
Status DisplayAliveNodesAtHighestLowest(MemberNode* root)
{
	/*
		FUNCTION TO FIND OUT NODES WHICH ARE ALIVE AND ARE AT THE HIGHEST/LOWEST LEVEL
	*/
	Status sc=SUCCESS;
	MemberNode* p;
	QueueDS* qptr;
	QueueDS q1;
	qptr=&q1;
	int level_continue,count,height;
	int level=0;
	if(root==NULL)
	{
		sc=FAILURE;
	}
	else
	{
			p=root;
			qptr=&q1;
			InitializeQueueDS(qptr);
			level_continue=0;
			printf("HIGHEST LEVEL:\n");
			while(p!=NULL && level==level_continue)
			{
				if(p->person_male.active_status==LIVE || p->person_female.active_status == LIVE)
				{
					printf("ALIVE NODE:\n");
					printf("PERSON MALE:%s Active_Status:%d\n",p->person_male.first_name,p->person_male.active_status);
					printf("PERSON FEMALE:%s Active_Status:%d\n",p->person_female.first_name,p->person_female.active_status);	
				}
				for(count=0;count < p->num_child;count++)
				{
					InsertInQueueDS(qptr,p->child[count]);
					qptr->rear->level=level+1;
				}
				if(!isQueueDSEmpty(qptr))
				{
					level=qptr->front->level;
				}
				DeleteFromQueueDS(qptr,&p);
			}
			printf("\nLOWEST LEVEL:\n");
			InitializeQueueDS(qptr);
			//INITIALIZE QUEUE
			height=getHeight(root);//GET THE HEIGHT OF THE TREE TO KNOW THE LOWEST LEVEL
			p=root;
			level=0;
			while(p!=NULL && level != height)
			{
				//visit
				//COME OUT OF THE LOOP AS SOON AS LOWEST LEVEL REACHED
				for(count = 0;count < p->num_child;count++)
				{
					InsertInQueueDS(qptr,p->child[count]);
					qptr->rear->level=level+1;

				}
				if(!isQueueDSEmpty(qptr))
				{
					level=qptr->front->level;
				}
				DeleteFromQueueDS(qptr,&p);
			}
			while( p != NULL)
			{
				//PRINT ALL THE QUEUE MEMBERS
				if(p->person_male.active_status==LIVE || p->person_female.active_status == LIVE)
				{
					printf("ALIVE NODE:\n");
					printf("PERSON MALE:%s Active_Status:%d\n",p->person_male.first_name,p->person_male.active_status);
					printf("PERSON FEMALE:%s Active_Status:%d\n",p->person_female.first_name,p->person_female.active_status);
				
				}
				for(count = 0;count < p->num_child;count++)
				{
					InsertInQueueDS(qptr,p->child[count]);
					qptr->rear->level=level+1;
				}
				if(!isQueueDSEmpty(qptr))
				{
					level=qptr->front->level;
				}
				DeleteFromQueueDS(qptr,&p);
			}
		
	}
	return sc;
}
Status High_Low_Head(Family_Identity* fptr)
{
	/*
		FUNCTION THAT DRIVES THE FINDING OF HEAD AND NODES WHICH ARE ALIVE AND ARE AT THE HIGHEST/LOWEST  LEVELS 
	*/
	Status sc=SUCCESS;
	int choice,i;
	Family_Identity* trv;
	MemberNode* root_family,*person;
	Person *family_head=NULL;
	Bool done=FALSE;
	int level=0;
	QueueDS q1;
	Node_Identifier* head=NULL;
	Bool found;
	char UID[MAX_UID_LENGTH];
	char surname[MAX_NAME_LENGTH],name[MAX_NAME_LENGTH];
	printf("ENTER SURNAME:\t");
	scanf("%s",surname);
	root_family=SearchFamily(fptr,surname);
	if(root_family==NULL)
	{
		printf("FAMILY NOT FOUND...\n");
	}
	else
	{
		sc=DisplayAliveNodesAtHighestLowest(root_family);
	}
	//FIND HEAD OF THE FAMILY FOR A SELECTED NODE
	printf("\nWANT TO KNOW THE HEAD OF FAMILY FOR A SELECTED NODE----1-YES/0-NO?\t");
	scanf("%d",&choice);
	if(choice)
	{
		printf("ENTER FIRST NAME:\t");
		scanf("%s",name);
		printf("ENTER UID(for UNIQUE IDENTIFICATION:\t");
		scanf("%s",UID);
		while(strlen(UID) != MAX_UID_LENGTH-1)
		{
			printf("ENTER A VALID UID(12 DIGITS)\n");
			scanf("%s",UID);
		}
		found=FALSE;
		for(i=0;i < HASH_TABLE_SIZE && !found;i++)
		{
			head = fptr->HashTable[i];
			while(head != NULL && !found)
			{
				root_family=SearchFamily(fptr,head->surname);
				person=FindPerson(root_family,name);
				if(person != NULL)
				{
					if(strcmp(person->person_male.UID,UID)==0 || strcmp(person->person_female.UID,UID)==0)
					{
						found=TRUE;
						family_head=HeadMember(root_family,&q1,&done,&level);
					}
				}
				head=head->next;
			}
		}
		if(!found)
		{
			sc=FAILURE;
			printf("NO SUCH PERSON EXISTS!\n");
		}
	}
	return sc;
}
Status HighestLowestEducation(Family_Identity* fptr)
{
	/*
		FUNCTION TO DETERMINE NODES WHICH HAVE HIGHEST/LOWEST EDUCATIONAL QUALIFICATION AMONG SAME LEVEL NODES
		INPUT IN THE FUNCTION ROUTINE:LEVEL (AND ALSO SOME OTHER OBVIOUS THINGS)
	*/
	Status sc=SUCCESS;
	char surname[MAX_NAME_LENGTH];
	int level_to_be_considered,max_possible_level,count,level;
	MemberNode* root_family,*p;
	int curr_max_size=0,curr_min_size=0;
	MemberNode* arr_max=NULL,*arr_min=NULL;
	int max_edu=INIT_MAX,min_edu=INIT_MIN;
	Bool done;
	QueueDS q1;
	QueueDS* qptr;
	qptr=&q1;
	printf("ENTER SURNAME:\t");
	scanf("%s",surname);
	root_family=SearchFamily(fptr,surname);
	if(root_family==NULL)
	{
		printf("FAMILY DOES NOT EXIST...\n");
		sc=FAILURE;
	}
	else
	{
		max_possible_level=getHeight(root_family);
		printf("ENTER LEVEL:\t");
		scanf("%d",&level_to_be_considered);
		while(level_to_be_considered < 0 || level_to_be_considered > max_possible_level)
		{
			//VALIDATE LEVEL ENTERED BY THE USER
			printf("ENTER A VALID LEVEL:\t");
			scanf("%d",&level_to_be_considered);
		}
		p=root_family;
		level=0;
		InitializeQueueDS(qptr);
		while(p != NULL && level != level_to_be_considered)
		{
			for(count=0;count < p->num_child;count++)
			{
				InsertInQueueDS(qptr,p->child[count]);
				qptr->rear->level=level+1;
			}
			if(!isQueueDSEmpty(qptr))
			{
				level=qptr->front->level;
			}
			DeleteFromQueueDS(qptr,&p);
		}

		//AT THIS STAGE p POINTS TO A NODE AT THE REQUIRED LEVEL AND QUEUE CONTAINS ALL OTHER NODES AT THAT LEVEL
		done=FALSE;
		while(!done)
		{
				if( (p->person_male.education_qualification + p->person_female.education_qualification) > max_edu)
				{
					if(arr_max!=NULL)
					{
						free(arr_max);
						arr_max=NULL;
					}
					arr_max=(MemberNode*)malloc(sizeof(MemberNode)*(1));
					arr_max[0]=*p;
					max_edu=(p->person_male.education_qualification + p->person_female.education_qualification);
					curr_max_size=1;
				}
				else if((p->person_male.education_qualification + p->person_female.education_qualification) == max_edu)
				{
					arr_max=(MemberNode*)realloc(arr_max,sizeof(MemberNode)*(curr_max_size+1));
					arr_max[curr_max_size]=*p;
					curr_max_size++;
				}
				if((p->person_male.education_qualification + p->person_female.education_qualification) < min_edu)
				{
					if(arr_min != NULL)
					{
						free(arr_min);
						arr_min=NULL;
					}
					arr_min=(MemberNode*)malloc(sizeof(MemberNode)*(1));
					arr_min[0]=*p;
					min_edu=(p->person_male.education_qualification + p->person_female.education_qualification);
					curr_min_size=1;
				}
				else if((p->person_male.education_qualification + p->person_female.education_qualification) == min_edu)
				{
					arr_min=(MemberNode*)realloc(arr_min,sizeof(MemberNode)*(curr_min_size+1));
					arr_min[curr_min_size]=*p;
					curr_min_size++;
				}
			if(isQueueDSEmpty(qptr))
			{
				done=TRUE;
			}
			DeleteFromQueueDS(qptr,&p);
		}
		printf("MAXIMUM EDUCATED NODES:\n");
		for(count=0;count<curr_max_size;count++)
		{
			printf("NODE: PERSON MALE :%s PERSON FEMALE :%s\n",arr_max[count].person_male.first_name,arr_max[count].person_female.first_name);
		}

		printf("MINIMUM EDUCATED NODES:\n");
		for(count=0;count<curr_min_size;count++)
		{
			printf("NODE: PERSON MALE :%s PERSON FEMALE :%s\n",arr_min[count].person_male.first_name,arr_min[count].person_female.first_name);
		}
		if(arr_max!=NULL)
		{
			free(arr_max);
			arr_max=NULL;
		}
		if(arr_min!=NULL)
		{
			free(arr_min);
			arr_min=NULL;
		}
	}
	return sc;
}
Status getSavingsForANode(Money* saving,char* name,MemberNode* root)
{
	/*
		CALCULATES SAVINGS FOR A NODE CONSISTING OF A MEMBER WITH NAME 'name' IN A FAMILY TREE IDENTIFIED BY 'root'
	*/
	Status sc=SUCCESS;
	MemberNode *parent=NULL,*person=NULL;
	Bool done;

	int count,num_live_child,count2;
	Money saving_person;
	*saving=0;
		parent=FindParentToAChild(root,name);//FIND PARENT TO THE CHILD NODE
		if(parent == NULL)
		{
			//IF NO PARENT--- THIS NODE CAN BE ROOT SO FIND IF SUCH A NODE EXISTS
			person=FindPerson(root,name);
			if(person!=NULL && (person->person_male.active_status==LIVE || person->person_female.active_status==LIVE))
			{
				//IF THE NODE IS ACTIVE REACH HERE
				for(count = 0;count < person->num_child;count++)
				{
					//CALCULATE NUMBER OF LIVING CHILDREN TO THIS NODE
					if(person->child[count]->person_male.active_status==LIVE || person->child[count]->person_female.active_status==LIVE)
					{
						num_live_child++;
					}
				}
				//SAVINGs OF THIS NODE = EARNING OF THIS NODE + 0(AS THIS IS ROOT NODE) - (NODE'S EARNING)*NUMBER OF CHILDREN ALIVE*10%
				//AGAIN FRACTIONAL MONEY NEGLECTED
				*saving=(person->person_male.earning+person->person_female.earning)-((person->person_male.earning+person->person_female.earning)*10.0*num_live_child)/100.0;
				person->saving_capacity=*saving;
				//UPDATE SAVING CAPACITY OF THE PERSON NODE
			}
			else
			{
				sc=FAILURE;
				printf("ERROR...\n");
			}
		}
		else//PARENT EXISTS
		{
			done=FALSE;
			for(count=0;count < parent->num_child && (!done);count++)
			{
				//get child node here in the LOOP
				if(strcmp(parent->child[count]->person_male.first_name,name)==0 || strcmp(parent->child[count]->person_female.first_name,name)==0)
				{
					//if member is alive
					if(parent->child[count]->person_male.active_status==LIVE || parent->child[count]->person_female.active_status==LIVE)
					{
						for(count2=0,num_live_child=0;count2 < parent->child[count]->num_child;count2++)
						{
							if(parent->child[count]->child[count2]->person_male.active_status==LIVE || parent->child[count]->child[count2]->person_female.active_status==LIVE)
							{
								num_live_child++;
							}
						}	
						*saving=(parent->child[count]->person_male.earning + parent->child[count]->person_female.earning) + ((parent->person_male.earning+parent->person_female.earning)*10.0)/100.0-((parent->child[count]->person_male.earning+parent->child[count]->person_female.earning)*10.0*num_live_child)/100.0;
						done=TRUE;
						parent->child[count]->saving_capacity=*saving;
					}
				}
				
			}
			if(!done)
			{
				sc=FAILURE;
			}
		}
	
	return sc;
}
/*done=FALSE;
		earning_of_parents=0;
		sc=calculateSavings(root,name,earning_of_parents,&done);

---COMMENTED FOR REUSABILITY---
Status calculateSavings(MemberNode* root,char* name,Money earning_of_parents,Bool* done)
{
	Status sc=SUCCESS;
	Money saving;
	int count;
	if(root == NULL)
	{
		sc=FAILURE;
	}
	else if(*done == TRUE)
	{
		;
	}
	else
	{
		if(strcmp(root->person_male.first_name,name) == 0)
		{
			root->person_male.saving_capacity = root->person_male.earning + ((earning_of_parents)*10)/100-((root->person_male.earning)*(root->num_child)*10)/100;
			printf("SAVING CAPACITY OF %s is %d\n",name,root->person_male.saving_capacity);
			*done=TRUE;
		}
		else if(strcmp(root->person_female.first_name,name) == 0)
		{
			root->person_female.saving_capacity = root->person_female.earning + ((earning_of_parents)*10)/100-((root->person_female.earning)*(root->num_child)*10)/100;

			printf("SAVING CAPACITY OF %s is %d\n",name,root->person_female.saving_capacity);
			*done=TRUE;
		}
		else
		{
			for(count = 0;count < root->num_child && !(*done) && sc;count++)
			{
				sc=calculateSavings(root->child[count],name,root->person_male.earning+root->person_female.earning,done);
			}
		}

	}
	return sc;
}
*/
Status HighestLowestSavings(Family_Identity* fptr)
{
	/*
		FUNCTION TO FIND OUT HIGHEST/LOWEST SAVING CAPACITY NODES AT A GIVEN LEVEL
		THIS FUNCTION IS SIMILAR TO HIGHEST_LOWEST_EDUCATION FUNCTION
	*/
	Status sc=SUCCESS;
	char surname[MAX_NAME_LENGTH];
	int level_to_be_considered,max_possible_level,count,level;
	MemberNode* root_family,*p;
	int curr_max_size=0,curr_min_size=0;
	MemberNode* arr_max=NULL,*arr_min=NULL;
	Money max_savings=0.0,min_savings=(float)(INT_MAX+0.0);
	Bool done;
	int num_live_child;
	QueueDS q1;
	QueueDS* qptr;
	qptr=&q1;
	printf("ENTER SURNAME:\t");
	scanf("%s",surname);
	root_family=SearchFamily(fptr,surname);
	if(root_family==NULL)
	{
		printf("FAMILY DOES NOT EXIST...\n");
		sc=FAILURE;
	}
	else
	{
		max_possible_level=getHeight(root_family);
		printf("ENTER LEVEL:\t");
		scanf("%d",&level_to_be_considered);
		while(level_to_be_considered < 0 || level_to_be_considered > max_possible_level)
		{
			printf("ENTER A VALID LEVEL:\t");
			scanf("%d",&level_to_be_considered);
		}
		p=root_family;
		level=0;
		if(level_to_be_considered == 0)
		{
			num_live_child=0;
			for(count = 0;count < p->num_child ; count++)
			{
				if(p->child[count]->person_male.active_status==LIVE || p->child[count]->person_female.active_status==LIVE)
				{
					num_live_child++;
				}
			}
			p->saving_capacity = (p->person_male.earning + p->person_female.earning)- ((p->person_male.earning+p->person_female.earning)*num_live_child*10.0)/100.0;
		}
			InitializeQueueDS(qptr);
			while(p != NULL && level != level_to_be_considered)
			{		
				for(count=0;count < p->num_child ;count++)
				{
					getSavingsForANode(&(p->child[count]->saving_capacity),p->child[count]->person_male.first_name,root_family);
					InsertInQueueDS(qptr,p->child[count]);
					qptr->rear->level=level+1;
				}
				if(!isQueueDSEmpty(qptr))
				{
					level=qptr->front->level;
				}
				DeleteFromQueueDS(qptr,&p);
			}
		
			done=FALSE;
			while(!done)
			{
					if( p->saving_capacity > max_savings)
					{
						if(arr_max!=NULL)
						{
							free(arr_max);
							arr_max=NULL;
						}
						arr_max=(MemberNode*)malloc(sizeof(MemberNode)*(1));
						arr_max[0]=*p;
						max_savings=p->saving_capacity;
						curr_max_size=1;
					}
					else if(p->saving_capacity == max_savings)
					{
						arr_max=(MemberNode*)realloc(arr_max,sizeof(MemberNode)*(curr_max_size+1));
						arr_max[curr_max_size]=*p;
						curr_max_size++;
					}
					if(p->saving_capacity < min_savings)
					{
						if(arr_min != NULL)
						{
							free(arr_min);
							arr_min=NULL;
						}
						arr_min=(MemberNode*)malloc(sizeof(MemberNode)*(1));
						arr_min[0]=*p;
						min_savings=p->saving_capacity;
						curr_min_size=1;
					}
					else if(p->saving_capacity == min_savings)
					{
						arr_min=(MemberNode*)realloc(arr_min,sizeof(MemberNode)*(curr_min_size+1));
						arr_min[curr_min_size]=*p;
						curr_min_size++;
					}
				
				if(isQueueDSEmpty(qptr))
				{
					done=TRUE;
				}
				DeleteFromQueueDS(qptr,&p);
		    }

			printf("MAXIMUM SAVING CAPACITY NODES:\n");
			for(count=0;count<curr_max_size;count++)
			{
				printf("NODE: PERSON MALE :%s PERSON FEMALE :%s  SAVINGS:%.2f\n",arr_max[count].person_male.first_name,arr_max[count].person_female.first_name,max_savings);
			}

			printf("MINIMUM SAVING CAPACITY NODES:\n");
			for(count=0;count<curr_min_size;count++)
			{
				printf("NODE: PERSON MALE :%s PERSON FEMALE :%s  SAVINGS:%.2f\n",arr_min[count].person_male.first_name,arr_min[count].person_female.first_name,min_savings);
			}
			if(arr_max!=NULL)
			{
				free(arr_max);
				arr_max=NULL;
			}
			if(arr_min!=NULL)
			{
				free(arr_min);
				arr_min=NULL;
			}
		}
	return sc;
}
Status savingsofFamily(MemberNode* root1,Money* spending_capacity,int* num_nodes,Money add_to_child)
{
	/*
		FUNCTION TO HELP FIND THE TOTAL SPENDING CAPACITY OF A TREE(IDENTIFIED BY root)
	*/
	Status sc=SUCCESS;
	int count,num_live_child;
	if(root1 == NULL)
	{
		sc=FAILURE;
	}
	else
	{
		for(count=0,num_live_child=0;count < root1->num_child && sc;count++)
		{
			//calculate NUMBER OF LIVE CHILDREN TO A NODE
			if(root1->child[count]->person_male.active_status==LIVE || root1->child[count]->person_female.active_status==LIVE)
			{
				num_live_child++;
			}
		}
		if(root1->person_male.active_status==LIVE || root1->person_female.active_status==LIVE)
		{
			//IF NODE IS ALIVE WE CAN UPDATE SAVING CAPACITY OF THAT NODE
			//add_to_child is the Money that A PARENT NODE SENDS TO THEIR CHILD NODE(INITIALLY(FOR root) IT IS 0)
			root1->saving_capacity = (root1->person_male.earning + root1->person_female.earning) + add_to_child -((root1->person_male.earning + root1->person_female.earning)*10.0*num_live_child)/100.0;
			(*num_nodes)++;
			*spending_capacity += root1->saving_capacity;
			add_to_child = ((root1->person_male.earning + root1->person_female.earning)*10.0)/100.0;
		}	
		for(count=0;count < root1->num_child && sc;count++)
		{
			sc=savingsofFamily(root1->child[count],spending_capacity,num_nodes,add_to_child);
		}
	}
	return sc;
}
Status avgEducation(MemberNode* root,int* education,int* num_alive)
{
	/*
		FUNCTION TO HELP FIND AVERAGE EDUCATION OF A FAMILY TREE(IDENTIFIED BY root)
		THIS FUNCTIONS SUMS UP THE WEIGHTAGE GIVEN TO AN EDUCATIONAL LEVEL FOR A FAMILY TREE
	*/
	Status sc=SUCCESS;
	int count;
	if(root==NULL)
	{
		sc=FAILURE;
	}
	else
	{
		if(root->person_male.active_status==LIVE)
		{
			(*education) += root->person_male.education_qualification;
			(*num_alive)++;
		}
		if(root->person_female.active_status==LIVE)
		{
			(*education) += root->person_female.education_qualification;
			(*num_alive)++;
		}
		for(count=0;count<root->num_child && sc;count++)
		{
			sc=avgEducation(root->child[count],education,num_alive);
		}
	}
	return sc;
}
Status PerPersonSpendingAvgEducation(Family_Identity* fptr)
{
	/*
		DRIVES THE CALCULATION OF PER PERSON SPENDING CAPACITY and AVERAGE EDUCATIONAL QUALIFICATION OF 2 TREES
	*/
	Status sc=SUCCESS;
	int num_alive1=0,num_alive2=0;
	MemberNode* root1,*root2;
	int education1,education2;
	float avgEducation1=0.0,avgEducation2=0.0;
	char surname1[MAX_NAME_LENGTH],surname2[MAX_NAME_LENGTH];
	Money spending_capacity1=0,spending_capacity2=0;
	int num_nodes1=0,num_nodes2=0;
	printf("ENTER SURNAME1:\t");
	scanf("%s",surname1);
	printf("ENTER SURNAME2:\t");
	scanf("%s",surname2);
	root1=SearchFamily(fptr,surname1);
	root2=SearchFamily(fptr,surname2);
	if(root1==NULL || root2==NULL)
	{
		sc=FAILURE;
		printf("FAMILY NOT FOUND EXCEPTION...\n");
	}
	else
	{
		spending_capacity1=0,spending_capacity2=0;
		education1=education2=0;
		if(savingsofFamily(root1,&spending_capacity1,&num_nodes1,0.0)&& savingsofFamily(root2,&spending_capacity2,&num_nodes2,0.0))
		{
			if(num_nodes1!=0)
			{
				printf("PER PERSON SPENDING CAPACITY OF %s=%.2f\n",surname1,spending_capacity1/(float)num_nodes1);
			}
			else
			{
				printf("PER PERSON SPENDING CAPACITY OF %s=UNDEFINED\n",surname1);
			}
			if(num_nodes2!=0)
			{
				printf("PER PERSON SPENDING CAPACITY OF %s=%.2f\n",surname2,spending_capacity2/(float)num_nodes2);
			}
			else
			{
				printf("PER PERSON SPENDING CAPACITY OF %s=UNDEFINED\n",surname2);
			}
		}
		else
		{
			sc=FAILURE;
			printf("ERROR\n");
		}
		if(avgEducation(root1,&education1,&num_alive1) && avgEducation(root2,&education2,&num_alive2))
		{
			if(num_alive1!=0)
			{
				avgEducation1=education1/((float)num_alive1);
				printf("AVERAGE EDUCTION of %s is %.2f\n",surname1,avgEducation1);
			}
			else
			{
				printf("AVERAGE EDUCTION of %s is UNDEFINED\n",surname1);
			}
			if(num_alive2!=0)
			{
				avgEducation2=education2/((float)num_alive2);
				printf("AVERAGE EDUCTION of %s is %.2f\n",surname2,avgEducation2);
			}
			else
			{
				printf("AVERAGE EDUCTION of %s is UNDEFINED\n",surname2);
			}
		}
		else
		{
			sc=FAILURE;
			printf("ERROR\n");
		}
	}
	return sc;
}
Status PerPersonSpendingAtALevel(Family_Identity* fptr)
{
	/*
		PER PERSON SPENDING CAPACITY AT A LEVEL GIVEN IS CALCULATED/DRIVEN BY THIS FUNCTION
		****CHECK THIS AGAIN
	*/
	char surname[MAX_NAME_LENGTH];
	MemberNode* root,*p;
	QueueDS q1,*qptr;
	Status sc=SUCCESS;
	int count,count2;
	int num_nodes=0,num_live_child=0;
	Money spending_capacity=0.0;
	qptr=&q1;
	int level_to_be_considered,max_possible_level,level;
	printf("ENTER SURNAME:\t");
	scanf("%s",surname);
	root=SearchFamily(fptr,surname);
	Bool brk;
	if(root==NULL)
	{
		printf("FAMILY NOT FOUND EXCEPTION...\n");
		sc=FAILURE;
	}
	else
	{
		p=root;
		max_possible_level=getHeight(root);
		printf("ENTER LEVEL:\t");
		scanf("%d",&level_to_be_considered);
		while(level_to_be_considered > max_possible_level)
		{
			//VALIDATE LEVEL ENTERED BY USER
			printf("ENTER A VALID LEVEL:\t");
			scanf("%d",&level_to_be_considered);
		}
		if(level_to_be_considered==0)
		{
			//ROOT LEVEL
			if(p->person_male.active_status==LIVE || p->person_female.active_status==LIVE)
			{
				//IF ROOT IS ALIVE NODE REACH HERE
				num_nodes++;
				for(count=0,num_live_child=0;count < p->num_child;count++)
				{
					//CALCULATE NUMBER OF LIVE CHILDREN NODES
					if(p->child[count]->person_male.active_status==LIVE || p->child[count]->person_female.active_status==LIVE)
					{
						num_live_child++;
					}
				}
				p->saving_capacity=(p->person_male.earning+p->person_female.earning)-((p->person_male.earning+p->person_female.earning)*num_live_child*10.0)/100.0;
				spending_capacity += p->saving_capacity;
			}
		}
		else //LEVEL TO BE CONSIDERED > 0
		{
			//THIS SNIPPET BELOW AIMS TO FILL THE QUEUE WITH PARENT NODES OF GIVEN LEVEL
			InitializeQueueDS(qptr);
			level=0;
			InsertInQueueDS(qptr,p);//ENTER 0th LEVEL IN QUEUE
			while(p != NULL && level != level_to_be_considered-1)
			{
				if(!isQueueDSEmpty(qptr))
				{
					level=qptr->front->level;
					if(level != level_to_be_considered-1)
					{
						DeleteFromQueueDS(qptr,&p);
						for(count=0;count < p->num_child;count++)
						{
							InsertInQueueDS(qptr,p->child[count]);
							qptr->rear->level=level+1;
						}
					}
				}
				else
				{
					p=NULL;
				}
			}
			//QUEUE CONTAINS PARENTS TO THE REQUIRED LEVEL
			if(!isQueueDSEmpty(qptr))
			{
				//UPDATE LEVEL BY REACHING HERE----ONE WILL ALWAYS REACH HERE BECAUSE QUEUE WILL CONTAIN SOMETHING ALWAYS(AS level_to_be_considered > 0)
				level=qptr->front->level;
			}
			while(!isQueueDSEmpty(qptr) && level != level_to_be_considered)//1st time level=level_to_be_considered-1 
			{
				DeleteFromQueueDS(qptr,&p);//TAKE OUT ONE PARENT NODE
				for(count = 0;count < p->num_child;count++)
				{
					if(p->child[count]->person_male.active_status==LIVE || p->child[count]->person_female.active_status==LIVE)
					{
						num_nodes++;//child to parent is alive
						for(count2=0,num_live_child=0;count2 < p->child[count]->num_child;count2++)
						{
							//calculate the number of live children nodes to this child(of parent)
							if(p->child[count]->child[count2]->person_male.active_status==LIVE || p->child[count]->child[count2]->person_female.active_status==LIVE)
							{
								num_live_child++;
							}
						}
						//update saving_capacity of child to parent
						p->child[count]->saving_capacity = (p->child[count]->person_male.earning + p->child[count]->person_female.earning) + ((p->person_male.earning+p->person_female.earning)*10.0)/100.0 - ((p->child[count]->person_male.earning + p->child[count]->person_female.earning)*10.0*num_live_child)/100.0;
						/*<test>*///printf("%d-----\n",p->child[count]->saving_capacity);//</test>
						spending_capacity += p->child[count]->saving_capacity;
						//update spending_capacity
					}
					if(!isQueueDSEmpty(qptr))
					{
						level=qptr->front->level;//update level
					}

				}

			}
		}
		if(num_nodes != 0)
		{
			printf("SPENDING CAPACITY AT LEVEL %d is %.2f \n",level_to_be_considered,(spending_capacity)/(float)num_nodes,num_nodes);
		}
		else
		{
			printf("SPENDING CAPACITY AT LEVEL %d is UNDEFINED\n",level_to_be_considered);
		}
	}
	return sc;
}
void UpdateForFamily(MemberNode* root_family,FILE* fp)
{
	/*
		FUNCTION THAT WRITES TO FILE 
		WHAT IT WRITES ---DATA OF A PARTICULAR FAMILY
	*/
				int count=0;
				if(root_family->person_male.first_name[0] != '\0')
				{
					fprintf(fp,"\n%d %d ", root_family->person_male.marital_status,root_family->person_male.gender);
					fprintf(fp,"%s ",root_family->person_male.first_name);
					fprintf(fp,"%d ",root_family->person_male.age);
					fprintf(fp,"%.2f ",root_family->person_male.earning);
					fprintf(fp,"%d ",root_family->person_male.education_qualification);
					fprintf(fp,"%d %s",root_family->person_male.active_status,root_family->person_male.UID);
				}
				if(root_family->person_female.first_name[0] != '\0')
				{
					fprintf(fp,"\n%d %d ", root_family->person_female.marital_status,root_family->person_female.gender);
					fprintf(fp,"%s ",root_family->person_female.first_name);
					fprintf(fp,"%d ",root_family->person_female.age);
					fprintf(fp,"%.2f ",root_family->person_female.earning);
					fprintf(fp,"%d ",root_family->person_female.education_qualification);
					fprintf(fp,"%d %s",root_family->person_female.active_status,root_family->person_female.UID);
				}
				fprintf(fp,"\n%d",root_family->num_child);
				
				for(count = 0;count < root_family->num_child ; count++)
				{
					fprintf(fp,"\nCHILD");
					UpdateForFamily(root_family->child[count],fp);
				}
				return;
}
Status UpdateFile(Family_Identity* fptr)
{
	/*
		DRIVER THAT UPDATES THE FILE DURING THE END OF THE PROGRAM
	*/
	Status sc=SUCCESS;
	int i;
	Bool first=TRUE;
	MemberNode* root_family=NULL;
	Family_Identity* forest_trv=fptr;
	FILE* fp=fopen(DATA_SOURCE_UPDATE,WRITE_MODE);
	Node_Identifier* head=NULL;
	if(fp == NULL)
	{
		sc=FAILURE;
	}
	else
	{
		
		for(i = 0; i < HASH_TABLE_SIZE ; i++)
		{
			head = fptr->HashTable[i];
			while(head != NULL)
			{
				root_family=head->root_family;
				/*UPDATE IN FILE*/
				if(!first)
				{
					fprintf(fp,"\n");
				}
				fprintf(fp,"%s FAMILY",head->surname);
				UpdateForFamily(root_family,fp);
				first=FALSE;
				head = head ->next;
			}
		}
		fclose(fp);
		fp=NULL;
	}
	return sc;
}
int main()
{
	/*
				DRIVER FUNCTION
	*/

	printf("\t\tFOREST OF FAMILY TREES\nCAUTION: TO AVOID ANY UNEXPECTED RESULTS,PLEASE TYPE ALL STRINGs IN UPPERCASE\n");
	int i,choice,internal_choice;
	Money saving_node;
	MemberNode* family_root=NULL;
	MemberNode* member_identity=NULL;
	Node_Identifier* nptr;
	Family_Identity* fptr=NULL;
	char surname[MAX_NAME_LENGTH],name[MAX_NAME_LENGTH];
	Family_Identity f1;
	FILE* fp=fopen(DATA_SOURCE,READ_MODE);
	if(fp==NULL)
	{
		printf("ERROR IN FINDING THE REQUESTED FILE! ERROR_CODE 404\n");
	}
	else
	{	
		fptr=&f1;
		fptr=Initialize_Family_Identity(fptr);	
		while(fscanf(fp,"%s",surname)!=EOF)
		{
				member_identity=NULL;
				printf("FILE INPUT TAKEN FOR FAMILY:%s\n",surname);
				MakeForestOfFamily(fptr,&member_identity,fp);
				if(InsertNewFamily(fptr,surname,member_identity))
				{
					DisplayFamilyMembers(member_identity);
				}
				else
				{
					if(DeleteTreeForFamily(&member_identity))//FREE THE FAMILY TREE OF DUPLICATE FAMILY
					{
						printf("FAMILY TREE FOR DUPLICATE SURNAME DOES NOT EXIST IN OUR PROGRAM!\n");
					}
				}
		}
		fclose(fp);
		do
		{
			printf("\n\t\tMENU---WELCOME TO THE FOREST OF FAMILY TREES\n");
			printf("1] INSERT A NEW MEMBER\n2] DEATH OF A MEMBER\n3] CHECK IF TWO NODES ARE IN THE SAME FAMILY\n4] KNOW SAVING CAPACITY OF A NODE(MEMBER) IN A FAMILY\n5] KNOW HIGHEST/LOWEST SAVING CAPACITY NODE/EDUCATION QUALIFICATION NODE AT A LEVEL\n6] KNOW THE ALIVE MEMBERS OF A FAMILY AT THE HIGHEST/LOWEST LEVEL.ALSO KNOW THE HEAD OF THE SAME FAMILY\n7] PER PERSON SPENDING CAPACITY AND AVERAGE EDUCATIONAL QUALIFICATION OF TWO FAMILIES\n8] PER PERSON SPENDING CAPACITY AT AT EACH LEVEL GIVEN A LEVEL NUMBER\n9] DISPLAY INFORMATION OF A FAMILY\n0] EXIT\n");
			scanf("%d",&choice);
			switch(choice)
			{
				case INSERT:
							printf("1] BIRTH\n2] MARRIAGE\n");
							scanf("%d",&internal_choice);
							switch(internal_choice)
							{
								case BIRTH:
											if(Birth(fptr))
											{
												printf("NODE ADDED SUCCESSFULLY\n");
											}
											else
											{
												printf("----UNSUCCESSFUL----\n");
											}
											break;
								case MARRIAGE:
											if(Marriage(fptr))
											{
												printf("SUCCESSFUL\n");
											}
											else
											{
												printf("----UNSUCCESSFUL----\n");
											}
											break;
								default:
											printf("YOU HAVE ENTERED AN INVALID CHOICE\n");
											break;
							}
							break;
				case DEATH:
							if(Death(fptr))
							{
								printf("OPERATION SUCCESSFUL\n");
							}
							else
							{
								printf("------OPERATION UNSUCCESSFUL----\n");
							}
							break;
				case HIGHEST_LOWEST_SAVINGS_EDUCATION:
							printf("1] SAVING CAPACITY\n2] EDUCATION QUALIFICATION\n");
							scanf("%d",&internal_choice);
							switch(internal_choice)
							{
								case EDUCATION:
											if(HighestLowestEducation(fptr))
											{
												printf("OPERATION SUCCESSFUL\n");
											}
											else
											{
												printf("-----OPERATION UNSUCCESSFUL-----\n");
											}
											break;
								case SAVINGS:
											if(HighestLowestSavings(fptr))
											{
												printf("OPERATION SUCCESSFUL\n");
											}
											else
											{
												printf("------OPERATION UNSUCCESSFUL------\n");
											}
											break;
								default:
											printf("INVALID CHOICE\n");
											break;
							}
							break;
				case SAME_FAMILY_CHECK:
							if(TwoInSameFamily(fptr))
							{
								printf("YES,THE TWO NODEs BELONG TO A SAME FAMILY\n");
							}
							else
							{
								printf("NO,THE TWO NODEs DONOT BELONG TO THE SAME FAMILY\n");
							}
							break;
				case HIGHEST_LOWEST_HEAD:
							if(High_Low_Head(fptr))
							{
								printf("SUCCESS!\n");
							}
							else
							{
								printf("-----UNSUCCESSFUL----\n");
							}
							break;
				case PER_PERSON_SPENDING_AVG_EDUCATION:
							if(PerPersonSpendingAvgEducation(fptr))
							{
								printf("SUCCESSFUL\n");
							}
							else
							{
								printf("--------UNSUCCESSFUL-------\n");
							}
							break;
				case GET_SAVING_CAPACITY_OF_A_NODE:
							//Status getSavingsForANode(Money* saving,char* name,MemberNode* root)
							printf("ENTER SURNAME:\t");
							scanf("%s",surname);
							family_root=SearchFamily(fptr,surname);
							if(family_root==NULL)
							{
								printf("FAMILY NOT FOUND...\n");
							}
							else
							{
								printf("ENTER NAME OF A MEMBER OF THE NODE YOU WANT TO SELECT:\n");
								scanf("%s",name);
								if(getSavingsForANode(&saving_node,name,family_root))
								{
									printf("SAVINGS : %.2f\n",saving_node);

									printf("SUCCESSFUL\n");
								}
								else
								{
									printf("-----UNSUCCESSFUL----\n");
								}
							}
							

							
							break;
				case PER_PERSON_SPENDING_AT_A_LEVEL:
							if(PerPersonSpendingAtALevel(fptr))
							{
								printf("SUCCESSFUL\n");
							}
							else
							{
								printf("-------UNSUCCESSFUL------\n");
							}
							break;
				case DISPLAY_A_FAMILY:
							printf("ENTER SURNAME:\t");
							scanf("%s",surname);
							family_root=SearchFamily(fptr,surname);
							if(family_root==NULL)
							{
								printf("FAMILY NOT FOUND...\n-----UNSUCCESSFUL-----\n");
							}
							else
							{
								DisplayFamilyMembers(family_root);
							}
							break;
				case EXIT:
							printf("!!!!YOU HAVE CHOSEN TO EXIT THE MENU!!!!\nTHANK YOU FOR USING OUR PROGRAM\n");
							break;
				default:
							printf("PLEASE ENTER A VALID CHOICE\n");
							break;
			}
		}while(choice!=EXIT);
		if(UpdateFile(fptr))
		{
			printf("FILE UPDATED SUCCESSFULLY\n");
		}
		else
		{
			printf("ERROR IN UPDATING FILE\n");
		}
	}
	
	return REPORT_SUCCESS_TO_CRE;
}
/*
	IF YOU FIND ANYTHING INCORRECT ,PLEASE REPORT TO THE AUTHOR(s) OF THIS CODE
*/
