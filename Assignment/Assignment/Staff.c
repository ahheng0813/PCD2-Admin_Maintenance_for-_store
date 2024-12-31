#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#pragma warning (disable:4996)

void addStaff(void);
void searchStaff(void);
void editStaff(void);
void displayStaff(void);
void deleteStaff(void);
void staffEvaluation(void);
void givingStaffEvaluation(void);
void displayStaffEvaluation(void);

void Staffheader(void);
void shortID(void);
void longID(void);
char* staffEvaluationConverter(int eCount);
int menuOption(int select);
void validDate(void);
void InvalidDay(void);
void InvalidMonth(void);
void InvalidYear(void);


typedef struct {
	int day, month, year;
}Date;

typedef struct {
	char staffID[5];
	char staffName[35];
	char staffGender;
	int staffAge;
	Date dateJoined;
	char position[30];
	double salary;
}Staff;

typedef struct
{
	int workQuality;
	int productivity;
	int communication;
	int collaboration;
}Evaluation;

void staff() {
	int response, option;

	do
	{
		printf("\n");
		printf("========================\n");
		printf(" Staff Information Menu \n");
		printf("========================\n\n");
		printf("1.Add Staff\n");
		printf("2.Search Staff Information\n");
		printf("3.Edit Staff Information\n");
		printf("4.Display Staff Information\n");
		printf("5.Delete Staff Information\n");
		printf("6.Staff Evaluation\n");
		printf("7.Exit\n");
		printf("\nSelect an Option: ");
		rewind(stdin);
		scanf("%d", &option);

		response = menuOption(option);

	} while (response != 7);
}

