#include <stdio.h>
#include <conio.h>
#include <windows.h>

#include <time.h> // for random seed generator

#define MAP_X 10
#define MAP_Y 10
#define BLOCKS 10

void instructions() {
	getch();
}

int startingMenu() {
	int option = -1;
	printf(
		"Ghostless Pac-man:\n"
		"Choose an option :\n"
		"(1) Start game\n"
		"(2) Instructions\n"
		"(3) Exit\n\n"
		"Enter option: "
	);
	scanf("%d", &option);
	while ((getchar()) != '\n');

	return option;
}

int getFoodRange() {
	int range;
	char query[] = "How many food do you want to be distributed in the board? (range of 2-9)\t";

	printf(query);
	scanf("%d", &range);
	while ((getchar()) != '\n');

	while (!(range >= 2 && range <= 9)) {
		printf("Please put a number within the range of 2-9! Please try again.\n");
		Sleep(1000);
		printf(query);
		scanf("%d", &range);
	}

	return range;
}

int pauseMenu() {
	system("cls");
	printf(
		"Ghostless Pac-man:\n"
		"Choose an option :\n"
		"(1) Resume game\n"
		"(2) Instructions\n"
		"(3) Exit\n\n"
		"Enter option: "
	);
		
	int option = -1;
	scanf("%d", &option);

	while((getchar())!='\n');

	switch (option) {
	case 1:
		break;
	case 2:
		instructions();
		pauseMenu();
		break;
	case 3:
		option = 0;
		break;
	default:
		printf("Please pick within the options!\n");
		Sleep(1000);
		pauseMenu();
		break;
	}
	system("cls");
	return option;
}

void getUserInput(int* xy) {
	switch (tolower(getch())) {
	case 'w':
		xy[0] += -1;
		xy[1] += 0;
		break;
	case 's':
		xy[0] += 1;
		xy[1] += 0;
		break;
	case 'd':
		xy[0] += 0;
		xy[1] += 1;
		break;
	case 'a':
		xy[0] += 0;
		xy[1] += -1;
		break;
	case 'm':
		if (!pauseMenu())
			xy[0] = 2;
		break;
	default:
		break;
	}
}

int gameLoop() {
	srand(time(NULL));

	int range = getFoodRange();

	int map[MAP_X][MAP_Y] = { 0 };				// generate air

	int x = rand() % MAP_X;
	int y = rand() % MAP_Y;

	map[x][y] = 1;							// generate exit

	int blocks = BLOCKS;
	while (blocks > 0) {
		x = rand() % MAP_X;
		y = rand() % MAP_Y;

		if (map[x][y] == 0) {
			map[x][y] = 2;					// generate blocks
			blocks--;
		}
	}

	int foodsToPrint = range;
	while (foodsToPrint > 0) {
		x = rand() % MAP_X;
		y = rand() % MAP_Y;

		if (map[x][y] == 0 && x != 0 && y != 0) {
			map[x][y] = 3;					// generate food
			foodsToPrint--;
		}
	}

	int xy[2] = { 0 };
	int remainingFood = range;

	while (1) {					// game loop
		system("cls");

		switch (map[xy[0]][xy[1]]) {		// check user position
		case 0:
			map[xy[0]][xy[1]] = 4;
			break;
		case 1:
			if (!remainingFood)
				return 1;
			break;
		case 2:
			return 0;
			break;
		case 3:
			remainingFood--;
			map[xy[0]][xy[1]] = 4;
			break;
		}

		for (int x = 0; x < 10; x++) {
			printf("|");
			for (int y = 0; y < 10; y++) {
				switch (map[x][y]) {
				case 0:
					printf(" |");
					break;
				case 1:
					printf("$|");
					break;
				case 2:
					printf("#|");
					break;
				case 3:
					printf("*|");
					break;
				case 4:
					printf("O|");
					break;
				}
			}
			printf("\n");
		}

		if (!(remainingFood && map[xy[0]][xy[1]] == 1))
			map[xy[0]][xy[1]] = 0;						// clear last user position

		if (_kbhit())
			getUserInput(&xy);

		if (xy[0] == 2)
			return 0;

		printf("Remaining food: %d\n", remainingFood);

		Sleep(10);
	}
}

int main() {
	system("cls");
	
	while (1) {
		switch (startingMenu()) {
		case 1:
			gameLoop();
			break;
		case 2:
			instructions();
			break;
		case 3:
			return 0;
			break;
		default:
			printf("Please pick within the options!\n");
			Sleep(1000);
			break;
		}
		system("cls");
	}

	return 0;
}