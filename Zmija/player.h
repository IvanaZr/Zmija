#define _CRT_SECURE_NO_WARNINGS

#include <time.h>

typedef enum {
	MENU_ADD = 1,
	MENU_DISPLAY,
	MENU_UPDATE,
	MENU_DELETE,
	MENU_SORTED,
	MENU_SEARCH_BY_NICKNAME,
	MENU_EXIT
} menu_choice_t;

typedef struct {
    char name[50];
    int score;
    time_t timestamp; 
} Player;

void addPlayer(const char* filename);
void displayPlayers(const char* filename);
void updatePlayer(const char* filename);
void deletePlayer(const char* filename);
int compareScoreDescending(const void* a, const void* b);
int compareName(const void* a, const void* b);
void displaySortedPlayers(const char* filename);
void searchPlayerByNickname(const char* filename);

#pragma once