void addStaff(void) {
	int i, count = 0;
	char correctDate;
	char staffID[5];
	char ans;
	Staff staff;
	Evaluation staffEvaluation;
	Staff checkID[20];

	FILE* fp;
	FILE* fe;

	do
	{
		fp = fopen("staff.bin", "rb");

		if (fp == NULL) {
			printf("Cant Open File");
		}

		//read file if there is data inside
		i = 0;
		while (fread(&checkID[i], sizeof(Staff), 1, fp) != 0)
		{
			i++;
		}

		fclose(fp); // close reading file

		fp = fopen("staff.bin", "ab"); //open adding file

		if (fp == NULL) {
			printf("Cant Open File");
		}

		//Add Staff Evaluation value
		fe = fopen("staffEvaluation.bin", "ab"); //open adding file

		if (fe == NULL) {
			printf("Cant Open File");
		}

		do
		{
			printf("Give Staff an ID, only 4 character: "); //Get ID
			rewind(stdin);
			scanf("%s", &staffID);

			for (count = 0; count < i; count++) { //check if ID is the same
				while (strcmp(staffID, checkID[count].staffID) == 0) {
					printf("\n");
					printf("  ====================\n");
					printf("   ! ID is the Same ! \n");
					printf("  ====================\n\n");

					printf("Give Staff an ID, only 4 character: "); //Get ID
					rewind(stdin);
					scanf("%s", &staffID);
				}
			}
			strcpy(staff.staffID, staffID);

			if (strlen(staff.staffID) < 4) { //check if ID too short
				shortID();
			}
			else if (strlen(staff.staffID) > 4) { //check if ID too long
				longID();
			}
		} while (strlen(staff.staffID) != 4);

		printf("Staff Name: "); //Get staff name
		rewind(stdin);
		scanf("%[^\n]", &staff.staffName);

		do {
			printf("Staff Gender (M = Male/F = Female): "); //Get gender
			rewind(stdin);
			scanf("%c", &staff.staffGender);

			staff.staffGender = toupper(staff.staffGender);

			if (staff.staffGender != 'M' && staff.staffGender != 'F') { //check if Gender is M or F
				printf("\n");
				printf("  ================================================\n");
				printf("   ! Unknown Gender (Only (M = Male/F = Female) ! \n");
				printf("  ================================================\n\n");
			}

		} while (staff.staffGender != 'M' && staff.staffGender != 'F');

		do {
			printf("Staff Age (must above 20 years old and lower than 60 years old): "); //Get Staff Age
			rewind(stdin);
			scanf("%d", &staff.staffAge);

			if (staff.staffAge < 20) { //check if age above 20
				printf("\n");
				printf("  =======================\n");
				printf("   ! Age must above 20 ! \n");
				printf("  =======================\n\n");
			}
			else if (staff.staffAge > 60) { //check if age lower than 60
				printf("\n");
				printf("  ============================\n");
				printf("   ! Age must lower than 60 ! \n");
				printf("  ============================\n\n");
			}
		} while (staff.staffAge < 20 || staff.staffAge > 60);

		do {
			printf("His/Her Hired Date (XX-XX-XXXX): ");
			rewind(stdin);
			scanf("%d-%d-%d", &staff.dateJoined.day, &staff.dateJoined.month, &staff.dateJoined.year);

			//check year
			if (staff.dateJoined.year >= 1900 && staff.dateJoined.year <= 9999) {
				//check month
				if (staff.dateJoined.month >= 1 && staff.dateJoined.month <= 12) {
					//check day
					if ((staff.dateJoined.day >= 1 && staff.dateJoined.day <= 31) && (staff.dateJoined.month == 1 || staff.dateJoined.month == 3
						|| staff.dateJoined.month == 5 || staff.dateJoined.month == 7 || staff.dateJoined.month == 8 || staff.dateJoined.month == 10
						|| staff.dateJoined.month == 12)) {

						validDate();
						correctDate = 'Y';
					}
					else if ((staff.dateJoined.day >= 1 && staff.dateJoined.day <= 30) && (staff.dateJoined.month == 2 || staff.dateJoined.month == 4
						|| staff.dateJoined.month == 6 || staff.dateJoined.month == 9 || staff.dateJoined.month == 11)) {

						validDate();
						correctDate = 'Y';
					}
					else {
						InvalidDay();
						correctDate = 'N';
					}
				}
				else {
					InvalidMonth();
					correctDate = 'N';
				}
			}
			else {
				InvalidYear();
				correctDate = 'N';
			}
		} while (correctDate == 'N');

		printf("Postion: ");
		rewind(stdin);
		scanf("%[^\n]", &staff.position);

		printf("Salary: ");
		rewind(stdin);
		scanf("%lf", &staff.salary);

		staffEvaluation.workQuality = 0;
		staffEvaluation.productivity = 0;
		staffEvaluation.communication = 0;
		staffEvaluation.collaboration = 0;

		fwrite(&staff, sizeof(Staff), 1, fp); //add staff to file
		fclose(fp);

		fwrite(&staffEvaluation, sizeof(Evaluation), 1, fe);
		fclose(fe);

		i++;

		printf("Do you want to add more? (Y=yes): ");
		rewind(stdin);
		scanf("%c", &ans);

	} while (ans == 'Y');

}

void searchStaff(void) {
	char staffID[5];
	char ans;
	int i = 0, count = 0, counter = 0;
	Staff staff[20];

	FILE* fp;
	fp = fopen("staff.bin", "rb");

	if (fp == NULL) {
		printf("Cant Open File");
	}

	//get ID
	do
	{
		do
		{
			printf("Staff ID: ");
			rewind(stdin);
			scanf("%s", &staffID);

			if (strlen(staffID) < 4) { //check if ID too short
				shortID();
			}
			else if (strlen(staffID) > 4) { //check if ID too long
				longID();
			}
		} while (strlen(staffID) != 4);

		while (fread(&staff[count], sizeof(Staff), 1, fp) != 0)
		{
			count++;
		}

		Staffheader();

		for (i = 0; i < count; i++)
		{
			if (strcmp(staffID, staff[i].staffID) == 0)
			{
				printf("%-6s", staff[i].staffID);
				printf("%-16s", staff[i].staffName);
				printf("%-8c", staff[i].staffGender);
				printf("%-5d", staff[i].staffAge);
				printf("%02d-%02d-%02d", staff[i].dateJoined.day, staff[i].dateJoined.month, staff[i].dateJoined.year);
				printf("  %-12s", staff[i].position);
				printf("RM%-13.2f\n", staff[i].salary);
				counter++;
			}
		}
		printf("========================================================================\n");
		printf("%d staff record is listed\n\n", counter);

		printf("Want to search again? (Y = yes) : ");
		rewind(stdin);
		scanf("%c", &ans);

		ans = toupper(ans);

	} while (ans == 'Y');
	fclose(fp);
}

