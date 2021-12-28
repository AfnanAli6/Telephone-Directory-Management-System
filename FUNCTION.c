#include "HEADER.h"

void createFile()
{
	FILE* file;
	file = fopen("tel.txt", "a");
	fclose(file);
}

void menuList() /*This function will print out all the available features that comes with this program*/
{
	printf("\n--------------------------------------------\n");
	printf("    APU STAFF TELEPHONE DIRECTORY SYSTEM    \n");
	printf("--------------------------------------------\n");
	printf("(1) Add New Staff Record\n");
	printf("(2) Search Existing Staff Record\n");
	printf("(3) List and Sort Existing Staff Record\n");
	printf("(4) Update Existing Staff Extension Number\n");
	printf("(5) HELP\n");
	printf("(6) EXIT\n");
	menuSelector(); /*This line calls the "menuSelector" function to perform the instructions in it*/
}


void menuSelector() /*This function directs the user's choice by calling the preffered feature that the user wants to use*/
{
	int selectedFuntion = 0; /*A manipulative variable that is initialized to zero which able to store the value of menu choice to activate specific case*/
	printf("\nEnter Menu Choice Digit [1 to 6] : ");
	scanf("%d", &selectedFuntion);
	
	switch (selectedFuntion)
	{
	case 1:
		addNewRecord(); /*Calls the function to perform adding new employee record*/
		break;
	case 2:
		searchRecord(); /*Calls the function to perform searching existing employee record using staff name or ID as search key*/
		break;
	case 3:
		listRecord(); /*Calls the function to perform list and sort existing employee record by their department*/
		break;
	case 4:
		updateRecord(); /*Calls the function to perform searching existing employee record using their ID and update their extension number*/
		break;
	case 5:
		menuList(); /*Calls the function to print out all the available features that comes with this program*/
		break;
	case 6:
		printf("\nPROGRAM SUCCESSFULLY TERMINATED\n\n");
		exit(); /*Terminates the program successfully*/
	default:
		printf("WRONG INPUT, TRY AGAIN\n\n"); /*When wrong menu choice is entered, it indicates error and directs back to calling the list of menu options*/
		menuList();
		break;
	}
}


void addNewRecord()
{
	struct employee
	{
		char employeeName[30];
		char employeeID[6];
		char employeeExtension[5];
		char employeeDeparment[30];
	};
	struct employee e; /*Using a structure called employee to store staff particulars (name, ID number, telephone extension number and their department name)*/

	int flag, numberCheck; /*initialized 'flag' variable to control the looping control structure. 
						   initialized 'numberCheck' variable to iterate each character of employee's name and check if user wrongly entered a numeric value*/

	/*Using 'do...while' looping structure to collect employee name from user until correct inputs are given without error*/
	do
	{
		flag = 0;
		printf("New Staff Name : ");
		scanf("\n%[^\n]", &e.employeeName);

		e.employeeName[0] = toupper(e.employeeName[0]); /*Capitalizing the starting letter of the first name*/

		for (numberCheck = 0; numberCheck < strlen(e.employeeName); numberCheck++) /*Using 'for' looping structure to iterate the numberCheck counter
																				   in order to go through the string of name entered*/
		{
			if ((e.employeeName[numberCheck] >= '0') && (e.employeeName[numberCheck] <= '9')) /*Using 'if' conditional structure to check each character inputted 
																							  does not contain any numeric value and give error message when consist of number*/
			{
				printf("NUMERIC OR SYMBOLS DETECTED, PLEASE USE ALPHABET ONLY. TRY AGAIN.\n\n");
				break;
			}
			else if (e.employeeName[numberCheck] == ' ') /*To check for blank space in string as an indication of the begining of the employee's last name, 
														 so that the numberCheck variable can +1 character to capitalize the starting letter of last name*/

				e.employeeName[numberCheck + 1] = toupper(e.employeeName[numberCheck + 1]); /*Capitalizing the starting letter of the last name*/

			if ((numberCheck + 1) == strlen(e.employeeName))
			{
				flag = 1; /*Assigning flag value to 1 in order to exit the 'do...while' looping structure*/
			}
		}
	} while (flag == 0);

	do
	{
		flag = 0;
		printf("New Staff ID : ");
		scanf("%s", &e.employeeID);

		if ((strlen(e.employeeID) == 5) && ((e.employeeID[0] == 'i') || (e.employeeID[0] == 'I')) && ((e.employeeID[1] == 'd') || (e.employeeID[1] == 'D')) && ((e.employeeID[2] >= '0') && (e.employeeID[2] <= '9')) && ((e.employeeID[3] >= '0') && (e.employeeID[3] <= '9')) && ((e.employeeID[4] >= '0') && (e.employeeID[4] <= '9')))
		{
			e.employeeID[0] = toupper(e.employeeID[0]);
			e.employeeID[1] = toupper(e.employeeID[1]);
			flag = 1;
		}
		else
			printf("\nTRY AGAIN USING CORRECT FORMAT. Example : [IDxxx --> ID123]\n\n");
	} while (flag == 0);

	do
	{
		flag = 0;
		printf("New Staff Extension Number : ");
		scanf("%s", &e.employeeExtension);


		if ((strlen(e.employeeExtension) == 4) && ((e.employeeExtension[0] >= '0') && (e.employeeExtension[0] <= '9')) && ((e.employeeExtension[1] >= '0') && (e.employeeExtension[1] <= '9')) && ((e.employeeExtension[2] >= '0') && (e.employeeExtension[2] <= '9')) && ((e.employeeExtension[3] >= '0') && (e.employeeExtension[3] <= '9')))
		{
			flag = 1;
		}
		else
			printf("\nTRY AGAIN USING CORRECT FORMAT. 4 DIGITS ONLY. Example : [xxxx ---> 1234]\n\n");
	} while (flag == 0);

	do
	{
		flag = 0;
		printf("\nAvailable Departments : Academic , Accomodation, Finance , Library , Scheduling\n");
		printf("\nNew Staff Department [FILL IN THE PREFERRED DEPARTMENT NAME] : ");
		scanf("%s", &e.employeeDeparment);

		e.employeeDeparment[0] = toupper(e.employeeDeparment[0]);
		flag = 1;

	} while (flag == 0);

	printf("\nNAME\tID\tEXTENSION\tDEPARTMENT\n");
	printf("-------------------------------------------------\n");
	printf("%s\t%s\t%s\t%s\n", e.employeeName, e.employeeID, e.employeeExtension, e.employeeDeparment);
	printf("-------------------------------------------------");

	FILE* file;
	file = fopen("tel.txt", "r");
	struct employee list[50];

	int existingIdCheck = 0;
	flag = 0;

	while ((!feof(file)) && flag == 0)
	{
		fscanf(file,"%s\t%s\t%s\t%s\n", list[existingIdCheck].employeeName, list[existingIdCheck].employeeID, list[existingIdCheck].employeeExtension, list[existingIdCheck].employeeDeparment);
		if ( (strcmp(list[existingIdCheck].employeeID, e.employeeID) == 0) || (strcmp(list[existingIdCheck].employeeExtension, e.employeeExtension) == 0) )
		{
			printf("\n\nSIMILAR STAFF RECORD EXIST IN FILE :\n");
			printf("-------------------------------------------------\n");
			printf("%s\t%s\t%s\t%s\n", list[existingIdCheck].employeeName, list[existingIdCheck].employeeID, list[existingIdCheck].employeeExtension, list[existingIdCheck].employeeDeparment);
			printf("-------------------------------------------------\n");
			flag++;
		}
		else
			existingIdCheck++;
	}


	fclose(file);

	if (flag == 0)
	{
		file = fopen("tel.txt", "a");
		fprintf(file, "%s\t%s\t%s\t%s\n", e.employeeName, e.employeeID, e.employeeExtension, e.employeeDeparment);
		fclose(file);
		printf("\nNEW STAFF RECORD HAS BEEN ADDED INTO FILE \n");
	}
	menuSelector();
}


