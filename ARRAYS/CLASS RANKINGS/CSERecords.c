#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
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
#define DATABASE_FAIL -1
#define AGAIN 4
#define ENTER_ALL 1
#define ENTER_FEW 2
#define USE_FILE 3
#define DISPLAY 1
#define SORT_ON_ENROLL 2
#define SORT_ON_SGPA 3
#define SORT_ON_CGPA 4
#define UPDATE 5
#define WRITE 1
#define APPEND 2
#define READ 3
#define CORRECTION 15
#define IDENTIFIER_LEN 2 
#define EDIT 1
#define DELETE 2
#define EDIT_ENROLL 1
#define EDIT_NAME 2
#define EDIT_SGPA 3
#define EDIT_CREDITS 4
//DRIVER CODE BEGINS--->>
int main()
{
	printf("\t\tVNIT,NAGPUR\n\tCOMPUTER SCIENCE AND ENGINEERING DEPATMENT\nPROJECT(DISPLAY RESULTS(BASIC VERSION)) DONE BY:ABDUL SATTAR MAPARA\n\nGUIDED AND MOTIVATED BY:R.B.KESKAR SIR\t\tTHANK YOU FOR USING OUR PROGRAM.\nFEATURES:\n*PROJECT FOR EASE OF VIEWING RESULTS\n*USES FILE HANDLING\n*ENABLES ADDING/UPDATING/DELETING RECORD(s) IN A PARTICULAR FORMAT IN THE FILE\n*ENABLES SORTING BASED ON DIFFERENT PARAMETERS THEREBY SAVING THE TEDIOUS CALCULATIONS AND SAVING THE PURPOSE\n--------------------------INSTRUCTIONS TO USER(s)-----------------------------\n*TRY NOT TO ENTER INCORRECT ENTRIES AS THIS IS A BASIC VERSION\n*INVALID ENTRY FOR A SEMESTER IS -1 AND INVALID ENTRY FOR CREDITS OF A SEMESTER IS 0(NEEDED TO STOP PROGRAM FROM TAKING EXTRA INPUTS(eg:if a Student is studying in SEMESTER 3(<8) there is no point in asking grade point for SEMESTER 4-8)\n*NAME FIELDS ARE SEPARTED BY UNDERSCORE(_) IN THE FORMAT USED FOR SIMPLICITY OF THE PROGRAM.KINDLY CO-OPERATE.\n*WHEN YOU OPT FOR RUNNING THE PROGRAM FOR ONLY SOME SEMESTER(s) THE CGPA DISPLAYED AT THAT TIME IS BY CONSIDERING ONLY THE SEMESTER(s) OPTED AT THAT TIME\n*KINDLY GIVE YOUR SUGGESTIONS ABOUT THE PROGRAM AND REPORT ANY BUG(s) IN THE PROGRAM BY CONTACTING AT:\ne-mail:abdulsmapara@gmail.com\n\n\n");
	/*START OF DECLARATIONS*/
	int choice,dept,numStudents,i,j,invalid,k,creditsAcc=0,menuChoice,fileChoice,mode,countNum,calcForSem[SEM_NUM],chosen,fewNum,found,updateChoice,editChoice,some_iterator;
	StudentRec *database,*temp,*SortOnEnroll,*SortOnCGPA,*SortOnSGPA;
	StudentRec inputFileRec;
	char ch;
	char again[AGAIN],editAgain[AGAIN];
	char againMenu[AGAIN];
	FILE *fp;
	char checkNum[CORRECTION];
	char identifier[IDENTIFIER_LEN];
	/*END OF DECLARATIONS*/
	for(i=0;i<SEM_NUM;i++)
	{
		calcForSem[i]=i+1;
	}
	dept=ChooseDept();
	numStudents=-1;
	strcpy(identifier,"A");

		do
		{

			menuChoice=StartMenu();
			switch(menuChoice)
			{
				case ENTER_ALL://open file in write mode
								printf("CAUTION:ANY DATA IF ALREADY PRESENT IN THE FILE WILL BE LOST\n");
								printf("NUMBER OF STUDENTS IN THE DEPARTMENT:\t");
								scanf("%d",&numStudents);
								mode=WRITE;
								fp=OpenFile(mode,dept);
								if(fp==NULL)
								{
									printf("ERROR\n");
								}
								else
								{
									
									for(i=0;i<numStudents;i++)
									{
										//INITIALIZE INPUT FILE REC
										inputFileRec.roll.type[0]='\0';
										inputFileRec.roll.admitYear=0;
										inputFileRec.roll.branch[0]='\0';
										inputFileRec.roll.num=0;
										inputFileRec.name[0]='\0';
										for(k=0;k<SEM_NUM;k++)
										{
											inputFileRec.sgpa[k]=-1;
											inputFileRec.credits[k]=0;

										}
										printf("\nREQUIRED FORMAT(EXAMPLE):\nBT[SPACE]16[SPACE]CSE[SPACE]029[SPACE]STUD_NAME[SPACE]SGPA1[SPACE]CREDITS1 and so on to SGPA8[SPACE]CREDITS8\n");
										printf("ENTER ROLL NUMBER IN SPECIFIED FORMAT\nADMISSION TYPE:\t");
										scanf("%s",inputFileRec.roll.type);
										printf("ADMISSION YEAR(2-DIGIT EG.16)\t");
										scanf("%d",&inputFileRec.roll.admitYear);
										printf("BRANCH ABBRV.\t");
										scanf("%s",inputFileRec.roll.branch);

										printf("ROLL NUMBER\t");
										scanf("%d",&inputFileRec.roll.num);
										while(inputFileRec.roll.num<1||inputFileRec.roll.num>numStudents)
										{
											printf("INVALID ROLL NUMBER\n");
											printf("ROLL NUMBER\t");
											scanf("%d",&inputFileRec.roll.num);
										}
										printf("NAME:\t");
										scanf("%s",inputFileRec.name);
										k=0;
										do
										{

											
											printf("SEM %d:\nSGPA:\t",k+1);
											scanf("%f",&inputFileRec.sgpa[k]);
											printf("CREDITS:\t");
											scanf("%d",&inputFileRec.credits[k]);
											k++;
										}while(k<SEM_NUM&&inputFileRec.sgpa[k-1]!=-1);
										
										//print to file
										fprintf(fp,"%c ",identifier[0]);
										fprintf(fp,"%s ",inputFileRec.roll.type);
										fprintf(fp,"%d ",inputFileRec.roll.admitYear);
										fprintf(fp,"%s ",inputFileRec.roll.branch);
										fprintf(fp,"%d ",inputFileRec.roll.num);
										fprintf(fp,"%s ",inputFileRec.name);
										k=0;
										while(k<SEM_NUM)
										{
											
											fprintf(fp, "%.2f ",inputFileRec.sgpa[k]);
											fprintf(fp,"%d",inputFileRec.credits[k]);
											if(k!=SEM_NUM-1)
											{
												fprintf(fp," ");
											}
											k++;
										}
										if(i!=(numStudents-1))
											fprintf(fp,"\n");
									}
									fclose(fp);
									fp=NULL;
									printf("RECORD(s) SAVED SUCCESSFULLY\n");
								}

								break;
				case ENTER_FEW://open file in append mode
								mode=APPEND;
								fp=OpenFile(mode,dept);
								if(fp==NULL)
								{
									printf("ERROR\n");
								}
								else
								{
									scanf("ENTER THE NUMBER OF STUDENTS WHOSE RECORDS YOU WANT TO ENTER\n");
									scanf("%d",&fewNum);
									for(i=0;i<fewNum;i++)
									{
										inputFileRec.roll.type[0]='\0';
										inputFileRec.roll.admitYear=0;
										inputFileRec.roll.branch[0]='\0';
										inputFileRec.roll.num=0;
										inputFileRec.name[0]='\0';
										for(k=0;k<SEM_NUM;k++)
										{
											inputFileRec.sgpa[k]=-1;
											inputFileRec.credits[k]=0;

										}
										printf("\nREQUIRED FORMAT(EXAMPLE):\nBT[SPACE]16[SPACE]CSE[SPACE]029[SPACE]STUD_NAME[SPACE]SGPA1[SPACE]CREDITS1 and so on to SGPA8[SPACE]CREDITS8\n");
										printf("ENTER ROLL NUMBER IN SPECIFIED FORMAT\nADMISSION TYPE:\t");
										scanf("%s",inputFileRec.roll.type);
										printf("ADMISSION YEAR(2-DIGIT EG.16)\t");
										scanf("%d",&inputFileRec.roll.admitYear);
										printf("BRANCH ABBRV.\t");
										scanf("%s",inputFileRec.roll.branch);

										printf("ROLL NUMBER\t");
										scanf("%d",&inputFileRec.roll.num);
										while(inputFileRec.roll.num<1||inputFileRec.roll.num>numStudents+fewNum)
										{
											printf("INVALID ROLL NUMBER\n");
											printf("ROLL NUMBER\t");
											scanf("%d",&inputFileRec.roll.num);
										}
										printf("NAME:\t");
										scanf("%s",inputFileRec.name);
										k=0;
										do
										{

											
											printf("SEM %d:\nSGPA:\t",k+1);
											scanf("%f",&inputFileRec.sgpa[k]);
											printf("CREDITS:\t");
											scanf("%d",&inputFileRec.credits[k]);
											k++;
										}while(k<SEM_NUM&&inputFileRec.sgpa[k-1]!=-1);
										
										//print to file
										fprintf(fp,"\n%c ",identifier[0]);
										fprintf(fp,"%s ",inputFileRec.roll.type);
										fprintf(fp,"%d ",inputFileRec.roll.admitYear);
										fprintf(fp,"%s ",inputFileRec.roll.branch);
										fprintf(fp,"%d ",inputFileRec.roll.num);
										fprintf(fp,"%s ",inputFileRec.name);
										k=0;
										while(k<SEM_NUM)
										{
											
											fprintf(fp, "%.2f ",inputFileRec.sgpa[k]);
											fprintf(fp,"%d",inputFileRec.credits[k]);
											if(k!=SEM_NUM-1)
											{
												fprintf(fp," ");
											}
											k++;
										}
										numStudents++;
									}
									fclose(fp);
									fp=NULL;
									printf("RECORDS SAVED SUCCESSFULLY\n");
								}
								break;
				case USE_FILE://open file in read mode
								mode=READ;
								fp=OpenFile(mode,dept);
								if(fp==NULL)
								{
									printf("ERROR\n");
								}
								else
								{
									do
									{
										invalid=0;
										
										if(numStudents==-1)
										{
											printf("NUMBER OF STUDENTS IN THE DEPARTMENT:\t");
											scanf("%d",&numStudents);
										}
										
											database=(StudentRec *)malloc((sizeof(StudentRec))*numStudents);
											printf("PLEASE CHECK THE NUMBER OF STUDENTS:%4d\nIF INCORRECT ENTER CORRECT(to correct it) ELSE ENTER ANY OTHER STRING\n",numStudents);
											scanf("%s",checkNum);
											if(!strcmp(checkNum,"CORRECT")||!strcmp(checkNum,"correct"))
											{
												printf("ENTER THE NUMBER OF STUDENTS:\t");
												scanf("%d",&numStudents);
												if(database!=NULL)
													free(database);
												database=NULL;
													
												database=(StudentRec *)malloc((sizeof(StudentRec))*numStudents);
											
											}
											
											if(database==NULL)
											{
												printf("ERROR IN CREATING DATABASE.SORRY!PLEASE RETRY\n");
											}
											else
											{
												Initialize(database,0,numStudents-1);
												//brk=feof(fp);//returns non-zero at eof
												
												for(countNum=0;(ch=fgetc(fp))!=EOF&&countNum<numStudents;countNum++)
												{
													//A PROBLEM HERE -----!!!DOUBT!!!-----

														if(ch!='A')
														{
															countNum--;
																

														}
														else
														{
															//printf("CHAR%c\n",ch);
															fscanf(fp,"%s",database[countNum].roll.type);
															fscanf(fp,"%d",&database[countNum].roll.admitYear);
															fscanf(fp,"%s",database[countNum].roll.branch);
															fscanf(fp,"%d",&database[countNum].roll.num);
															fscanf(fp,"%s",database[countNum].name);
															k=0;
															do
															{
																fscanf(fp,"%f",&database[countNum].sgpa[k]);
																fscanf(fp,"%d",&database[countNum].credits[k]);
																k++;
															}while(k<SEM_NUM);
															

															
															//TEST---
															//printf("%s %d %s %d %s ",database[countNum].roll.type,database[			countNum].roll.admitYear,database[countNum].roll.branch,database[countNum].roll.num,database[countNum].name);
															//---TEST
															/*
																char name[NAME_LEN];
																EnrollNum roll;
																int credits[SEM_NUM];
																	float sgpa[SEM_NUM];
																float cgpa;*/
															
															//printf("%s\n%s\n",database[i].roll.type,database[i].name);
															//printf("COUNT NUM %d\n",countNum);
		
														}
													
														
																													
												}
												

												if(countNum!=numStudents||ch!=EOF)
												{
													invalid=1;
													if(ch!=EOF)
													{
														printf("\nSOMETHING WENT WRONG.\nNUMBER OF STUDENTS ARE MORE THAN WHAT YOU ENTERED\n");
													}
													else
													{
														printf("\nSOMETHING WENT WRONG.\nEXPECTED NUMBER OF STUDENTS:%d\n",countNum);
													}
													fclose(fp);
													fp=NULL;
													fp=OpenFile(mode,dept);
													if(fp==NULL)
													{
														invalid=0;

														printf("ERROR IN OPENING FILE.\n");
													}	

												}	
												else
												{
													invalid=0;
					
												}
											}
										}while(invalid);
									
									if(fp!=NULL&&database!=NULL)
									{
										fclose(fp);
										fp=NULL;
									
										//store cgpa here
										for(some_iterator=0;some_iterator<SEM_NUM;some_iterator++)
										{
											calcForSem[some_iterator]=some_iterator+1;
										}
										CalcCGPA(database,0,numStudents-1,calcForSem);
										//options(MENU)LIKE SORT ON CGPA HERE...
										chosen=UseFileMenu();
										switch(chosen)
										{
											case DISPLAY:
															display(database,0,numStudents-1);
															break;
											case SORT_ON_ENROLL:
															SortOnEnroll=(StudentRec *)malloc(sizeof(StudentRec)*numStudents);
															if(SortOnEnroll==NULL)
															{
																printf("ERROR\n");
															}
															else
															{
																Initialize(SortOnEnroll,0,numStudents-1);
																for(i=0;i<=numStudents-1;i++)
																{
																	transfer(SortOnEnroll,database,i,i);
																}
																Sort_On_Enroll(SortOnEnroll,0,numStudents-1);
																printf("SORTED ON ENROLLMENT NUMBER\n");
																display(SortOnEnroll,0,numStudents-1);
																free(SortOnEnroll);
																SortOnEnroll=NULL;
																
															}
															break;
											case SORT_ON_SGPA:
															SortOnSGPA=(StudentRec *)malloc(sizeof(StudentRec)*numStudents);
															temp=(StudentRec *)malloc(sizeof(StudentRec)*numStudents);
															if(SortOnSGPA==NULL||temp==NULL)
															{
																printf("ERROR\n");
															}
															else
															{
																Initialize(SortOnSGPA,0,numStudents-1);
																Initialize(temp,0,numStudents-1);
																printf("ENTER SEMESTER NUMBER(s) .IF DONE ENTER AN INVALID SEMESTER NUMBER\n");
																k=0;
																do
																{
																	
																	scanf("%d",&calcForSem[k]);
																	k++;
																}while(k<SEM_NUM&&calcForSem[k-1]<=SEM_NUM&&calcForSem[k-1]>0);
																k-=1;
																while(k<SEM_NUM)
																{
																	calcForSem[k]=-1;
																	k++;
																}
																SortCalcForSem(calcForSem,0,k-1);
																for(i=0;i<numStudents;i++)
																{
																	transfer(SortOnSGPA,database,i,i);
																}
																CalcCGPA(SortOnSGPA,0,numStudents-1,calcForSem);
																Sort_On_CGPA(SortOnSGPA,0,numStudents-1,temp);
																printf("SORTED(RANKWISE) ON SGPA OF SEMESTERS FEEDED IN THE PROGRAM\n");
																display(SortOnSGPA,0,numStudents-1);
																free(SortOnSGPA);
																SortOnSGPA=NULL;
																free(temp);
																temp=NULL;

															}
															break;
											case SORT_ON_CGPA:
															for(i=0;i<SEM_NUM;i++)
															{
																calcForSem[i]=i+1;
															}
															SortOnCGPA=(StudentRec *)malloc(sizeof(StudentRec)*numStudents);
															temp=(StudentRec *)malloc(sizeof(StudentRec)*numStudents);
															if(SortOnCGPA==NULL||temp==NULL)
															{
																printf("ERROR\n");
															}
															else
															{
																Initialize(SortOnCGPA,0,numStudents-1);
																Initialize(temp,0,numStudents-1);
																for(i=0;i<numStudents;i++)
																{
																	transfer(SortOnCGPA,database,i,i);
																}
																Sort_On_CGPA(SortOnCGPA,0,numStudents-1,temp);
																printf("\t\tSORTED RANK WISE(ON CGPA)\n");
																display(SortOnCGPA,0,numStudents-1);
																free(SortOnCGPA);
																SortOnCGPA=NULL;
																free(temp);
																temp=NULL;
															}
															break;

											case UPDATE:
															inputFileRec.roll.type[0]='\0';
															inputFileRec.roll.admitYear=0;
															inputFileRec.roll.branch[0]='\0';
															inputFileRec.roll.num=0;
															inputFileRec.name[0]='\0';
															printf("ENTER ENROLLMENT NUMBER WHOSE ENTRY NEEDS TO BE UPDATED\nADMISSION TYPE:\t");

															scanf("%s",inputFileRec.roll.type);
															printf("ADMISSION YEAR:\t");
															scanf("%d",&inputFileRec.roll.admitYear);
															printf("BRANCH ABBRV.\t");
															scanf("%s",inputFileRec.roll.branch);
															printf("ROLL NUMBER:\t");
															scanf("%d",&inputFileRec.roll.num);
															found=0;
															for(i=0;i<numStudents&&!found;)
															{
																if(!(strcmp(database[i].roll.type,inputFileRec.roll.type))&&(database[i].roll.admitYear==inputFileRec.roll.admitYear)&&(!strcmp(database[i].roll.branch,inputFileRec.roll.branch))&&(database[i].roll.num==inputFileRec.roll.num))
																{
																	found=1;
																}
																else
																{
																	i++;
																}
															}
															if(found)
															{
																updateChoice=updateMenu();
																switch(updateChoice)
																{
																	case EDIT:
																			do
																			{
																				printf("\t\tMENU-EDIT\n1]EDIT ENROLLMENT NUMBER\n2]EDIT NAME\n3]EDIT SGPA OF A PARTICULAR SEMESTER\n4]EDIT CREDITS FOR A PARTICULAR SEMESTER\nCHOICE FROM 1-4\t");
																				scanf("%d",&editChoice);
																				while(editChoice>4||editChoice<1)
																				{
																					printf("CHOICE FROM 1-4\t");
																					scanf("%d",&editChoice);
																				}
																				
																				switch(editChoice)
																				{
																					case EDIT_ENROLL:
																									printf("ENTER THE CORRECT ENROLLMENT NUMBER\nADMISSION TYPE:\t");
																									scanf("%s",database[i].roll.type);
																									printf("ADMISSION YEAR:\t");
																									scanf("%d",&database[i].roll.admitYear);
																									printf("BRANCH ABBRV.\t");
																									scanf("%s",database[i].roll.branch);
																									printf("ENROLLMENT NUMBER\n");
																									scanf("%d",&database[i].roll.num);

																									break;
																					case EDIT_NAME:
																									printf("ENTER CORRECTED NAME:\t");
																									scanf("%s",database[i].name);
																									break;
																					case EDIT_SGPA:
																									k=0;
																									printf("ENTER SEMESTER NUMBERS WHOSE SGPA(s) are to be edited\nENTER -1 TO STOP\n");

																									do
																									{
																										scanf("%d",&calcForSem[k]);
																										k++;
																									}while(k<SEM_NUM&&calcForSem[k-1]<=SEM_NUM&&calcForSem[k-1]>0);
																									k-=1;
																									while(k<SEM_NUM)
																									{
																										calcForSem[k]=-1;
																										k++;
																									}
																									SortCalcForSem(calcForSem,0,k-1);
																									k=0;
																									j=0;
																									do
																									{
																										if(calcForSem[j]-1==k)
																										{
																											printf("ENTER CORRECTED SGPA OF SEMESTER %d:\t",k+1);
																											scanf("%f",&database[i].sgpa[k]);
																											j++;
																										}
																										k++;
																									}while(k<SEM_NUM&&calcForSem[j]>0&&calcForSem[j]<=SEM_NUM&&database[i].sgpa[k-1]!=-1);
																									if(database[i].sgpa[k-1]==-1)
																									{
																										printf("STUDENT RECORD SAYS THAT SGPA OF SEMESTER %d IS INVALID.SO THE DATABASE DOES NOT ALLOW CORRECTING/ADDING SGPA OF NEXT SEMESTER\n",k);
																									}
																									break;
																					case EDIT_CREDITS:
																									k=0;
																									printf("ENTER SEMESTER NUMBERS WHOSE CREDIT(s) are to be edited\nENTER -1 TO STOP\n");

																									do
																									{
																										scanf("%d",&calcForSem[k]);
																										k++;
																									}while(k<SEM_NUM&&calcForSem[k-1]<=SEM_NUM&&calcForSem[k-1]>0);
																									k-=1;
																									while(k<SEM_NUM)
																									{
																										calcForSem[k]=-1;
																										k++;
																									}
																									SortCalcForSem(calcForSem,0,k-1);
																									k=0;
																									j=0;
																									do
																									{
																										if(calcForSem[j]-1==k)
																										{
																											printf("ENTER CORRECTED CREDITS FOR SEMESTER%d:\t",k+1);
																											scanf("%d",&database[i].credits[k]);
																											j++;
																										}
																										k++;
																									}while(k<SEM_NUM&&calcForSem[j]>0&&calcForSem[j]<=SEM_NUM&&database[i].credits[k-1]!=0);
																									if(database[i].sgpa[k-1]==-1)
																									{
																										printf("STUDENT RECORD SAYS THAT CREDITS OF SEMESTER %d IS INVALID.SO THE DATABASE DOES NOT ALLOW CORRECTING/ADDING CREDITS OF NEXT SEMESTER\n",k);
																									}
																									
																									break;

																				}
																				printf("WANT TO EDIT THE SAME RECORD AGAIN---YES/NO\t");
																				scanf("%s",editAgain);
																			}while(!strcmp(editAgain,"YES"));
																			break;
																	case DELETE:
																			printf("DELETING THE RECORD.\n");
																			Initialize(database,i,i);
																			printf("SELECTED RECORD DELETED SUCCESSFULLY\n");
																			//SHIFT RECORDS TO LEFT
																			for(j=i+1;j<numStudents;j++)
																			{
																				transfer(database,database,j-1,j);
																			}
																			Initialize(database,j-1,j-1);
																			numStudents-=1;
																			break;
																}
																mode=WRITE;
																fp=OpenFile(mode,dept);
																if(fp!=NULL)
																{
																	strcpy(identifier,"A");
																	for(i=0;i<numStudents;i++)
																	{
																		fprintf(fp,"%c ",identifier[0]);
																		fprintf(fp,"%s ",database[i].roll.type);
																		fprintf(fp,"%d ",database[i].roll.admitYear);
																		fprintf(fp,"%s ",database[i].roll.branch);
																		fprintf(fp,"%d ",database[i].roll.num);
																		fprintf(fp,"%s ",database[i].name);
																		k=0;
																		while(k<SEM_NUM)
																		{
																			fprintf(fp,"%.2f ",database[i].sgpa[k]);
																			fprintf(fp,"%d",database[i].credits[k]);
																			if(k!=SEM_NUM-1)
																				fprintf(fp," ");
																			k++;
																		}
																		if(i!=numStudents-1)
																			fprintf(fp,"\n");
																	}
																	fclose(fp);
																	fp=NULL;
																}
																else
																{
																	printf("RECORDS COULD NOT BE UPDATED IN THE FILE\nERROR\n");
																}
															}
															else
															{
																printf("SORRY.THE REQUESTED RECORD COULD NOT BE FOUND\n");
															}
															break;
										}
										free(database);
										database=NULL;

									}
									

								}
								break;//break of SWITCH CASE
			}
							
									
			
			printf("WANT TO USE THE MENU AGAIN---YES ,ANY OTHER STRING FOR NO----YES/NO\t");
			scanf("%s",againMenu);
		}while((!strcmp(againMenu,"YES"))||(!strcmp(againMenu,"yes")));
		
	return 0;
}