void editStaff(void) {
	char ID[5];
	char ans, confirmation, correctDate;
	int i, staffCount = 0, count = 0;
	Staff staff[20];
	char name[35], position[30], gender;
	int age, day, month, year;
	double salary;

	FILE* fp;
	fp = fopen("staff.bin", "rb");

	if (fp == NULL) {
		printf("Cant Open File");
	}

	while (fread(&staff[staffCount], sizeof(Staff), 1, fp) != 0) {
		staffCount++;
	}
	fclose(fp);

	do
	{
		do
		{
			printf("Enter ID you want to edit: ");
			rewind(stdin);
			scanf("%s", &ID);

			if (strlen(ID) < 4) { //check if ID too short
				shortID();
			}
			else if (strlen(ID) > 4) { //check if ID too long
				longID();
			}

		} while (strlen(ID) != 4);

		Staffheader();

		for (i = 0; i < staffCount; i++)
		{
			if (strcmp(ID, staff[i].staffID) == 0)
			{
				printf("%-6s", staff[i].staffID);
				printf("%-16s", staff[i].staffName);
				printf("%-8c", staff[i].staffGender);
				printf("%-5d", staff[i].staffAge);
				printf("%02d-%02d-%02d", staff[i].dateJoined.day, staff[i].dateJoined.month, staff[i].dateJoined.year);
				printf("  %-12s", staff[i].position);
				printf("RM%-13.2f\n", staff[i].salary);
				printf("========================================================================\n");

				printf("Staff Name: "); //Get staff name
				rewind(stdin);
				scanf("%[^\n]", &name);

				do {
					printf("Staff Gender (M = Male/F = Female): "); //Get gender
					rewind(stdin);
					scanf("%c", &gender);

					gender = toupper(gender);

					if (gender != 'M' && gender != 'F') { //check if Gender is M or F
						printf("\n");
						printf("  ================================================\n");
						printf("   ! Unknown Gender (Only (M = Male/F = Female) ! \n");
						printf("  ================================================\n\n");
					}

				} while (gender != 'M' && gender != 'F');

				do {
					printf("Staff Age (must above 20 years old and lower than 60 years old): "); //Get Staff Age
					rewind(stdin);
					scanf("%d", &age);

					if (age < 20) { //check if age above 20
						printf("\n");
						printf("  =======================\n");
						printf("   ! Age must above 20 ! \n");
						printf("  =======================\n\n");
					}
					else if (age > 60) { //check if age lower than 60
						printf("\n");
						printf("  ============================\n");
						printf("   ! Age must lower than 60 ! \n");
						printf("  ============================\n\n");
					}
				} while (age < 20 || age > 60);

				do {
					printf("His/Her Hired Date (XX-XX-XXXX): ");
					rewind(stdin);
					scanf("%d-%d-%d", &day, &month, &year);

					//check year
					if (year >= 1900 && year <= 9999) {
						//check month
						if (month >= 1 && month <= 12) {
							//check day
							if ((day >= 1 && day <= 31) && (month == 1 || month == 3 || month == 5
								|| month == 7 || month == 8 || month == 10 || month == 12))
							{
								validDate();
								correctDate = 'Y';
							}
							else if ((day >= 1 && day <= 30) && (month == 2 || month == 4 || month == 6
								|| month == 9 || month == 11))
							{
								validDate();
								correctDate = 'Y';
							}
							else {
								InvalidDay();
								correctDate = 'N';
							}
						}
						else {
							InvalidMonth();
							correctDate = 'N';
						}
					}
					else {
						InvalidYear();
						correctDate = 'N';
					}
				} while (correctDate == 'N');

				printf("Postion: ");
				rewind(stdin);
				scanf("%[^\n]", &position);

				printf("Salary: ");
				rewind(stdin);
				scanf("%lf", &salary);

				printf("Confirm the Changes (Y=yes)? ");
				rewind(stdin);
				scanf("%c", &confirmation);
				if (toupper(confirmation) == 'Y') {
					strcpy(staff[i].staffName, name);
					staff[i].staffGender = gender;
					staff[i].staffAge = age;
					staff[i].dateJoined.day = day;
					staff[i].dateJoined.month = month;
					staff[i].dateJoined.year = year;
					strcpy(staff[i].position, position);
					staff[i].salary = salary;
					count++;
					printf("\nModify Completed!!\n");
				}

			}
		}
		printf("Do you want to edit more staff information (Y = yes): ");
		rewind(stdin);
		scanf("%c", &ans);

		ans = toupper(ans);

	} while (ans == 'Y');

	fp = fopen("staff.bin", "wb");

	if (fp == NULL)
	{
		printf("\n\nFile cannot be open !!\n");
		exit(-1);
	}

	for (i = 0; i < staffCount; i++)
	{
		fwrite(&staff[i], sizeof(Staff), 1, fp);
	}
	fclose(fp);
	printf("\n%d Record(s) modified\n\n", count);

}

