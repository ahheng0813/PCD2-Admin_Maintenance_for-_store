#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#pragma warning(disable:4996)
#pragma warning(disable:6031)


typedef struct {
	char memberID[5];
	char name[30];
	char gender;
	int memberIC[13];
	int phoneNum[11];
	char uplineID[5];
}Member;

void memberRecord(void);
void addMember(void);
void modifyRecord(void);
void searchRecord(void);
void deleteRecord(void);
int memberDisplay(int option);
void memberFinalReport(void);
int memberAdd(int report);

member()
{
	int option;

	do {
		printf("Option\n");
		printf("1: View Member record\n");
		printf("2: Add New Member\n");
		printf("3: Search Member\n");
		printf("4: Modify Member\n");
		printf("5: Delete Member\n");
		printf("6: Generate member Report\n");
		printf("7: Exit\n");
		printf("Select Option:");
		scanf("%d", &option);
		rewind(stdin);

		option = memberDisplay(option);
	} while (option != 7);

}

int memberDisplay(int option) {
	switch (option) {
	case 1:

		memberRecord();
		break;
	case 2:
		addMember();
		break;
	case 3:
		searchRecord();
		break;
	case 4:
		modifyRecord();
		
		break;
	case 5:
		deleteRecord();
		break;
	case 6:
		memberFinalReport();
		break;
	case 7:
		break;

	default:
		printf("Please Insert Only 1, 2, 3, 4, 5 ,6 or 7\n");
		break;

	}

	return option;
}

void memberRecord(void)
{
	int i = 0;
	FILE* fp;
	int mcount = 0;
	Member s[20];
	int found = 0;
	fp = fopen("member.txt", "r");



	if (!fp)
	{
		printf("FILE can't be open");
		exit(-1);
	}

	printf("Member Information\n");
	printf("==================\n");

	while
		(fscanf(fp, "%[^\|]|", &s[i].memberID) != EOF) {
		fscanf(fp, "%[^\|]|", &s[i].name);
		fscanf(fp, "%c|", &s[i].gender);
		fscanf(fp, "%[^\|]|", &s[i].memberIC);
		fscanf(fp, "%[^\|]|", &s[i].phoneNum);
		fscanf(fp, "%s ", &s[i].uplineID);

		found = 1;
		printf("\n\nMember ID\t\t: %s\n", s[i].memberID);
		printf("Name\t\t: %s\n", s[i].name);
		printf("gender \t: %c\n", s[i].gender);
		printf("member IC \t\t\t: %s\n", s[i].memberIC);
		printf("phone number \t\t: %s\n", s[i].phoneNum);
		printf("uplineID \t\t\t: %s\n\n", s[i].uplineID);

	}

	fclose(fp);
	

	if (found == 0) {
		printf("No member Existed!!\n");
	}

}

