#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define MAXCHAR 1000

int Input(char *text);
void OpenFile(char *filename);
void CreateBoard();
void AddBoat(char *type, int len, char col, int row,char orient);
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

        //CreateBoard();
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
    files = fopen(strcat(filename,".txt"), "r"); 
    
    if (files == NULL){
        printf("Could not open file %s",filename);
    }
    else{
        int counter = 1;
        while (fgets(str, MAXCHAR, files) != NULL) {
            char type[15]; 
            int len;
            char col;
            int row;
            char orient;

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
                            //printf("%d %s", i, type);
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
            AddBoat(type, len, col, row, orient);
            counter = 1;
        }
        fclose(files);
    }
}

void AddBoat(char *type, int len, char col, int row,char orient){
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

    char *board[10][10];

    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            if (i == row && j == col_to_num){
                board[i][j] = "X";
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
            else{
                board[i][j] = "_";
            }
            
        }
    }
    if (error == false){
        printf("\n  A  B  C  D  E  F  G  H  I  J\n");
        for (int i = 0; i < 10; i++){
            printf("%d", i);
            for (int j = 0; j < 10; j++){
                printf("[%s]", board[i][j]);
            }
            printf("%d\n", i);
        }
        printf("  A  B  C  D  E  F  G  H  I  J\n");
    }
}

void CreateBoard(){
    char *board[10][10];

    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            board[i][j] = "_";
        }
    }

    printf("\n  A  B  C  D  E  F  G  H  I  J\n");
    for (int i = 0; i < 10; i++){
        printf("%d", i);
        for (int j = 0; j < 10; j++){
            printf("[%s]", board[i][j]);
        }
        printf("%d\n", i);
    }
    printf("  A  B  C  D  E  F  G  H  I  J\n");
}

void Game(){
    
}