void searchRecord()
{
	struct employee
	{
		char employeeName[30];
		char employeeID[6];
		char employeeExtension[5];
		char employeeDeparment[30];
	};

	int i = 0, flag = 0;
	char searchKey[50];

	FILE* file;
	file = fopen("tel.txt", "r");
	struct employee list[50];

	printf("\nTo Search, Enter Staff Name or Staff ID : ");
	scanf("\n%[^\n]", searchKey);

	if ((strlen(searchKey) == 5) && ((searchKey[0] == 'i') || (searchKey[0] == 'I')) && ((searchKey[1] == 'd') || (searchKey[1] == 'D')) && ((searchKey[2] >= '0') && (searchKey[2] <= '9')))
	{
		searchKey[0] = toupper(searchKey[0]);
		searchKey[1] = toupper(searchKey[1]);
	}
	else
	{
		searchKey[0] = toupper(searchKey[0]);
		int capitalizerCounter = 0;
		for (capitalizerCounter = 0; capitalizerCounter < strlen(searchKey); capitalizerCounter++)
		{
			if (searchKey[capitalizerCounter] == ' ')
				searchKey[capitalizerCounter + 1] = toupper(searchKey[capitalizerCounter + 1]);
		}
	}

	while (!feof(file))
	{
		fscanf(file, "%[^\t]\t%s\t%s\t%[^\n]\n", &list[i].employeeName, &list[i].employeeID, &list[i].employeeExtension, &list[i].employeeDeparment);
		if (((strcmp(searchKey, list[i].employeeName)) == 0) || ((strcmp(searchKey, list[i].employeeID)) == 0))
		{
			printf("\nSEARCH RESULT OF STAFF RECORD :\n");
			printf("-------------------------------------------------\n");
			printf("NAME\t\tID\tEXTENSION\tDEPARTMENT\n");
			printf("-------------------------------------------------\n");
			printf("%s\t%s\t%s\t%s\n", list[i].employeeName, list[i].employeeID, list[i].employeeExtension, list[i].employeeDeparment);
			flag++;
			i++;
		}
	}

	if (flag == 0)
	{
		printf("\nSTAFF RECORD DOES NOT EXIST\n");
	}

	fclose(file);
	menuSelector();
}