void displayStaff(void) {
	int counter = 0;
	Staff staff;

	FILE* fp;
	fp = fopen("staff.bin", "rb");

	if (fp == NULL)
	{
		printf("Cant Open File");
	}

	Staffheader();

	while (fread(&staff, sizeof(Staff), 1, fp) != 0)
	{
		printf("%-6s", staff.staffID);
		printf("%-16s", staff.staffName);
		printf("%-8c", staff.staffGender);
		printf("%-5d", staff.staffAge);
		printf("%02d-%02d-%02d", staff.dateJoined.day, staff.dateJoined.month, staff.dateJoined.year);
		printf("  %-12s", staff.position);
		printf("RM%-13.2f\n", staff.salary);
		counter++;
	}
	printf("========================================================================\n");
	printf("%d staff record is listed\n\n", counter);

	fclose(fp);
}

void deleteStaff(void)
{
	Staff staff[20];
	int sCount = 0, i = 0, deleteIndex = 0;
	char ID[5];
	char ans;

	FILE* fp;
	fp = fopen("staff.bin", "rb");

	if (fp == NULL) {
		printf("Can't Open File");
		exit(-1);
	}

	while (fread(&staff[sCount], sizeof(Staff), 1, fp) != 0)
	{
		sCount++;
	}
	fclose(fp); //close read file

	do
	{
		printf("Enter ID you want to delete: ");
		rewind(stdin);
		scanf("%s", &ID);

		if (strlen(ID) < 4) { //check if ID too short
			shortID();
		}
		else if (strlen(ID) > 4) { //check if ID too long
			longID();
		}

	} while (strlen(ID) != 4);

	for (i = 0; i < sCount; i++)
	{
		if (strcmp(ID, staff[i].staffID) == 0)
		{
			Staffheader();
			printf("%-6s", staff[i].staffID);
			printf("%-16s", staff[i].staffName);
			printf("%-8c", staff[i].staffGender);
			printf("%-5d", staff[i].staffAge);
			printf("%02d-%02d-%02d", staff[i].dateJoined.day, staff[i].dateJoined.month, staff[i].dateJoined.year);
			printf("  %-12s", staff[i].position);
			printf("RM%-13.2f\n\n", staff[i].salary);

			printf("Confirm to delete? (Y=yes): ");
			rewind(stdin);
			scanf("%c", &ans);

			ans = toupper(ans);

			if (ans == 'Y')
			{
				fp = fopen("staff.bin", "wb");

				if (fp == NULL)
				{
					printf("Can't Open File");
					exit(-1);
				}

				deleteIndex = i;
				for (i = deleteIndex; i < sCount; i++)
				{
					staff[i] = staff[i + 1];
				}
				sCount--;
				printf("\n===========================\n");
				printf(" Delete Process Successful \n");
				printf("===========================\n\n");
			}
		}
	}

	for (i = 0; i < sCount; i++)
	{
		fwrite(&staff[i], sizeof(Staff), 1, fp);
	}
	fclose(fp);
}

