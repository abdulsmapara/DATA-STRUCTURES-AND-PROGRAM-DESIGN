/*
ASSIGNMENT DONE BY : ABDUL SATTAR MAPARA and SHIVAM MISHRA
*/
#include <stdio.h>
#include <string.h>
#define MAX_SIZE 5
#define MAX_SIZE_PRINT "5"
#define COMP_ID 8
#define PROC_LEVEL 3
#define SUCCESS 1
#define FAILURE 0
#define SUCCESS_UPDATE 1
#define SUCCESS_NEW 2
#define procLevelI3 "I3"
#define procLevelI5 "I5"
#define procLevelI7 "I7"
#define MAX 16
#define MIN 1
#define REPEAT_CHOICE 4
#define FIRST_GREATER 1
#define BOTH_EQUAL 0
#define SECOND_GREATER -1
#define COMMON_LIST 1
#define INCREASE_LIFE_PERIOD 1
#define PURCHASE 2
#define SELL 3
#define UPGRADE_PROCESSOR 4
#define NOT_FOUND -1						//if not found in array we need invalid index in an array which is =-1
#define procIsI3 3
#define procIsI5 5
#define procIsI7 7
#define SET 1




typedef struct 							//DATE
{
	int day;
	int month;
	int year;
}date;

typedef struct 							//TIME PERIOD
{
	int nDays;
	int nMonths;
	int nYears;
}period;

typedef struct
{
	char compId[COMP_ID];					//KEY----Computer Id
	date date_of_manufacture;				//date of manufacture of computer
	date date_of_purchase;					//KEY-----Date on which IMS purchased the computer
	period warranty;					//time period-->warranty(eg.6months20days)Days also added for flexibility
	char procLevel[PROC_LEVEL];				//I3 I5 I7
	period life;						//LIFE PERIOD OF Computer
	date writeOff;						//WriteOff date to be calculated based on life period and dateOfManufacture
}InventoryMS;							//INVENTORY MANAGEMENT SYSTEM
typedef struct
{
	char compId[COMP_ID];					
	date date_of_manufacture;				
	date date_of_purchase;					
	period warranty;					
	char procLevel[PROC_LEVEL];				
	period life;						
	date writeOff;						
	int event;
}UpdateIMS;
int menu()
{
	int choice;
	printf("\t\tMENU\n1) INSERT\n2) DELETE\n3) GET TOTAL NUMBER OF COMPUTERS OF EACH LEVEL SEPERATELY\n");
	printf("4) CHECK IF A LIST IS EMPTY OR NOT\n5) CHECK IF A LIST IS FULL OR NOT\n6) LIST OF COMPUTERS HAVING LONGEST USABILITY PERIOD\n");
	printf("7) UPDATE LIST\n8) GET SORTED ON DATE OF PURCHASE\n9) GET SORTED ON WARRANTY PERIOD EXPIRY\n10)GET SORTED ON USED PERIOD\n11) LIST UNIQUE\n12) LIST UNION\n13) LIST INTERSECTION\n14) LIST DIFFERENCE\n15) LIST SYMMETRIC DIFFERENCE\n16) VIEW LIST OF A PARTICULAR PROCESSOR LEVEL OR COMMON LIST\nYOUR CHOICE FROM 1 TO 16:::::\t\t");
	
	scanf("%d",&choice);
	
	while(choice>MAX||choice<MIN)
	{
		printf("Enter valid choice from 1 to 16\n\t");
		scanf("%d",&choice);
	}
return choice;
}	
int inputSize(int max_size)
{
	int numRecords;
	scanf("%d",&numRecords);
	while(numRecords>max_size)
	{
		printf("Enter SIZE not more than ");
		puts(MAX_SIZE_PRINT);
		printf("\n");
		scanf("%d",&numRecords);
	}
	return numRecords;
}	
InventoryMS inputStruct(InventoryMS input)
{
			printf("Enter COMPUTER ID\t");
			scanf("%s",input.compId);
        		printf("Enter PROCESSOR LEVEL---I3/I5/I7\n");
			scanf("%s",input.procLevel);
			while(((strcmp(input.procLevel,procLevelI3))&&((strcmp(input.procLevel,procLevelI5))&&((strcmp(input.procLevel,procLevelI7))))))
			{
				printf("Record of computers with I3 I5 I7 processor levels are only maintained.Please check the processor level.Also take care of the case\n");
				input.procLevel[0]='\0';
				scanf("%s",input.procLevel);
				
			}//Validation of procLevel
			printf("Enter DATE OF MANUFACTURE\nDATE:\t");
			scanf("%d",&input.date_of_manufacture.day);
			printf("MONTH:\t");
			scanf("%d",&input.date_of_manufacture.month);
			printf("YEAR:\t");
			scanf("%d",&input.date_of_manufacture.year);
			printf("Enter DATE OF PURCHASE\nDATE:\t");
			scanf("%d",&input.date_of_purchase.day);
			printf("MONTH:\t");
			scanf("%d",&input.date_of_purchase.month);
			printf("YEAR:\t");
			scanf("%d",&input.date_of_purchase.year);
			printf("Enter warranty period\nYEARS:\t");
			scanf("%d",&input.warranty.nYears);
			printf("MONTHS:\t");
			scanf("%d",&input.warranty.nMonths);
			printf("DAYS:\t");
			scanf("%d",&input.warranty.nDays);
			printf("Enter Life period\nYEARS:\t");
			scanf("%d",&input.life.nYears);
			printf("MONTHS:\t");
			scanf("%d",&input.life.nMonths);
			printf("DAYS:\t");
			scanf("%d",&input.life.nDays);
			return input;
}
void InitializeUpdateInput(UpdateIMS input[],int start,int end)
{
	int i=start;
	while(i<=end)
	{
		input[i].event=0;
		input[i].compId[0]='\0';
		input[i].procLevel[0]='\0';
		input[i].date_of_purchase.day=0;
		input[i].date_of_purchase.month=0;
		input[i].date_of_purchase.year=0;
		input[i].date_of_manufacture.day=0;
		input[i].date_of_manufacture.month=0;
		input[i].date_of_manufacture.year=0;
		input[i].warranty.nDays=-1;
		input[i].warranty.nMonths=-1;
		input[i].warranty.nYears=-1;
		input[i].life.nDays=-1;
		input[i].life.nMonths=-1;
		input[i].life.nYears=-1;
		input[i].writeOff.day=0;
		input[i].writeOff.month=0;
		input[i].writeOff.year=0;
		i++;
	}
return;
}
UpdateIMS inputNecessary(UpdateIMS input)
{
	
	printf("Enter DATE OF PURCHASE\nDATE:\t:");
	scanf("%d",&input.date_of_purchase.day);
	printf("MONTH:\t");
	scanf("%d",&input.date_of_purchase.month);
	printf("YEAR:\t");
	scanf("%d",&input.date_of_purchase.year);
	printf("Enter ComputerID \n");
	scanf("%s",input.compId);
	return input;
	
}
UpdateIMS PurchaseInfo(UpdateIMS input)
{
			
        		printf("Enter PROCESSOR LEVEL---I3/I5/I7\n");
			scanf("%s",input.procLevel);
			while(((strcmp(input.procLevel,procLevelI3))&&((strcmp(input.procLevel,procLevelI5))&&((strcmp(input.procLevel,procLevelI7))))))
			{
				printf("Record of computers with I3 I5 I7 processor levels are only maintained.Please check the processor level.Also take care of the case\n");
				input.procLevel[0]='\0';
				scanf("%s",input.procLevel);
				
			}//Validation of procLevel
			printf("Enter DATE OF MANUFACTURE\nDATE:\t");
			scanf("%d",&input.date_of_manufacture.day);
			printf("MONTH:\t");
			scanf("%d",&input.date_of_manufacture.month);
			printf("YEAR:\t");
			scanf("%d",&input.date_of_manufacture.year);
			
			printf("Enter warranty period\nYEARS:\t");
			scanf("%d",&input.warranty.nYears);
			printf("MONTHS:\t");
			scanf("%d",&input.warranty.nMonths);
			printf("DAYS:\t");
			scanf("%d",&input.warranty.nDays);
			printf("Enter Life period\nYEARS:\t");
			scanf("%d",&input.life.nYears);
			printf("MONTHS:\t");
			scanf("%d",&input.life.nMonths);
			printf("DAYS:\t");
			scanf("%d",&input.life.nDays);
			return input;
}						
int datecompare(date a,date b)      			//returns 1 if a>b;0 if a=b;-1 if a<b (equivalent to a-b)
{
    int i=SECOND_GREATER;
    if(a.year>b.year||(a.year==b.year&&a.month>b.month)||(a.year==b.year&&a.month==b.month&&a.day>b.day))
    {
        i=FIRST_GREATER;
    }
    else if(a.year==b.year&&a.month==b.month&&a.day==b.day)
    {
        i=BOTH_EQUAL;
    }
    return i;
}
int periodcompare(period a,period b)      		//returns 1 if a>b;0 if a=b;-1 if a<b (equivalent to a-b)
{
    int i=SECOND_GREATER;
    if(a.nYears>b.nYears||(a.nYears==b.nYears&&a.nMonths>b.nMonths)||(a.nYears==b.nYears&&a.nMonths==b.nMonths&&a.nDays>b.nDays))
    {
        i=FIRST_GREATER;
    }
    else if(a.nYears==b.nYears&&a.nMonths==b.nMonths&&a.nDays==b.nDays)
    {
        i=BOTH_EQUAL;
    }
    return i;
}
int posFind(InventoryMS comp[],char compId[],date date_of_purchase,int low,int high)
{
	int pos=NOT_FOUND;
	int i=low;
	while(i<=high&&pos==NOT_FOUND)
	{
		while((i<=high)&&(comp[i].date_of_purchase.year==date_of_purchase.year)&&(comp[i].date_of_purchase.month==date_of_purchase.month)&&(comp[i].date_of_purchase.day==date_of_purchase.day)&&(pos==NOT_FOUND))
		{
			if(!(strcmp(comp[i].compId,compId)))
			{
				pos=i;	
			}
			else
			{
				i++;
			}
		}
		if(pos==NOT_FOUND)
		{
			i++;
		}
	}
	return pos;
}
void Initialize(InventoryMS comp[],int start,int end,char procLevel[])
{
	int i=start;
	while(i<=end)
	{
		comp[i].compId[0]='\0';
		comp[i].date_of_manufacture.day=0;
		comp[i].date_of_manufacture.month=0;
		comp[i].date_of_manufacture.year=0;
		comp[i].date_of_purchase.day=0;
		comp[i].date_of_purchase.month=0;
		comp[i].date_of_purchase.year=0;
		comp[i].warranty.nDays=-1;
		comp[i].warranty.nMonths=-1;
		comp[i].warranty.nYears=-1;
		strcpy(comp[i].procLevel,procLevel);
		comp[i].life.nDays=-1;
		comp[i].life.nMonths=-1;
		comp[i].life.nYears=-1;
		comp[i].writeOff.day=0;
		comp[i].writeOff.month=0;
		comp[i].writeOff.year=0;
		i++;
	}
return;

}
void transfer(InventoryMS compDest[],int index1,InventoryMS compSource[],int index2)		//transfer from compSource to compDest
{
		strcpy(compDest[index1].compId,compSource[index2].compId);
		compDest[index1].date_of_manufacture.day=compSource[index2].date_of_manufacture.day;
		compDest[index1].date_of_manufacture.month=compSource[index2].date_of_manufacture.month;
		compDest[index1].date_of_manufacture.year=compSource[index2].date_of_manufacture.year;
		compDest[index1].date_of_purchase.day=compSource[index2].date_of_purchase.day;
		compDest[index1].date_of_purchase.month=compSource[index2].date_of_purchase.month;
		compDest[index1].date_of_purchase.year=compSource[index2].date_of_purchase.year;
		strcpy(compDest[index1].procLevel,compSource[index2].procLevel);
		compDest[index1].warranty.nDays=compSource[index2].warranty.nDays;
		compDest[index1].warranty.nMonths=compSource[index2].warranty.nMonths;
		compDest[index1].warranty.nYears=compSource[index2].warranty.nYears;
		compDest[index1].life.nDays=compSource[index2].life.nDays;
		compDest[index1].life.nMonths=compSource[index2].life.nMonths;
		compDest[index1].life.nYears=compSource[index2].life.nYears;
		compDest[index1].writeOff.day=compSource[index2].writeOff.day;
		compDest[index1].writeOff.month=compSource[index2].writeOff.month;
		compDest[index1].writeOff.year=compSource[index2].writeOff.year;
		return;
}
int getNumComputers(InventoryMS comp[],int size)
{
    int i=0;
    while((i<size)&&(comp[i].date_of_purchase.day!=0))
    {
    	i++;
    }
    return i;
}


