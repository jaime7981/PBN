#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define MAXCHAR 


int CheckGender(char *gender);
void SongsGener(char *gender,int *counter);

FILE *files;
int main(int argc, char **argv){

    if(argc ==4){//Consultar por Generos Musicales
        char *g=argv[1];
        char *gender=argv[2];
        int populate= atoi(argv[3]);
        CheckGender(gender);
        if(g[1]=='g' && (populate>=0 && populate<=100) ){//Si ingresa g y una popularidad valida.
            int songs=0;
            SongsGener(gender,&songs);
            printf("%d\n",songs);
            printf("Funciona\n");//
        }
        else{
            printf("Error: the query is invalid\n");
            exit(1);
        }
    }
    else if(argc ==3){//Consultar Canciones por modo
        char *p=argv[1];
        char *mood=argv[2];

        if(p[1]=='p' && (strcmp(mood,"Major")==0 || strcmp(mood,"Minor")==0)){//Si ingrsa p y selecciona el modo correcto
            
            printf("Funciona\n");
        }
        else{
            printf("Error: the query is invalid\n");
            exit(1);
        }
    }
    else{
        printf("Error: query argumants are invalid.\n");
        exit(1);
    }
        return 0;
}

int CheckGender(char *gender){//Checkea si el genero ingresado es correcto

    files= fopen("genres.txt","r");
    int space= strlen(gender);
    char *type_of_gender=(char*)malloc(space*sizeof(char));
    char c=fgetc(files);
    int len=0;
    if(files!=NULL){
        while(c!=EOF){
            for(int i=0;i<space;i++){
                type_of_gender[i]=c;
                c=fgetc(files);
            }
            len=strlen(type_of_gender);
            if(c==';'){
                while(c!='\n'){
                    c=fgetc(files);
                }
            }
            else{
                len++;
                while(c!='\n'){
                    c=fgetc(files);
                }
            }
            //printf("%d  %d  %s %s\n",space,len,type_of_gender,gender);
            if(strcmp(type_of_gender,gender)==0 && (space==len)){
                    //printf("El genero si esta\n");
                    fclose(files);
                    return 0;
            }
            else{
                free(type_of_gender);
                type_of_gender=(char*)malloc(space*sizeof(char));
                len=0;
            }
            c=fgetc(files);
        }
    }
    else{
        printf("Error: Could not open file %s\n",gender);
        exit(1);
    }
    printf("The genre is not found in the database, please try again.\n");
    free(type_of_gender);
    fclose(files);
    exit(1);
   
}

void SongsGener(char *gender, int *counter){
    files= fopen("genres.txt","r");
    int space= strlen(gender);
    char *type_of_gender=(char*)malloc(space*sizeof(char));
    char c=fgetc(files);
    int total=0;

    while(c!=EOF){
        if(c!='\n'){
            for(int i=0;i<space;i++){
                type_of_gender[i]=c;
                c=fgetc(files);
            }
            if(strcmp(type_of_gender,gender)==0){
                (*counter)++;
            }
            else{
                free(type_of_gender);
                type_of_gender=(char*)malloc(space*sizeof(char));
            }
        }
        while(c!='\n'){
            c=fgetc(files);
        }
        total++;
        c=fgetc(files);
    }
    //printf("%d/%d\n",counter,total);
    free(type_of_gender);
    fclose(files);
}

