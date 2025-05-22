#define _CRT_SECURE_NO_WARNINGS

// main.c

#include <stdio.h>
#include "player.h"

int main() {
    const char* filename = "players.dat";

    int izbor;

    do {
        printf("\n=== Glavni Izbornik ===\n");
        printf("1. Dodaj igrača\n");
        printf("2. Prikaži igrače\n");
        printf("3. Ažuriraj rezultat igrača\n");
        printf("4. Obriši igrača\n");
        printf("5. Prikaži sortirane rezultate\n");
        printf("6. Pretraži igrača po imenu\n");
        printf("0. Izlaz\n");
        printf("Odabir: ");
        scanf("%d", &izbor);

        switch (izbor) {
        case 1:
            addPlayer(filename);
            break;
        case 2:
            displayPlayers(filename);
            break;
        case 3:
            updatePlayer(filename);
            break;
        case 4:
            deletePlayer(filename);
            break;
        case 5:
            displaySortedPlayers(filename);
            break;
        case 6:
            searchPlayerByName(filename);
            break;
        case 0:
            printf("Izlaz...\n");
            break;
        default:
            printf("Neispravan unos.\n");
        }

    } while (izbor != 0);

    return 0;
}

