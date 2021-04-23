#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define MAXCHAR 


int main(int argc, char **argv){

    if(argc ==4){//Consular po Generos Musicales
        char *g=argv[1];
        char *gender=argv[2];
        int populate= atoi(argv[3]);
        if(g[1]=='g' && (populate>=0 && populate<=100) ){//Si ingresa g y una popularidad valida.
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

        if(p[1]=='p' && (strcmp(mood,"Major")==0 || strcmp(mood,"Minor")==0)){//Si ingrsa p y selecciona el modo correcto-
            printf("Funciona\n");//
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