int shiftLeft(InventoryMS comp[],int start,int end)
{
	int i=start+1;
	int stop;
	while((i<=end+1)&&(comp[i].date_of_purchase.day!=0))
	{	
		
		transfer(comp,i-1,comp,i);
		i++;
	}
	stop=i-1;
	return stop;
}
int shiftRight(InventoryMS comp[],int size,int start,int end)
{
	int i=end-1;
	start+=1;
	while((i>=start))
	{
		
		transfer(comp,i+1,comp,i);
		//TEST printf("IN SHIFT===i=%d\n",i);
		i--;
	}
return i+1;
}
void displayList(InventoryMS comp[],int size)
{	
    int i;
    printf("\t\tDISPLAYING LIST:::\n");
    for(i=0;i<size&&comp[i].date_of_purchase.day!=0;i++)
    {
        printf("\nCOMPUTER ID   =   %s\n",comp[i].compId);
        printf("COMPUTER PROCESSOR LEVEL  =   %s\n",comp[i].procLevel);
        printf("COMPUTER DATE OF MANUFACTURE::\n");
        printf("DATE:\t%d\n",comp[i].date_of_manufacture.day);
        printf("MONTH:\t%d\n",comp[i].date_of_manufacture.month);
        printf("YEAR:\t%d\n",comp[i].date_of_manufacture.year);
        printf("COMPUTER DATE OF PURCHASE::\n");
        printf("DATE:\t%d\n",comp[i].date_of_purchase.day);
        printf("MONTH:\t%d\n",comp[i].date_of_purchase.month);
        printf("YEAR:\t%d\n",comp[i].date_of_purchase.year);
        printf("WARRANTY PERIOD::\n");
        printf("YEARS:\t%d\n",comp[i].warranty.nYears);
        printf("MONTHS:\t%d\n",comp[i].warranty.nMonths);
        printf("DAYS:\t%d\n",comp[i].warranty.nDays);
        printf("LIFE PERIOD:::\n");
        printf("YEARS:\t%d\n",comp[i].life.nYears);
        printf("MONTHS:\t%d\n",comp[i].life.nMonths);
        printf("DAYS:\t%d\n",comp[i].life.nDays);
        printf("WRITE OFF DATE::\n");
        printf("DATE:\t%d\n",comp[i].writeOff.day);
        printf("MONTH:\t%d\n",comp[i].writeOff.month);
        printf("YEAR:\t%d\n",comp[i].writeOff.year);
        
        
        
    }
    return;
}
int Insert(InventoryMS comp[],int size,char compId[],char procLevel[],date date_of_manufacture,date date_of_purchase,period warranty,period life)
{
	int i=0,j,stop;
	int freeIndex=0;				//Flag to find if free space exists
	int status=SUCCESS_NEW;
	int FoundSame=0;
	while(i<size&&!(FoundSame))
	{
		if((datecompare(date_of_purchase,comp[i].date_of_purchase)==0)&&(!(strcmp(compId,comp[i].compId))))
		{
			FoundSame=1;
		}
		else
		{
			i++;
		}
	}
	if(FoundSame)					//Update
	{
		
			strcpy(comp[i].compId,compId);
			strcpy(comp[i].procLevel,procLevel);
			comp[i].date_of_manufacture.day=date_of_manufacture.day;
			comp[i].date_of_manufacture.month=date_of_manufacture.month;
			comp[i].date_of_manufacture.year=date_of_manufacture.year;
			comp[i].warranty.nDays=warranty.nDays;
			comp[i].warranty.nMonths=warranty.nMonths;
			comp[i].warranty.nYears=warranty.nYears;
			comp[i].life.nDays=life.nDays;
			comp[i].life.nMonths=life.nMonths;				
			comp[i].life.nYears=life.nYears;
			comp[i].writeOff.day=0;
			comp[i].writeOff.month=0;
			comp[i].writeOff.year=0;
			comp[i].writeOff.day=date_of_manufacture.day+life.nDays;
			printf("UPDATING.\n");
			while(comp[i].writeOff.day>30)
			{
				comp[i].writeOff.day-=30;
				comp[i].writeOff.month+=1;
			}
		
			comp[i].writeOff.month+=date_of_manufacture.month+life.nMonths;
			while(comp[i].writeOff.month>12)
			{
				comp[i].writeOff.month-=12;
				comp[i].writeOff.year+=1;
			}
			comp[i].writeOff.year+=date_of_manufacture.year+life.nYears;
			status=SUCCESS_UPDATE;
	
	}
	else
	{
		i=0;
		
		while(i<size&&!(freeIndex))
		{
			if(comp[i].date_of_purchase.day==0)
			{
				freeIndex=1;
			}
			else
			{
				i++;
			}
		}
		if(freeIndex)
		{
			j=i-1;						//ith pos is free

			while((j>=0)&&(comp[j].date_of_purchase.year>date_of_purchase.year))
			{
				j--;

			}
			while((j>=0)&&(comp[j].date_of_purchase.year==date_of_purchase.year)&&(comp[j].date_of_purchase.month>date_of_purchase.month))
			{
				j--;

			}
			while((j>=0)&&(comp[j].date_of_purchase.year==date_of_purchase.year)&&(comp[j].date_of_purchase.month==date_of_purchase.month)&&(comp[j].date_of_purchase.day>date_of_purchase.day))
			{
				j--;
			}
			while((j>=0)&&(comp[j].date_of_purchase.year==date_of_purchase.year)&&(comp[j].date_of_purchase.month==date_of_purchase.month)&&(comp[j].date_of_purchase.day==date_of_purchase.day)&&(strcmp(comp[j].compId,compId)>0))
			{
				j--;
			}
			if(j!=i-1)
			{
				stop=shiftRight(comp,size,j,i);
				Initialize(comp,stop,stop,comp[stop].procLevel);
					
				
			}
			j++;

			strcpy(comp[j].compId,compId);
			strcpy(comp[j].procLevel,procLevel);
			comp[j].date_of_manufacture.day=date_of_manufacture.day;
			comp[j].date_of_manufacture.month=date_of_manufacture.month;
			comp[j].date_of_manufacture.year=date_of_manufacture.year;
			comp[j].date_of_purchase.day=date_of_purchase.day;
			comp[j].date_of_purchase.month=date_of_purchase.month;
			comp[j].date_of_purchase.year=date_of_purchase.year;
			comp[j].warranty.nDays=warranty.nDays;
			comp[j].warranty.nMonths=warranty.nMonths;
			comp[j].warranty.nYears=warranty.nYears;
			comp[j].life.nDays=life.nDays;
			comp[j].life.nMonths=life.nMonths;
			comp[j].life.nYears=life.nYears;
			comp[j].writeOff.day=date_of_manufacture.day+life.nDays;
			while(comp[j].writeOff.day>30)
			{
				comp[j].writeOff.day-=30;
				comp[j].writeOff.month+=1;
			}

			comp[j].writeOff.month+=date_of_manufacture.month+life.nMonths;
			while(comp[j].writeOff.month>12)
			{
				comp[j].writeOff.month-=12;
				comp[j].writeOff.year+=1;
			}
			comp[j].writeOff.year+=date_of_manufacture.year+life.nYears;


		}
		else
		{
			status=FAILURE;
			printf("Insert Operation FAILED\n");
		}
	}
	
	return status;
}
int Delete(InventoryMS comp[],int size,date date_of_purchase,char compId[])
{
	int stop;
	int pos=NOT_FOUND;
	int i=0;
	while(i<size&&pos==NOT_FOUND)
	{
		while((i<size)&&(comp[i].date_of_purchase.year==date_of_purchase.year)&&(comp[i].date_of_purchase.month==date_of_purchase.month)&&(comp[i].date_of_purchase.day==date_of_purchase.day)&&(pos==NOT_FOUND))
		{
			if(!(strcmp(comp[i].compId,compId)))
			{
				pos=i;	
			}
			else
			{
				i++;
			}
		}
		if(pos==NOT_FOUND)
		{
			i++;
		}
	}
	
	if(pos==NOT_FOUND)
	{
		printf("Delete Operation FAILED\n");
	}
	else
	{
		
		if(!(strcmp(comp[pos].procLevel,procLevelI3)))
		{
			pos=procIsI3;			//pos=3
		}
		else if(!(strcmp(comp[pos].procLevel,procLevelI5)))
		{
			pos=procIsI5;			//pos=5
		}
		else
		{
			pos=procIsI7;			//pos=7
		}
		Initialize(comp,i,i,comp[i].procLevel);
		stop=shiftLeft(comp,i,size-2);
		Initialize(comp,stop,stop,comp[stop].procLevel);
	}
return pos;
	
}

