#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <Windows.h>
#pragma warning (disable : 4996)
#pragma warning (disable : 6031)


void displaySales(void);
void addSales(void);
void searchSales(void);
void modifySales(void);
void deleteSales(void);
void salesReport(void);
double memDiscount(double totals, double mDiscount);
int selectMenu(int choice);
int finalQuantity(int new, int old);
double totalPrice(double price, double quantity);

void reportHead(void);

typedef struct {
	char memberID[10];
	char memberName[20];
}Member;

typedef struct {
	char sOrderId[5];
	char itemCode[5];
	double price;
	int quantity;
	double discount;
	char payment[10];
	double total;

}Sales;

typedef struct {
	char invoiceID[5];
	char senderName[30];
	char itemCode[5];
	int quantity;
	double price;
	double tIPrice;

}Stock;

sales() {
	int request, option;

	do {
		printf("\n______________________________________");
		printf("\nSelect Option:\n");
		printf("1: Display Sales List\n");
		printf("2: Add Sales\n");
		printf("3: Search Sales Order\n");
		printf("4: Modify Sales\n");
		printf("5: Delete Sales\n");
		printf("6: Sales Report\n");
		printf("7: Exit\n");
		printf("______________________________________");
		printf("\nOption: ");
		scanf("%d", &option);
		rewind(stdin);

		printf("______________________________________\n\n");

		request = selectMenu(option);


	} while (request != 7);


}

int selectMenu(int choice) {
	switch (choice) {
	case 1:
		displaySales();
		break;
	case 2:
		addSales();
		break;
	case 3:
		searchSales();
		break;

	case 4:
		modifySales();
		break;
	case 5:
		deleteSales();
		break;

	case 6:
		salesReport();
		break;

	case 7:
		break;

	default:
		printf("\n\nInvalid Input!! Please Input Only 1-7\n");
		break;

	}


	return choice;

}

void displaySales(void) {

	Sales s[20];
	FILE* fsales;
	int count = 0;
	SYSTEMTIME t;
	int i = 0;
	int found = 0;

	fsales = fopen("salesOrder.bin", "rb");

	if (fsales == NULL)
	{
		printf("\nFile cannot be open !!");
		exit(-1);
	}
	GetLocalTime(&t);
	printf("======================================================================================================================\n");
	printf("=======================================\t         MLM SYSTEM\t      ================================================\n");
	printf("=======================================\t     %d/%d/%d  %d:%d:%d      ================================================\n", t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute, t.wSecond);
	printf("======================================================================================================================\n");
	printf("======================================================================================================================\n");
	printf("=== Sales Order ID\tItem ID\t    Price(RM)\t   Quantity      Discount(RM)\t   Payment Method\tTotal(RM)  ===\n");
	printf("======================================================================================================================");

	while (fread(&s[i], sizeof(Sales), 1, fsales) != 0) {

		found = 1;
		printf("\n\t%10s\t", s[i].sOrderId);
		printf("%7s\t", s[i].itemCode);
		printf("%13.2f\t", s[i].price);
		printf("%11d\t", s[i].quantity);
		printf("%13.2f\t", s[i].discount);
		printf("\t%9s\t", s[i].payment);
		printf("%9.2lf", s[i].total);

	}
	if (found != 1) {
		printf("\n\t\t\t\t\t No Sales Order ID Exist!!!\n\n");
	}

	fclose(fsales);
}

