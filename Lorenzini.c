#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //Para pasar de Mayus a Mins toupper tulower
#include <time.h>

#define MAXCHAR 1000

void OpenFile(char filename[20], char playerone[10][10]);
bool AddBoat(char type[30], int len, char col, int row, char orient, char playerboard[10][10]);
void PrintBoard(char playerboard[10][10]);
bool UserInput(char user_input[4]);
void RowColumns(int row, int col, char user_input[4]);

//Agrege parametros para ir jugando con los tableros de ataque y los del barco

// Esta funcion no se va a poder usar en juego automatizado, pq el bot va a tender a ingresar coordenadas anteriores
// HAbria que crae una funcion parecida y que le diga al bot que no use esas coordenadas
void Game(char player1field[10][10],char player2field[10][10],char playerone[10][10],char playertwo[10][10]);
void AutomatedGame(char player1field[10][10],char player2field[10][10],char playerone[10][10],char playertwo[10][10]);


//Funciones Jota

//Para crear los tableros de ataque
void BoardAux(char player[10][10]); 

//Para verificar que el tiro hizo impacto, hundido o agua y tambien que avise si tiro un lugar ya atacado (pierde turno)
bool VerifyShoot(int inputrow, int inputcols, char player[10][10], char player_enemy[10][10]);

//Lo mismo que RowColumns solo que las separe porque no se me asignaban a las variables
int Row(int row, char user_input[5]);
int Columns(int col, char user_input[5]);



FILE *files;

int main(int argc, char *argv[]){
    char *gamemode;
    char *p1name;
    char *p2name;

    if (argc == 4){
        gamemode = argv[1];
        p1name = argv[2];
        p2name = argv[3];

        char playerone[10][10];
        OpenFile(p1name, playerone);
        PrintBoard(playerone);

        char player1field[10][10];//para tablero de ataque
        BoardAux(player1field); 

        char playertwo[10][10];
        OpenFile(p2name, playertwo);
        PrintBoard(playertwo);

        char player2field[10][10];//para tablero de ataque
        BoardAux(player2field);

        if (gamemode[1] == *"a"){
            printf("Gamemode: Automated\n");
            AutomatedGame(player1field,player2field,playerone,playertwo);
        }
        else if (gamemode[1] == *"v"){
            printf("Gamemode: Vesus\n");
            Game(player1field,player2field,playerone,playertwo);
        }
        else {
            printf("Error: gamemode is incorrect");
            printf("Something with the boat settings went wrong");
            exit(1);
        }

    }
    else{
        printf("Error: Console Input is incorrect");
        exit(1);
    }
    return 0;
}

