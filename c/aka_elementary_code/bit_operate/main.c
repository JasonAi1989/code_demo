#include <stdio.h>
#include <stdlib.h>
#include "d2b.h"
#include "exchange.h"
#include "encryption.h"
#include "multi.h"
#include "common.h"

int main(int argc, char *argv[])
{
	int choice;
	while (1) {
		printf("1.decimal to bilary\n");
		printf("2.x * y\n");
		printf("3.low or up exchange\n");
		printf("4.encryption\n");
		printf("5.exit\n");
		printf("please choice [1-5]:");
		if (scanf("%d", &choice) == 0) {
			empty_cache();
			system("clear");
			continue;
		}
		system("clear");
		if (choice >= 1 && choice <= 5) {
			switch (choice) {
			case 1:
				d2b();
				break;
			case 2:
				multi();
				break;
			case 3:
				exchange();
				break;
			case 4:
				encryption();
				break;
			case 5:
				return 0;
			}
		}
	}
	return 0;
}
