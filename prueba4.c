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
  char *By;
  int ponits;
  struct C1* next;
}C1;
//Statements

Genders* ReadData(Genders* raiz,char* gender_query);
Genders* ReadGenres(Genders* raiz,char* gender_query);

char* ReadLine(FILE* files, size_t initial_size, char sep);
char* Delimiter(char* line, const char* seps);


int CheckGender(char *gender, int *counter);
int ReadSongs(Genders* raiz);
int AtoiPro(char *array);
int CheckSong(char *IdSong,Genders* raiz);
int InsertaCancion(Genders* raiz,Songs* Name,char* IdSong,char* Popularity);

void Printer(Genders* raiz);
void Leaks(Genders* raiz);
void Printer2(Genders* raiz,Songs* Name);
void prueba(Genders* raiz,char* gender_query);
void prueba2(Genders* raiz,char* gender_query);
//Main
int main(int argc, char **argv){
    char *gender_query=argv[1];
    Genders* raiz = NULL;
    Genders* aux;
    Songs* aux2;
    int songs=0;
    if(argc==4){
      char* g=argv[1];
      char* gender_query=argv[2];
      int populate= atoi(argv[3]);

      CheckGender(gender_query,&songs);

      if(g[1] == 'g' && (populate >= 0 && populate <= 100) && (songs>0) ){//Si ingresa g y una popularidad valida.
        raiz= ReadData(raiz,gender_query);
        prueba2(raiz,gender_query);
        //Printer(raiz);
      }
      else{
        printf("Error: the query is invalid\n");
        exit(1);
      }
    }
    else if(argc==3){
      char* p= argv[1];
      char* mood= argv[2];

      if(p[1]=='p' && (strcmp(mood,"Major")==0 || strcmp(mood,"Minor")==0)){
        printf("Constula 2\n");
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
    printf("Se encontro el genero con un total de %d matches\n", songs);
    Leaks(raiz);
    return 0;
    /*
    raiz = ReadGenres(raiz,gender_query);
    Printer(raiz);
    Leaks(raiz);
    */
    return 0;
}
//Functions
//Agrega informacion de genres.txt
Genders* ReadGenres(Genders* raiz,char* gender_query){
    FILE* files;
    files = fopen("genres.txt","r");
    Genders* Song;
    char* Gender;
    char* IdSong;
    char* By;
    Genders* aux;

    files = fopen("genres.txt","r");

    if (files == NULL){ 
        printf("Error: File 'genres.txt' could not be opened\n");
        exit(1);
    }
    
    while (!feof(files)){
        Gender = ReadLine(files,10,';');
        IdSong = ReadLine(files,10,';');
        By     = ReadLine(files,10,'\n');

        if (strcmp(Gender,gender_query)==0){
             Song= (Genders*)malloc(sizeof(Genders));
             Song->Gender=Gender;
             Song->IdSong=IdSong;
             Song->By=By;
             Song->Entity=NULL;
             Song->next = NULL;

             aux = raiz;
            if (aux != NULL){
                while (aux->next != NULL)
                {
                aux = (Genders*)aux->next;
                }
            }

            if (raiz == NULL){
                raiz = (Genders*)Song;

            }
            else 
            {
                aux->next = (struct Genders*)Song;
            }
        }
    }

    fclose(files);
    return raiz;
}
//Lee lineas de genres.txt
char* ReadLine(FILE* files, size_t initial_size, char sep)
{
  char* song_data = NULL;
  int c;
  size_t len = 0;

  /* asigna memoria */
  song_data = malloc(initial_size);

  if (!song_data){
     return NULL;
    }

    while ((c = fgetc(files)) != EOF && c == sep);

    while ((c != EOF) && (c != sep))
    {
      song_data[len] = c;
      len++;

      /* agrega memoria si lo necesita */
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
//Separa por ; cada informacion por orden
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
//Imprime estructura con informacion.
void Printer(Genders* raiz){
    Genders* aux;
    aux=raiz;
    while(aux!=NULL){

        printf("%s %s %s\n",aux->Gender,aux->IdSong,aux->By);
        aux=(Genders*)aux->next;
    }   
}
//Libera memoria para fuga
void Leaks(Genders* raiz){
    Genders* aux;
    while(raiz!=NULL){
        aux=raiz;
        raiz=(Genders*)raiz->next;
    }
}

//Mis funciones de mierda
int CheckGender(char *gender, int *counter){//Checkea si el genero ingresado es correcto
    FILE* files;
    files= fopen("genres.txt","r");

    int space = strlen(gender);
    char *type_of_gender = (char*)malloc(2*space*sizeof(char));

    char c = fgetc(files);
    int ct = 0;
    int total = 0;
    bool check = true;

    if (files != NULL){
        while (c != EOF){
            if (c != '\n') {
                if (c == ';' && check == true){
                    check = false;
                    //printf("%s / %s\n", type_of_gender, gender);
                    if (strcmp(gender, type_of_gender) == 0){
                        total ++;
                    }

                    for (int a = 0; a < space; a ++){
                        type_of_gender[a] = *"";
                    }
                }
                if (check == true){
                    type_of_gender[ct] = c;
                    ct ++;
                }
            }
            else if (c == '\n'){
                check = true;
                ct = 0;

                for (int a = 0; a < 2*space; a ++){
                    type_of_gender[a] = *"";
                }
            }
            c = fgetc(files);
        }
    }

    if (total > 0){
        *counter = total;
        free(type_of_gender);
        fclose(files);
        return 0;
    }
    else{
        printf("Error: Genere not founded\n");
        free(type_of_gender);
        fclose(files);
        exit(1);
    }
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

      
      Name=(Songs*)malloc(sizeof(Songs));
      Name->IdSong=IdSong;
      Name->Popularity=Popularity;
      Name->Mode=Mode;
      Name->next=NULL;

      err=InsertaCancion(raiz,Name,IdSong, Popularity);


         
      
       

    }
  }
  fclose(files);
  return err;


}

int InsertaCancion(Genders* raiz,Songs* Name,char* IdSong,char* Popularity){
  int err;
  Genders* aux;
  Songs* aux2;
  Songs* aux3;

  err=0;

  aux=raiz;
  while((aux!=NULL)&&(strcmp(aux->IdSong,IdSong)!=0)){
    aux=(Genders*)aux->next;
  }

  if(aux!=NULL){
    if(strcmp(aux->IdSong,IdSong)==0){
      aux2=(Songs*)aux->Entity;
      while(aux2!=NULL){
        if((strcmp(aux2->IdSong,Name->IdSong)==0)){
          break;//printf("Algo pasa aqui\n");
        }
        aux3=aux2;
        aux2=(Songs*)aux2->next;
      }


      if(aux->Entity==NULL){
        aux->Entity=(struct Songs*)Name;
      }
      else{
        aux3->next=(struct Songs*)Name;
      }
      //printf("Name->IdSong[%s] Name->Popularity[%s] Name->Mode[%s]\n",Name->IdSong,Name->Popularity,Name->Mode);
      
    }
  }
  return err;
}


int AtoiPro(char *array){
  int Popularity;
  Popularity=atoi(array);
  free(array);
  return Popularity;
}


//es que retorne la posicion donde se encuetra el dato

/*
void Printer2(Genders* raiz,Songs* Name){
  Genders* aux;
  Songs* aux2;

  aux=raiz;
  aux2=Name;
  printf("%s\n",aux->Gender);
  while(aux2!=NULL){
    printf("%s \n",aux2->Mode);
    aux2=(Songs*)aux2->next;
    //aux2=(Songs*)aux2->next;
  }
}
*/
Genders* ReadData(Genders* raiz,char* gender_query){
  int err;
  Genders* aux;
  raiz=ReadGenres(raiz,gender_query);

  err=ReadSongs(raiz);
  aux=raiz;

  while(aux!=NULL){
    aux=(Genders*)aux->next;
  }
  return raiz;
}

void prueba(Genders* raiz,char* gender_query){
  Genders* aux;
  Songs* aux2;
  Songs* aux3;
  aux=raiz;
  printf("%s\n",gender_query);
  while(aux!=NULL){
      //printf("%s %s\n",aux->IdSong,aux->By);
      aux2=(Songs*)aux->Entity;
      while(aux2!=NULL){
        if(strcmp(aux->Gender,gender_query)==0){
          printf("\t%s %s\n",aux->By,aux2->Popularity);
        }
        aux2=(Songs*)aux2->next;
      }
      aux=(Genders*)aux->next;
    }

  }

void prueba2(Genders* raiz,char* gender_query){
  Genders* aux;
  Songs* aux2;
  Songs* aux3;
  aux=raiz;
  printf("%s\n",gender_query);
  while(aux!=NULL){
      //printf("%s %s\n",aux->IdSong,aux->By);
      aux2=(Songs*)aux->Entity;
      while(aux2!=NULL){
        printf("\t%s %s\n",aux->By,aux2->Popularity);
        aux2=(Songs*)aux2->next;
      }
      aux=(Genders*)aux->next;
    }

  }