void addSales(void) {
	Sales s[20];
	Member m[20];
	Stock o[20];
	FILE* fsales, * fmember, * fstock;
	char add;
	int record = 0;
	int i = 0;
	char sOrderID[5];
	int order = 0, member = 0;
	char mem;
	char memberID[10];
	char itemCode[5];
	double finalTotal = 0;
	double mDiscount;
	double total = 0;
	int memberFound = 0;
	int memberS = 0;
	int k = 0, z = 0;
	int stockFound = 0;
	int stock = 0;
	double totalQuantity = 0, currentQuantity = 0;


	fstock = fopen("stockInfo.txt", "r");

	if (fstock == NULL) {
		printf("\nFILE CAN'T BE OPEN\n");
	}
	while
		(fscanf(fstock, "%s", &o[z].invoiceID) != EOF) {
		fscanf(fstock, "%[^\n]", &o[z].senderName);
		fscanf(fstock, "%s", &o[z].itemCode);
		fscanf(fstock, "%d", &o[z].quantity);
		fscanf(fstock, "%lf", &o[z].price);
		fscanf(fstock, "%lf", &o[z].tIPrice);

		z++;
	}


	fclose(fstock);


	printf("\n\nAdd Sales Order ?  (Y to Comfirm X to Exit)");

	scanf("%c", &add);
	add = toupper(add);
	rewind(stdin);

	while (add == 'Y') {

		do {
			fsales = fopen("salesOrder.bin", "rb");

			if (fsales == NULL)
			{
				printf("\n\nFile cannot be open !!");
				exit(-1);
			}

			while (fread(&s[i], sizeof(Sales), 1, fsales)) {
				i++;
			}

			fclose(fsales);


			fsales = fopen("salesOrder.bin", "ab");

			if (fsales == NULL)
			{
				printf("\n\nFile cannot be open !!");
				exit(-1);
			}



			printf("Sales Order ID: ");
			scanf("%[^\n]", &sOrderID);
			rewind(stdin);

			if (strlen(sOrderID) < 4) {
				shortID();
			}
			else if (strlen(sOrderID) > 4) {
				longID();
			}

			for (order = 0; order < i; order++) {
				while (strcmp(sOrderID, s[order].sOrderId) == 0) {
					printf("Sales ID Repeated!!\n");

					printf("Sales Order ID: ");
					scanf("%[^\n]", &sOrderID);
					rewind(stdin);

				}

			}
			strcpy(s[i].sOrderId, sOrderID);

		} while (strlen(sOrderID) != 4);



		do {

			do {

				printf("\nItem Code : ");
				scanf("%s", &itemCode);
				rewind(stdin);

				stockFound = 0;

				if (strlen(itemCode) < 4) {
					shortID();
				}
				else if (strlen(itemCode) > 4) {
					longID();
				}

			} while (strlen(itemCode) != 4);


			for (stock = 0; stock < z; stock++) {
				if (strcmp(itemCode, o[stock].itemCode) == 0) {
					stockFound = 1;
					printf("\nQuantity :");
					scanf("%d", &s[i].quantity);
					rewind(stdin);

					fstock = fopen("stockInfo.txt", "w");

					if (fstock == NULL)
					{
						printf("\nFILE CAN'T BE OPEN\n");
						exit(-1);
					}

					currentQuantity = o[stock].quantity;
					o[stock].quantity = finalQuantity(s[i].quantity, currentQuantity);

					strcpy(s[i].itemCode, itemCode);

					s[i].price = o[stock].price;
				}


			}
			if (stockFound == 0) {
				printf("\nInvalid Item ID!!!\n");

			}
		} while (stockFound == 0);



		for (stock = 0; stock < z; stock++) {
			fprintf(fstock, "%s ", o[stock].invoiceID);
			fprintf(fstock, "%s\n", o[stock].senderName);
			fprintf(fstock, "%s ", o[stock].itemCode);
			fprintf(fstock, "%d ", o[stock].quantity);
			fprintf(fstock, "%lf ", o[stock].price);
			fprintf(fstock, "%lf\n\n ", o[stock].tIPrice);
		}

		fclose(fstock);




		printf("\nPayment Method:");
		scanf("%[^\n]", s[i].payment);
		rewind(stdin);

		fmember = fopen("member.txt", "r");

		if (!fmember) {
			printf("File cannot be open");
			exit(-1);

		}


		while (fscanf(fmember, "%[^\|]|", &m[k].memberID) != EOF) {
			k++;
		}


		fclose(fmember);


		total = totalPrice(s[i].price, s[i].quantity);


		printf("\nMember ? (Y to comfirm):");
		rewind(stdin);
		scanf("%c", &mem);

		if (toupper(mem) == 'Y')
		{
			do {


				printf("\nMember ID:");
				rewind(stdin);
				scanf("%[^\n]", &memberID);



				for (memberS = 0; memberS < k; memberS++) {
					if (strcmp(memberID, m[memberS].memberID) == 0) {
						memberFound = 1;
						mDiscount = 0.95;
						finalTotal = memDiscount(total, mDiscount);
						s[i].total = finalTotal;
						s[i].discount = total - finalTotal;

					}


				}
				if (!memberFound) {
					printf("\nInvalid Member ID!!\n");
				}

			} while (memberFound == 0);

		}
		else {

			s[i].discount = 0;

			s[i].total = total;

		}

		rewind(stdin);


		fwrite(&s[i], sizeof(Sales), 1, fsales);


		printf("\nRecord Successfully Added...\n\n");

		record++;


		printf("Add another record (Y=yes)? ");

		scanf("%c", &add);
		add = toupper(add);
		rewind(stdin);

		fclose(fsales);
	}




}