void addMember(void)
{

	FILE* fp;
	Member s[10];
	char memberID[10];
	char name[30];
	char gender;
	int memberIC[13];
	int phoneNum[11];
	char uplineID[5];
	char ans;
	char add;
	int i = 0, mcount = 0, totalRecord = 0;
	int members;

	



		do{ 
			printf("Add Member ? (Y for Yes, X to Exit)\n");
			scanf("%c", &add);
			add = toupper(add);
			rewind(stdin);

			switch (add) {

				case 'Y':

				do {
					fp = fopen("member.txt", "r");

					if (!fp)
					{
						printf("fILE can't be open");
						exit(-1);
					}


					while
						(fscanf(fp, "%[^\|]|", &s[i].memberID) != EOF) {
						fscanf(fp, "%[^\|]|", &s[i].name);
						fscanf(fp, "%c|", &s[i].gender);
						fscanf(fp, "%[^\|]|", &s[i].memberIC);
						fscanf(fp, "%[^\|]|", &s[i].phoneNum);
						fscanf(fp, "%s ", &s[i].uplineID);
						i++;
					}
					fclose(fp);

					fclose(fp);


					fp = fopen("member.txt", "a");

					if (!fp)
					{
						printf("FILE can't be open");
						exit(-1);
					}


					printf("\nMember ID\t\t: ");
					scanf("%s", &memberID);
					rewind(stdin);


					if (strlen(memberID) < 4) {
						printf("Order ID Is Too Short Like You!!!\n");
					}
					else if (strlen(memberID) > 4) {
						printf("Order ID Is Too Long Like Ming Jian\n");
					}

					for (members = 0; members < i; members++) {
						while (strcmp(memberID, s[members].memberID) == 0) {
							printf("Member ID Repeated!!\n");

							printf("Member ID: ");
							scanf("%s", &memberID);
							rewind(stdin);

						}

					}

				} while (strlen(memberID) != 4);


			printf("\nName  \t\t:");
			scanf("%[^\n]", &name);
			rewind(stdin);



			do {
				printf("\nGender (M = Male/F = Female): "); //Get gender
				scanf("%c", &gender);
				rewind(stdin);

				gender = toupper(gender);

				if (gender != 'M' && gender != 'F') { //check if Gender is M or F
					printf("\n");
					printf("  ================================================\n");
					printf("   ! Unknown Gender (Only (M = Male/F = Female) ! \n");
					printf("  ================================================\n\n");
				}

			} while (gender != 'M' && gender != 'F');

			printf("\nMember IC \t\t\t:");
			scanf("%s", &memberIC);
			rewind(stdin);

			printf("\nPhone Number \t\t:");
			scanf("%s", &phoneNum);
			rewind(stdin);

			printf("\nUp Line ID \t\t:");
			scanf("%s", &uplineID);
			rewind(stdin);

			printf("Comfirm Add Member? (Y To Comfirm): ");
			scanf("%c", &ans);
			printf("\n");
			rewind(stdin);


			if (toupper(ans) == 'Y') {

				strcpy(s[i].memberID, memberID);
				strcpy(s[i].name, name);
				s[i].gender = gender;
				strcpy(s[i].memberIC, memberIC);
				strcpy(s[i].phoneNum, phoneNum);
				strcpy(s[i].uplineID, uplineID);

				mcount++;

				totalRecord = memberAdd(mcount);

				fprintf(fp, "%s|%s|%c|%s|%s|%s\n", s[i].memberID, s[i].name, s[i].gender, s[i].memberIC, s[i].phoneNum, s[i].uplineID);

				printf("Record Successfuly Added...\n\n");
				fclose(fp);
			}

				break;
				case 'X':
					break;
				default:
					printf("Please Input Only Y or X\n");
			}
	
		} while (add != 'X');

			printf("%d Record Added!!\n", mcount);

}

int memberAdd(int record) {
	int totalRecord;

	totalRecord = record;

	return totalRecord;

}
void searchRecord(void)
		{

			int i = 0;
			FILE* fp;
			int found;
			Member s[20];
			int mcount;
			char memberID[5];
			char ans;
			char add;


			fp = fopen("member.txt", "r");

			if (!fp)
			{
				printf("FILE can't be open");
				exit(-1);
			}

			while
				(fscanf(fp, "%[^\|]|", &s[i].memberID) != EOF) {
				fscanf(fp, "%[^\|]|", &s[i].name);
				fscanf(fp, "%c|", &s[i].gender);
				fscanf(fp, "%[^\|]|", &s[i].memberIC);
				fscanf(fp, "%[^\|]|", &s[i].phoneNum);
				fscanf(fp, "%s ", &s[i].uplineID);
				i++;
				mcount = i;

			}
			fclose(fp);

			do {
				printf("\n Enter the member id you want to search:");
				rewind(stdin);
				scanf("%s", memberID);

				found = 0;

				for (i = 0; i < mcount; i++) {
					if (strcmp(s[i].memberID, memberID) == 0) {
						found = 1;
						printf("\n\nMember ID\t\t: %s\n", s[i].memberID);
						printf("  \t\t:name %s\n", s[i].name);
						printf("gender \t: %c\n", s[i].gender);
						printf("member IC \t\t\t: %s\n", s[i].memberIC);
						printf("phone number \t\t: %s\n", s[i].phoneNum);
						printf("uplineID \t\t\t: %s\n\n", s[i].uplineID);

					}
				}

				if (!found) {
					printf("Invalid Member ID(%s)\n", memberID);
				}

				printf("More Member To Search? (Y to Confirm) : ");
				rewind(stdin);
				scanf("%c", &add);

			} while (toupper(add) == 'Y');



		}

