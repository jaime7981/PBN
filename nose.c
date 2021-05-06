#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


//Info
typedef struct{
    char *IdSong;
    char *Popularity;
    char *Mode;
    struct Songs* next;
}Songs;

typedef struct{
    char *Gender;
    char *IdSong;
    char *By;
    struct Songs* Entity;
    struct Genders* next;
}Genders;

typedef struct{
    char *Artist;
    char *points;
    struct Artistas *next;
}Artistas;

typedef struct{
    char *Gender;
    int  Song_mode;
    struct Types *next;
}Types;

//Statements

     //Type Struct
Genders* ReadData(Genders*raiz);
Genders* ReadGenres(Genders* raiz);

    //Type char
char* ReadLine(FILE* files,size_t initial_size,char sep);
char* Delimiter(char* line, const char* seps);
    //Type int
int ReadSongs(Genders* raiz);
int InsertSong(Genders* raiz,Songs* Name,char* IdSong);
    //Type void
void Printer(Genders* raiz,char* gender_query);

//Main
int main(int argc, char **argv){
    Genders* raiz=NULL;
    Genders* aux;

    if(argc==4){
        //Query1
        char *g=argv[1];
        char *gender_query=argv[2];
        int populate=atoi(argv[3]);
        int songs=1;
        if(g[1]=='g' && (populate>=0 && populate <=100) && (songs>0)){
            //Start query 1
            raiz=ReadData(raiz);
            Printer(raiz,gender_query);
        }
        else{
            printf("Error: the query is invalid\n");
            exit(1);
        }
    }
    else if(argc==3){
        //Query2
        char *p=argv[1];
        char *mode_query=argv[2];

        if(p[1]=='p' && (strcmp(mode_query,"Major")==0 || strcmp(mode_query,"Minor")==0)){
            //Start query 2
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
    while(raiz!=NULL){
        aux=raiz;
        raiz=(Genders*)raiz->next;
        free(aux);
    }
    printf("imprimio todo\n");
    return 0;
}

Genders* ReadData(Genders*raiz){
    Genders *aux;
    int err;
    raiz= ReadGenres(raiz);
    err= ReadSongs(raiz);
    //p=raiz
    while(aux!=NULL){
        aux=(Genders*)aux->next;
    }
    return raiz;
}

Genders* ReadGenres(Genders* raiz){
    FILE* files;
    files= fopen("genres.txt","r");

    Genders *Songs;
    char* Gender;
    char* IdSong;
    char* By;
    Genders* aux;

    if(files==NULL){
        printf("Error: File 'genres.txt' could not be opened\n");
        exit(1);
    }
    else{
        while(!feof(files)){

            Gender = ReadLine(files,10,';');
            IdSong = ReadLine(files,10,';');
            By     = ReadLine(files,10,'\n');

            if(strlen(Gender)>=0){
                Songs= (Genders*)malloc(sizeof(Genders));
                Songs->Gender=Gender;
                Songs->IdSong=IdSong;
                Songs->By=By;
                Songs->Entity=NULL;
                Songs->next = NULL;
                aux=raiz;
                if(aux!=NULL){
                    while(aux->next!=NULL){
                        aux=(Genders*)aux->next;
                    }
                }
                if(raiz==NULL){
                    raiz=(Genders*)Songs;
                }
                else{
                    aux->next=(struct Genders*)Songs;
                }
            }
        }
    }

    return raiz;
}

int ReadSongs(Genders* raiz){
    FILE* files;
    Songs* Name;
    char* IdSong;//link
    char* Popularity;
    char* Mode;
    int err=0;
    int check;
    files= fopen("songs.txt","r");

    if(files==NULL){
        printf("Error: 'songs.txt' could not be opened\n");
        exit(1);
    }
    else{
        while(!feof(files)){
            IdSong= ReadLine(files,10,';');
            Popularity=ReadLine(files,10,';');
            Mode=ReadLine(files,10,'\n');

            if(strlen(IdSong)>0){
                Name=(Songs*)malloc(sizeof(Songs));
                Name->IdSong=IdSong;
                Name->Popularity=Popularity;
                Name->Mode=Mode;
                Name->next=NULL;

                err=InsertSong(raiz,Name,IdSong);
            }
    
        }
    }
    fclose(files);
    return err;
}

int InsertSong(Genders* raiz,Songs* Name,char* IdSong){
    Genders* aux;
    Songs* aux2;
    Songs* aux3;
    int err;
    aux=raiz;
    err=0;
    while((aux!=NULL) && strcmp(aux->IdSong,IdSong)!=0){
        aux=(Genders*)aux->next;
    }
    if(aux!=NULL){
        if(strcmp(aux->IdSong,IdSong)==0){
            aux2=(Songs*)aux->Entity;
            while(aux2!=NULL){
                if(strcmp(aux2->IdSong,Name->IdSong)==0){
                    break;
                }
                aux3=aux2;
                aux2=(Songs*)aux2->next; 
            }
            if(aux2!=NULL){
                
            }
            else{
                if(aux->Entity==NULL){
                    aux->Entity=(struct Songs*)Name;
                }
                else{
                    aux3->next=(struct Songs*)Name;
                }
            }
        }
    }
    return err;
}


char* ReadLine(FILE* files,size_t initial_size,char sep){
    char* song_data = NULL;
    int c;
    size_t len = 0;
    song_data = malloc(initial_size);
    if (!song_data){
        return NULL;
    }
    while ((c = fgetc(files)) != EOF && c == sep);
    while ((c != EOF) && (c != sep)){
        song_data[len] = c;
        len++;
        if (len == initial_size){
            song_data = realloc(song_data, initial_size += 10);
            if (!song_data) {
                return NULL;
            }
        }
        c = fgetc(files);
    }
    song_data[len] = 0;
    len++;
    Delimiter(song_data,"\t\n\v ");
    return realloc(song_data, len);
}

char* Delimiter(char* line, const char* seps){
  int i;
  if (seps == NULL) {
    seps = "\t\n\v ";
  }
  i = strlen(line) - 1;
  while (i >= 0 && strchr(seps, line[i]) != NULL) {
    line[i] = '\0';
    i--;
  }
  return line;
}

void Printer(Genders* raiz,char* gener_query){
    Genders* aux;
    Songs* aux2;
    aux=raiz;
    while(aux!=NULL){
        aux2=(Songs*)aux->Entity;
        if(aux2!=NULL){
            if(strcmp(gener_query,aux->Gender)==0){
                printf("%s %s %s %s %s\n",aux->Gender,aux2->IdSong,aux2->Mode,aux->By,aux2->Popularity);
            }
            aux2=(Songs*)aux2->next;
        }
        aux=(Genders*)aux->next;
    }
}