void OpenFile(char filename[20], char player[10][10]){
    char str[MAXCHAR];
    files = fopen(filename, "r");
    
    if (files == NULL){
        printf("Could not open file %s\n",filename);
    }
    else{
        int counter = 1;
        for (int a = 0; a < sizeof(*player); a++){
            for (int b = 0; b < sizeof(player[a]); b++){
                player[a][b] = *"_";
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
            error = AddBoat(type, len, col, row, orient, player);
            if (error == false){
                //printf("Boat added correctly\n");
            }
            else {
                printf("Something with the boat settings went wrong");
                exit(1);
            }
            
            counter = 1;
        }
        fclose(files);
    }
}

bool AddBoat(char type[30], int len, char col, int row,char orient, char playerboard[10][10]){
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


bool UserInput(char user_input[4]){
    printf("Shoot your enemy! exit game(e)\n");
    fgets(user_input, 100, stdin);
    
    if(user_input[0]==101) exit(0);
    	
    else {
    	user_input[0] = toupper(user_input[0]); //Si no ingreso la columna el Mayus, que lo cuente igual
        if(user_input[0]>64 && user_input[0]<75 ){
            
        }
        else {
            printf("ERORR no pusiste bien el parametro de columna\n");
            return false;
        }
        if(user_input[2]>47 && user_input[2]<58){
            
        }
        else {
            printf("ERROR:No pusiste bien el parametro de fila\n");
            return false;
        }
    }

    return true;
}

void RowColumns(int row, int col, char user_input[4]){
    for (int a = 0; a < user_input[a]!=0; a++){
        int inputaux = (int)user_input[a];
        printf("%d\n",inputaux);
        if (inputaux == 101){
            exit(0);
        }
        else {
        	if (inputaux < 58 && inputaux > 47){	
            		row = inputaux - 48;
            		break;
        	}
        	if (inputaux < 75 && inputaux > 64) {
            		col = inputaux - 65;
            		break;
        	}	
        }
        
    }
    printf("col: %d row: %d\n", col, row);
}


void Game(char player1field[10][10],char player2field[10][10],char playerone[10][10],char playertwo[10][10]){
    bool continue_game = true;
    bool player_one_turn = true;
    while (continue_game) {
        char user_input[5];
        int inputrow;
        int inputcol;
        bool inputcheck = true;

        if (player_one_turn){
        	printf("Turno del jugador 1:\n");
            PrintBoard(player1field);
            while (true){
                UserInput(user_input);
                inputrow = Row(inputrow, user_input);
                inputcol = Columns(inputcol,user_input);
                inputcheck = VerifyShoot(inputrow,inputcol,player1field,playertwo);
                if (inputcheck){
                    break;
                }
            }
            player_one_turn = false;
        }
        else {
        	printf("Turno del jugador 2:\n");
        	PrintBoard(player2field); //Que muestre el tablero de ataque
            while (true){
                UserInput(user_input);
                inputrow = Row(inputrow, user_input);
                inputcol = Columns(inputcol,user_input);
                inputcheck = VerifyShoot(inputrow,inputcol,player2field,playerone);
                if (inputcheck){
                    break;
                }
            }
            player_one_turn = true; //Cambia de turno
        }
    }
}

void AutomatedGame(char player1field[10][10],char player2field[10][10],char playerone[10][10],char playertwo[10][10]){
    bool continue_game = true;
    bool player_one_turn = true;
    bool check_automated_shot = true;

    srand(time(0));

    while (continue_game) {
        char user_input[5];
        int inputrow;
        int inputcol;

        int pcinputrow;
        int pcinputcol;
        bool inputcheck = true;

        if (player_one_turn){
        	printf("Turno del jugador 1:\n");
            PrintBoard(player1field);
            while (true){
                UserInput(user_input);
                inputrow = Row(inputrow, user_input);
                inputcol = Columns(inputcol,user_input);
                inputcheck = VerifyShoot(inputrow,inputcol,player1field,playertwo);
                if (inputcheck){
                    break;
                }
            }
            player_one_turn = false;
        }
        else {
        	printf("PC plays:\n");
        	PrintBoard(player2field); //Que muestre el tablero de ataque
            while (true)
            {
                pcinputrow = rand()%9;
                pcinputcol = rand()%9;
                check_automated_shot = VerifyShoot(inputrow,inputcol,player2field,playerone); //Que verifique el tiro
                if (check_automated_shot == true){
                    break;
                }
            }
            player_one_turn = true; //Cambia de turno
        
        }
    }
}


// Funcion de tablero de ataque
void BoardAux(char player[10][10]){
	
	
	//printf("\n  A  B  C  D  E  F  G  H  I  J\n");
	for(int i=0;i<10;i++){
		//printf("%d",i);
		for(int j=0;j<10;j++){
			player[i][j]=*"_";
			//printf("[%c]",player[i][j]);
		}
		//printf("%d\n",i);
	}
	//printf("  A  B  C  D  E  F  G  H  I  J\n");
}

// Funcion verificadora de tiro
bool VerifyShoot(int inputrow, int inputcols, char player[10][10], char player_enemy[10][10]){
	if(player_enemy[inputrow][inputcols]==95){//No le achunto  //95 es _
		if(player[inputrow][inputcols]==95){//Que verifique que no haya marcado la misma posicion antes
			printf("Agua!\n");
			printf("\n");
			printf("--------------------------\n");
			printf("\n");
			player[inputrow][inputcols]=*".";
		}
		else{
			printf("Ya disparaste en esa zona!\n");
			printf("\n");
			printf("--------------------------\n");
			printf("\n");
            return false;
		}	
	}
	else {
		//Que verifique si no puso la misma coordenada que una jugada anterior
		if(player_enemy[inputrow][inputcols]==88){
			if(player[inputrow][inputcols]!=88){ //Que verifique que no haya marcado 
							      //la misma posicion antes ya habiendo hecho un impacto
				printf("Impacto!\n");//88 es X
				printf("\n");
				printf("--------------------------\n");
				printf("\n");
				player[inputrow][inputcols]=*"X";
			}
			else{
			printf("Ya disparaste en esa zona!\n");
			printf("\n");
			printf("--------------------------\n");
			printf("\n");
            return false;
			}
		}
	}
    return true;
}


// Funciones de parametros
int Row(int row, char user_input[4]){
	return user_input[2]-48;
}

int Columns(int col, char user_input[4]){
	return (int)user_input[0]-65;
}