#include <stdio.h>
#include <ctype.h>
#include <time.h>

// Windows-Dpeendent
#include <conio.h>
#include <Windows.h>

#define MAP_X 10
#define MAP_Y 10
#define BLOCKS 10

#define AIR ' '
#define BLOCK '#'
#define FOOD '*'
#define EXIT '$'
#define PLAYER 'O'

#define GAME_STOPPED -2
#define GAME_LOST -1
#define GAME_PAUSED 0
#define GAME_PLAYING 1
#define GAME_WON 2

// Instructions
void instructions() {
	system("cls");
	printf("Objective:\n"
				"\tTo simulate the famous Pacman game but without Blink, Pinky, Inky, and Clyde. This makes the game fairly lot simple.\n\n"
			"Navigation:\n"
				"\tTo control Pacman, the characters W, S, A and D are used.W is used to make it move UP, S to move DOWN, A to go LEFT and D to move RIGHT.When Pac - man collides with any part blocks or the boundaries, the game ends and the user loses.\n\n"
			"Collecting Food:\n"
				"\tThere will be randomly distributed across the board indicated by ‘ * ’(or any symbol you wish, just add this to your documentation).Points will be accumulated as Pac - man will collect the food. (the number of points will be the programmer’s discretion.) Displaying the points will either be during the game or after the player collects all the food and exits the board.\n\n"
			"Blocks:\n"
				"\tRandomly place blocks across the board.Positions of blocks should be different every time the program is run.\n\n"
			"Board Exit:\n"
				"\tHow will the game end with the user winning ? The game will Pacman eats all the food and moves out of the board.There will be a mark on the board on any part of the border to indicate the exit point.Once it steps on the marked exit, the game is done and the player wins.\n\n");
	_getch();
	system("cls");
}

// Menus
int mainMenu() {
	int option = -1;
	printf(
		"Ghostless Pac-man:\n"
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
	int range;
	char query[] = "How many food do you want to be distributed in the board? (range of 2-9)\t";

	printf(query);
	scanf("%d", &range);
	while ((getchar()) != '\n');

	if (!(range >= 2 && range <= 9)) {
		printf("Please put a number within the range of 2-9! Please try again.\n");
		Sleep(1000);
		range = getFoodRange();
	}

	return range;
}

void pauseMenu(int *gameState) {
	system("cls");

	while (1) {
		int option = -1;
		printf(
			"Ghostless Pac-man:\n"
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
			break;
		case 3:
			*gameState = GAME_STOPPED;
			return;
		default:
			printf("Please pick within the options!\n");
			Sleep(1000);
			break;
		}
		system("cls");
	}
}

// Game Loop

// Function Declarations
void generateBlocks(char map[MAP_X][MAP_Y], int range);															// function 1
void generateFoods(char map[MAP_X][MAP_Y], int range);															// function 2
int checkGameStatus(char map[MAP_X][MAP_Y], int playerPositionX, int playerPositionY, int* remainingFood);		// function 3
void printPlayerStatus(int gameState, int remainingFood);														// function 4

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

		if (map[x][y] && !(x == 0 && y == 0) && !(x == 0 && y == 1) && !(x == 1 && y == 0)) {
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

	for (int y = 0; y < MAP_Y; y++) {
		printf("|");
		for (int x = 0; x < MAP_X; x++) {
			printf("%c|", map[x][y]);
		}
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
	if (playerPositionX < 0 || playerPositionX > MAP_X || playerPositionY < 0 || playerPositionY > MAP_Y)
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
	default:
		return GAME_PLAYING;
	}
}

void getUserInput(int *playerX, int *playerY, int *gameState) {
	switch (tolower(_getch())) {
	case 'm':
		*gameState = GAME_PAUSED;
		break;
	case 'w':
		*playerY += -1;
		break;
	case 's':
		*playerY += 1;
		break;
	case 'd':
		*playerX += 1;
		break;
	case 'a':
		*playerX += -1;
		break;
	}
}

void printPlayerStatus(int gameState, int remainingFood) {
	switch (gameState) {
	case GAME_PLAYING:
		printf("Game is running! (Remaining Food: %d)\n", remainingFood);
		break;
	case GAME_WON:
		printf("You won!\n");
		_getch();
		break;
	case GAME_LOST:
		printf("You lost!\n");
		_getch();
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
	printPlayerStatus(gameState, remainingFood);

	while (gameState == GAME_PLAYING) {
		if (_kbhit()) {
			getUserInput(&playerX, &playerY, &gameState);

			if (gameState == GAME_PAUSED)
				pauseMenu(&gameState);

			if (gameState != GAME_STOPPED)
				gameState = checkGameStatus(map, playerX, playerY, &remainingFood);

			printPlayer(map, playerX, playerY);
			printPlayerStatus(gameState, remainingFood);
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