#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define MAXCHAR 

struct Genders{
    char *tog;
    char *id;
    char *artist;
};


int CheckGender(char *gender,  int *counter);
void SongsGener(char *gender,int *counter);
void GenderData(char *gender_query,int genre_songs, struct Genders *ptr);
bool check(char *linea,char *genero);

FILE *files;
int main(int argc, char **argv){

    if(argc == 4){//Consultar por Generos Musicales
        char *g = argv[1];
        char *gender = argv[2];
        int populate = atoi(argv[3]);
        int songs = 0;

        CheckGender(gender, &songs);
        printf("Se encontro el genero con un total de %d matches\n", songs);

        struct Genders *songs_by_gender;

        if(g[1] == 'g' && (populate >= 0 && populate <= 100) ){//Si ingresa g y una popularidad valida.
            
            GenderData(gender, songs, songs_by_gender);

            for (int a = 1; a < songs; a ++){
                printf("Cancion: %s\nArtista: %s\nGenero: %s\n\n",(songs_by_gender + a)->id, (songs_by_gender + a)->artist, (songs_by_gender + a)->tog);
            }
            printf("Funciona\n");
        }
        else{
            printf("Error: the query is invalid\n");
            exit(1);
        }
    }
    else if(argc == 3){//Consultar Canciones por modo
        char *p = argv[1];
        char *mood = argv[2];

        if(p[1] == 'p' && (strcmp(mood,"Major") == 0 || strcmp(mood,"Minor") == 0)){//Si ingrsa p y selecciona el modo correcto
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

int CheckGender(char *gender, int *counter){//Checkea si el genero ingresado es correcto
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
<<<<<<< HEAD
    printf("The genre is not found in the database, please try again.\n");
    free(type_of_gender);
    fclose(files);
    exit(1);
}

void SongsGener(char *gender, int *counter){
    files = fopen("genres.txt","r");

    int space = strlen(gender);
    char *type_of_gender = (char*)malloc(space*sizeof(char));

    char c = fgetc(files);
    int total = 0;

    printf("Estoy pegado en un while?\n");

    while(c != EOF){
        if(c == '\n'){
            //printf("%c\n", c); Saltos de linea
            if (){
                total ++;
            }
            
        }
        else {
            //printf("%c", c); Letras
        }
        c = fgetc(files);
    }

    /*
    while(c != EOF){
        if(c != '\n'){

            c = fgetc(files);
                
            if(strcmp(type_of_gender,gender) == 0){
                (*counter)++;
            }
            else{
                free(type_of_gender);
                type_of_gender = (char*)malloc(space*sizeof(char));
            }
        }
        c = fgetc(files);
    }*/

    printf("%d / %d\n",counter,total);
    free(type_of_gender);
    fclose(files);
=======
>>>>>>> 43c77c8f6725efbaeca259642dc9e603dc73080a
}

void GenderData(char *gender_query, int genre_songs, struct Genders *ptr){
    files = fopen("genres.txt","r");

    int space = strlen(gender_query);
    char *gender_aux = (char*)malloc(2*space*sizeof(char));
    char c = fgetc(files);
    int counter = 0;

    ptr = (struct Genders*) malloc(counter*sizeof(struct Genders));

    while(c != EOF){

        for(int i = 0; i < space; i++){//El genero ya esta checkeado, lo relleno para compararlo con el archivo.
            gender_aux[i] = c;
            c = fgetc(files);
        }

        if(c != '\n'){
            if(strcmp(gender_aux,gender_query) == 0){//Aqui el c=fgetc(files)= ";", entra cuando identifica al genero.
                //ptr[songs].tog=(char*)malloc(strlen(gender_aux)*sizeof(char));  Asigno memoria para guardar el genero. //Creo que esto no es neserario.
                ptr = (struct Genders*) realloc(ptr, (counter + 1)*sizeof(struct Genders));

                strcpy((ptr + counter)->tog, gender_aux);
                //strcpy(ptr[songs].tog,gender_aux); //Genero

                c= fgetc(files);//Avanza una letra para ingregando lo demas.
                int actual = 2;
                int len = 0;
                char *id_aux = (char*)malloc(actual*sizeof(char));

                while(c != '\n'){
                    if(len == actual){//Si necesita mas memoria.
                        actual += 2;//Lo agrande de a dos espacios.
                        char*id_aux2 = (char*)realloc(id_aux,actual*sizeof(char));
                        if(!id_aux2){
                            printf("Song name too long for available memory. \n");
                        }
                        else{
                            id_aux = id_aux2;
                        }
                    }
                    else{
                        if(c != ';'){//Agrega letra siguiente de la cancion.
                            id_aux[len] = c;
                            len++;
                            c = fgetc(files);
                        }
                        else{//Desde aqui trabaja con el artista.
                            c = fgetc(files);
                            int actual2 = 1;
                            int len2 = 0;
                            char *artist_aux = (char*)malloc(actual2*sizeof(char));
                            while(c != '\n'){
                                artist_aux[len2] = c;
                                if(len2 == actual2){//Si necesita mas memoria.
                                    actual2++;//Le agrego uno porque el largo es muy variable.
                                    char *artist_aux2 = (char*)realloc(artist_aux,actual2*sizeof(char));
                                    if(!artist_aux2){
                                        printf("Artist name too long for available memory. \n");
                                    }
                                    else{
                                        artist_aux = artist_aux2;
                                    }
                                }
                                c = fgetc(files);
                                len2++;
                            }
                            //ptr[songs].artist=(char*)malloc(strlen(artist_aux)*sizeof(char));//Asigno memoria para struct.
                            strcpy((ptr + counter)->artist,artist_aux);

                            free(artist_aux);//Lo libero para nuevo artista.
                            actual2 = 1;
                            len2 = 0;
                            artist_aux = (char*)malloc(actual2*sizeof(char));
                            
                        }
                    }
                }

                //ptr[songs].id=(char*)malloc(strlen(id_aux)*sizeof(char));//Asigno memoria para struct.
                strcpy((ptr + counter)->id,id_aux);
                free(id_aux);//Lo libero ara nueva cancion.
                actual = 2;
                len = 0;
                id_aux = (char*)malloc(actual*sizeof(char));
                counter++;
            }
            else{
                free(gender_aux);
                gender_aux = (char*)malloc(space*sizeof(char));
            }
        }
        c = fgetc(files);
    }

    free(gender_aux);
    fclose(files);
}

void Cargar(char *genero, int songs){
    files = fopen("genres.txt", "r");

    int canciones_revisadas = 0; 
    int cantidad_canciones = 0; 
    char c = fgetc(files);
    int initial_size = 2; 
    int actual_size = initial_size;
    int letras_agregadas = 0;
    char *linea = malloc(sizeof(char)*initial_size);  	
    char *token;

    while (c != EOF){ 
    	bool ch=true;
        if (c == '\n'){
          
            linea[letras_agregadas] = 0; 
            ch = check(linea,genero);
            //printf("%s\n", artista);
            //break;
            if(ch){
                printf("%s\n",linea);//Printea la linea entera Ej Movie;09JiiTTzyna9MmQMgfzxnv;Amalya
                token=strtok(linea,";");
                printf("%s\n",token);//Movie
                token=strtok(NULL,";");
                printf("%s\n",token);//09JiiTTzyna9MmQMgfzxnv
                token=strtok(NULL,";");
                printf("%s\n",token);//Amalya
                token=strtok(NULL,";");
                cantidad_canciones++;   	 	
            }
            free(linea); // Libera la linea para qu epueda usarla en la siguiente.
            canciones_revisadas++;
            linea = (char*)malloc(sizeof(char)*initial_size); 
            actual_size = initial_size; 
            letras_agregadas = 0; 
        }
	
        else{
            if (letras_agregadas == actual_size){
   
                actual_size *= 3;
                actual_size /= 2;
                char *p = (char*)realloc(linea, sizeof(char) * actual_size);                                          
                if(!p){//checkea si no queda memoria
                    
                }
                else{
                    linea = p;
                } 
                

            }
            linea[letras_agregadas] = c;//le agrega la letra
            letras_agregadas++;
        }
        c = fgetc(files);//itera letra
    }
    fclose(files);
    //printf("Canciones revisadas: %d\n", canciones_revisadas); 
    //printf("%d Canciones.\n", cantidad_canciones); 

}

bool check(char *linea,char *genero){//Checke si la linea corresponde al genero consultado	
	int j = strlen(genero);

	for(int i = 0; i < j; i++){
		if(linea[i] != genero[i]){
			return false;//retorna falso si encuentra una diferencia
		}
	}
	return true;
}
