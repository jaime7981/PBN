#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define MAXCHAR 1000

void OpenFile(char filename[20], char playerone[10][10]);
bool AddBoat(char type[30], int len, char col, int row, char orient, char playerboard[10][10]);
void PrintBoard(char playerboard[10][10]);
void UserInput(char user_input[5]);
void RowColumns(int row, int col, char user_input[5]);
void Game();
FILE *files;

int main(int argc, char *argv[]){
    char *gamemode;
    char *p1name;
    char *p2name;

    if (argc == 4){
        gamemode = argv[1];
        p1name = argv[2];
        p2name = argv[3];

        char playerone[10][10];
        OpenFile(p1name, playerone);
        PrintBoard(playerone);

        char playertwo[10][10];
        OpenFile(p2name, playertwo);
        PrintBoard(playertwo);

        if (gamemode[1] == *"a"){
            printf("Gamemode: Automated\n");
            Game();
        }
        else if (gamemode[1] == *"v"){
            printf("Gamemode: Vesus\n");
            Game();
        }
        else {
            printf("Error: gamemode is incorrect");
            printf("Something with the boat settings went wrong");
            exit(1);
        }

    }
    else{
        printf("Error: Console Input is incorrect");
        exit(1);
    }
    return 0;
}

void OpenFile(char filename[20], char player[10][10]){
    char str[MAXCHAR];
    files = fopen(filename, "r");
    
    if (files == NULL){
        printf("Could not open file %s\n",filename);
    }
    else{
        int counter = 1;
        for (int a = 0; a < sizeof(*player); a++){
            for (int b = 0; b < sizeof(player[a]); b++){
                player[a][b] = *"_";
            }
        }

        while (fgets(str, MAXCHAR, files) != NULL) {
            char type[15]; 
            int len;
            char col;
            int row;
            char orient;
            bool error;

            for (int i = 0; i <= sizeof(str); i++){
                char aux = str[i-1];
                
                if (str[i] == *";"){
                    switch (counter) {
                        case 1:
                            for (int j = 0; j < 15; j++){
                                if (j < i){
                                    type[j] = str[j];
                                }
                                else{
                                    type[j] = *"";
                                }
                            }
                            break;
                        case 2:
                            len = atoi(&str[(i-1)]);
                            break;
                        case 3:
                            col = aux;
                            break;
                        case 4:
                            row = atoi(&str[(i-1)]);
                            aux = str[i+1];
                            orient = aux;
                            break;
                    }
                    counter ++;
                }
            }
            printf("boat: %s length: %d column: %c row: %d orientation: %c\n", type, len, col, row, orient);
            error = AddBoat(type, len, col, row, orient, player);
            if (error == false){
                //printf("Boat added correctly\n");
            }
            else {
                printf("Something with the boat settings went wrong");
                exit(1);
            }
            
            counter = 1;
        }
        fclose(files);
    }
}

bool AddBoat(char type[30], int len, char col, int row,char orient, char playerboard[10][10]){
    int col_to_num = (int)col - 65;
    bool pos;
    bool error = false;
    int counter = 0;

    if (orient == *"h"){
        pos = true;
    }
    else{
        pos = false;
    }

    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            if (i == row && j == col_to_num){
                if (playerboard[i][j] != *"X"){
                    playerboard[i][j] = *"X";
                    if (pos == true){
                        counter ++;
                        if (counter < len){
                            col_to_num ++;
                            if (col_to_num >= 10){
                                printf("Boat out of bounds\n");
                                error = true;
                                break;
                            }
                        }
                    }
                    if (pos == false){
                        counter ++;
                        if (counter < len){
                            row ++;
                            if (row >= 10){
                                printf("Boat out of bounds\n");
                                error = true;
                                break;
                            }
                        }
                    }
                }
                else {
                    printf("Boat already in place\n");
                    error = true;
                    break;
                }
            }
        }
    }
    return error;
}

void PrintBoard(char playerboard[10][10]){

    printf("\n  A  B  C  D  E  F  G  H  I  J\n");
    for (int i = 0; i < 10; i++){
        printf("%d", i);
        for (int j = 0; j < sizeof(playerboard[i]); j++){
            printf("[%c]", playerboard[i][j]);
        }
        printf("%d\n", i);
    }
    printf("  A  B  C  D  E  F  G  H  I  J\n");
}

void UserInput(char user_input[5]){
    printf("Shoot your enemy! exit game(e)\n");
    fgets(user_input, 100, stdin);
    for (int a = 0; a < strlen(user_input); a++){
        if (user_input[a] == *","){

        }
    }
}

void RowColumns(int row, int col, char user_input[5]){
    for (int a = 0; a < strlen(user_input); a++){
        int inputaux = (int)user_input[a];
        if (inputaux == 101){
            exit(0);
        }
        else if (inputaux < 58 && inputaux > 47){
            row = inputaux - 48;
        }
        else if (inputaux < 75 && inputaux > 64) {
            col = inputaux - 65;
        }
    }
    printf("col: %d row: %d\n", col, row);
}

void Game(){
    bool continue_game = true;

    while (continue_game) {
        bool player_one_turn = true;
        char user_input[5];
        int inputrow;
        int inputcols;

        if (player_one_turn){
            UserInput(user_input);
            RowColumns(inputrow, inputcols, user_input);
            player_one_turn = false;
        }
        else {
            UserInput(user_input);
            RowColumns(inputrow, inputcols, user_input);
            player_one_turn = true;
        }
    }
}