int isEmpty(InventoryMS comp[])
{
    int status=FAILURE;
    if(comp[0].date_of_purchase.day==0)
    {
        status=SUCCESS;			//success means isEmpty
    }
    return status;

}
int isFull(InventoryMS comp[])
{
    int status=FAILURE;
    if(comp[MAX_SIZE-1].date_of_purchase.day!=0)
    {
        status=SUCCESS;
    }				
    return status;

}



int compareWarrantyPeriodExpiry(InventoryMS temp1,InventoryMS temp2)
{
	int dt_status;
	date expiry1,expiry2;
	expiry1.day=0,expiry1.month=0,expiry1.year=0;
	expiry2.day=0,expiry2.month=0,expiry2.year=0;
	expiry1.day=temp1.date_of_purchase.day+temp1.warranty.nDays;
	while(expiry1.day>30)
	{
		expiry1.day-=30;
		expiry1.month++;
	}
	expiry1.month+=temp1.date_of_purchase.month+temp1.warranty.nMonths;
	while(expiry1.month>12)
	{
		expiry1.month-=12;
		expiry1.year++;
	}
	expiry1.year+=temp1.date_of_purchase.year+temp1.warranty.nYears;
	expiry2.day=temp2.date_of_purchase.day+temp2.warranty.nDays;
	while(expiry2.day>30)
	{
		expiry2.day-=30;
		expiry2.month++;
	}
	expiry2.month+=temp2.date_of_purchase.month+temp2.warranty.nMonths;
	while(expiry2.month>12)
	{
		expiry2.month-=12;
		expiry2.year++;
	}
	expiry2.year+=temp2.date_of_purchase.year+temp2.warranty.nYears;
	dt_status=datecompare(expiry1,expiry2);
	return dt_status;
}
void MergeSelfWarrantyPeriodExpiry(InventoryMS comp[],InventoryMS temp[],int start,int end)
{
	int mid=(start+end)/2;
	int i,j,k;
	int compare_status;
	i=start;
	j=mid+1;
	k=start;
	while(i<=mid&&j<=end)
	{
		compare_status=compareWarrantyPeriodExpiry(comp[i],comp[j]);
		
		if(compare_status==FIRST_GREATER)
		{
		
			
			transfer(temp,k,comp,j);
			j++;
			k++;
				
		}
		else
		{
			
			transfer(temp,k,comp,i);
			i++;
			k++;
		}
	}
	while(i<=mid)
	{
			
			transfer(temp,k,comp,i);
			i++;
			k++;
	}
	while(j<=end)
	{
			
			transfer(temp,k,comp,j);
			j++;
			k++;
	}
	j=start;
	k=start;
	while(j<=end)
	{
			
			transfer(comp,j,temp,k);
			j++;
			k++;
	}
return;
}
int newInsert(InventoryMS comp[],int size,char compId[],char procLevel[],date date_of_manufacture,date date_of_purchase,period warranty,period life)													//comp is from listUnique in main()
{
	
	int i=0,j,stop;
	int freeIndex=0;				//Flag to find if free space exists
	int status=SUCCESS_NEW;
	int FoundSame=0;
	while(i<size&&!(FoundSame))
	{
		if((datecompare(date_of_purchase,comp[i].date_of_purchase)==0)&&(!(strcmp(compId,comp[i].compId))))
		{
			FoundSame=1;

		}
		else
		{
			i++;
		}
	}
	if(FoundSame)					//Update
	{
		if(strcmp(procLevel,comp[i].procLevel)>0)
		{
			strcpy(comp[i].compId,compId);
			strcpy(comp[i].procLevel,procLevel);
			comp[i].date_of_manufacture.day=date_of_manufacture.day;
			comp[i].date_of_manufacture.month=date_of_manufacture.month;
			comp[i].date_of_manufacture.year=date_of_manufacture.year;
			comp[i].warranty.nDays=warranty.nDays;
			comp[i].warranty.nMonths=warranty.nMonths;
			comp[i].warranty.nYears=warranty.nYears;
			comp[i].life.nDays=life.nDays;
			comp[i].life.nMonths=life.nMonths;				
			comp[i].life.nYears=life.nYears;
			comp[i].writeOff.day=0;
			comp[i].writeOff.month=0;
			comp[i].writeOff.year=0;
			comp[i].writeOff.day=date_of_manufacture.day+life.nDays;

			printf("UPDATING.\n");
			while(comp[i].writeOff.day>30)
			{
				comp[i].writeOff.day-=30;
				comp[i].writeOff.month+=1;
			}
		
			comp[i].writeOff.month+=date_of_manufacture.month+life.nMonths;
			while(comp[i].writeOff.month>12)
			{
				comp[i].writeOff.month-=12;
				comp[i].writeOff.year+=1;
			}
			comp[i].writeOff.year+=date_of_manufacture.year+life.nYears;
			status=SUCCESS_UPDATE;
		}
	}
	else
	{
		i=0;

		while(i<size&&!(freeIndex))
		{
			if(comp[i].date_of_purchase.day==0)
			{
				freeIndex=1;
			}
			else
			{
				i++;
			}
		}
		if(freeIndex)
		{
			j=i-1;						//ith pos is free

			while((j>=0)&&(comp[j].date_of_purchase.year>date_of_purchase.year))
			{
				j--;

			}
			while((j>=0)&&(comp[j].date_of_purchase.year==date_of_purchase.year)&&(comp[j].date_of_purchase.month>date_of_purchase.month))
			{
				j--;

			}
			while((j>=0)&&(comp[j].date_of_purchase.year==date_of_purchase.year)&&(comp[j].date_of_purchase.month==date_of_purchase.month)&&(comp[j].date_of_purchase.day>date_of_purchase.day))
			{
				j--;
			}
			while((j>=0)&&(comp[j].date_of_purchase.year==date_of_purchase.year)&&(comp[j].date_of_purchase.month==date_of_purchase.month)&&(comp[j].date_of_purchase.day==date_of_purchase.day)&&(strcmp(comp[j].compId,compId)>0))
			{
				j--;
			}
			if(j!=i-1)
			{
				stop=shiftRight(comp,size,j,i);
				Initialize(comp,stop,stop,comp[stop].procLevel);
					
				
			}
			j++;

			strcpy(comp[j].compId,compId);
			strcpy(comp[j].procLevel,procLevel);
			comp[j].date_of_manufacture.day=date_of_manufacture.day;
			comp[j].date_of_manufacture.month=date_of_manufacture.month;
			comp[j].date_of_manufacture.year=date_of_manufacture.year;
			comp[j].date_of_purchase.day=date_of_purchase.day;
			comp[j].date_of_purchase.month=date_of_purchase.month;
			comp[j].date_of_purchase.year=date_of_purchase.year;
			comp[j].warranty.nDays=warranty.nDays;
			comp[j].warranty.nMonths=warranty.nMonths;
			comp[j].warranty.nYears=warranty.nYears;
			comp[j].life.nDays=life.nDays;
			comp[j].life.nMonths=life.nMonths;
			comp[j].life.nYears=life.nYears;
			comp[j].writeOff.day=date_of_manufacture.day+life.nDays;
			while(comp[j].writeOff.day>30)
			{
				comp[j].writeOff.day-=30;
				comp[j].writeOff.month+=1;
			}

			comp[j].writeOff.month+=date_of_manufacture.month+life.nMonths;
			while(comp[j].writeOff.month>12)
			{
				comp[j].writeOff.month-=12;
				comp[j].writeOff.year+=1;
			}
			comp[j].writeOff.year+=date_of_manufacture.year+life.nYears;


		}
		else
		{
			status=FAILURE;
			printf("Insert Operation FAILED\n");
		}
	}
	
	return status;

}
void MergeSortWarrantyPeriodExpiry(InventoryMS comp[],InventoryMS temp[],int start,int end)
{
	int mid;
	if(start<end)
	{
		mid=(start+end)/2;
		MergeSortWarrantyPeriodExpiry(comp,temp,start,mid);
		MergeSortWarrantyPeriodExpiry(comp,temp,mid+1,end);
		MergeSelfWarrantyPeriodExpiry(comp,temp,start,end);
	}
return;
	
}
int SortOnWarrantyPeriodExpiry(InventoryMS temp[],InventoryMS getSortedOnWarrantyPeriodExpiry[],int size)
{
	int status,ret_status=SUCCESS,i;
	status=isEmpty(temp);
	InventoryMS temporary[MAX_SIZE];
	if(status==SUCCESS)
	{
		ret_status=FAILURE;
	}
	else
	{

		Initialize(temporary,0,MAX_SIZE-1,"");
		for(i=0;i<size&&temp[i].date_of_purchase.day!=0;i++)
		{
			transfer(getSortedOnWarrantyPeriodExpiry,i,temp,i);//getSortedOnWarrantyPeriodExpiry[i]=temp[i];
		}
		MergeSortWarrantyPeriodExpiry(getSortedOnWarrantyPeriodExpiry,temporary,0,i-1);
	}
	return ret_status;
}
int compareUsedPeriod(InventoryMS a,InventoryMS b)   //if a<b then -1 otherwise output is 1
{
    int status=1;
    if((a.writeOff.year-a.date_of_purchase.year)<(b.writeOff.year-b.date_of_purchase.year))
    {
        status=-1;
    }
    else if(((a.writeOff.year-a.date_of_purchase.year)==(b.writeOff.year-b.date_of_purchase.year))&&((a.writeOff.month-a.date_of_purchase.month)<(b.writeOff.month-b.date_of_purchase.month)))
    {
        status=-1;
    }
    else if(((a.writeOff.year-a.date_of_purchase.year)==(b.writeOff.year-b.date_of_purchase.year))&&((a.writeOff.month-a.date_of_purchase.month)==(b.writeOff.month-b.date_of_purchase.month))&&((a.writeOff.day-a.date_of_purchase.day)<(b.writeOff.day-b.date_of_purchase.day)))
    {
        status=-1;
    }
    return status;
}
int getLongestUsedPeriod(InventoryMS comp[],int size,InventoryMS longestUsedPeriod[])		//same size of longestUsedPeriod
{
	int status,pos,j,i;
	if(isEmpty(comp))
	{
		status=FAILURE;
	}
	else
	{
		status=SUCCESS,pos=0,j=0,i;
		for(i=1;i<size&&comp[i].date_of_purchase.day!=0;i++)
    		{
			if(compareUsedPeriod(comp[pos],comp[i])==-1)
            		{
                		pos=i;
                		status=SUCCESS;
           		 }
   	 	}
    		for(i=0;i<size&&comp[i].date_of_purchase.day!=0;i++)
		{
        		if((datecompare(comp[i].date_of_purchase,comp[pos].date_of_purchase)==0)&&(datecompare(comp[i].writeOff,comp[pos].writeOff)==0))
			{
            			
            			transfer(longestUsedPeriod,j,comp,i);//longestUsedPeriod[j]=comp[i];
            			j++;
           		 
        		}
    		}

	}
return status;
}
void mergeselfOnUsedPeriod(InventoryMS comp[],InventoryMS temp[],int low,int high)
{
    int i=low,mid=((low+high)/2),j=mid+1,k=low;
    while(i<=mid&&j<=high)
    {
        if(compareUsedPeriod(comp[i],comp[j])==-1)
        {
            transfer(temp,k,comp,i);//temp[k++]=comp[i++];
            k++;
            i++;
        }
        else
        {
            transfer(temp,k,comp,j);//temp[k++]=comp[j++];
            k++;
            j++;
            
        }
    }
    while(i<=mid)
    {
        transfer(temp,k,comp,i);//temp[k++]=comp[i++];
         k++;
         i++;
    }
    while(j<=high)
    {
        transfer(temp,k,comp,j);//temp[k++]=comp[j++];
        k++;
        j++;
    }
    i=low;
    k=low;
    while(i<=high)
    {
        transfer(comp,i,temp,k);//comp[i++]=temp[k++];
        i++;
        k++;
    }
return;
}

