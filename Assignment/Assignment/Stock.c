#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h> //strcmp
#include<time.h>//display system time 
#include<conio.h>
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

typedef struct {
	char invoiceID[5];
	char senderName[30];
	char itemCode[5];
	int quantity;
	double price;
	double tIPrice;

}Sales;

void viewStock(void);
void addStock(void);
void searchStock(void);
void modifyStock(void);
void deleteStock(void);
void stockReport(void);
int optionDisplay(int option);
void addStockProcess(char add);


stock() {
	int option;

	do {
		printf("_________________________________________\n");

		printf("|\t Option \t\t\t|\n");
		printf("|\t 1: View All Stock \t\t|\n");
		printf("|\t 2: Add New Stock \t\t|\n");
		printf("|\t 3: Search Stock \t\t|\n");
		printf("|\t 4: Modify Stock \t\t|\n");
		printf("|\t 5: Delete Stock \t\t|\n");
		printf("|\t 6: Generate Stock Report \t|\n");
		printf("|\t 7: Exit \t\t\t|\n");
		printf("_________________________________________\n");
		printf(" \t Select Option:");
		scanf("%d", &option);
		rewind(stdin);

		option = optionDisplay(option);

	} while (option != 7);

}

int optionDisplay(int option) {
	switch (option) {
	case 1:

		viewStock();
		option = 0;
		break;
	case 2:
		addStock();
		option = 0;
		break;
	case 3:
		searchStock();
		option = 0;
		break;
	case 4:
		modifyStock();
		option = 0;
		break;
	case 5:
		deleteStock();
		option = 0;
		break;
	case 6:
		stockReport();
		option = 0;
		break;
	case 7:
		break;

	default:
		printf("Please Insert Only 1, 2, 3, 4, 5 ,6 or 7\n");
		break;

	}

	return option;
}

void viewStock(void) {

	int i = 0;
	FILE* fp;
	int found = 0;
	Sales s[20];

	fp = fopen("stockInfo.txt", "r");



	if (!fp)
	{
		printf("File can't be open");
		exit(-1);
	}
	printf("____________________________________________________\n");
	while
		(fscanf(fp, "%s", &s[i].invoiceID) != EOF) {
		fscanf(fp, "%[^\n]", &s[i].senderName);
		fscanf(fp, "%s", &s[i].itemCode);
		fscanf(fp, "%d", &s[i].quantity);
		fscanf(fp, "%lf", &s[i].price);
		fscanf(fp, "%lf", &s[i].tIPrice);

		found = 1;
		printf("Invoice  \t\t: %s\n", s[i].invoiceID);
		printf("Sender Name \t\t:%s\n", s[i].senderName);
		printf("Item Code  \t\t: %s\n", s[i].itemCode);
		printf("Quantity Ordered \t: %d\n", s[i].quantity);
		printf("Price \t\t\t: %.2f\n", s[i].price);
		printf("------------------------------------------------\n");
		printf("Total Price \t\t: %.2f\n", s[i].tIPrice);
		printf("____________________________________________________\n");

	}

	if (found != 1) {
		printf("\n\t\tNo Data Availabale!!\n");
		printf("____________________________________________________\n");
	}
	fclose(fp);
}

void addStock(void) {

	char add;

	printf("Add Stock? ? (Y for Yes, X to Exit) : ");
	rewind(stdin);
	scanf("%c", &add);
	add = toupper(add);

	addStockProcess(add);

}