void modifyRecord(void)
{
	int i = 0;
	FILE* fp;
	int found;
	Member s[20];
	int mcount;
	char memberID[5];
	char name[30];
	char gender;
	int memberIC[13];
	int phoneNum[11];
	char uplineID[5];
	char ans;
	char add;
	fp = fopen("member.txt", "r");

	if (!fp)
	{
		printf("FILE can't be open");
		exit(-1);
	}

	while
		(fscanf(fp, "%[^\|]|", &s[i].memberID) != EOF) {
		fscanf(fp, "%[^\|]|", &s[i].name);
		fscanf(fp, "%c|", &s[i].gender);
		fscanf(fp, "%[^\|]|", &s[i].memberIC);
		fscanf(fp, "%[^\|]|", &s[i].phoneNum);
		fscanf(fp, "%s ", &s[i].uplineID);
		i++;
		

	}

	mcount = i;
	fclose(fp);

	fp = fopen("member.txt", "w");

	if (!fp) {
		printf("File Cannot be open!\n");
		exit(-1);
	}

	do {
		printf("\n Enter the member id you want to modify:");
		rewind(stdin);
		scanf("%s", &memberID);

		found = 0;

		for (i = 0; i < mcount; i++) {
			if (strcmp(s[i].memberID, memberID) == 0) {
				found = 1;
				printf("\n\nMember ID\t\t: %s\n", s[i].memberID);
				printf("name  \t\t: %s\n", s[i].name);
				printf("gender \t: %c\n", s[i].gender);
				printf("Member ID \t\t\t: %s\n", s[i].memberIC);
				printf("Phone Number \t\t: %s\n", s[i].phoneNum);
				printf("Up Line ID \t\t\t: %s\n\n", s[i].uplineID);

				printf("\nMember ID\t\t: ");
				scanf("%s", &memberID);
				rewind(stdin);

				printf("\nName  \t\t:");
				scanf("%[^\n]", &name);
				rewind(stdin);

				printf("\nGender \t:");
				scanf("%c", &gender);
				rewind(stdin);

				printf("\nMember IC \t\t\t:");
				scanf("%s", &memberIC);
				rewind(stdin);

				printf("\nPhone Number \t\t:");
				scanf("%s", &phoneNum);
				rewind(stdin);


				printf("\nUp Line ID \t\t:");
				scanf("%s", &uplineID);
				rewind(stdin);

				printf("Comfirm Modify Sales Order? (Y To Comfirm): ");
				scanf("%c", &ans);
				printf("\n");
				rewind(stdin);
				if (toupper(ans) == 'Y') {

					strcpy(s[i].memberID, memberID);
					strcpy(s[i].name, name);
					s[i].gender = gender;
					strcpy(s[i].memberIC, memberIC);
					strcpy(s[i].phoneNum, phoneNum);
					strcpy(s[i].uplineID, uplineID);

					printf("\n\nRecord Successfuly Modified...\n\n");
				}

			}
		}

		if (!found) {
			printf("Invalid Member ID(%d)\n", memberID);
		}

		printf("More Sales Order To modify? (Y to Confirm) : ");
		rewind(stdin);
		scanf("%c", &add);

	} while (toupper(add) == 'Y');

	for (i = 0; i < mcount; i++) {
		fprintf(fp, "%s|%s|%c|%s|%s|%s\n", s[i].memberID, s[i].name, s[i].gender, s[i].memberIC, s[i].phoneNum, s[i].uplineID);
	}


	fclose(fp);


}

