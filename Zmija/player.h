#define _CRT_SECURE_NO_WARNINGS

// player.h

#ifndef PLAYER_H
#define PLAYER_H

#include <time.h>

typedef struct {
    char name[50];
    int score;
    time_t timestamp; // vrijeme kad je rezultat postignut
} Player;

void addPlayer(const char* filename);
void displayPlayers(const char* filename);

#endif


// player.h – dodaj ove prototipove

void updatePlayer(const char* filename);
void deletePlayer(const char* filename);

int compareScoreDescending(const void* a, const void* b);
int compareName(const void* a, const void* b);
void displaySortedPlayers(const char* filename);
void searchPlayerByName(const char* filename);