void addStockProcess(char add) {
	FILE* fp;
	Sales s[20];
	int i = 0;
	char invoiceID[5];
	char senderName[30];
	char itemCode[5];
	int quantity;
	double price = 0;
	double tIPrice = 0;
	char ans;
	int stock = 0;
	char reply;
	int calculate = 0;

	while (add != 'X') {

		switch (add) {

		case 'Y':

			do {
				fp = fopen("stockInfo.txt", "r");

				if (fp == NULL) {
					printf("\nFILE CAN'T BE OPEN\n");
				}
				while
					(fscanf(fp, "%s", &s[i].invoiceID) != EOF) {
					fscanf(fp, "%[^\n]", &s[i].senderName);
					fscanf(fp, "%s", &s[i].itemCode);
					fscanf(fp, "%d", &s[i].quantity);
					fscanf(fp, "%lf", &s[i].price);
					fscanf(fp, "%lf", &s[i].tIPrice);

					i++;
				}

				fclose(fp);

				fp = fopen("stockInfo.txt", "a");

				if (fp == NULL)
				{
					printf("\nFILE CAN'T BE OPEN\n");
					exit(-1);
				}
				printf("\nInvoice ID\t\t: ");
				rewind(stdin);
				scanf("%s", &invoiceID);
				rewind(stdin);

				if (strlen(invoiceID) < 4) {
					printf("Order ID Is Too Short!!!\n");
				}
				else if (strlen(invoiceID) > 4) {
					printf("Order ID Is Too Long!!!\n");
				}

				for (stock = 0; stock < i; stock++) {
					while (strcmp(invoiceID, s[stock].invoiceID) == 0) {
						printf("\nInvoice ID Repeated!!");

						printf("\nInvoice ID\t\t: ");
						scanf("%s", &invoiceID);
						rewind(stdin);
					}
				}
			} while (strlen(invoiceID) != 4);

			printf("Sender Name \t\t: ");
			rewind(stdin);
			scanf("%[^\n]", &senderName);

			printf("\nItem Code  \t\t: ");
			scanf("%s", &itemCode);
			rewind(stdin);

			printf("\nQuantity Ordered \t: ");
			scanf("%d", &quantity);
			rewind(stdin);

			printf("\nPrice \t\t\t:");
			scanf("%lf", &price);
			rewind(stdin);



			printf("Comfirm Add Stock? (Y To Comfirm): ");
			scanf("%c", &ans);
			printf("\n");
			rewind(stdin);
			if (toupper(ans) == 'Y') {

				strcpy(s[i].invoiceID, invoiceID);
				strcpy(s[i].senderName, senderName);
				strcpy(s[i].itemCode, itemCode);

				tIPrice = quantity * price;


				s[i].quantity = quantity;
				s[i].price = price;
				s[i].tIPrice = tIPrice;


				fprintf(fp, "%s ", s[i].invoiceID);
				fprintf(fp, "%s\n", s[i].senderName);
				fprintf(fp, "%s ", s[i].itemCode);
				fprintf(fp, "%d ", s[i].quantity);
				fprintf(fp, "%lf ", s[i].price);
				fprintf(fp, "%lf\n\n ", s[i].tIPrice);


				printf("\n\nRecord Successfuly Added...\n\n");

				calculate++;


				fclose(fp);
			}

			printf("\nAdd More Stock?? (Y to Comfirm, X To Exit):");
			rewind(stdin);
			scanf("%c", &add);
			add = toupper(add);

			break;

		case 'X':
			break;
		default:
			printf("Please Input Only Y or X\n");
			printf("Add Stock ? ? (Y for Yes, X to Exit)\n");
			rewind(stdin);
			scanf("%c", &add);
			add = toupper(add);

			break;
		}

	}

	printf("%d Stock Added!!\n", calculate);



}

void searchStock(void)
{
	int i = 0;
	FILE* fp;
	int found;
	Sales s[20];
	int scount;
	char itemCode[5];
	char add;

	fp = fopen("stockInfo.txt", "r");



	if (!fp)
	{
		printf("FILE can't be open");
	}

	while
		(fscanf(fp, "%s", &s[i].invoiceID) != EOF) {
		fscanf(fp, "%[^\n]", &s[i].senderName);
		fscanf(fp, "%s", &s[i].itemCode);
		fscanf(fp, "%d", &s[i].quantity);
		fscanf(fp, "%lf", &s[i].price);
		fscanf(fp, "%lf", &s[i].tIPrice);
		i++;
		scount = i;

	}
	fclose(fp);

	do {
		printf("\n Enter the item code you want to search:");
		rewind(stdin);
		scanf("%s", itemCode);

		found = 0;

		for (i = 0; i < scount; i++) {
			if (strcmp(s[i].itemCode, itemCode) == 0) {
				found = 1;
				printf("Item Code  \t\t: %s\n", s[i].itemCode);
				printf("Available Stock \t: %d\n", s[i].quantity);
				printf("Price \t\t\t: %.2f\n", s[i].price);


			}
		}

		if (!found) {
			printf("Invalid Item Code(%s)\n", itemCode);
		}

		printf("More Item To Search? (Y to Confirm) : ");
		rewind(stdin);
		scanf("%c", &add);

	} while (toupper(add) == 'Y');


}


