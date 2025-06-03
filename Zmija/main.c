#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "player.h"
#include "snake.h"
int main() {
    const char* filename = "players.dat";

    int izbor;

    do {
        printf("\n=== Main menu ===\n");
        printf("1. Add player\n", MENU_ADD);
        printf("2. Display players\n", MENU_DISPLAY);
        printf("3. Update player\n", MENU_UPDATE);
        printf("4. Delete player\n", MENU_DELETE);
        printf("5. Display scoreboard\n", MENU_SORTED);
        printf("6. Search player by nickname\n", MENU_SEARCH_BY_NICKNAME);
        printf("0. Exit\n", MENU_EXIT);
        printf("Choose: ");
        scanf("%d", &izbor);

        switch (izbor) {
        case MENU_ADD:
            snake(filename);
            break;
        case MENU_DISPLAY:
            displayPlayers(filename);
            break;
        case MENU_UPDATE:
            updatePlayer(filename);
            break;
        case MENU_DELETE:
            deletePlayer(filename);
            break;
        case MENU_SORTED:
            displaySortedPlayers(filename);
            break;
        case MENU_SEARCH_BY_NICKNAME:
            searchPlayerByNickname(filename);
            break;
        case MENU_EXIT:
            printf("Exiting game.");
            break;
        default:
            printf("Invalid choice.\n");
        }

    } while (izbor != 0);

    return 0;
}

