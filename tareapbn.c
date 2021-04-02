#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define MAXCHAR 1000

int Input(char *text);
void OpenFile(char *filename);
void PrintBoard(char playerboard[10][10]);
bool AddBoat(char *type, int len, char col, int row, char orient, char playerboard[10][10]);
FILE *files;

int main(int argc, char *argv[]){
    char *gamemode;
    char *p1name;
    char *p2name;

    if (argc == 4){
        gamemode = argv[1];
        p1name = argv[2];
        p2name = argv[3];

        OpenFile(p1name);
        OpenFile(p2name);

    }
    else{
        printf("Error: Console Input is incorrect");
        return 0;
    }
    return 0;
}

int Input(char *text){
    int value;
    printf("%s", text);
    scanf("%d", &value);
    return value;
}

void OpenFile(char filename[]){
    char str[MAXCHAR];
    files = fopen(filename, "r");
    
    if (files == NULL){
        printf("Could not open file %s\n",filename);
    }
    else{
        int counter = 1;
        char playerboard[10][10];
        for (int a = 0; a < sizeof(playerboard); a++){
            for (int b = 0; b < sizeof(playerboard[a]); b++){
                playerboard[a][b] = *"_";
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
            error = AddBoat(type, len, col, row, orient, playerboard);
            if (error == false){
                //printf("Boat added correctly\n");
            }
            else {
                printf("Something with the boat settings went wrong");
                exit(1);
                break;
            }
            
            counter = 1;
        }
        PrintBoard(playerboard);
        fclose(files);
    }
}

bool AddBoat(char *type, int len, char col, int row,char orient, char playerboard[10][10]){
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

void Game(){
    
}