void modifyStock(void)
{
	int i = 0;
	FILE* fp;
	int found;
	Sales s[20];
	int scount;
	char invoiceID[5];
	char senderName[30];
	char itemCode[5];
	int quantity;
	double price = 0;
	double tIPrice = 0;
	char add, ans;
	fp = fopen("stockInfo.txt", "r");



	if (!fp)
	{
		printf("fILE can't be open");
		exit(-1);
	}

	while
		(fscanf(fp, "%s", &s[i].invoiceID) != EOF) {
		fscanf(fp, "%[^\n]", &s[i].senderName);
		fscanf(fp, "%s", &s[i].itemCode);
		fscanf(fp, "%d", &s[i].quantity);
		fscanf(fp, "%lf", &s[i].price);
		fscanf(fp, "%lf", &s[i].tIPrice);
		i++;
		scount = i;

	}
	fclose(fp);

	fp = fopen("stockInfo.txt", "w");

	if (!fp) {
		printf("File Cannot be open!\n");
		exit(-1);
	}

	do {
		do {
			printf("\n Enter the invoice id you want to modify:");
			rewind(stdin);
			scanf("%s", invoiceID);

			if (strlen(invoiceID) < 4) {
				printf("Order ID Is Too Short!!!\n");
			}
			else if (strlen(invoiceID) > 4) {
				printf("Order ID Is Too Long!!!\n");
			}
		} while (strlen(invoiceID) != 4);
		found = 0;

		for (i = 0; i < scount; i++) {
			if (strcmp(s[i].invoiceID, invoiceID) == 0) {
				found = 1;
				printf("Invoice  \t\t: %s\n", s[i].invoiceID);
				printf("Sender Name \t\t:%s\n", s[i].senderName);
				printf("Item Code  \t\t: %s\n", s[i].itemCode);
				printf("Quantity Ordered \t: %d\n", s[i].quantity);
				printf("Price \t\t\t: %.2f\n", s[i].price);
				printf("Total Price \t\t: %.2f\n", s[i].tIPrice);

				printf("\nInvoice ID\t\t: ");
				rewind(stdin);
				scanf("%s", &invoiceID);
				rewind(stdin);

				printf("Sender Name :");
				rewind(stdin);
				scanf("%[^\n]", &senderName);

				printf("\nItem Code  \t\t:");
				scanf("%s", &itemCode);
				rewind(stdin);

				printf("\nQuantity Ordered \t:");
				scanf("%d", &quantity);
				rewind(stdin);

				printf("\nPrice \t\t\t:");
				scanf("%lf", &price);
				rewind(stdin);


				printf("Comfirm Modify Invoice? (Y To Comfirm): ");
				scanf("%c", &ans);
				printf("\n");
				rewind(stdin);
				if (toupper(ans) == 'Y') {
					strcpy(s[i].invoiceID, invoiceID);
					strcpy(s[i].senderName, senderName);
					strcpy(s[i].itemCode, itemCode);

					tIPrice = quantity * price;

					s[i].quantity = quantity;
					s[i].price = price;
					s[i].tIPrice = tIPrice;
					printf("\n\nRecord Successfuly Modified...\n\n");
				}

			}
		}

		if (!found) {
			printf("Invalid Invoice ID(%s)\n", invoiceID);
		}

		printf("More Invoice To modify? (Y to Confirm) : ");
		rewind(stdin);
		scanf("%c", &add);

	} while (toupper(add) == 'Y');

	for (i = 0; i < scount; i++) {
		fprintf(fp, "%s ", s[i].invoiceID);
		fprintf(fp, "%s \n", s[i].senderName);
		fprintf(fp, "%s ", s[i].itemCode);
		fprintf(fp, "%d ", s[i].quantity);
		fprintf(fp, "%lf ", s[i].price);
		fprintf(fp, "%lf\n\n ", s[i].tIPrice);

	}


	fclose(fp);


}