void mergesortOnUsedPeriod(InventoryMS A[],InventoryMS C[],int start,int end)
{
    int mid;
    if(start<end)
    {
        mid=(start+end)/2;
        mergesortOnUsedPeriod(A,C,start,mid);
        mergesortOnUsedPeriod(A,C,mid+1,end);
        mergeselfOnUsedPeriod(A,C,start,end);
    }
return;
}
int getSortedOnUsedPeriod(InventoryMS comp[],int size,InventoryMS temp[])
{
    int status=FAILURE;
    int ret_status=SUCCESS;
    status=isEmpty(comp);
    if(status==SUCCESS)
    {
    	ret_status=FAILURE;
    }
    else
    {
    	InventoryMS temporary[MAX_SIZE];
    	int i;
   	 for(i=0;i<size&&comp[i].date_of_purchase.day!=0;i++)
    	{
        	transfer(temp,i,comp,i);//temp[i]=comp[i];
    	}
    	mergesortOnUsedPeriod(temp,temporary,0,size-1);
    }
    return ret_status;
}

int Union(InventoryMS listUnion[],InventoryMS list1[],int numRecordsListUnion1,InventoryMS list2[],int numRecordsListUnion2)
{
	int size=0;
	int i=0;
	int j=0;
	int dtResult;
	while((i<numRecordsListUnion1)&&(j<numRecordsListUnion2))
	{
		dtResult=datecompare(list1[i].date_of_purchase,list2[j].date_of_purchase);
		if(dtResult==FIRST_GREATER)
		{
			transfer(listUnion,size,list2,j);
			j++;
		}
		else if(dtResult==BOTH_EQUAL&&(strcmp(list1[i].compId,list2[j].compId)>=0))
		{
			if(strcmp(list1[i].compId,list2[j].compId)==0)
			{
				transfer(listUnion,size,list1,i);
				i++;
				j++;
			}
			else
			{
				transfer(listUnion,size,list2,j);
				j++;
			}
		}
		else
		{
			transfer(listUnion,size,list1,i);
			i++;
		}
		size++;
		
	}
	while((i<numRecordsListUnion1))
	{
		
			
		
		transfer(listUnion,size,list1,i);
		i++;
		
		size++;
		
	}
	while((j<numRecordsListUnion2))
	{
		
		transfer(listUnion,size,list2,j);
		j++;
		size++;
	}
	return (size);
}

int Intersection(InventoryMS listIntersection[],InventoryMS list1[],int numRecordsIntersection1,InventoryMS list2[],int  numRecordsIntersection2)
{
	int pos,i=0,size=0;
	while(i<numRecordsIntersection2)
	{
		pos=posFind(list1,list2[i].compId,list2[i].date_of_purchase,0,numRecordsIntersection1-1);
		if(!(pos==NOT_FOUND))							//equivalent to if(FOUND)			
		{
			if(strcmp(list1[pos].procLevel,list2[i].procLevel)>0)
			{
				listIntersection[size++]=list1[pos];
			}
			else
			{
				listIntersection[size++]=list2[i];
			}
				
		}
		i++;
	}
	return size;
}
int Difference(InventoryMS listDiff[],InventoryMS list1[],int numRecordsDiff1,InventoryMS list2[],int numRecordsDiff2)
{

	int i=0,pos,status,maxSizeDiff,sizeListDiff=0;
	maxSizeDiff=numRecordsDiff1;
	if(numRecordsDiff2>maxSizeDiff)
	{
		maxSizeDiff=numRecordsDiff2;
	}
	while(i<numRecordsDiff1)
	{
		pos=posFind(list2,list1[i].compId,list1[i].date_of_purchase,0,numRecordsDiff2-1);
		if(pos==NOT_FOUND)	//Insert in listDiff
		{
			
			status=Insert(listDiff,maxSizeDiff,list1[i].compId,list1[i].procLevel,list1[i].date_of_manufacture,list1[i].date_of_purchase,list1[i].warranty,list1[i].life);
			sizeListDiff++;
		}
		i++;
		
	}
	return sizeListDiff;
}
int SymmetricDifference(InventoryMS listSymmDiff[],InventoryMS list1[],int numRecordsSymmDiff1,InventoryMS list2[],int numRecordsSymmDiff2)
{
	InventoryMS listSymmDiff12[MAX_SIZE],listSymmDiff21[MAX_SIZE];
	Initialize(listSymmDiff12,0,MAX_SIZE-1,"");
	Initialize(listSymmDiff21,0,MAX_SIZE-1,"");	
	int sizeDiff12=Difference(listSymmDiff12,list1,numRecordsSymmDiff1,list2,numRecordsSymmDiff2);
	int sizeDiff21=Difference(listSymmDiff21,list2,numRecordsSymmDiff2,list1,numRecordsSymmDiff1);
	int sizeSymmDiff=Union(listSymmDiff,listSymmDiff12,sizeDiff12,listSymmDiff21,sizeDiff21);
	return sizeSymmDiff;
}
void IncreaseLifeFunc(InventoryMS comp[],int pos,period increaseLife)
{
	comp[pos].life.nDays+=increaseLife.nDays;
	while(comp[pos].life.nDays>30)
	{
		comp[pos].life.nMonths++;
		comp[pos].life.nDays-=30;
	}
	comp[pos].life.nMonths+=increaseLife.nMonths;
	while(comp[pos].life.nMonths>12)
	{
		comp[pos].life.nYears++;
		comp[pos].life.nMonths-=12;
	}
	comp[pos].life.nYears+=increaseLife.nYears;
	comp[pos].writeOff.day+=increaseLife.nDays;
	while(comp[pos].writeOff.day>30)
	{
		comp[pos].writeOff.month++;
		comp[pos].writeOff.day-=30;
	}
	comp[pos].writeOff.month+=increaseLife.nMonths;
	while(comp[pos].writeOff.month>12)
	{
		comp[pos].writeOff.year++;
		comp[pos].writeOff.month-=12;
	}
	comp[pos].writeOff.year+=increaseLife.nYears;
	return;
	
}

