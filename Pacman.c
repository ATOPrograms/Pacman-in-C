#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define ROW 31
#define COL 28
#define MAX_PATH_LENGTH 346

typedef struct{
	int xAxis;
	int yAxis;
} Coord;

typedef struct{
	Coord head;
	Coord tail;
} Trails;

char grid[ROW][COL] =
{
	{ "XXXXXXXXXXXXXXXXXXXXXXXXXXXX" },
	{ "X..........................X" }, //26
	{ "X.XXXX.XXXXX.XX.XXXXX.XXXX.X" }, //6
	{ "XoXXXX.XXXXX.XX.XXXXX.XXXXoX" }, //6
	{ "X.XXXX.XXXXX.XX.XXXXX.XXXX.X" }, //6
	{ "X..........................X" }, //26
	{ "X.XXXX.XX.XXXXXXXX.XX.XXXX.X" }, //6
	{ "X.XXXX.XX.XXXXXXXX.XX.XXXX.X" }, //6
	{ "X......XX....XX....XX......X" }, //20
	{ "XXXXXX.XXXXX XX XXXXX.XXXXXX" }, //2
	{ "     X.XXXXX XX XXXXX.X     " }, //2
	{ "     X.XX          XX.X     " }, //2
	{ "     X.XX XXX--XXX XX.X     " }, //2
	{ "XXXXXX.XX X      X XX.XXXXXX" }, //2
	{ "      .   X      X   .      " }, //2
	{ "XXXXXX.XX X      X XX.XXXXXX" }, //2
	{ "     X.XX XXXXXXXX XX.X     " }, //2
	{ "     X.XX          XX.X     " }, //2
	{ "     X.XX XXXXXXXX XX.X     " }, //2
	{ "XXXXXX.XX XXXXXXXX XX.XXXXXX" }, //2
	{ "X............XX............X" }, //24
	{ "X.XXXX.XXXXX.XX.XXXXX.XXXX.X" }, //6
	{ "X.XXXX.XXXXX.XX.XXXXX.XXXX.X" }, //6
	{ "Xo..XX.......  .......XX..oX" }, //20
	{ "XXX.XX.XX.XXXXXXXX.XX.XX.XXX" }, //6
	{ "XXX.XX.XX.XXXXXXXX.XX.XX.XXX" }, //6
	{ "X......XX....XX....XX......X" }, //20
	{ "X.XXXXXXXXXX.XX.XXXXXXXXXX.X" }, //4
	{ "X.XXXXXXXXXX.XX.XXXXXXXXXX.X" }, //4
	{ "X..........................X" }, //26
	{ "XXXXXXXXXXXXXXXXXXXXXXXXXXXX" }
};

void placeDude(int dudeX, int dudeY){
	grid[dudeY][dudeX] = '@';
}

void placeGhosts(int ghostX, int ghostY){
	grid[ghostY][ghostX] = '&';
}

void printGrid(){
	int i, j;
	
	for(i = 0; i < ROW; i++){
		for(j = 0; j < COL; j++){
			printf("%c", grid[i][j]);
			printf("%c", grid[i][j]);
		}
		
		printf("\n");
	}
		
}

char startGame(char userInput){
	while(userInput == '+'){
		userInput = getch();
	}
	
	return(userInput);
}

