
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RecordsFunc.h"
#define CSE 1
#define ECE 2
#define MEC 3
#define EEE 4
#define CIV 5
#define CME 6
#define MET 7
#define MIN 8
#define ARC 9
#define BRANCH_LEN 4
#define NAME_LEN 100
#define SEM_NUM 8
#define TYPE_LEN 3
#define WRITE 1
#define APPEND 2
#define READ 3
#define INVALID_INDEX -1


int ChooseDept()
{
	int dept;
	printf("DEPARTMENTS\n1]CSE\n2]ECE\n3]MEC\n4]EEE\n5]CIV\n6]CME\n7]MET\n8]MIN\n9]ARC\nENTER CHOICE 1-9\t");
	scanf("%d",&dept);
	while(dept!=1)
	{
		if(dept<1||dept>9)
			printf("ENTER A CHOICE IN THE RANGE 1-9\n");
		else		//dept 2-9
			printf("RECORDS FOR THE DEPARTMENT UNDER PROCESS\n");

		scanf("%d",&dept);
	}
	return dept;
}
int StartMenu()
{
	int choice;
	printf("\t\tMENU\n1]ENTER RECORD(s) FOR ALL THE STUDENTS\n2]ENTER RECORD(s) FOR A FEW STUDENTS\n3]USE EXISTING FILE(s)\nPLEASE ENTER YOUR CHOICE NUMBER FROM 1 TO 3\t");
	scanf("%d",&choice);
	while(choice<1||choice>3)
	{
		printf("CHOICE RANGE 1 TO 3\t");
		scanf("%d",&choice);
	}
	return choice;
}
void Initialize(StudentRec *database,int low,int high)
{
	int i=low,k=0;
	/*
						char name[NAME_LEN];
						EnrollNum roll;
						int credits[SEM_NUM];
						float sgpa[SEM_NUM];
						float cgpa;
	*/
	while(i<=high)
	{
		database[i].name[0]='\0';
		database[i].roll.type[0]='\0';
		database[i].roll.admitYear=0;
		database[i].roll.branch[0]='\0';
		database[i].roll.num=0;
		k=0;
		while(k<SEM_NUM)
		{
			database[i].credits[k]=0;
			database[i].sgpa[k]=-1;
			k++;
		}
		database[i].cgpa=0.0;
		i++;
	}
	return;
}
void transfer(StudentRec *destination,StudentRec *source,int dest,int src)
{
	strcpy(destination[dest].roll.type,source[src].roll.type);
	destination[dest].roll.admitYear=source[src].roll.admitYear;
	strcpy(destination[dest].roll.branch,source[src].roll.branch);
	destination[dest].roll.num=source[src].roll.num;
	strcpy(destination[dest].name,source[src].name);

	int k=0;
	while(k<SEM_NUM)
	{
		destination[dest].sgpa[k]=source[src].sgpa[k];
		destination[dest].credits[k]=source[src].credits[k];
		
		k++;
	}
	destination[dest].cgpa=source[src].cgpa;
	return;

}
void MergeSelfCGPA(StudentRec *database,int low,int upto,int high,StudentRec *temp)
{
	
	int i=low;
	int j=upto+1;
	int k=0;
	while(i<=upto&&j<=high)
	{
		if(database[i].cgpa<database[j].cgpa)
		{
			transfer(temp,database,k,j);
			j++;
			k++;
		}
		else
		{
			transfer(temp,database,k,i);
			i++;
			k++;
		}
	}
	while(i<=upto)
	{
		transfer(temp,database,k,i);
		i++;
		k++;
	}
	while(j<=high)
	{
		transfer(temp,database,k,j);
		j++;
		k++;
	}
	
	for(k=k-1;k>=0;k--)
	{
		transfer(database,temp,low+k,k);
	}
	return;
}
void Sort_On_CGPA(StudentRec *database,int low,int high,StudentRec *temp)
{
	int mid;
	if(low<high)
	{
		mid=(low+high)/2;
		Sort_On_CGPA(database,low,mid,temp);
		Sort_On_CGPA(database,mid+1,high,temp);
		MergeSelfCGPA(database,low,mid,high,temp);
	}
	return;
}
void display(StudentRec *database,int low,int high)
{
	int i,k;
	printf("SR.NO.\tENROLL\t\tNAME\t\t\t\t\t\t\tSGPA(s) and CREDIT(s)\t\tCGPA\n");
	for(i=low;i<=high;i++)
	{
			printf("%d\t",i+1);
			printf("%2s",database[i].roll.type);
			printf("%d",database[i].roll.admitYear);
			printf("%3s",database[i].roll.branch);
			printf("%3d\t",database[i].roll.num);
			printf("%-50s\t",database[i].name);
							
			k=0;
			while(k<SEM_NUM&&database[i].sgpa[k]!=-1)
			{
				printf("%0.2f ",database[i].sgpa[k]);
				printf("%d ",database[i].credits[k]);
				k++;
			}
			printf("\t%.2f",database[i].cgpa);
			printf("\n");
	}
	return;

}
FILE * OpenFile(int mode,int dept)
{
	FILE *FilePointer;
	FilePointer=NULL;
	switch(mode)
	{
		case WRITE:
		//assume ADMISSION YEAR 2016(CAN TAKE INPUT BUT THE PROJECT WOULD BECOME TOO LENGTHY SO LET THE ADMISSION YEAR BE 2016)
			switch(dept)
			{
				case CSE:
						FilePointer=fopen("CSE1620_RESULT.txt","w");
						printf("\tCOMPUTER SCIENCE AND ENGINEERING DEPARTMENT");
						break;
				case ECE:
						FilePointer=fopen("ECE1620_RESULT.txt","w");
						printf("\tELECTRONICS AND COMMUNICATION ENGINEERING DEPARTMENT");
						break;
				case MEC:
						FilePointer=fopen("MEC1620_RESULT.txt","w");
						printf("\tMECHANICAL ENGINEERING DEPARTMENT");
						break;
				case EEE:
						FilePointer=fopen("EEE1620_RESULT.txt","w");
						printf("\tELECTRICAL AND ELECTRONICS ENGINEERING DEPARTMENT");
						break;
				case CIV:
						FilePointer=fopen("CIV1620_RESULT.txt","w");
						printf("\tCIVIL ENGINEERING DEPARTMENT");
						break;
				case CME:
						FilePointer=fopen("CME1620_RESULT.txt","w");
						printf("\tCHEMICAL ENGINEERING DEPARTMENT");
						break;
				case MET:
						FilePointer=fopen("MET1620_RESULT.txt","w");
						printf("\tMETALLURY AND MATERIAL SCIENCE ENGINEERING DEPARTMENT");
						break;
				case MIN:
						FilePointer=fopen("MIN1620_RESULT.txt","w");
						printf("\tMINING ENGINEERING DEPARTMENT");
						break;
				case ARC:
						FilePointer=fopen("ARC1620_RESULT.txt","w");
						printf("\tARCHITECTURE DEPARTMENT");
						break;


			}
			
			break;
		case APPEND:
			switch(dept)
			{
				case CSE:
						FilePointer=fopen("CSE1620_RESULT.txt","a");
						printf("\tCOMPUTER SCIENCE AND ENGINEERING DEPARTMENT");
						break;
				case ECE:
						FilePointer=fopen("ECE1620_RESULT.txt","a");
						printf("\tELECTRONICS AND COMMUNICATION ENGINEERING DEPARTMENT");
						break;
				case MEC:
						FilePointer=fopen("MEC1620_RESULT.txt","a");
						printf("\tMECHANICAL ENGINEERING DEPARTMENT");
						break;
				case EEE:
						FilePointer=fopen("EEE1620_RESULT.txt","a");
						printf("\tELECTRICAL AND ELECTRONICS ENGINEERING DEPARTMENT");
						break;
				case CIV:
						FilePointer=fopen("CIV1620_RESULT.txt","a");
						printf("\tCIVIL ENGINEERING DEPARTMENT");
						break;
				case CME:
						FilePointer=fopen("CME1620_RESULT.txt","a");
						printf("\tCHEMICAL ENGINEERING DEPARTMENT");
						break;
				case MET:
						FilePointer=fopen("MET1620_RESULT.txt","a");
						printf("\tMETALLURY AND MATERIAL SCIENCE ENGINEERING DEPARTMENT");
						break;
				case MIN:
						FilePointer=fopen("MIN1620_RESULT.txt","a");
						printf("\tMINING ENGINEERING DEPARTMENT");
						break;
				case ARC:
						FilePointer=fopen("ARC1620_RESULT.txt","a");
						printf("\tARCHITECTURE DEPARTMENT");
						break;


			}
			
			break;
		case READ:
			switch(dept)
			{
				case CSE:
						FilePointer=fopen("CSE1620_RESULT.txt","r");
						break;
				case ECE:
						FilePointer=fopen("ECE1620_RESULT.txt","r");
						break;
				case MEC:
						FilePointer=fopen("MEC1620_RESULT.txt","r");
						break;
				case EEE:
						FilePointer=fopen("EEE1620_RESULT.txt","r");
						break;
				case CIV:
						FilePointer=fopen("CIV1620_RESULT.txt","r");
						break;
				case CME:
						FilePointer=fopen("CME1620_RESULT.txt","r");
						break;
				case MET:
						FilePointer=fopen("MET1620_RESULT.txt","r");
						break;
				case MIN:
						FilePointer=fopen("MIN1620_RESULT.txt","r");
						break;
				case ARC:
						FilePointer=fopen("ARC1620_RESULT.txt","r");
						break;


			}
			

	}
	printf("\n");
	return FilePointer;
}
void SortCalcForSem(int *calcForSem,int low,int high)
{
	//small array so no issues with any sorting
	int i,j,sorted=0,temp;
	for(i=low;i<(high)&&!sorted;i++)
	{
		sorted=1;
		for(j=low;j<(high-i);j++)
		{
			if(calcForSem[j]>calcForSem[j+1]&&calcForSem[j+1]!=INVALID_INDEX)
			{
				sorted=0;
				temp=calcForSem[j];
				calcForSem[j]=calcForSem[j+1];
				calcForSem[j+1]=temp;
			}
		}
	}
}
void CalcCGPA(StudentRec *database,int low,int high,int *calcForSem)
{
	int i,k,j=0,creditsAcc;
	for(i=low;i<=high;i++)
	{
		k=0;
		j=0;
		creditsAcc=0;
		database[i].cgpa=0.0;//CRUCIAL
		while(k<SEM_NUM&&database[i].sgpa[k]!=-1)
		{
			if((calcForSem[j]-1)==k)
			{
				creditsAcc+=database[i].credits[k];
				database[i].cgpa+=(database[i].sgpa[k]*database[i].credits[k]);
				j++;
			}
			k++;
		}
		if(creditsAcc!=0)
			database[i].cgpa=database[i].cgpa/creditsAcc;

	}
	return;
}
int UseFileMenu(void)
{
	int chosen;
	printf("\t\tUSE EXISTING FILE-MENU\n1]DISPLAY THE RESULT\n2]SORT ON ENROLLMENT NUMBER\n3]SORT ON SGPA(s)\n4]SORT ON CGPA\n5]UPDATE/DELETE RECORD(s)\nPLEASE ENTER CHOICE FROM 1 TO 5\t");
	scanf("%d",&chosen);
	while(chosen<1&&chosen>5)
	{
		printf("CHOICE RANGE:1 TO 5\nENTER CHOICE FROM 1 TO 5\t");
		scanf("%d",&chosen);
	}
	return chosen;
}
void Sort_On_Enroll(StudentRec *database,int low,int high)
{
	StudentRec temp;
	int i,j,sorted=0,k;
	for(i=low;i<(high)&&!sorted;i++)
	{
		sorted=1;
		for(j=low;(j<(high-i));j++)
		{
			if(database[j].roll.num>database[j+1].roll.num)
			{
				sorted=0;
				strcpy(temp.roll.type,database[j].roll.type);
				temp.roll.admitYear=database[j].roll.admitYear;
				strcpy(temp.roll.branch,database[j].roll.branch);
				temp.roll.num=database[j].roll.num;
				strcpy(temp.name,database[j].name);

				k=0;
				while(k<SEM_NUM)
				{
					temp.sgpa[k]=database[j].sgpa[k];
					temp.credits[k]=database[j].credits[k];
		
					k++;
				}
				temp.cgpa=database[j].cgpa;
	
				strcpy(database[j].roll.type,database[j+1].roll.type);
				database[j].roll.admitYear=database[j+1].roll.admitYear;
				strcpy(database[j].roll.branch,database[j+1].roll.branch);
				database[j].roll.num=database[j+1].roll.num;
				strcpy(database[j].name,database[j+1].name);

				k=0;
				while(k<SEM_NUM)
				{
					database[j].sgpa[k]=database[j+1].sgpa[k];
					database[j].credits[k]=database[j+1].credits[k];
		
					k++;
				}
				database[j].cgpa=database[j+1].cgpa;
				
				strcpy(database[j+1].roll.type,temp.roll.type);
				database[j+1].roll.admitYear=temp.roll.admitYear;
				strcpy(database[j+1].roll.branch,temp.roll.branch);
				database[j+1].roll.num=temp.roll.num;
				strcpy(database[j+1].name,temp.name);

				k=0;
				while(k<SEM_NUM)
				{
					database[j+1].sgpa[k]=temp.sgpa[k];
					database[j+1].credits[k]=temp.credits[k];
		
					k++;
				}
				database[j+1].cgpa=temp.cgpa;

			}
		}
	}
}
int updateMenu(void)
{
	int choice;
	printf("\t\tUPDATE-MENU\n1]EDIT THE CHOSEN RECORD\n2]DELETE THE CHOSEN RECORD\nPLEASE SPECIFY CHOICE FROM 1-2\t");
	scanf("%d",&choice);
	while(choice<1||choice>2)
	{
		printf("PLEASE SPECIFY CHOICE FROM 1-2\t");
		scanf("%d",&choice);
	}
	return choice;
}


