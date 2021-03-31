#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define MAXCHAR 1000

int Input(char *text);
void OpenFile(char *filename);
void CreateBoard();
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

        CreateBoard();
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
        while (fgets(str, MAXCHAR, files) != NULL) printf("%s", str);
        fclose(files);
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