void staffEvaluation(void) {
	int response;

	do {
		printf("\n=======================\n");
		printf(" Staff Evaluation Menu \n");
		printf("=======================\n\n");
		printf("1.Staff Evaluation Form\n");
		printf("2.Display Form\n");
		printf("3.Exit\n");
		printf("\nSelect an Option: ");
		rewind(stdin);
		scanf("%d", &response);

		switch (response) {
		case 1:
			givingStaffEvaluation(); break;
		case 2:
			displayStaffEvaluation(); break;
		case 3:
			break;
		default:
			printf("\n");
			printf("  ==============================\n");
			printf("   ! Invalid Value (Only 1-3) ! \n");
			printf("  ==============================\n\n");
			break;
		}
	} while (response != 3);
}

void givingStaffEvaluation(void) {
	Staff staff[20];
	Evaluation staffEvaluation[20];
	char staffID[5], ans, confirm;
	int i, sCount = 0, eCount = 0;
	int workQuality = 0, productivity = 0, communication = 0, collaboration = 0;

	FILE* fp;
	FILE* fe;

	fp = fopen("staff.bin", "rb");
	if (fp == NULL) {
		printf("Can't Open File");
		exit(-1);
	}
	while (fread(&staff[sCount], sizeof(Staff), 1, fp) != 0)
	{
		sCount++;
	}
	fclose(fp); //close read file


	fe = fopen("staffEvaluation.bin", "rb"); //read evalaluation file
	if (fe == NULL) {
		printf("Cant Open File");
	}
	while (fread(&staffEvaluation[eCount], sizeof(Evaluation), 1, fe) != 0) {
		eCount++;
	}
	fclose(fe);//close read file

	do
	{
		do
		{
			printf("Staff ID: ");
			rewind(stdin);
			scanf("%s", &staffID);

			if (strlen(staffID) < 4) { //check if ID too short
				shortID();
			}
			else if (strlen(staffID) > 4) { //check if ID too long
				longID();
			}
		} while (strlen(staffID) != 4);

		Staffheader();

		for (i = 0; i < sCount; i++)
		{
			if (strcmp(staffID, staff[i].staffID) == 0)
			{
				printf("%-6s", staff[i].staffID);
				printf("%-16s", staff[i].staffName);
				printf("%-8c", staff[i].staffGender);
				printf("%-5d", staff[i].staffAge);
				printf("%02d-%02d-%02d", staff[i].dateJoined.day, staff[i].dateJoined.month, staff[i].dateJoined.year);
				printf("  %-12s", staff[i].position);
				printf("RM%-13.2f\n", staff[i].salary);
				printf("========================================================================\n\n");

				printf(" 1=Poor, 2=Average, 3=Good, 4=Great , 5=Excellent\n");

				printf("Rate his/her Work Quality (1-5): ");
				rewind(stdin);
				scanf("%d", &workQuality);

				printf("Rate his/her Productivity (1-5): ");
				rewind(stdin);
				scanf("%d", &productivity);

				printf("Rate his/her Communication Skill (1-5): ");
				rewind(stdin);
				scanf("%d", &communication);

				printf("Rate his/her Collaborative Skill(1-5): ");
				rewind(stdin);
				scanf("%d", &collaboration);

				printf("Confirm? (Y=yes): ");
				rewind(stdin);
				scanf("%c", &confirm);

				confirm = toupper(confirm);

				if (confirm == 'Y')
				{
					staffEvaluation[i].workQuality = workQuality;
					staffEvaluation[i].productivity = productivity;
					staffEvaluation[i].communication = communication;
					staffEvaluation[i].collaboration = collaboration;
					printf("Your Review has been Added\n");
				}
			}
		}
		printf("Do you want to rate more staff information (Y = yes): ");
		rewind(stdin);
		scanf("%c", &ans);

		ans = toupper(ans);

	} while (ans == 'Y');

	fe = fopen("staffEvaluation.bin", "wb");

	if (fp == NULL)
	{
		printf("\n\nFile cannot be open !!\n");
		exit(-1);
	}

	for (i = 0; i < sCount; i++)
	{
		fwrite(&staffEvaluation[i], sizeof(Evaluation), 1, fp);
	}
	fclose(fe);

	printf("\nRecord(s) Added\n\n");

}