void deleteRecord(void) {
	int i = 0;
	FILE* fp;
	int found;
	Member s[20];
	int mcount;
	char memberID[5];
	char add, ans;
	int deleteIndex = 0;
	

	

	do {
		fp = fopen("member.txt", "r");

		if (!fp)
		{
			printf("fILE can't be open");
			exit(-1);
		}

		while
			(fscanf(fp, "%[^\|]|", &s[i].memberID) != EOF) {
			fscanf(fp, "%[^\|]|", &s[i].name);
			fscanf(fp, "%c|", &s[i].gender);
			fscanf(fp, "%[^\|]|", &s[i].memberIC);
			fscanf(fp, "%[^\|]|", &s[i].phoneNum);
			fscanf(fp, "%s ", &s[i].uplineID);
			i++;
			mcount = i;

		}
		fclose(fp);

		fp = fopen("member.txt", "w");

		if (!fp) {
			printf("File Cannot be open!\n");
			exit(-1);
		}

		printf("\n Enter the member id you want to delete:");
		rewind(stdin);
		scanf("%s", memberID);

		found = 0;

		for (i = 0; i < mcount; i++) {
			if (strcmp(s[i].memberID, memberID) == 0) {
				found = 1;
				printf("\n\nMember ID\t\t: %s\n", s[i].memberID);
				printf("  \t\t:name %s\n", s[i].name);
				printf("gender \t: %c\n", s[i].gender);
				printf("member IC \t\t\t: %s\n", s[i].memberIC);
				printf("phone number \t\t: %s\n", s[i].phoneNum);
				printf("uplineID \t\t\t: %s\n\n", s[i].uplineID);


				printf("Comfirm delete member? (Y To Comfirm): ");
				rewind(stdin);
				scanf("%c", &ans);

				printf("\n");
				rewind(stdin);
				if (toupper(ans) == 'Y') {
					deleteIndex = i;

					for (i = deleteIndex; i < mcount; i++) {
						s[i] = s[i + 1];
					}

					mcount--;


					printf("\n\nRecord Successfuly Modified...\n\n");
				}

			}
		}

		if (!found) {
			printf("Invalid member id(%s)\n", memberID);
		}


		for (i = 0; i < mcount; i++) {
			fprintf(fp, "%s|%s|%c|%s|%s|%s\n", s[i].memberID, s[i].name, s[i].gender, s[i].memberIC, s[i].phoneNum, s[i].uplineID);
		}

		fclose(fp);


		printf("More member ID To delete? (Y to Confirm) : ");
		rewind(stdin);
		scanf("%c", &add);

	} while (toupper(add) == 'Y');


}

void memberFinalReport(void) {

	int i = 0;
	FILE* fp;
	int found;
	Member s[20];
	int mcount;
	char memberID[5];
	char add, ans;
	int deleteIndex = 0;
	int mrecord;
	fp = fopen("member.txt", "r");

	if (!fp) {
		printf("\nFile can't be open!!\n");
		exit(-1);
	}

	while
		(fscanf(fp, "%[^\|]|", &s[i].memberID) != EOF) {
		fscanf(fp, "%[^\|]|", &s[i].name);
		fscanf(fp, "%c|", &s[i].gender);
		fscanf(fp, "%[^\|]|", &s[i].memberIC);
		fscanf(fp, "%[^\|]|", &s[i].phoneNum);
		fscanf(fp, "%s ", &s[i].uplineID);

		i++;
	}

	reportHead(); //FROM SALES

	printf("\n\tTotal Member: %d\n\n", i);
	printf("======================================================================================================================\n");
	printf("======================================================================================================================\n");
	fclose(fp);



}
