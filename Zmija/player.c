#define _CRT_SECURE_NO_WARNINGS // player.c
#pragma warning(disable : 4146)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "player.h"

void addPlayer(const char* filename) {
    FILE* file = fopen(filename, "ab"); // append binary
    if (!file) {
        perror("Greška pri otvaranju datoteke");
        return;
    }

    Player newPlayer;
    printf("Unesite ime igrača: ");
    scanf("%49s", newPlayer.name);

    printf("Unesite rezultat: ");
    scanf("%d", &newPlayer.score);

    newPlayer.timestamp = time(NULL); // trenutno vrijeme

    fwrite(&newPlayer, sizeof(Player), 1, file);
    fclose(file);

    printf("Igrač uspješno dodan.\n");
}

void displayPlayers(const char* filename) {
    FILE* file = fopen(filename, "rb"); // read binary
    if (!file) {
        perror("Greška pri otvaranju datoteke");
        return;
    }

    Player temp;
    int i = 1;
    printf("\n=== Lista igrača ===\n");

    while (fread(&temp, sizeof(Player), 1, file) == 1) {
        char* dateStr = ctime(&temp.timestamp); // formatirano vrijeme
        if (dateStr[strlen(dateStr) - 1] == '\n') dateStr[strlen(dateStr) - 1] = '\0';

        printf("%d. %s | Score: %d | Datum: %s\n", i++, temp.name, temp.score, dateStr);
    }

    fclose(file);
}

// player.c – dodaj ovu funkciju

void updatePlayer(const char* filename) {
    FILE* file = fopen(filename, "r+b"); // read+write binary
    if (!file) {
        perror("Greška pri otvaranju datoteke");
        return;
    }

    char targetName[50];
    printf("Unesite ime igrača za ažuriranje: ");
    scanf("%49s", targetName);

    Player temp;
    int found = 0;

    while (fread(&temp, sizeof(Player), 1, file) == 1) {
        if (strcmp(temp.name, targetName) == 0) {
            printf("Trenutni rezultat: %d\n", temp.score);
            printf("Unesite novi rezultat: ");
            scanf("%d", &temp.score);
            temp.timestamp = time(NULL);

            fseek(file, -sizeof(Player), SEEK_CUR); // vrati se unazad
            fwrite(&temp, sizeof(Player), 1, file);
            found = 1;
            printf("Rezultat ažuriran.\n");
            break;
        }
    }

    if (!found) {
        printf("Igrač nije pronađen.\n");
    }

    fclose(file);
}

// player.c – dodaj ovu funkciju

void deletePlayer(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Greška pri otvaranju datoteke");
        return;
    }

    FILE* tempFile = fopen("temp.dat", "wb");
    if (!tempFile) {
        perror("Greška pri otvaranju privremene datoteke");
        fclose(file);
        return;
    }

    char targetName[50];
    printf("Unesite ime igrača za brisanje: ");
    scanf("%49s", targetName);

    Player temp;
    int deleted = 0;

    while (fread(&temp, sizeof(Player), 1, file) == 1) {
        if (strcmp(temp.name, targetName) != 0) {
            fwrite(&temp, sizeof(Player), 1, tempFile);
        }
        else {
            deleted = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    if (deleted) {
        remove(filename);
        rename("temp.dat", filename);
        printf("Igrač obrisan.\n");
    }
    else {
        remove("temp.dat");
        printf("Igrač nije pronađen.\n");
    }
}

int compareScoreDescending(const void* a, const void* b) {
    const Player* p1 = (const Player*)a;
    const Player* p2 = (const Player*)b;
    return p2->score - p1->score; // padajući redoslijed
}

void displaySortedPlayers(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Greška pri otvaranju datoteke");
        return;
    }

    // Prvo prebroji koliko igrača ima
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    int count = fileSize / sizeof(Player);
    if (count == 0) {
        printf("Nema podataka za prikaz.\n");
        fclose(file);
        return;
    }

    // Alociraj memoriju
    Player* players = malloc(count * sizeof(Player));
    if (!players) {
        perror("Greška pri alokaciji memorije");
        fclose(file);
        return;
    }

    fread(players, sizeof(Player), count, file);
    fclose(file);

    // Sortiraj po rezultatu
    qsort(players, count, sizeof(Player), compareScoreDescending);

    printf("\n--- SORTIRANA LISTA IGRAČA (po rezultatu) ---\n");
    for (int i = 0; i < count; ++i) {
        printf("%s - %d - %s", players[i].name, players[i].score, ctime(&players[i].timestamp));
    }

    free(players);
}

int compareName(const void* a, const void* b) {
    return strcmp(((Player*)a)->name, ((Player*)b)->name);
}

void searchPlayerByName(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Greška pri otvaranju datoteke");
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    int count = fileSize / sizeof(Player);
    if (count == 0) {
        printf("Nema podataka za pretraživanje.\n");
        fclose(file);
        return;
    }

    Player* players = malloc(count * sizeof(Player));
    if (!players) {
        perror("Greška pri alokaciji memorije");
        fclose(file);
        return;
    }

    fread(players, sizeof(Player), count, file);
    fclose(file);

    // Sortiraj po imenu prije bsearch
    qsort(players, count, sizeof(Player), compareName);

    char searchName[50];
    printf("Unesite ime igrača za pretragu: ");
    scanf("%49s", searchName);

    Player key;
    strncpy(key.name, searchName, sizeof(key.name));

    Player* found = bsearch(&key, players, count, sizeof(Player), compareName);
    if (found) {
        printf("Pronađen igrač: %s - %d - %s", found->name, found->score, ctime(&found->timestamp));
    }
    else {
        printf("Igrač nije pronađen.\n");
    }

    free(players);
}