void listRecord()
{
	struct employee
	{
		char employeeName[30];
		char employeeID[6];
		char employeeExtension[5];
		char employeeDeparment[30];
	};

	struct employee list[50];
	int i = 0;

	FILE* file;
	file = fopen("tel.txt", "r");

	while (!feof(file))
	{
		fscanf(file, "%[^\t]\t%s\t%s\t%[^\n]\n", &list[i].employeeName, &list[i].employeeID, &list[i].employeeExtension, &list[i].employeeDeparment);
		i++;
	}

	int records = i;
	int departmentTypes = 5, markerA = 0, markerB = 0;
	char departmentArray[5][30] = { "Academic", "Accomodation", "Finance", "Library", "Scheduling" };

	printf("\nLIST OF RECORDS SORTED BY DEPARTMENT :\n");
	printf("-------------------------------------------------\n");
	printf("NAME\t\tID\tEXTENSION\tDEPARTMENT\n");
	printf("-------------------------------------------------\n");

	for (int markerA = 0; markerA < departmentTypes; markerA++) // for it to go through each of the department in an alphabetical order
	{
		for (int markerB = 0; markerB < records; markerB++) // for it to loop throught each records of employee found
		{
			if (strstr(list[markerB].employeeDeparment, departmentArray[markerA]) != NULL) // perform printing those records with the matching name of the department
			{
				printf("%s\t%s\t%s\t%s\n", list[markerB].employeeName, list[markerB].employeeID, list[markerB].employeeExtension, list[markerB].employeeDeparment);
			}
		}
	}
	fclose(file);
	menuSelector();
}


void updateRecord()
{
	struct employee
	{
		char employeeName[30];
		char employeeID[6];
		char employeeExtension[5];
		char employeeDeparment[30];
	};
	struct employee list[50];

	int i = 0, flag = 0;
	char newEmployeeExtension[5];
	char searchKey[50];

	FILE* file;
	file = fopen("tel.txt", "r");

	printf("\nEnter Employee ID To Update Extension Number : ");
	scanf("\n%[^\n]", searchKey);

	if ((strlen(searchKey) == 5) && ((searchKey[0] == 'i') || (searchKey[0] == 'I')) && ((searchKey[1] == 'd') || (searchKey[1] == 'D')) && ((searchKey[2] >= '0') && (searchKey[2] <= '9')))
	{
		searchKey[0] = toupper(searchKey[0]);
		searchKey[1] = toupper(searchKey[1]);
	}

	while (!feof(file))
	{
		fscanf(file, "%[^\t]\t%s\t%s\t%[^\n]\n", &list[i].employeeName, &list[i].employeeID, &list[i].employeeExtension, &list[i].employeeDeparment);
		if ((strcmp(searchKey, list[i].employeeID)) == 0)
		{
			printf("\nSEARCH RESULT OF CURRENT EMPLOYEE RECORD :\n\n");

			printf("-------------------------------------------------\n");
			printf("NAME\t\tID\tEXTENSION\tDEPARTMENT\n");
			printf("-------------------------------------------------\n");
			printf("%s\t%s\t%s\t%s", list[i].employeeName, list[i].employeeID, list[i].employeeExtension, list[i].employeeDeparment);
			
			while (flag == 0)
			{
				printf("\n\nNew Staff (Updated) Extension Number : ");
				scanf("%s", newEmployeeExtension);
				if ((strlen(newEmployeeExtension) == 4) && ((newEmployeeExtension[0] >= '0') && (newEmployeeExtension[0] <= '9')) && ((newEmployeeExtension[1] >= '0') && (newEmployeeExtension[1] <= '9')) && ((newEmployeeExtension[2] >= '0') && (newEmployeeExtension[2] <= '9')) && ((newEmployeeExtension[3] >= '0') && (newEmployeeExtension[3] <= '9')))
				{
					strcpy(list[i].employeeExtension, newEmployeeExtension);
					flag = 1;
				}
				else
				{
					printf("\nTRY AGAIN USING CORRECT FORMAT. 4 DIGITS ONLY. Example : [xxxx ---> 1234]\n");
				}
			} 
		}
		i++;
	}
	fclose(file);

	if (flag == 1)
	{
		file = fopen("tel.txt", "w");
		int updateWriter;
		for (updateWriter = 0; updateWriter < i; updateWriter++)
		{
			if ((updateWriter + 1) == i)
			{
				fprintf(file, "%s\t%s\t%s\t%s", list[updateWriter].employeeName, list[updateWriter].employeeID, list[updateWriter].employeeExtension, list[updateWriter].employeeDeparment);
				printf("\nEMPLOYEE EXTENSION NUMBER HAS BEEN UPDATED !\n");
				break;
			}
			fprintf(file, "%s\t%s\t%s\t%s\n", list[updateWriter].employeeName, list[updateWriter].employeeID, list[updateWriter].employeeExtension, list[updateWriter].employeeDeparment);
		}
		fclose(file);
	}
	else
		printf("\nSTAFF RECORD DOES NOT EXIST\n");
	menuSelector();
}