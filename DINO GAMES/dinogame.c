#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>

#define SCREEN_WIDTH 50
#define SCREEN_HEIGHT 10
#define GROUND_LEVEL 8
#define JUMP_HEIGHT 4

typedef struct {
    int x, y;
    int isJumping;
} Dino;

typedef struct {
    int x, y;
} Obstacle;

void initDino(Dino *dino) {
    dino->x = 5;
    dino->y = GROUND_LEVEL;
    dino->isJumping = 0;
}

void drawScreen(Dino *dino, Obstacle *obstacle) {
    system("cls");

    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            if (x == dino->x && y == dino->y) {
                printf("D");
            } else if (x == obstacle->x && y == obstacle->y) {
                printf("O");
            } else if (y == GROUND_LEVEL) {
                printf("_");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void updateDino(Dino *dino) {
    if (dino->isJumping) {
        dino->y--;
        if (dino->y <= GROUND_LEVEL - JUMP_HEIGHT) {
            dino->isJumping = 0;
        }
    } else if (dino->y < GROUND_LEVEL) {
        dino->y++;
    }
}

void moveObstacle(Obstacle *obstacle) {
    obstacle->x--;
    if (obstacle->x < 0) {
        obstacle->x = SCREEN_WIDTH - 1;
        obstacle->y = GROUND_LEVEL;
    }
}

int checkCollision(Dino *dino, Obstacle *obstacle) {
    return (dino->x == obstacle->x && dino->y == obstacle->y);
}

int main() {
    Dino dino;
    Obstacle obstacle = {SCREEN_WIDTH - 1, GROUND_LEVEL};
    
    initDino(&dino);

    while (1) {
        drawScreen(&dino, &obstacle);
        updateDino(&dino);
        moveObstacle(&obstacle);

        if (checkCollision(&dino, &obstacle)) {
            printf("Game Over! You hit the obstacle.\n");
            break;
        }

        if (_kbhit()) {
            char ch = _getch();
            if (ch == ' ') {
                if (dino.y == GROUND_LEVEL) {
                    dino.isJumping = 1;
                }
            }
        }

        usleep(100000);
    }
 
    return 0;
}
 