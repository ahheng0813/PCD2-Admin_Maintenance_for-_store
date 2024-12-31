#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

void main() {
	int choice;

	printf("\t\t=================================================================\n");
	printf("\t\t  .____.__.____.__.____.  .___.          .____.__.____.__.____.\n");
	printf("\t\t  |                    |  |   |          |                    |\n");
	printf("\t\t  |     __      __     |  |   |          |     __      __     |\n");
	printf("\t\t  |    |  |    |  |    |  |   |          |    |  |    |  |    |\n");
	printf("\t\t  |    |  |    |  |    |  |   |          |    |  |    |  |    |\n");
	printf("\t\t  |    |  |    |  |    |  |   |          |    |  |    |  |    |\n");
	printf("\t\t  |    |  |____|  |    |  |   |________. |    |  |____|  |    |\n");
	printf("\t\t  |____|          |____|  |____________| |____|          |____|\n");
	printf("\t\t=================================================================\n");

	printf("\n");
	do {
		printf("=============\n");
		printf("  Main Menu  \n");
		printf("=============\n");
		printf("1.Member Menu\n");
		printf("2.Staff Menu\n");
		printf("3.Sales Menu\n");
		printf("4.Stock Menu\n");
		printf("5.Exit\n");

		printf("\nSelect a Menu: ");
		rewind(stdin);
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			member();
			break;
		case 2:
			staff(); 
			break;
		case 3:
			sales();
			break;
		case 4:
			stock();
			break;
		case 5:
			break;
		default:
			printf("\n");
			printf("  ==============================\n");
			printf("   ! Invalid Value (Only 1-5) ! \n");
			printf("  ==============================\n\n");
			break;
		}
	} while (choice != 5);
	system("pause");
}