// Standard Libraries
#include <stdio.h>
#include <ctype.h>
#include <time.h>

// Windows-Dependent Libraries
#include <conio.h>
#include <Windows.h>

// Map Settings
#define MAP_X 10
#define MAP_Y 10
#define BLOCKS 10

// Display Configuration
#define AIR ' '
#define BLOCK '#'
#define FOOD '*'
#define EXIT '$'
#define PLAYER 'O'

// Game States
#define GAME_STOPPED -2
#define GAME_LOST -1
#define GAME_PAUSED 0
#define GAME_PLAYING 1
#define GAME_WON 2

// Title
void printTitle() {
	printf(	
" ______     __  __     ______     ______     ______   __         ______     ______     ______                         	\n"
"/\\  ___\\   /\\ \\_\\ \\   /\\  __ \\   /\\  ___\\   /\\__  _\\ /\\ \\       /\\  ___\\   /\\  ___\\   /\\  ___\\                        	\n"
"\\ \\ \\__ \\  \\ \\  __ \\  \\ \\ \\/\\ \\  \\ \\___  \\  \\/_/\\ \\/ \\ \\ \\____  \\ \\  __\\   \\ \\___  \\  \\ \\___  \\                       	\n"
" \\ \\_____\\  \\ \\_\\ \\_\\  \\ \\_____\\  \\/\\_____\\    \\ \\_\\  \\ \\_____\\  \\ \\_____\\  \\/\\_____\\  \\/\\_____\\                      	\n"
"  \\/_____/   \\/_/\\/_/   \\/_____/   \\/_____/     \\/_/   \\/_____/   \\/_____/   \\/_____/   \\/_____/                      	\n"
"                                                                                                                      	\n"
"                                                    ______   ______     ______     __    __     ______     __   __    	\n"
"                                                   /\\  == \\ /\\  __ \\   /\\  ___\\   /\\ \"-./  \\   /\\  __ \\   /\\ \"-.\\ \\   	\n"
"                                                   \\ \\  _-/ \\ \\  __ \\  \\ \\ \\____  \\ \\ \\-./\\ \\  \\ \\  __ \\  \\ \\ \\-.  \\  	\n"
"                                                    \\ \\_\\    \\ \\_\\ \\_\\  \\ \\_____\\  \\ \\_\\ \\ \\_\\  \\ \\_\\ \\_\\  \\ \\_\\\\\"\\_\\ 	\n"
"                                                     \\/_/     \\/_/\\/_/   \\/_____/   \\/_/  \\/_/   \\/_/\\/_/   \\/_/ \\/_/ 	\n\n\n");
}

// Instructions
void instructions() {
	system("cls");
	printTitle();
	printf("+ Objective:\n\n"
				"    - Collect all foods before entering the exit to win the game.\n\n"
			"+ Navigation:\n\n"
				"    - To control Pacman, the characters W, S, A and D are used. W is used to make it move UP, S to move DOWN, A to go LEFT and D to move RIGHT. When Pacman collides with any blocks, boundaries or the exit without eating all the food, the game ends and you loses.\n\n"
			"+ Collecting Food:\n\n"
				"    - Foods will be randomly distributed across the board indicated by '*'. A progress indicator at the bottom left of the game will indicate your food collection progress.\n\n"
			"+ Exit:\n\n"
				"    - The game will end when Pacman eats all the food and enters the exit. There will be a '$' to indicate the exit point. Once Pacman steps on the exit after collecting all the foods, the game will be done and the you will win.\n\n");
	printf("\nPress any key to continue... ");
	_getch();
	system("cls");
}

