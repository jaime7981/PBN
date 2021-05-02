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



int CheckGender(char *gender);
void SongsGener(char *gender,int *counter);
void Genderata(char *gender_query,int genre_songs, struct Genders *ptr);
bool check(char *linea,char *genero);

FILE *files;
int main(int argc, char **argv){

    if(argc ==4){//Consultar por Generos Musicales
        char *g=argv[1];
        char *gender=argv[2];
        int populate= atoi(argv[3]);
        CheckGender(gender);
        struct Genders  *songs_by_gender;
        if(g[1]=='g' && (populate>=0 && populate<=100) ){//Si ingresa g y una popularidad valida.
            int songs=0;
            SongsGener(gender,&songs);
            GenderData(gender,songs,songs_by_gender);
            printf("Cualquier Cancion----> Para checkear que se ingresaron bien los datos\
            \nCancion: %s\nArtista: %s\nGenero: %s\n\n",(songs_by_gender+1)->id,(songs_by_gender)->artist,(songs_by_gender+1)->tog);
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

void GenderData(char *gender_query,int genre_songs, struct Genders *ptr){

    files= fopen("genres.txt","r");
    int space= strlen(gender_query);
    char *gender_aux=(char*)malloc(space*sizeof(char));
    char c=fgetc(files);
    int songs=0;

    while(c!=EOF){

        for(int i=0;i<space;i++){//El genero ya esta checkeado, lo relleno para compararlo con el archivo.
            gender_aux[i]=c;
            c=fgetc(files);
        }

        if(c!='\n'){
            if(strcmp(gender_aux,gender_query)==0){//Aqui el c=fgetc(files)= ";", entra cuando identifica al genero.
                ptr[songs].tog=(char*)malloc(strlen(gender_aux)*sizeof(char));//Asigno memoria para guardar el genero. //Creo que esto no es neserario.
                strcpy(ptr[songs].tog,gender_aux); //Genero
                c= fgetc(files);//Avanza una letra para ingregando lo demas.

                int actual=2;
                int len=0;
                char *id_aux=(char*)malloc(actual*sizeof(char));
                while(c!='\n'){
                    if(len==actual){//Si necesita mas memoria.
                        actual+=2;//Lo agrande de a dos espacios.
                        char*id_aux2=(char*)realloc(id_aux,actual*sizeof(char));
                        if(!id_aux2){
                            printf("Song name too long for available memory. \n");
                        }
                        else{
                            id_aux=id_aux2;
                        }
                    }
                    else{
                        if(c!=';'){//Agrega letra siguiente de la cancion.
                            id_aux[len]=c;
                            len++;
                            c=fgetc(files);
                        }
                        else{//Desde aqui trabaja con el artista.
                            c=fgetc(files);
                            int actual2=1;
                            int len2=0;
                            char *artist_aux=(char*)malloc(actual2*sizeof(char));
                            while(c!='\n'){
                                artist_aux[len2]=c;
                                if(len2==actual2){//Si necesita mas memoria.
                                    actual2++;//Le agrego uno porque el largo es muy variable.
                                    char *artist_aux2=(char*)realloc(artist_aux,actual2*sizeof(char));
                                    if(!artist_aux2){
                                        printf("Artist name too long for available memory. \n");
                                    }
                                    else{
                                        artist_aux=artist_aux2;
                                    }
                                }
                                c=fgetc(files);
                                len2++;
                            }
                            ptr[songs].artist=(char*)malloc(strlen(artist_aux)*sizeof(char));//Asigno memoria para struct.
                            strcpy(ptr[songs].artist,artist_aux);
                            free(artist_aux);//Lo libero para nuevo artista.
                            actual2=1;
                            len2=0;
                            artist_aux=(char*)malloc(actual2*sizeof(char));
                            
                        }
                    }
                }
                ptr[songs].id=(char*)malloc(strlen(id_aux)*sizeof(char));//Asigno memoria para struct.
                strcpy(ptr[songs].id,id_aux);
                free(id_aux);//Lo libero ara nueva cancion.
                actual=2;
                len=0;
                id_aux=(char*)malloc(actual*sizeof(char));
                songs++;
            }
            else{
                free(gender_aux);
                gender_aux=(char*)malloc(space*sizeof(char));
            }
        }
        c=fgetc(files);
    }
    free(gender_aux);
    fclose(files);
}

void Cargar(char *genero, int songs){
    files= fopen("genres.txt", "r");
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
            ch=check(linea,genero);
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
	int j=strlen(genero);
	for(int i=0;i<j;i++){
		if(linea[i]!=genero[i]){
			return false;//retorna falso si encuentra una diferencia
		}

	}
	return true;
}