double memDiscount(double totals, double mDiscount) {
	double totalDiscount;

	totalDiscount = totals * mDiscount;

	return totalDiscount;
}

int finalQuantity(int new, int old) {
	int totalQuantity;

	totalQuantity = old - new;
	return totalQuantity;

}

double totalPrice(double price, double quantity) {
	double total;

	total = price * quantity;

	return total;
}

void searchSales(void) {
	char cont;
	int i = 0;
	int sCount;
	int found;
	char sOrderId[5];

	Sales s[20];
	FILE* fsales;


	fsales = fopen("salesOrder.bin", "rb");

	if (fsales == NULL)
	{
		printf("\n\nFile cannot be open !!");
		exit(-1);
	}

	while (fread(&s[i], sizeof(Sales), 1, fsales))
		i++;
	sCount = i;
	fclose(fsales);

	do {
		do {
			printf("\n\nEnter the sales id to be search:");
			rewind(stdin);
			scanf("%[^\n]", sOrderId);

			found = 0;


			if (strlen(sOrderId) < 4) {
				printf("Order ID Is Too Short Like You!!!\n");
			}
			else if (strlen(sOrderId) > 4) {
				printf("Order ID Is Too Long Like Ming Jian\n");
			}

			for (i = 0; i < sCount; i++) {

				if (strcmp(sOrderId, s[i].sOrderId) == 0) {
					found = 1;
					printf("\n\nSales Order ID  : %s\n", s[i].sOrderId);
					printf("Item ID\t\t: %s\n", s[i].itemCode);
					printf("Price\t\t: RM%.2f\n", s[i].price);
					printf("Quantity\t: %d\n", s[i].quantity);
					printf("Discount\t: RM%.2f\n", s[i].discount);
					printf("Payment Method\t: %s\n", s[i].payment);
					printf("Total \t\t: RM%.2f\n", s[i].total);
				}
			}

		} while (strlen(sOrderId) != 4);


		if (!found)
			printf("\nInvalid Sales ID (%s)\n", sOrderId);
		printf("\nMore sales order to search? (Y=yes) : ");
		rewind(stdin);
		scanf("%c", &cont);

	} while (toupper(cont) == 'Y');

}