void resetScreenPosition(){
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

void changeDudeLocation(int *dudeX, int *dudeY, char *userInput, int *placeHolderX, int *placeHolderY, int *directionY, int *directionX, char *direction, char *directionPlaceholder, int *tictacCounter){
	char inputPlaceholder = *userInput;
	
	*placeHolderX = *dudeX;
	*placeHolderY = *dudeY;
	
    if(kbhit()){
		*userInput = getch();
		
		switch (*userInput){
			case 'w':
				if(grid[*dudeY-1][*dudeX] == 'X' || grid[*dudeY-1][*dudeX] == '-'){
					*directionX = 0;
					*directionY = -1;
					*direction = *userInput;
					*userInput = inputPlaceholder;
				}
				break;
			case 's':
				if(grid[*dudeY+1][*dudeX] == 'X' || grid[*dudeY+1][*dudeX] == '-'){
					*directionX = 0;
					*directionY = 1;
					*direction = *userInput;
					*userInput = inputPlaceholder;
				}
				break;
			case 'd':
				if(grid[*dudeY][*dudeX+1] == 'X' || grid[*dudeY][*dudeX+1] == '-'){
					*directionX = 1;
					*directionY = 0;
					*direction = *userInput;
					*userInput = inputPlaceholder;
				}
				break;
			case 'a':
				if(grid[*dudeY][*dudeX-1] == 'X' || grid[*dudeY][*dudeX-1] == '-'){
					*directionX = -1;
					*directionY = 0;
					*direction = *userInput;
					*userInput = inputPlaceholder;
				}
				break;
			default:
				break;
		}
		
		*directionPlaceholder = inputPlaceholder;
	}
	
	if(grid[*dudeY+*directionY][*dudeX+*directionX] != 'X' && grid[*dudeY+*directionY][*dudeX+*directionX] != '-' && *directionX != 2 && *directionY != 2 && *userInput == *directionPlaceholder){
		*userInput = *direction;
		*directionX = 2;
		*directionY = 2;
		*directionPlaceholder = '-';
	}
	
	switch (*userInput){
        case 'w':
			if(grid[*dudeY-1][*dudeX] != 'X' && grid[*dudeY-1][*dudeX] != '-'){
				if(grid[*dudeY-1][*dudeX] == '.' || grid[*dudeY-1][*dudeX] == 'o'){
					*tictacCounter += 1;
				}
				*dudeY -= 1;
			}
            break;
        case 's':
			if(grid[*dudeY+1][*dudeX] != 'X' && grid[*dudeY+1][*dudeX] != '-'){
				if(grid[*dudeY+1][*dudeX] == '.' || grid[*dudeY+1][*dudeX] == 'o'){
					*tictacCounter += 1;
				}
				*dudeY += 1;
			}
            break;
        case 'd':
			if (*dudeX == COL - 1){
				*dudeX += 1;
			}
			else if(grid[*dudeY][*dudeX+1] != 'X' && grid[*dudeY][*dudeX+1] != '-'){
				if(grid[*dudeY][*dudeX+1] == '.' || grid[*dudeY][*dudeX+1] == 'o'){
					*tictacCounter += 1;
				}
				*dudeX += 1;
			}
            break;
        case 'a':
			if (*dudeX == 0){
				*dudeX -= 1;
			}
			else if (grid[*dudeY][*dudeX-1] != 'X' && grid[*dudeY][*dudeX-1] != '-'){
				if(grid[*dudeY][*dudeX-1] == '.' || grid[*dudeY][*dudeX-1] == 'o'){
					*tictacCounter += 1;
				}
				*dudeX -= 1;
			}
            break;
        default:
            break;
    }
	
	if (*dudeX == -1){
		*dudeX += COL;
	}
	else if(*dudeX == COL){
		*dudeX -= COL;
	}
	
	grid[*placeHolderY][*placeHolderX] = ' ';
}

void ghostExitCage(int *moves, int *ghostX, int *ghostY, char *oldChar, int *ghost_moves){
	if(*ghost_moves == 0){
		*oldChar = grid[*ghostY][*ghostX+1];			
		*ghostX = *ghostX += 1;
	}
	else if(*ghost_moves == 1 || *ghost_moves == 2){
		*oldChar = grid[*ghostY-1][*ghostX];
		*ghostY = *ghostY -= 1;
	}
	
	*ghost_moves += 1;
}

bool checkVisited(Coord *visited, int visitedCounter, int tempXAxis, int tempYAxis, bool inVisited){
	int i;
	
	for(i = 0; i <= visitedCounter; i++){
		if(visited[i].xAxis == tempXAxis && visited[i].yAxis == tempYAxis){
			inVisited = true;
		}
	}
	
	return inVisited;
}

void findPath(bool *inVisited, Coord *visited, int *visitedCounter, int tempXAxis, int tempYAxis, int *queueCounter, Coord *queue, Trails *trail, int dudeY, int dudeX, bool *targetNotFound, int *targetX, int *targetY, int *targetIndex, int *trailCounter, int *ghostX, int *ghostY){
	*inVisited = checkVisited(visited, *visitedCounter, tempXAxis, tempYAxis, *inVisited);
	
	if(*inVisited == false){
		*queueCounter += 1;
		queue[*queueCounter].xAxis = tempXAxis;
		queue[*queueCounter].yAxis = tempYAxis;
				
		trail[*trailCounter].tail.xAxis = queue[*visitedCounter].xAxis;
		trail[*trailCounter].tail.yAxis = queue[*visitedCounter].yAxis;
		trail[*trailCounter].head.xAxis = tempXAxis;
		trail[*trailCounter].head.yAxis = tempYAxis;
				
		if(tempYAxis == dudeY && tempXAxis == dudeX){
			if(*visitedCounter == 0){
				*ghostY = dudeY;
				*ghostX = dudeX;
			}
			*targetNotFound = false;
			*targetX = trail[*trailCounter].tail.xAxis;
			*targetY = trail[*trailCounter].tail.yAxis;
			*targetIndex = *trailCounter;
		}
				
		*trailCounter += 1;
	}
	
	*inVisited = false;
}

void ghostPathfinding(int *ghostX, int *ghostY, int dudeX, int dudeY, char *oldChar, bool *gameNotOver){
	int visitedCounter = 0;
	int queueCounter = 0;
	int trailCounter = 0;
	int targetIndex = 0;
	int targetX = 0;
	int targetY = 0;
	int i;
	int tempXAxis = 0;
	int tempYAxis = 0;
	Coord queue[MAX_PATH_LENGTH*2];
	Coord visited[MAX_PATH_LENGTH*2];
	Trails trail[MAX_PATH_LENGTH*2];
	bool targetNotFound = true;
	bool inVisited = false;
	
	queue[0].xAxis = *ghostX;
	queue[0].yAxis = *ghostY;
	
	while(targetNotFound){
		if(grid[queue[visitedCounter].yAxis-1][queue[visitedCounter].xAxis] != 'X' && grid[queue[visitedCounter].yAxis-1][queue[visitedCounter].xAxis] != '-' && targetNotFound
		){
			tempXAxis = queue[visitedCounter].xAxis;
			tempYAxis = queue[visitedCounter].yAxis-1;
			inVisited = checkVisited(visited, visitedCounter, tempXAxis, tempYAxis, inVisited);
			findPath(&inVisited, visited, &visitedCounter, tempXAxis, tempYAxis, &queueCounter, queue, trail, dudeY, dudeX, &targetNotFound, &targetX, &targetY, &targetIndex, &trailCounter, &*ghostX, &*ghostY);
			
			inVisited = false;
		}
		if(grid[queue[visitedCounter].yAxis][queue[visitedCounter].xAxis+1] != 'X' && grid[queue[visitedCounter].yAxis][queue[visitedCounter].xAxis+1] != '-' && targetNotFound){
			tempXAxis = queue[visitedCounter].xAxis+1;
			tempYAxis = queue[visitedCounter].yAxis;
			inVisited = checkVisited(visited, visitedCounter, tempXAxis, tempYAxis, inVisited);
			findPath(&inVisited, visited, &visitedCounter, tempXAxis, tempYAxis, &queueCounter, queue, trail, dudeY, dudeX, &targetNotFound, &targetX, &targetY, &targetIndex, &trailCounter, &*ghostX, &*ghostY);

			inVisited = false;
		}
		if(grid[queue[visitedCounter].yAxis+1][queue[visitedCounter].xAxis] != 'X' && grid[queue[visitedCounter].yAxis+1][queue[visitedCounter].xAxis] != '-' && targetNotFound){
			tempXAxis = queue[visitedCounter].xAxis;
			tempYAxis = queue[visitedCounter].yAxis+1;
			inVisited = checkVisited(visited, visitedCounter, tempXAxis, tempYAxis, inVisited);
			findPath(&inVisited, visited, &visitedCounter, tempXAxis, tempYAxis, &queueCounter, queue, trail, dudeY, dudeX, &targetNotFound, &targetX, &targetY, &targetIndex, &trailCounter, &*ghostX, &*ghostY);
			
			inVisited = false;
		}
		if(grid[queue[visitedCounter].yAxis][queue[visitedCounter].xAxis-1] != 'X' && grid[queue[visitedCounter].yAxis][queue[visitedCounter].xAxis-1] != '-' && targetNotFound){
			tempXAxis = queue[visitedCounter].xAxis-1;
			tempYAxis = queue[visitedCounter].yAxis;
			inVisited = checkVisited(visited, visitedCounter, tempXAxis, tempYAxis, inVisited);
			findPath(&inVisited, visited, &visitedCounter, tempXAxis, tempYAxis, &queueCounter, queue, trail, dudeY, dudeX, &targetNotFound, &targetX, &targetY, &targetIndex, &trailCounter, &*ghostX, &*ghostY);
			
			inVisited = false;
		}
		
		visitedCounter += 1;
		visited[visitedCounter].yAxis = queue[visitedCounter-1].yAxis;
		visited[visitedCounter].xAxis = queue[visitedCounter-1].xAxis;
	}
	
	if(*ghostY == dudeY && *ghostX == dudeX){
		*gameNotOver = false;
	}
	else{
		for(i = targetIndex-1; i >= 0; i--){
			if(targetX == trail[i].head.xAxis && targetY == trail[i].head.yAxis){
				targetX = trail[i].tail.xAxis;
				targetY = trail[i].tail.yAxis;
			}
			if(targetX == *ghostX && targetY == *ghostY){
				if(grid[trail[i].head.yAxis][trail[i].head.xAxis] != '&'){
					*oldChar = grid[trail[i].head.yAxis][trail[i].head.xAxis];
				}
				*ghostY = trail[i].head.yAxis;
				*ghostX = trail[i].head.xAxis;
			}
		}
	}
}

void changeGhostLocation(int *ghostX, int *ghostY, int dudeX, int dudeY, int *moves, int *ghostPlaceHolderX, int *ghostPlaceHolderY, char *oldChar, bool *gameNotOver, int *ghost_moves){
	*ghostPlaceHolderX = *ghostX;
	*ghostPlaceHolderY = *ghostY;
	grid[*ghostPlaceHolderY][*ghostPlaceHolderX] = *oldChar;
	
	if(*ghost_moves < 3){
		ghostExitCage(&*moves, &*ghostX, &*ghostY, &*oldChar, &*ghost_moves);
	}
	else{
		ghostPathfinding(&*ghostX, &*ghostY, dudeX, dudeY, &*oldChar, &*gameNotOver);
	}
}

int main(){
	int dudeX = 13;
	int dudeY = 23;
	int redX = 12;
	int redY = 13;
	int pinkX = 12;
	int pinkY = 13;
	int yellowX = 12;
	int yellowY = 13;
	int cyanX = 12;
	int cyanY = 13;
	int directionX = 2;
	int directionY = 2;
	int tictacCounter = 0;
	int moves = 0;
	int red_moves = 0;
	int pink_moves = 0;
	int yellow_moves = 0;
	int cyan_moves = 0;
	int placeHolderX;
	int placeHolderY;
	int redPlaceHolderX;
	int redPlaceHolderY;
	int pinkPlaceHolderX;
	int pinkPlaceHolderY;
	int yellowPlaceHolderX;
	int yellowPlaceHolderY;
	int cyanPlaceHolderX;
	int cyanPlaceHolderY;
	int sleepCounter = 0;
	char userInput = '+';
	char direction;
	char directionPlaceholder;
	char red_oldChar = ' ';
	char pink_oldChar = ' ';
	char yellow_oldChar = ' ';
	char cyan_oldChar = ' ';
	bool gameNotOver = true;
	
	system("cls");
	
	while(gameNotOver){
		if(tictacCounter != 248){
			placeDude(dudeX, dudeY);
			placeGhosts(redX, redY);
			placeGhosts(pinkX, pinkY);
			placeGhosts(yellowX, yellowY);
			placeGhosts(cyanX, cyanY);
			printGrid();
			userInput = startGame(userInput);
			
			if(sleepCounter % 2 == 0){
				changeDudeLocation(&dudeX, &dudeY, &userInput, &placeHolderX, &placeHolderY, &directionX, &directionY, &direction, &directionPlaceholder, &tictacCounter);
				moves += 1;
			}
			if(sleepCounter % 3 == 0){
				if(moves >= 0){
					changeGhostLocation(&redX, &redY, dudeX, dudeY, &moves, &redPlaceHolderX, &redPlaceHolderY, &red_oldChar, &gameNotOver, &red_moves);
				}
			}
			if(sleepCounter % 4 == 0){
				if(moves >= 20){
					changeGhostLocation(&pinkX, &pinkY, dudeX, dudeY, &moves, &pinkPlaceHolderX, &pinkPlaceHolderY, &pink_oldChar, &gameNotOver, &pink_moves);
				}
			}
			if(sleepCounter % 5 == 0){
				if(moves >= 40){
					changeGhostLocation(&yellowX, &yellowY, dudeX, dudeY, &moves, &yellowPlaceHolderX, &yellowPlaceHolderY, &yellow_oldChar, &gameNotOver, &yellow_moves);
				}
			}
			if(sleepCounter % 6 == 0){
				if(moves >= 60){
					changeGhostLocation(&cyanX, &cyanY, dudeX, dudeY, &moves, &cyanPlaceHolderX, &cyanPlaceHolderY, &cyan_oldChar, &gameNotOver, &cyan_moves);
				}
			}
			
			if(tictacCounter >= 246){
				if(tictacCounter == 247){
					printf("\n			  You Won!\n");
					Sleep(2000);
				}
				tictacCounter += 1;
				if(tictacCounter == 248){
					gameNotOver = false;
				}
			}
			
			if(gameNotOver == false && tictacCounter < 246){
				system("cls");
				placeGhosts(redX, redY);
				placeGhosts(pinkX, pinkY);
				placeGhosts(yellowX, yellowY);
				placeGhosts(cyanX, cyanY);
				printGrid();
				printf("\n			  Game Over.\n");
				Sleep(2000);
			}
			
			resetScreenPosition();
			
			Sleep(1);
			
			sleepCounter += 1;
			
			if(sleepCounter == 7){
				sleepCounter = 0;
			}
		}
	}
	
	system("cls");
    return(0);
}