// Menus
int mainMenu() {
	int option = -1;
	printTitle();
	printf(
		"Choose an option:\n"
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
	system("cls");
	printTitle();

	int range;
	char query[] = "How many food do you want to be distributed in the board? (range of 2-9): ";

	printf(query);
	scanf("%d", &range);
	while ((getchar()) != '\n');

	if (!(range >= 2 && range <= 9)) {
		printf("Please put a number within the range of 2-9! Please try again.");
		Sleep(1000);
		range = getFoodRange();
	}

	return range;
}

void pauseMenu(int *gameState) {
	system("cls");

	printTitle();

	int option = -1;
	printf(
		"Choose an option:\n"
		"(1) Resume game\n"
		"(2) Instructions\n"
		"(3) Exit\n\n"
		"Enter option: "
	);

	scanf("%d", &option);
	while ((getchar()) != '\n');

	switch (option) {
	case 1:
		*gameState = GAME_PLAYING;
		return;
	case 2:
		instructions();
		pauseMenu(gameState);
		break;
	case 3:
		*gameState = GAME_STOPPED;
		return;
	default:
		printf("Please pick within the options!");
		Sleep(1000);
		pauseMenu(gameState);
		break;
	}

	system("cls");
}

// Game Loop

// Function Declarations
void generateBlocks(char map[MAP_X][MAP_Y], int range);															// function 1
void generateFoods(char map[MAP_X][MAP_Y], int range);															// function 2
int checkGameStatus(char map[MAP_X][MAP_Y], int playerPositionX, int playerPositionY, int* remainingFood);		// function 3
void printPlayerStatus(int gameState, int remainingFood, int numOfFoods);										// function 4

void fillAir(char map[MAP_X][MAP_Y]) {
	for (int y = 0; y < MAP_Y; y++)
		for (int x = 0; x < MAP_X; x++)
			map[x][y] = AIR;
}

void generateBlocks(char map[MAP_X][MAP_Y], int numOfBlocks) {
	int x, y;

	while (numOfBlocks > 0) {
		x = rand() % MAP_X;
		y = rand() % MAP_Y;

		if (map[x][y] == AIR && !(x == 0 && y == 0) && !(x == 0 && y == 1) && !(x == 1 && y == 0)) {
			map[x][y] = BLOCK;
			numOfBlocks--;
		}
	}
}

void generateFoods(char map[MAP_X][MAP_Y], int numOfFoods) {
	int x, y;

	while (numOfFoods > 0) {
		x = rand() % MAP_X;
		y = rand() % MAP_Y;

		if (map[x][y] == AIR && !(x == 0 && y == 0) && !(x == 0 && y == 1) && !(x == 1 && y == 0)) {
			map[x][y] = FOOD;
			numOfFoods--;
		}
	}
}

void generateExit(char map[MAP_X][MAP_Y]) {
	int x, y;
	int numberOfExits = 1;

	while (numberOfExits > 0) {
		x = rand() % MAP_X;
		y = rand() % MAP_Y;

		if (map[x][y] == AIR && !(x == 0 && y == 0) && !(x == 0 && y == 1) && !(x == 1 && y == 0)) {
			map[x][y] = EXIT;
			numberOfExits--;
		}
	}
}

void printMap(char map[MAP_X][MAP_Y]) {
	system("cls");
	printTitle();

	printf("\t\t\t\t\t+");
	for (int x=0; x< MAP_X; x++) 
		printf("---+");
	printf("\n");

	for (int y = 0; y < MAP_Y; y++) {
		printf("\t\t\t\t\t|");
		for (int x = 0; x < MAP_X; x++) {
			printf(" %c |", map[x][y]);
		}
		printf("\n");
		
		printf("\t\t\t\t\t+");
		for (int x=0; x< MAP_X; x++) 
			printf("---+");
		printf("\n");
	}
}

void printPlayer(char map[MAP_X][MAP_Y], int playerPositionX, int playerPositionY) {
	char updatedMap[MAP_X][MAP_Y];

	for (int y = 0; y < MAP_Y; y++)
		for (int x = 0; x < MAP_X; x++)
			updatedMap[x][y] = map[x][y];

	updatedMap[playerPositionX][playerPositionY] = PLAYER;
	printMap(updatedMap);

	if (map[playerPositionX][playerPositionY] == FOOD)
		map[playerPositionX][playerPositionY] = AIR;
}

int checkGameStatus(char map[MAP_X][MAP_Y], int playerPositionX, int playerPositionY, int *remainingFood) {
	if (playerPositionX < 0 || playerPositionX > MAP_X - 1 || playerPositionY < 0 || playerPositionY > MAP_Y - 1)
		return GAME_LOST;
		
	switch (map[playerPositionX][playerPositionY]) {
	case BLOCK:
		return GAME_LOST;
	case FOOD:
		(*remainingFood)--;
		return GAME_PLAYING;
	case EXIT:
		if (!(*remainingFood))
			return GAME_WON;
		else
			return GAME_LOST;
		break;
	default:
		return GAME_PLAYING;
	}
}

void getUserInput(int *playerX, int *playerY, int *gameState) {
	switch (toupper(_getch())) {
	case 'M':
		*gameState = GAME_PAUSED;
		break;
	case 'W':
		*playerY += -1;
		break;
	case 'S':
		*playerY += 1;
		break;
	case 'D':
		*playerX += 1;
		break;
	case 'A':
		*playerX += -1;
		break;
	default:
		break;
	}
}

void printWon() {
	system("cls");
	printTitle();
	printf(
		" __  __     ______     __  __                                                           \n"
		"/\\ \\_\\ \\   /\\  __ \\   /\\ \\/\\ \\                                                          \n"
		"\\ \\____ \\  \\ \\ \\/\\ \\  \\ \\ \\_\\ \\                                                         \n"
		" \\/\\_____\\  \\ \\_____\\  \\ \\_____\\                                                        \n"
		"  \\/_____/   \\/_____/   \\/_____/                                                        \n"
		"                                                                                        \n"
		"                                                    __     __     ______     __   __    \n"
		"                                                   /\\ \\  _ \\ \\   /\\  __ \\   /\\ \"-.\\ \\   \n"
		"                                                   \\ \\ \\/ \".\\ \\  \\ \\ \\/\\ \\  \\ \\ \\-.  \\  \n"
		"                                                    \\ \\__/\".~\\_\\  \\ \\_____\\  \\ \\_\\\\\"\\_\\ \n"
		"                                                     \\/_/   \\/_/   \\/_____/   \\/_/ \\/_/ \n");
	_getch();
}

void printLost() {
	system("cls");
	printTitle();
	printf(
		" __  __     ______     __  __                                                                \n"
		"/\\ \\_\\ \\   /\\  __ \\   /\\ \\/\\ \\                                                               \n"
		"\\ \\____ \\  \\ \\ \\/\\ \\  \\ \\ \\_\\ \\                                                              \n"
		" \\/\\_____\\  \\ \\_____\\  \\ \\_____\\                                                             \n"
		"  \\/_____/   \\/_____/   \\/_____/                                                             \n"
		"                                                                                             \n"
		"                                                    __         ______     ______     ______  \n"
		"                                                   /\\ \\       /\\  __ \\   /\\  ___\\   /\\__  _\\ \n"
		"                                                   \\ \\ \\____  \\ \\ \\/\\ \\  \\ \\___  \\  \\/_/\\ \\/ \n"
		"                                                    \\ \\_____\\  \\ \\_____\\  \\/\\_____\\    \\ \\_\\ \n"
		"                                                     \\/_____/   \\/_____/   \\/_____/     \\/_/ \n");
	_getch();
}

void printPlayerStatus(int gameState, int remainingFood, int numOfFoods) {
	switch (gameState) {
	case GAME_PLAYING:
		printf("Progress: %2.f\%\n", ((float) numOfFoods - (float) remainingFood) /(float)  numOfFoods * 100.0);
		break;
	case GAME_WON:
		printWon();
		break;
	case GAME_LOST:
		printLost();
		break;
	}
}

int gameLoop(int numOfFoods) {
	srand(time(NULL));

	char map[MAP_X][MAP_Y];
	int remainingFood = numOfFoods;
	int gameState = GAME_PLAYING;
	int playerX = 0, playerY = 0;

	fillAir(map);
	generateBlocks(map, BLOCKS);
	generateFoods(map, numOfFoods);
	generateExit(map);

	printPlayer(map, playerX, playerY);
	printPlayerStatus(gameState, remainingFood, numOfFoods);

	while (gameState == GAME_PLAYING) {
		if (_kbhit()) {
			getUserInput(&playerX, &playerY, &gameState);

			if (gameState == GAME_PAUSED)
				pauseMenu(&gameState);

			if (gameState != GAME_STOPPED)
				gameState = checkGameStatus(map, playerX, playerY, &remainingFood);

			printPlayer(map, playerX, playerY);
			printPlayerStatus(gameState, remainingFood, numOfFoods);
		}
	}
	system("cls");

	return gameState;
}

int main() {
	system("cls");
	int gameState;

	while (1) {
		switch (mainMenu()) {
		case 1:
			gameState = gameLoop(getFoodRange());
			if (gameState == GAME_STOPPED)
				return 0;
			break;
		case 2:
			instructions();
			break;
		case 3:
			system("cls");
			return 0;
			break;
		default:
			printf("Please pick within the options!");
			Sleep(1000);
			break;
		}
		system("cls");
	}
	
	return 0;
}