void UpdateLists(InventoryMS comp[],int sizeComp,UpdateIMS input[],int sizeInput,InventoryMS compI3[],InventoryMS compI5[],InventoryMS compI7[])	
{
	int i=0,pos,status;
	int notValid=1;
	char store[PROC_LEVEL];
	store[0]='\0';
	while(i<sizeInput)
	{
		
		printf("CHOICE:%d\t",input[i].event);
		switch(input[i].event)
		{
			case INCREASE_LIFE_PERIOD:
				printf("EVENT INCREASE LIFE PERIOD\n");
				pos=posFind(comp,input[i].compId,input[i].date_of_purchase,0,sizeComp-1);
				period increaseLife;
				
				if(pos!=NOT_FOUND)
				{
					printf("Enter by how much LIFE PERIOD of the specified computer should be Increased\nYEARS:\t");
					scanf("%d",&increaseLife.nYears);
					printf("MONTHS:\t");
					scanf("%d",&increaseLife.nMonths);
					printf("DAYS:\t");
					scanf("%d",&increaseLife.nDays);
					IncreaseLifeFunc(comp,pos,increaseLife);
					if(!(strcmp(comp[pos].procLevel,procLevelI3)))
					{
						pos=posFind(compI3,input[i].compId,input[i].date_of_purchase,0,getNumComputers(compI3,MAX_SIZE-1));
						IncreaseLifeFunc(compI3,pos,increaseLife);
					}
					else if(!(strcmp(comp[pos].procLevel,procLevelI5)))
					{
						pos=posFind(compI5,input[i].compId,input[i].date_of_purchase,0,getNumComputers(compI5,MAX_SIZE-1));
						IncreaseLifeFunc(compI5,pos,increaseLife);
					}
					else
					{
						pos=posFind(compI7,input[i].compId,input[i].date_of_purchase,0,getNumComputers(compI7,MAX_SIZE-1));
						IncreaseLifeFunc(compI7,pos,increaseLife);
					}
					
					printf("LIFE PERIOD INCREASED OF THE SPECIFIED COMPUTER\n"); 
				}
				else
				{
					printf("SPECIFIED COMPUTER NOT FOUND\n");
				}
				break;
			case PURCHASE:
					printf("EVENT PURCHASE\n");
					input[i]=PurchaseInfo(input[i]);
				
					status=Insert(comp,MAX_SIZE,input[i].compId,input[i].procLevel,input[i].date_of_manufacture,input[i].date_of_purchase,input[i].warranty,input[i].life);
					if((status==SUCCESS_NEW)||status==SUCCESS_UPDATE)
					{
						if(status==SUCCESS_NEW)
						{
							printf("Purchased computer successfully inserted\n");
						}
						else 
						{
							printf("ALERT::COMPUTER FOUND WITH SAME KEY\nFOUND COMPUTER UPDATED\n");
						}
						if(!(strcmp(input[i].procLevel,procLevelI3)))
						{
							status=Insert(compI3,MAX_SIZE,input[i].compId,input[i].procLevel,input[i].date_of_manufacture,input[i].date_of_purchase,input[i].warranty,input[i].life);
						}
						else if(!(strcmp(input[i].procLevel,procLevelI5)))
						{
							status=Insert(compI5,MAX_SIZE,input[i].compId,input[i].procLevel,input[i].date_of_manufacture,input[i].date_of_purchase,input[i].warranty,input[i].life);
						}
						else
						{
							status=Insert(compI7,MAX_SIZE,input[i].compId,input[i].procLevel,input[i].date_of_manufacture,input[i].date_of_purchase,input[i].warranty,input[i].life);
						}
					}
				
				
				break;
			case SELL://int Delete(InventoryMS comp[],int size,date date_of_purchase,char compId[])
				printf("EVENT SELL\n");
				status=Delete(comp,sizeComp,input[i].date_of_purchase,input[i].compId);
				if(status!=NOT_FOUND)
				{
					if(status==procIsI3)
					{
						status=Delete(compI3,MAX_SIZE,input[i].date_of_purchase,input[i].compId);
					}
					else if(status==procIsI5)
					{
						status=Delete(compI5,MAX_SIZE,input[i].date_of_purchase,input[i].compId);
					}
					else 
					{
						status=Delete(compI7,MAX_SIZE,input[i].date_of_purchase,input[i].compId);
					}
					printf("SPECIFIED COMPUTER SOLD(DELETED)\n");
				}
				else
				{
					printf("SPECIFIED COMPUTER NOT FOUND\n");
				}
				break;
			case UPGRADE_PROCESSOR:
					printf("EVENT:UPGRADE PROCESSOR LEVEL\n");
				
				
				
					pos=posFind(comp,input[i].compId,input[i].date_of_purchase,0,sizeComp-1);
					if(pos!=NOT_FOUND)
					{
						if(!(strcmp(procLevelI7,comp[pos].procLevel)))
						{
							printf("A COMPUTER WITH PROCESSOR LEVEL I7 CANNOT BE UPGRADED\n");
						}
						else
						{
							printf("ENTER PROCESSOR LEVEL TO WHICH THE SPECIFIED COMPUTER'S PROCESSOR LEVEL SHOULD UPGRADE TO:\t");
							scanf("%s",input[i].procLevel);
							if(strcmp(input[i].procLevel,comp[pos].procLevel)>0)
							{
								if(!(strcmp(procLevelI5,input[i].procLevel))||!(strcmp(procLevelI7,input[i].procLevel)))
								{
			
			
									notValid=0;
			
			
								}
							}
							while(notValid)
							{
								printf("ENTER VALID PROCESSOR LEVEL FOR UPGRADATION\n");
								scanf("%s",input[i].procLevel);
								if(strcmp(input[i].procLevel,comp[pos].procLevel)>0)
								{
									if(!(strcmp(procLevelI5,input[i].procLevel))||!(strcmp(procLevelI7,input[i].procLevel)))
									{
			
			
										notValid=0;
			
			
									}
								}
							}
						
						
						
							strcpy(store,comp[pos].procLevel);
							
							comp[pos].procLevel[0]='\0';
							strcpy(comp[pos].procLevel,input[i].procLevel);
							if(!(strcmp(comp[pos].procLevel,procLevelI5)))
							{
								status=Insert(compI5,MAX_SIZE,comp[pos].compId,comp[pos].procLevel,comp[pos].date_of_manufacture,comp[pos].date_of_purchase,comp[pos].warranty,comp[pos].life);
							
							
							
							}
							if(!(strcmp(comp[pos].procLevel,procLevelI7)))
							{
								status=Insert(compI7,MAX_SIZE,comp[pos].compId,comp[pos].procLevel,comp[pos].date_of_manufacture,comp[pos].date_of_purchase,comp[pos].warranty,comp[pos].life);
							
							
							}
							if(!(strcmp(store,procLevelI3)))
							{
								status=Delete(compI3,MAX_SIZE,comp[pos].date_of_purchase,comp[pos].compId);
							
							}
							else //I5
							{
								status=Delete(compI5,MAX_SIZE,comp[pos].date_of_purchase,comp[pos].compId);
							}
							printf("\nPROCESSOR LEVEL OF SPECIFIED COMPUTER UPGRADED SUCCESSFULLY FROM %s TO %s\n",store,comp[pos].procLevel);
						}
						
					}	
					else
					{
						printf("SPECIFIED COMPUTER NOT FOUND\n");
					}
				
				
				
				break;
			default:
				printf("ENTER VALID CHOICE\n");
				break;
		}
		i++;
	}
	return;
}
int main()
{
	printf("\t\tVNIT,NAGPUR\n\t\tCOMPUTER SCIENCE AND ENGINEERING\n\t\tINVENTORY MANAGEMENT SYSTEM\n\t\tCREATED BY:BT16CSE053(ABDUL SATTAR MAPARA),BT16CSE056(SHIVAM MISHRA)\n\t\tGUIDED BY:RESPECTED KESKAR SIR\n");
	printf("ABOUT THE SYSTEM::\n**EACH MONTH IS ASSUMED TO BE OF 30 DAYS(ASSUMPTION)\n**THERE ARE EXACTLY 12 MONTHS IN AN YEAR\n**VALID INPUTS ARE EXPECTED FOR EACH FIELD FOR THE PROGRAM TO RUN SUCCESSFULLY\n\nPROCEEDING TO THE PROGRAM----->\n");
	/*ARRAY OF STRUCTURE DECLARATIONS*/
	InventoryMS comp[MAX_SIZE];
	InventoryMS compI3[MAX_SIZE];
	InventoryMS compI5[MAX_SIZE];
	InventoryMS compI7[MAX_SIZE];
	InventoryMS longestUsedPeriod[MAX_SIZE];
	InventoryMS getSortedOnWarrantyPeriodExpiry[MAX_SIZE];
	InventoryMS getSortOnUsedPeriod[MAX_SIZE];
	InventoryMS listUnique[MAX_SIZE];
	InventoryMS listUnion[2*MAX_SIZE];
	InventoryMS list1[MAX_SIZE];
	InventoryMS list2[MAX_SIZE];
	InventoryMS listIntersection[MAX_SIZE];
	InventoryMS listDiff[MAX_SIZE];
	InventoryMS listSymmDiff[2*MAX_SIZE];
	/*INITIALIZE ALL DATABASES*/
	Initialize(comp,0,MAX_SIZE-1,"");
	Initialize(compI3,0,MAX_SIZE-1,procLevelI3);
	Initialize(compI5,0,MAX_SIZE-1,procLevelI5);
	Initialize(compI7,0,MAX_SIZE-1,procLevelI7);
	
	Initialize(getSortedOnWarrantyPeriodExpiry,0,MAX_SIZE-1,"");
        
        InventoryMS Input;
	int i=0,j=0,option,numRecords,numRecordsListUnion1,numRecordsListUnion2,numRecordsIntersection1,numRecordsIntersection2,SizeIntersection;
	int numRecordsDiff1,numRecordsDiff2,maxSizeDiff;
	int numRecordsSymmDiff1,numRecordsSymmDiff2;
	
	
	int status;
	int sizeListOpr;
	int maxPurchase,maxSell,maxInrLife,maxUpgradeProc;
	
	int numRecordsListUnique;
	UpdateIMS input[MAX_SIZE];
	int countEvents;
	int flag,flag1,flag2,flag3,flag4;
	//FIRST TIME INPUT FROM USER-----STORED IN COMMON ARRAY OF STRUCTURE COMP------
	printf("ENTER NUMBER OF RECORDS YOU WANT TO ENTER\n");
	numRecords=inputSize(MAX_SIZE);	
	while(i<numRecords)
	{
		Input=inputStruct(Input);
		
		//INSERT INFO INTO COMMON LIST
		status=Insert(comp,MAX_SIZE,Input.compId,Input.procLevel,Input.date_of_manufacture,Input.date_of_purchase,Input.warranty,Input.life);
		if(status==SUCCESS_UPDATE||status==SUCCESS_NEW)
		{
			printf("INSERT Operation SUCCESSFUL\n");
			if(!(strcmp(Input.procLevel,procLevelI3)))
			{
				status=Insert(compI3,MAX_SIZE,Input.compId,procLevelI3,Input.date_of_manufacture,Input.date_of_purchase,Input.warranty,Input.life);
			}
			else if(!(strcmp(Input.procLevel,procLevelI5)))
			{
				status=Insert(compI5,MAX_SIZE,Input.compId,procLevelI5,Input.date_of_manufacture,Input.date_of_purchase,Input.warranty,Input.life);
			}
			if(!(strcmp(Input.procLevel,procLevelI7)))
			{
				status=Insert(compI7,MAX_SIZE,Input.compId,procLevelI7,Input.date_of_manufacture,Input.date_of_purchase,Input.warranty,Input.life);
			}
		}
		i++;

	}
	char another[REPEAT_CHOICE];
	char repeat[REPEAT_CHOICE];
	char ListView[PROC_LEVEL];
	do
	{
		option=menu();
		switch(option)
		{
	    		case 1:
	    			
        			Input=inputStruct(Input);
        			
				//INSERT INFO INTO COMMON LIST
				status=Insert(comp,MAX_SIZE,Input.compId,Input.procLevel,Input.date_of_manufacture,Input.date_of_purchase,Input.warranty,Input.life);
			if(status==SUCCESS_UPDATE||status==SUCCESS_NEW)
			{
				printf("INSERT OPERATION SUCCESSFUL\n");
				if(!(strcmp(Input.procLevel,procLevelI3)))
				{
					status=Insert(compI3,MAX_SIZE,Input.compId,procLevelI3,Input.date_of_manufacture,Input.date_of_purchase,Input.warranty,Input.life);
				}
				else if(!(strcmp(Input.procLevel,procLevelI5)))
				{
					status=Insert(compI5,MAX_SIZE,Input.compId,procLevelI5,Input.date_of_manufacture,Input.date_of_purchase,Input.warranty,Input.life);
				}
				if(!(strcmp(Input.procLevel,procLevelI7)))
				{
					status=Insert(compI7,MAX_SIZE,Input.compId,procLevelI7,Input.date_of_manufacture,Input.date_of_purchase,Input.warranty,Input.life);
				}
				if(status==SUCCESS_NEW)
				{
					numRecords++;
				}
				
			}
			
			break;
	    		case 2:
	       			//Delete:::Take date of purchase and compId and call Delete function
				printf("Enter COMPUTER ID\t");
				scanf("%s",Input.compId);
				printf("Enter Date of Purchase\nDATE\t:");
				scanf("%d",&Input.date_of_purchase.day);
				printf("MONTH\t:");
				scanf("%d",&Input.date_of_purchase.month);
				printf("YEAR\t:");
				scanf("%d",&Input.date_of_purchase.year);
				status=Delete(comp,numRecords,Input.date_of_purchase,Input.compId);	
				if(status!=NOT_FOUND)
				{
					if(status==procIsI3)
					{
						status=Delete(compI3,MAX_SIZE,Input.date_of_purchase,Input.compId);	
						printf("Deleted entry from ");
						puts(procLevelI3);
						printf("\n"); 
					}
					else if(status==procIsI5)
					{
						status=Delete(compI5,MAX_SIZE,Input.date_of_purchase,Input.compId);
						printf("Deleted entry from ");
						puts(procLevelI5);
						printf("\n"); 
					}
					else
					{
						status=Delete(compI7,MAX_SIZE,Input.date_of_purchase,Input.compId);
						printf("Deleted entry from ");
						puts(procLevelI7);
						printf("\n"); 
					}
					printf("Delete Operation SUCCESSFUL\n");
					numRecords--;
				}
				
       				 break;
       			 case 3:
            			printf("\nThe total number of computers in common record is %d\n",getNumComputers(comp,MAX_SIZE));
           		       	printf("\nThe total number of computers in list of computers with I3 procLevel is %d\n",getNumComputers(compI3,MAX_SIZE));
           			 printf("\nThe total number of computers in list of computers with I5 procLevel is %d\n",getNumComputers(compI5,MAX_SIZE));
            			 printf("\nThe total number of computers in list of computers with I7 procLevel is %d\n",getNumComputers(compI7,MAX_SIZE));
           			 break;
        		case 4:
           			 if(isEmpty(comp)==SUCCESS)
            			 {
                			printf("The common record is empty");
            			 }
           			 else
           			 {
              				 printf("The common record is not empty");
               				 if(isEmpty(compI3)==SUCCESS)
              			         {
                   				 printf("The list of computers with procLevel I3 is empty");
               				 }
                			if(isEmpty(compI5)==SUCCESS)
                			{
                   				 printf("The list of computers with procLevel I5 is empty");
                			}
              			       if(isEmpty(compI7)==SUCCESS)
               			        {
                  				  printf("The list of computers with procLevel I7 is empty");
                			}
            			}
            			break;
       		     case 5:
            			if(isFull(comp)==SUCCESS)
           			{
               				 printf("THE COMMON RECORD IS FULL\n");
               				 if(isFull(compI3)==SUCCESS)
                			{
                    				printf("THE LIST OF COMPUTERS WITH PROCLEVEL I3 IS FULL\n");
                			}
               				 else if(isFull(compI5)==SUCCESS)
               				{
                   				 printf("THE LIST OF COMPUTERS WITH PROCLEVEL I5 IS FULL\n");
                			}
                			else if(isFull(compI7)==SUCCESS)
                			{
                    				printf("THE LIST OF COMPUTERS WITH PROCLEVEL I7 IS FULL\n");
               				}
            			}

           		        else
           			{
               				 printf("THE COMMON RECORD IS NOT FULL\n");
            			 }
            			break;
            			
        	   case 6:
        	   		 Initialize(longestUsedPeriod,0,MAX_SIZE-1,"");
        	   		 ListView[0]='\0';
        	   		 printf("ENTER PROCESSOR LEVEL FOR WHICH COMPUTER(S) WITH LONGEST USED PERIOD ARE TO BE SHOWN\nIF YOUR CHOICE IS COMMON RECORD ENTER I0\n");
        	   		 scanf("%s",ListView);
        	   		 if(!(strcmp(ListView,"I3")))
        	   		 {
        	   		 	status=getLongestUsedPeriod(compI3,numRecords,longestUsedPeriod);
           			 	if(status==SUCCESS)
           		        	 {
                				printf("THE FOLLOWING HAVE THE LONGEST USED PERIOD\n");
                				for(i=0;(i<numRecords)&&(longestUsedPeriod[i].date_of_purchase.day!=0);i++)
               					 {
                   					 printf("\n%s",longestUsedPeriod[i].compId);
                    					printf(" %s\n",longestUsedPeriod[i].procLevel);
               					 }
            		   	 	 }
            		   	 
            		   		else
            		   	        {
            		   	 		printf("THE RECORD IS EMPTY\n");
            		   	 	}
        	   		 }
        	   		 else if(!(strcmp(ListView,"I5")))
        	   		 {
        	   		 	status=getLongestUsedPeriod(compI5,numRecords,longestUsedPeriod);
           			 	if(status==SUCCESS)
           		        	 {
                				printf("THE FOLLOWING HAVE THE LONGEST USED PERIOD\n");
                				for(i=0;(i<numRecords)&&(longestUsedPeriod[i].date_of_purchase.day!=0);i++)
               					 {
                   					 printf("\n%s",longestUsedPeriod[i].compId);
                    					printf(" %s\n",longestUsedPeriod[i].procLevel);
               					 }
            		   	 	 }
            		   	 
            		   		else
            		   	        {
            		   	 		printf("THE RECORD IS EMPTY\n");
            		   	 	}
        	   		 }
        	   		 else if(!(strcmp(ListView,"I7")))
        	   		 {
        	   		 	status=getLongestUsedPeriod(compI7,numRecords,longestUsedPeriod);
           			 	if(status==SUCCESS)
           		        	 {
                				printf("THE FOLLOWING HAVE THE LONGEST USED PERIOD\n");
                				for(i=0;(i<numRecords)&&(longestUsedPeriod[i].date_of_purchase.day!=0);i++)
               					 {
                   					 printf("\n%s",longestUsedPeriod[i].compId);
                    					printf(" %s\n",longestUsedPeriod[i].procLevel);
               					 }
            		   	 	 }
            		   	 
            		   		else
            		   	        {
            		   	 		printf("THE RECORD IS EMPTY\n");
            		   	 	}
        	   		 }
        	   		 else if(!(strcmp(ListView,"I0")))
        	   		 {
        	   		 	status=getLongestUsedPeriod(comp,numRecords,longestUsedPeriod);
           			 	if(status==SUCCESS)
           		        	 {
                				printf("THE FOLLOWING HAVE THE LONGEST USED PERIOD\n");
                				for(i=0;(i<numRecords)&&(longestUsedPeriod[i].date_of_purchase.day!=0);i++)
               					 {
                   					 printf("\n%s",longestUsedPeriod[i].compId);
                    					printf(" %s\n",longestUsedPeriod[i].procLevel);
               					 }
            		   	 	 }
            		   	 
            		   		else
            		   	        {
            		   	 		printf("THE RECORD IS EMPTY\n");
            		   	 	}
        	   		 }
        	   		 else
        	   		 {
        	   		 	printf("INVALID CHOICE\n");
        	   		 }
        	   		 
        	   		 
            			break;
            	 case 7:
            	 		maxPurchase=0;
            	 		maxSell=0;
            	 		maxInrLife=0;
            	 		maxUpgradeProc=0;
            	 		InitializeUpdateInput(input,0,MAX_SIZE-1);
            	 		countEvents=0;
				strcpy(repeat,"YES");
				flag=1;
				flag1=0;
				flag2=0;
				flag3=0;
				flag4=0;
				while(flag&&(!(strcmp(repeat,"YES"))))
				{
					printf("\t\tUPDATE LISTS\nEVENT NO.\t\tEVENT NAME\t\t\n1]\t\tINCREASE LIFE PERIOD OF A COMPUTER\n2]\t\tPURCHASE A COMPUTER\n3]\t\tSELL A COMPUTER\n4]\t\tUPGRADE PROCESSOR OF A COMPUTER\n");
					printf("ENTER EVENT NO.\n");
					scanf("%d",&input[countEvents].event);
					if(maxPurchase>=MAX_SIZE-numRecords)
					{
						flag1=1;
						if(input[countEvents].event==PURCHASE)
						{
							input[countEvents].event=NOT_FOUND;
							printf("MAXIMUM SIZE REACHED to add to the list.List is completely Full\n");
							
						}
					}
					if(maxSell>=numRecords)
					{
						flag2=1;
						if(input[countEvents].event==SELL)
						{
							input[countEvents].event=NOT_FOUND;
							printf("NO MORE COMPUTERS AVAILABLE TO BE SOLD \n");
							
						}
					}
					if(maxInrLife>=numRecords)
					{
						flag3=1;
						if(input[countEvents].event==INCREASE_LIFE_PERIOD)
						{
							input[countEvents].event=NOT_FOUND;
							printf("NO MORE COMPUTERS AVAILABLE TO INCREASE LIFE PERIOD \n");
							
						}
					}
					if(maxUpgradeProc>=numRecords-getNumComputers(compI7,MAX_SIZE))
					{
						flag4=1;
						if(input[countEvents].event==UPGRADE_PROCESSOR)
						{
							input[countEvents].event=NOT_FOUND;
							printf("NO MORE COMPUTERS AVAILABLE TO UPGRADE THEIR PROCESSOR LEVELS \n");
							
						}
					}
					if(flag1&&flag2&&flag3&&flag4)
					{
						flag=0;
						printf("NO MORE OPERATIONS CURRENTLY\n");
					}
					else
					{
						while(input[countEvents].event>4||input[countEvents].event<1)
						{
							printf("Enter EVENT NO. CORRECTLY\n");
							scanf("%d",&input[countEvents].event);
							if(flag1&&input[countEvents].event==PURCHASE)
							{
								printf("MAXIMUM SIZE REACHED to add to the list.List is completely Full\n");
								input[countEvents].event=NOT_FOUND;
							}
							else if(flag2&&input[countEvents].event==SELL)
							{
								printf("NO MORE COMPUTERS AVAILABLE TO BE SOLD \n");
								input[countEvents].event=NOT_FOUND;
							}
							else if(flag3&&input[countEvents].event==INCREASE_LIFE_PERIOD)
							{
								printf("NO MORE COMPUTERS AVAILABLE TO INCREASE LIFE PERIOD \n");
								input[countEvents].event=NOT_FOUND;
							}
							else if(flag4&&input[countEvents].event==UPGRADE_PROCESSOR)
							{
								printf("NO MORE COMPUTERS AVAILABLE TO UPGRADE THEIR PROCESSOR LEVELS \n");
								input[countEvents].event=NOT_FOUND;
							}
						}
						switch(input[countEvents].event)
						{
							case PURCHASE:
								maxPurchase++;
								break;
							case SELL:
								maxSell++;
								break;
							case INCREASE_LIFE_PERIOD:
								maxInrLife++;
								break;
							case UPGRADE_PROCESSOR:
								maxUpgradeProc++;
								break;
							
							
							
						}
						input[countEvents]=inputNecessary(input[countEvents]);
						countEvents++;
						printf("Want to enter another event---YES/NO\n");
						scanf("%s",repeat);
					}
				}
				
            	 		UpdateLists(comp,numRecords,input,countEvents,compI3,compI5,compI7);
            	 		numRecords=getNumComputers(comp,MAX_SIZE);
            	 		
            	 		break;	
       		 case 8:	
				if(isEmpty(comp))
				{
					printf("COMMON RECORD IS EMPTY\n");
				}
				else
				{
					printf("ORIGINAL LIST(COMMON RECORD) SORTED ON DATE OF PURCHASE::\n");
            				displayList(comp,numRecords);
            			}
            			printf("\n");
            		
            			
            			break;
        	 case 9:
        	 		Initialize(getSortedOnWarrantyPeriodExpiry,0,numRecords-1,"");
           			status=SortOnWarrantyPeriodExpiry(comp,getSortedOnWarrantyPeriodExpiry,numRecords);
           			if(status==FAILURE)
           			{
           				printf("THE RECORD COULD NOT BE SORTED ON WARRANTY PERIOD EXPIRY DATE\n");
           			}
           			else
           			{
           		        	printf("THE SORTED LIST ON WARRANTY PERIOD EXPIRY IS\n");
           		        	
            				displayList(getSortedOnWarrantyPeriodExpiry,numRecords);
            			}
           			break;
        	 case 10:
        	 		 Initialize(getSortOnUsedPeriod,0,MAX_SIZE-1,"");
           			 status=getSortedOnUsedPeriod(comp,numRecords,getSortOnUsedPeriod);
           			 if(status==FAILURE)
           			{
           				printf("THE RECORD COULD BE SORTED ON USED PERIOD\n");
           			}
           			else
           			{
          			  	printf("\nTHE SORTED LIST ON USED PERIOD IS\n");
          			  	displayList(getSortOnUsedPeriod,numRecords);
          			}
            			break;
            	case 11:
            		printf("Enter size of list for generating unique elements from it not more than ");
            		puts(MAX_SIZE_PRINT);
            		printf("\n");
			numRecordsListUnique=inputSize(MAX_SIZE);
            		Initialize(listUnique,0,numRecordsListUnique-1,"");
            		i=0;
            		while(i<numRecordsListUnique)
            		{
            			
				Input=inputStruct(Input);
				//INSERT INFO INTO listUnique
				status=newInsert(listUnique,numRecordsListUnique,Input.compId,Input.procLevel,Input.date_of_manufacture,Input.date_of_purchase,Input.warranty,Input.life);
				if(status==SUCCESS_NEW||status==SUCCESS_UPDATE)
				{
					printf("INSERT OPERATION SUCCESSFUL\n");
				}
				i++;
            		}
            		if(isEmpty(listUnique))
            		{
            			printf("LIST IS EMPTY\n");
            		}
            		else
            		{
				printf("List of Unique elements from your recently entered list is\n");
            			displayList(listUnique,numRecordsListUnique);
            		}
            		break;	
            	case 12:
            		printf("Enter size of list 1 for its union with list 2 not more than ");
            		puts(MAX_SIZE_PRINT);
            		printf("\n");
            		
            		numRecordsListUnion1=inputSize(MAX_SIZE);
            		
            		
            		printf("Enter size of list 2 for its union with list 1 not more than ");
            		puts(MAX_SIZE_PRINT);
            		printf("\n");
                      	numRecordsListUnion2=inputSize(MAX_SIZE);
                      	
                      	
            		Initialize(listUnion,0,numRecordsListUnion1+numRecordsListUnion2-1,"");
             		Initialize(list1,0,numRecordsListUnion1-1,""); 
             		Initialize(list2,0,numRecordsListUnion2-1,""); 
             		i=0;
             		printf("Enter List1 for UNION with List2\n");
            		while(i<numRecordsListUnion1)
            		{
            			Input=inputStruct(Input);
				//INSERT INFO INTO list1
				status=Insert(list1,numRecordsListUnion1,Input.compId,Input.procLevel,Input.date_of_manufacture,Input.date_of_purchase,Input.warranty,Input.life);
				if(status==SUCCESS_NEW||status==SUCCESS_UPDATE)
				{
					printf("INSERT OPERATION SUCCESSFUL\n");
				}
				i++;
            		} 
            		i=0;
             		printf("Enter List2 for UNION with List1\n");
            		while(i<numRecordsListUnion2)
            		{
            			Input=inputStruct(Input);
				//INSERT INFO INTO list2
				status=Insert(list2,numRecordsListUnion2,Input.compId,Input.procLevel,Input.date_of_manufacture,Input.date_of_purchase,Input.warranty,Input.life);
				if(status==SUCCESS_NEW||status==SUCCESS_UPDATE)
				{
					printf("INSERT OPERATION SUCCESSFUL\n");
				}
				i++;
            		}
            		sizeListOpr=Union(listUnion,list1,numRecordsListUnion1,list2,numRecordsListUnion2);
            		printf("UNION DONE\n"); 
            		if(sizeListOpr!=0)
            		{
            			displayList(listUnion,sizeListOpr);
            		}
            		else
            		{
            			printf("UNION CONTAINS NO ELEMENTS\n");
            		}	     		
            		break;
            	case 13:
            		printf("Enter size of list 1 for its INTERSECTION with list 2 not more than ");
            		puts(MAX_SIZE_PRINT);
            		printf("\n");
            		
            		numRecordsIntersection1=inputSize(MAX_SIZE);
            		
            		
            		printf("Enter size of list 2 for its INTERSECTION with list 1 not more than ");
            		puts(MAX_SIZE_PRINT);
            		printf("\n");
                      	numRecordsIntersection2=inputSize(MAX_SIZE);
                      	
                      	SizeIntersection=numRecordsIntersection1;
                      	if(SizeIntersection<numRecordsIntersection2)
                      		SizeIntersection=numRecordsIntersection2;
                      		
            		Initialize(listIntersection,0,SizeIntersection-1,"");
             		Initialize(list1,0,numRecordsIntersection1-1,""); 
             		Initialize(list2,0,numRecordsIntersection2-1,""); 
             		i=0;
             		printf("Enter List1 for INTERSECTION with List2\n");
            		while(i<numRecordsIntersection1)
            		{
            			Input=inputStruct(Input);
				
				status=Insert(list1,numRecordsIntersection1,Input.compId,Input.procLevel,Input.date_of_manufacture,Input.date_of_purchase,Input.warranty,Input.life);
				if(status==SUCCESS_NEW||status==SUCCESS_UPDATE)
				{
					printf("INSERT OPERATION SUCCESSFUL\n");
				}
				i++;
            		} 
            		i=0;
             		printf("Enter List2 for INTERSECTION with List1\n");
            		while(i<numRecordsIntersection2)
            		{
            			Input=inputStruct(Input);
				
				status=Insert(list2,numRecordsIntersection2,Input.compId,Input.procLevel,Input.date_of_manufacture,Input.date_of_purchase,Input.warranty,Input.life);
				if(status==SUCCESS_NEW||status==SUCCESS_UPDATE)
				{
					printf("INSERT OPERATION SUCCESSFUL\n");
				}
				i++;
            		}
            		sizeListOpr=Intersection(listIntersection,list1,numRecordsIntersection1,list2,numRecordsIntersection2);
            		if(sizeListOpr!=0)
            		{
				displayList(listIntersection,sizeListOpr);
			}
			else
			{
				printf("INTERSECTION CONTAINS NO ELEMENTS\n");
			}
			break;
		case 14:
			printf("Enter size of list 1 for operation DIFFERENCE with list2 not more than ");
            		puts(MAX_SIZE_PRINT);
            		printf("\n");
            		
            		numRecordsDiff1=inputSize(MAX_SIZE);
            		
            		
            		printf("Enter size of list 2 for operation DIFFERENCE with list2 not more than ");
            		puts(MAX_SIZE_PRINT);
            		printf("\n");
                      	numRecordsDiff2=inputSize(MAX_SIZE);
                      	maxSizeDiff=numRecordsDiff1;
                      	if(maxSizeDiff<numRecordsDiff2)
                      	{
                      		maxSizeDiff=numRecordsDiff2;
                      	}
            		Initialize(listDiff,0,maxSizeDiff-1,"");
             		Initialize(list1,0,numRecordsDiff1-1,""); 
             		Initialize(list2,0,numRecordsDiff2-1,""); 
             		i=0;
             		printf("Enter list1 for operation DIFFERENCE with list2 \n");
            		while(i<numRecordsDiff1)
            		{
            			Input=inputStruct(Input);
				//INSERT INFO INTO list1
				status=Insert(list1,numRecordsDiff1,Input.compId,Input.procLevel,Input.date_of_manufacture,Input.date_of_purchase,Input.warranty,Input.life);
				if(status==SUCCESS_NEW||status==SUCCESS_UPDATE)
				{
					printf("INSERT OPERATION SUCCESSFUL\n");
				}
				i++;
            		} 
            		i=0;
             		printf("Enter list2 for operation DIFFERENCE with list1 \n");
            		while(i<numRecordsDiff2)
            		{
            			Input=inputStruct(Input);
				//INSERT INFO INTO list2
				status=Insert(list2,numRecordsDiff2,Input.compId,Input.procLevel,Input.date_of_manufacture,Input.date_of_purchase,Input.warranty,Input.life);
				if(status==SUCCESS_NEW||status==SUCCESS_UPDATE)
				{
					printf("INSERT OPERATION SUCCESSFUL\n");
				}
				i++;
            		}
            		sizeListOpr=Difference(listDiff,list1,numRecordsDiff1,list2,numRecordsDiff2);
            		if(sizeListOpr!=0)
            		{
            			printf("\tDIFFERENCE DONE\n"); 
            			displayList(listDiff,sizeListOpr);
            		}
            		else
            		{
            			printf("DIFFERENCE DOES NOT CONTAIN ANY ELEMENTS\n");
            		}	     		
            		break;
            	case 15:
            		printf("Enter size of list 1 for operation SYMMETRIC DIFFERENCE with list2 not more than ");
            		puts(MAX_SIZE_PRINT);
            		printf("\n");
            		
            		numRecordsSymmDiff1=inputSize(MAX_SIZE);
            		
            		
            		printf("Enter size of list 2 for operation SYMMETRIC DIFFERENCE with list2 not more than ");
            		puts(MAX_SIZE_PRINT);
            		printf("\n");
                      	numRecordsSymmDiff2=inputSize(MAX_SIZE);                     	        
            		Initialize(listSymmDiff,0,numRecordsSymmDiff1+numRecordsSymmDiff2-1,"");
             		Initialize(list1,0,numRecordsSymmDiff1-1,""); 
             		Initialize(list2,0,numRecordsSymmDiff2-1,""); 
             		i=0;
             		printf("Enter list1 for operation SYMMETRIC DIFFERENCE with list2 \n");
            		while(i<numRecordsSymmDiff1)
            		{
            			Input=inputStruct(Input);
				//INSERT INFO INTO list1
				status=Insert(list1,numRecordsSymmDiff1,Input.compId,Input.procLevel,Input.date_of_manufacture,Input.date_of_purchase,Input.warranty,Input.life);
				if(status==SUCCESS_NEW||status==SUCCESS_UPDATE)
				{
					printf("INSERT OPERATION SUCCESSFUL\n");
				}
				i++;
            		} 
            		i=0;
             		printf("Enter list2 for operation SYMMETRIC DIFFERENCE with list1 \n");
            		while(i<numRecordsSymmDiff2)
            		{
            			Input=inputStruct(Input);
				//INSERT INFO INTO list2
				status=Insert(list2,numRecordsSymmDiff2,Input.compId,Input.procLevel,Input.date_of_manufacture,Input.date_of_purchase,Input.warranty,Input.life);
				if(status==SUCCESS_NEW||status==SUCCESS_UPDATE)
				{
					printf("INSERT OPERATION SUCCESSFUL\n");
				}
				i++;
            		}
            		
            		sizeListOpr=SymmetricDifference(listSymmDiff,list1,numRecordsSymmDiff1,list2,numRecordsSymmDiff2);
            		if(sizeListOpr!=0)
            		{
            			printf("\t\tSYMMETRIC DIFFERENCE DONE on your lists\n");
            			displayList(listSymmDiff,sizeListOpr);
            		}
            		else
            		{
            			printf("NO ELEMENTS FOUND AFTER SYMMETRIC DIFFERENCE OPERATION\n");
            		}
            		break;
		case 16:
			ListView[0]='\0';
			printf("ENTER PROCESSOR LEVEL WHOSE LIST IS TO BE DISPLAYED\nIF YOU WANT TO VIEW COMMON LIST ENTER I0\n");
			scanf("%s",ListView);
			if(!(strcmp(ListView,"I0")))
			{
				if(isEmpty(comp))
				{
					printf("LIST IS EMPTY\n");
				}
				else
				{
					displayList(comp,MAX_SIZE);
				}
			}
			else if(!(strcmp(ListView,"I3")))
			{
				if(isEmpty(compI3))
				{
					printf("LIST IS EMPTY\n");
				}
				else
				{
					displayList(compI3,MAX_SIZE);
				}
			}
			else if(!(strcmp(ListView,"I5")))
			{
				if(isEmpty(compI5))
				{
					printf("LIST IS EMPTY\n");
				}
				else
				{
					displayList(compI5,MAX_SIZE);
				}
			}
			else if(!(strcmp(ListView,"I7")))
			{
				if(isEmpty(compI7))
				{
					printf("LIST IS EMPTY\n");
				}
				else
				{
					displayList(compI7,MAX_SIZE);
				}
			}
			else
			{
				printf("CHOICE NOT VALID\n");
			}
			break;
		default:
	    			printf("\n\t\tPLEASE FILL IN A VALID CHOICE\n");
	    			break;
		}
		printf("WANT TO CHOOSE ANOTHER TIME FROM MENU-----YES OR NO\t");
		scanf("%s",another);
	}while(!strcmp(another,"YES"));
	printf("\n\t\tTHANK YOU\n");	
return 0;

}