void modifySales(void) {
	char ans, cont;
	int i = 0, modiCount = 0;
	int sCount;
	int found;
	char sOrderId[5];
	int quantity;
	char itemCode[5];
	double price;
	double discount;
	char payment[10];
	double total;

	Sales s[20];
	FILE* fsales;


	fsales = fopen("salesOrder.bin", "rb");

	if (fsales == NULL)
	{
		printf("\n\nFile cannot be open !!");
		exit(-1);
	}

	while (fread(&s[i], sizeof(Sales), 1, fsales))
		i++;
	sCount = i;
	fclose(fsales);



	do {
		do {
			printf("\n\nEnter the sales id to be modify:");
			rewind(stdin);
			scanf("%[^\n]", sOrderId);

			found = 0;


			if (strlen(sOrderId) < 4) {
				printf("\nOrder ID Is Too Short Like You!!!\n");
			}
			else if (strlen(sOrderId) > 4) {
				printf("\nOrder ID Is Too Long Like Ming Jian\n");
			}


			for (i = 0; i < sCount; i++) {

				if (strcmp(sOrderId, s[i].sOrderId) == 0) {
					found = 1;
					printf("\n\nSales Order ID  : %s\n", s[i].sOrderId);
					printf("Item ID\t\t: %s\n", s[i].itemCode);
					printf("Price\t\t: RM%.2f\n", s[i].price);
					printf("Quantity\t: %d\n", s[i].quantity);
					printf("Discount\t: RM%.2f\n", s[i].discount);
					printf("Payment Method\t: %s\n", s[i].payment);
					printf("Total \t\t: RM%.2f\n", s[i].total);

					printf("\nItem Code : ");
					scanf("%s", &itemCode);
					rewind(stdin);

					printf("\nItem Price :");
					scanf("%lf", &price);
					rewind(stdin);

					printf("\nQuantity :");
					scanf("%d", &quantity);
					rewind(stdin);

					printf("\nDiscount :");
					scanf("%lf", &discount);
					rewind(stdin);

					printf("\nPayment Method:");
					scanf("%[^\n]", payment);
					rewind(stdin);

					total = price * quantity - discount;

					printf("Confirm To Modify (Y=yes)? ");
					rewind(stdin);
					scanf("%c", &ans);
					if (toupper(ans) == 'Y') {
						strcpy(s[i].itemCode, itemCode);
						s[i].price = price;
						s[i].quantity = quantity;
						s[i].discount = discount;
						strcpy(s[i].payment, payment);
						s[i].total = total;
						modiCount++;

						printf("\n\nModify Completed!!\n");
					}

					printf("\n\nSales Order ID  : %s\n", s[i].sOrderId);
					printf("Item ID\t\t: %s\n", s[i].itemCode);
					printf("Price\t\t: RM%.2f\n", s[i].price);
					printf("Quantity\t: %d\n", s[i].quantity);
					printf("Discount\t: RM%.2f\n", s[i].discount);
					printf("Payment Method\t: %s\n", s[i].payment);
					printf("Total \t\t: RM%.2f\n", s[i].total);
				}
			}
		} while (strlen(sOrderId) != 4);

		if (!found)
			printf("\nInvalid Sales ID (%s)\n", sOrderId);

		printf("\nAny more sales order to modify? (Y=yes) : ");
		rewind(stdin);
		scanf("%c", &cont);

	} while (toupper(cont) == 'Y');

	fsales = fopen("salesOrder.bin", "wb");

	if (fsales == NULL)
	{
		printf("\n\nFile cannot be open !!\n");
		exit(-1);
	}

	for (i = 0; i < sCount; i++)
		fwrite(&s[i], sizeof(Sales), 1, fsales);
	fclose(fsales);
	printf("\n%d Record(s) modified\n\n", modiCount);

}