void deleteStock(void) {
	int i = 0;
	FILE* fp;
	int found;
	Sales s[20];
	int scount = 0;
	char invoiceID[5];

	char add, ans;
	int deleteIndex = 0;
	fp = fopen("stockInfo.txt", "r");



	if (!fp)
	{
		printf("fILE can't be open");
		exit(-1);
	}

	while
		(fscanf(fp, "%s", &s[i].invoiceID) != EOF) {
		fscanf(fp, "%[^\n]", &s[i].senderName);
		fscanf(fp, "%s", &s[i].itemCode);
		fscanf(fp, "%d", &s[i].quantity);
		fscanf(fp, "%lf", &s[i].price);
		fscanf(fp, "%lf", &s[i].tIPrice);
		i++;
		scount = i;
	}


	fclose(fp);

	fp = fopen("stockInfo.txt", "w");

	if (!fp) {
		printf("File Cannot be open!\n");
		exit(-1);
	}

	do {
		do {
			printf("\n Enter the invoice id you want to delete:");
			rewind(stdin);
			scanf("%s", invoiceID);
			if (strlen(invoiceID) < 4) {
				printf("Order ID Is Too Short!!!\n");
			}
			else if (strlen(invoiceID) > 4) {
				printf("Order ID Is Too Long!!!\n");
			}
		} while (strlen(invoiceID) != 4);
		found = 0;

		for (i = 0; i < scount; i++) {
			if (strcmp(s[i].invoiceID, invoiceID) == 0) {
				found = 1;
				printf("Invoice  \t\t: %s\n", s[i].invoiceID);
				printf("Sender Name \t\t:%s\n", s[i].senderName);
				printf("Item Code  \t\t: %s\n", s[i].itemCode);
				printf("Quantity Ordered \t: %d\n", s[i].quantity);
				printf("Price \t\t\t: %.2f\n", s[i].price);
				printf("Total Price \t\t: %.2f\n", s[i].tIPrice);

				printf("Comfirm delete Sales Order? (Y To Comfirm): ");
				rewind(stdin);
				scanf("%c", &ans);

				printf("\n");
				rewind(stdin);
				if (toupper(ans) == 'Y') {
					deleteIndex = i;

					for (i = deleteIndex; i < scount; i++) {
						s[i] = s[i + 1];

						scount--;


						printf("\n\nRecord Successfuly Deleted...\n\n");
					}
				}
			}
		}

		if (!found) {
			printf("Invalid Invoice ID(%s)\n", invoiceID);
		}

		printf("More Invoice To delete? (Y to Confirm) : ");
		rewind(stdin);
		scanf("%c", &add);

	} while (toupper(add) == 'Y');

	for (i = 0; i < scount; i++) {
		fprintf(fp, "%s ", s[i].invoiceID);
		fprintf(fp, "%s\n", s[i].senderName);
		fprintf(fp, "%s ", s[i].itemCode);
		fprintf(fp, "%d ", s[i].quantity);
		fprintf(fp, "%lf ", s[i].price);
		fprintf(fp, "%lf \n\n", s[i].tIPrice);

	}

	fclose(fp);
}


void stockReport(void)
{
	int tInvoice = 0;
	FILE* fp;
	Sales s[20];
	int i = 0;
	int stock;
	fp = fopen("stockInfo.txt", "r");



	if (!fp)
	{
		printf("File can't be open");
		exit(-1);
	}

	while
		(fscanf(fp, "%s", &s[i].invoiceID) != EOF) {
		fscanf(fp, "%[^\n]", &s[i].senderName);
		fscanf(fp, "%s", &s[i].itemCode);
		fscanf(fp, "%d", &s[i].quantity);
		fscanf(fp, "%lf", &s[i].price);
		fscanf(fp, "%lf", &s[i].tIPrice);

		i++;

	}
	printf("============================================================\n");
	printf("===================\t  MING JIAN  \t====================\n");
	printf("===================\t   SDN BHD   \t====================\n");
	printf("============================================================\n\n");

	tInvoice = i;
	printf("Total Invoice: %d\n", tInvoice);
	printf("Item Code\tQuantity\n");
	printf("______________________________\n");
	for (stock = 0; stock < i; stock++) {

		printf("%7s\t%15d\n", s[stock].itemCode, s[stock].quantity);
	}

	time_t t;
	t = time(NULL);
	struct tm tm = *localtime(&t);
	printf("\n\n\nCurrent Date\t: %d-%d-%d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
	printf("Current Time\t: %d:%d:%d\n\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
	printf("=============================================================\n");
	printf("=============================================================\n");
	return 0;



}