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
    struct Artistas *next;
}Artistas;

typedef struct{
    char *Gender;
    struct Types *next;
}Types;

//Statements

     //Type Struct
Genders* ReadData(Genders*raiz);
Genders* ReadGenres(Genders* raiz);
Artistas* AddArtista(Artistas* ar,char*Nombre);

    //Type char
char* ReadLine(FILE* files,size_t initial_size,char sep);
char* Delimiter(char* line, const char* seps);

    //Type int
int ReadSongs(Genders* raiz);
int InsertSong(Genders* raiz,Songs* Name,char* IdSong);
int check(Artistas* ar,char*Name);

    //Type void
void Query1(Genders* raiz,char* gender_query,int populate);

//Main
int main(int argc, char **argv){
    Genders* raiz=NULL;
    Genders* aux;
    printf("Inicio de programa\n");
    if(argc==4){
        //Query1
        char *g=argv[1];
        char *gender_query=argv[2];
        int populate=atoi(argv[3]);
        int songs=1;
        if(g[1]=='g' && (populate>=0 && populate <=100) && (songs>0)){
            //Start query 1
            printf("Rellenando datos\n");
            raiz=ReadData(raiz);
            printf("Inicio de consulta\n");
            Query1(raiz,gender_query,populate);
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
            //raiz=ReadData(raiz);
            //Query2(raiz,mode_query);
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
    printf("Extrayendo generos\n");
    raiz= ReadGenres(raiz);
    printf("Extrayendo canciones\n");
    err= ReadSongs(raiz);
    aux=raiz;
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
        printf("Agadiendo generos, esto puede demorar unos minutos\n");
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
    fclose(files);
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
        printf("Anadiendo canciones parte 1, esto puede estar tardando\n");
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

//Para Query1
void Query1(Genders* raiz,char* gender_query, int populate){
    Genders* aux;
    Songs* aux2;
    Genders* aux3;
    Songs* aux4;
    Artistas* ar=NULL;
    char* artista;
    aux=raiz;
    aux3=raiz;
    float count;
    float points;
    char* artistas;
    float a;
    int l;
    printf("%s\n",gender_query);
    int err;
    while(aux!=NULL){//parte el reccorido
        aux2=(Songs*)aux->Entity;//para acceder a los puntos
        if(aux2!=NULL){
            if(strcmp(gender_query,aux->Gender)==0){//Filta por el genero
                points=0;
                count=0;
                while(aux3!=NULL){
                    aux4=(Songs*)aux3->Entity;
                    if(aux4!=NULL){
                        if(strcmp(aux3->By,aux->By)==0){
                        points+=atoi(aux4->Popularity);
                        count++;
                        //free(aux3->By);
                        }
                        aux4=(Songs*)aux4->next;
                    }
                    aux3=(Genders*)aux3->next;

                }
                aux3=raiz;
                l=check(ar,aux->By);
                if(l==1){

                }
                else{
                    if((points/count)> populate){
                        ar= AddArtista(ar,aux->By);
                        printf("\t%s:%.2f\n",aux->By,points/count);
                    }
                }
                a=0;
            }
            aux2=(Songs*)aux2->next;

        }
        aux=(Genders*)aux->next;
    }
    /*
    while(ar!=NULL){
        aux5=ar;
        ar=(Artistas*)ar->next;
        free(aux5);
    }
    */

}

Artistas* AddArtista(Artistas* ar,char* Nombre){
    Artistas* nuevoArtista,*aux;
    nuevoArtista=(Artistas*)malloc(sizeof(Artistas));
    //char* Nombre_aux;
    //Nombre_aux=you(Nombre,10,'\n');
    //nuevoArtista->Artist=Nombre_aux;
    nuevoArtista->Artist=Nombre;
    nuevoArtista->next=NULL;
    if(ar==NULL){
        ar=nuevoArtista;
    }
    else{
        aux=ar;
        while(aux->next!=NULL){
            aux=(Artistas*)aux->next;
        }
        aux=nuevoArtista;

    }
    return ar;
}
int check(Artistas* ar,char*Name){
    int err=0;
    Artistas* aux;
    aux=ar;
    while(aux!=NULL){
        if(strcmp(aux->Artist,Name)==0){
            err=1;
            break;
        }
        aux=(Artistas*)aux->next;
    }
    return err;

}