void deleteSales(void) {
	char ans, cont;
	int i = 0;
	int sCount;
	int found = 0;
	char sOrderId[5];

	Sales s[20];
	FILE* fsales, * fsales_temp;

	fsales = fopen("salesOrder.bin", "rb");

	if (!fsales) {
		printf("\nFile Cannot Be Open!!\n");
		exit(-1);
	}
	fsales_temp = fopen("tmp.bin", "wb");
	if (!fsales_temp) {
		printf("\nFile Cannot Be Open!!\n");
		exit(-1);
	}

	while (fread(&s[i], sizeof(Sales), 1, fsales))
		i++;
	sCount = i;
	fclose(fsales);
	do {
		do {
			do {
				printf("\nPlease Insert The Sales Order ID TO DELETE:");
				rewind(stdin);
				scanf("%[^\n]", sOrderId);


				if (strlen(sOrderId) < 4) {
					printf("Order ID Is Too Short Like You!!!\n");
				}
				else if (strlen(sOrderId) > 4) {
					printf("Order ID Is Too Long Like Ming Jian\n");
				}
			} while (strlen(sOrderId) != 4);

			for (i = 0; i < sCount; i++) {

				if (strcmp(sOrderId, s[i].sOrderId) == 0) {
					found = 1;
					printf("\n\nSales Order ID  : %s\n", s[i].sOrderId);
					printf("Item ID\t\t: %s\n", s[i].itemCode);
					printf("Price\t\t: RM%.2f\n", s[i].price);
					printf("Quantity\t: %d\n", s[i].quantity);
					printf("Discount\t: RM%.2f\n", s[i].discount);
					printf("Payment Method\t: %s\n", s[i].payment);
					printf("Total \t\t: RM%.2f\n", s[i].total);


					printf("\nConfirm To Delete (Y=yes)? ");
					rewind(stdin);
					scanf("%c", &ans);

					if (toupper(ans) == 'Y') {
						printf("\nSales Order Had Been Deleted!!\n");

					}
					else
						fwrite(&s[i], sizeof(Sales), 1, fsales_temp);
				}
				else {
					fwrite(&s[i], sizeof(Sales), 1, fsales_temp);
				}

			}

		} while (strlen(sOrderId) != 4);

		if (!found)
			printf("\nInvalid Sales ID (%s)\n", sOrderId);

		printf("\nAny more sales order to DELETE? (Y=yes) : ");
		rewind(stdin);
		scanf("%c", &cont);

	} while (toupper(cont) == 'Y');


	fclose(fsales_temp);

	remove("salesOrder.bin");
	rename("tmp.bin", "salesOrder.bin");



}

void salesReport(void) {
	Sales s[20];
	FILE* fsales;
	int count;
	int i = 0;
	int found = 0;
	int totalQuantity = 0;
	double totalPrice = 0;
	SYSTEMTIME t;

	GetLocalTime(&t);

	fsales = fopen("salesOrder.bin", "rb");

	if (fsales == NULL)
	{
		printf("\nFile cannot be open !!");
		exit(-1);
	}

	reportHead();

	while (fread(&s[i], sizeof(Sales), 1, fsales) != 0)
		i++;
	count = i;
	fclose(fsales);

	for (i = 0; i < count; i++) {
		found = 1;
		totalQuantity = totalQuantity + s[i].quantity;
		totalPrice = totalPrice + s[i].total;
	}
	printf("\n\tEnd Terminal Date : %d/%d/%d\n", t.wDay, t.wMonth, t.wYear);
	printf("\tTime \t\t  : %d:%d:%d\n\n", t.wHour, t.wMinute, t.wSecond);
	printf("\n\tTotal Sales Order \t: %d", i);
	printf("\n\tTotal Item Sold\t\t: %d", totalQuantity);
	printf("\n\tTotal Profits\t\t: %0.2lf\n\n", totalPrice);
	printf("======================================================================================================================\n");
	printf("======================================================================================================================\n");
	if (!found)
		printf("\nNO RECORD EXIST!!\n");

}


void reportHead(void) {

	SYSTEMTIME t;

	GetLocalTime(&t);
	printf("======================================================================================================================\n");
	printf("=======================================\t         MLM SYSTEM\t     =================================================\n");
	printf("=======================================\t     %d/%d/%d  %d:%d:%d     ==================================================\n", t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute, t.wSecond);
	printf("======================================================================================================================\n");
}