void displayStaffEvaluation(void) {
	Staff staff[20];
	Evaluation staffEvaluation[20];
	int i, sCount = 0, eCount = 0;
	char* gradeWq[15], * gradeP[15], * gradeCM[15], * gradeCL[15];

	FILE* fp;
	FILE* fe;

	fp = fopen("staff.bin", "rb");
	if (fp == NULL) {
		printf("Can't Open File");
		exit(-1);
	}
	while (fread(&staff[sCount], sizeof(Staff), 1, fp) != 0)
	{
		sCount++;
	}
	fclose(fp); //close read file


	fe = fopen("staffEvaluation.bin", "rb"); //read evalaluation file
	if (fe == NULL) {
		printf("Cant Open File");
	}
	while (fread(&staffEvaluation[eCount], sizeof(Evaluation), 1, fe) != 0) {
		eCount++;
	}
	fclose(fe);//close read file

	printf("\n==================================================================================================\n");
	printf("                                     All Staff Evaluation Form                                    \n");
	printf("==================================================================================================\n");
	printf(" ID        Name        Work Quality    Productivity    Communication Skill    Collaboration Skill \n");
	printf("====  ==============  ==============  ==============  =====================  =====================\n");

	for (i = 0; i < sCount; i++) {
		printf("%-6s", staff[i].staffID);
		printf("%-16s", staff[i].staffName);

		*gradeWq = staffEvaluationConverter(staffEvaluation[i].workQuality);
		*gradeP = staffEvaluationConverter(staffEvaluation[i].productivity);
		*gradeCM = staffEvaluationConverter(staffEvaluation[i].communication);
		*gradeCL = staffEvaluationConverter(staffEvaluation[i].collaboration);

		printf("%-16s", *gradeWq);
		printf("%-16s", *gradeP);
		printf("%-23s", *gradeCM);
		printf("%-21s\n", *gradeCL);
	}
}

char* staffEvaluationConverter(int eCount) {
	char response[15];

	switch (eCount) {
	case 0:
		return "None";  break;
	case 1:
		return "Poor";  break;
	case 2:
		return "Average";  break;
	case 3:
		return  "Good";  break;
	case 4:
		return "Great";  break;
	case 5:
		return "Excellent";  break;
	default: break;
	}
}

int menuOption(int select) {
	switch (select) {
	case 1:
		addStaff(); break;
	case 2:
		searchStaff();  break;
	case 3:
		editStaff();  break;
	case 4:
		displayStaff(); break;
	case 5:
		deleteStaff(); break;
	case 6:
		staffEvaluation(); break;
	case 7: break;
	default:
		printf("\n");
		printf("  ==============================\n");
		printf("   ! Invalid Value (Only 1-7) ! \n");
		printf("  ==============================\n\n");
		break;
	}

	return select;
}

void Staffheader(void) {
	printf("\n========================================================================\n");
	printf("                         Staff Information                              \n");
	printf("========================================================================\n");
	printf(" ID        Name       Gender  Age  Date Hired   Position    Salary (RM) \n");
	printf("====  ==============  ======  ===  ==========  ==========  =============\n");
}

void shortID(void) {
	printf("\n");
	printf("  ==================\n");
	printf("   ! ID too Short ! \n");
	printf("  ==================\n\n");
}

void longID(void) {
	printf("\n");
	printf("  =================\n");
	printf("   ! ID too Long ! \n");
	printf("  =================\n\n");
}

void validDate(void) {
	printf("\n");
	printf("  ============\n");
	printf("   Valid Date \n");
	printf("  ============\n\n");
}

void InvalidDay(void) {
	printf("\n"); //Invalid Day
	printf("  =================\n");
	printf("   ! Invalid Day ! \n");
	printf("  =================\n\n");
}

void InvalidMonth(void) {
	printf("\n"); //Invalid Month
	printf("  ===================\n");
	printf("   ! Invalid Month ! \n");
	printf("  ===================\n\n");
}

void InvalidYear(void) {
	printf("\n"); //Invalid Year
	printf("  ==================\n");
	printf("   ! Invalid Year ! \n");
	printf("  ==================\n\n");
}