#ifndef RECORDS_FUNC_H
#define RECORDS_FUNC_H
#define BRANCH_LEN 4
#define NAME_LEN 100
#define SEM_NUM 8
#define TYPE_LEN 3
typedef enum{FAILURE,SUCCESS} status;
typedef enum{false,true} boolean;
typedef struct 
{
	char type[TYPE_LEN];
	int admitYear;
	char branch[BRANCH_LEN];
	int num;					
	/*EnrollNum::::BT16CSE045   TYPE BT(BA means architecture) admitYear 16(SHOULD BE TWO DIGIT )branch CSE num 045(SHOULD BE 3 DIGIT)*/
}EnrollNum;

typedef struct 
{
	char name[NAME_LEN];
	EnrollNum roll;
	int credits[SEM_NUM];
	float sgpa[SEM_NUM];
	float cgpa;
}StudentRec;

int ChooseDept(void);
int StartMenu(void);
void Initialize(StudentRec *database,int low,int high);
void transfer(StudentRec *destination,StudentRec *source,int dest,int src);
void MergeSelfCGPA(StudentRec *database,int low,int upto,int high,StudentRec *temp);
void Sort_On_CGPA(StudentRec *database,int low,int high,StudentRec *temp);
void display(StudentRec *database,int low,int high);
FILE * OpenFile(int mode,int dept);
void SortCalcForSem(int *calcForSem,int low,int high);
void CalcCGPA(StudentRec *database,int low,int high,int *calcForSem);
void MergeSelfEnroll(StudentRec *database,int low,int upto,int high,StudentRec *temp);
void Sort_On_Enroll(StudentRec *database,int low,int high);
int UseFileMenu(void);
int updateMenu(void);
#endif

