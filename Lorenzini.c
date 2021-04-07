#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //Para pasar de Mayus a Mins toupper tulower
#include <time.h>

#define MAXCHAR 1000

int OpenFile(char filename[20], char playerone[10][10]);
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
bool VerifyShoot(int inputrow, int inputcols, char player[10][10], char player_enemy[10][10], int player_shoot, int takendown);

int BoatDown(int inputrow, int inputcols, char player_enemy[10][10]);

//Lo mismo que RowColumns solo que las separe porque no se me asignaban a las variables
int Row(int row, char user_input[5]);
int Columns(int col, char user_input[5]);



FILE *files;

int main(int argc, char *argv[]){
    char *gamemode;
    char *p1name;
    char *p2name;
    int p1_boatcounter = 0;
    int p2_boatcounter = 0;

    if (argc == 4){
        gamemode = argv[1];
        p1name = argv[2];
        p2name = argv[3];

        char playerone[10][10];
        p1_boatcounter = OpenFile(p1name, playerone);
        //PrintBoard(playerone);
        char player1field[10][10];//para tablero de ataque
        BoardAux(player1field); 

        char playertwo[10][10];
        p2_boatcounter = OpenFile(p2name, playertwo);
        //PrintBoard(playertwo);

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
            exit(1);
        }

    }
    else{
        printf("Error: Console Input is incorrect");
        exit(1);
    }
    return 0;
}

int OpenFile(char filename[20], char player[10][10]){
    char str[MAXCHAR];
    files = fopen(filename, "r");
    int boatcounter = 0;
    int X_counter = 0;
    
    if (files == NULL){
        printf("Error: Could not open file %s\n",filename);
        exit(1);
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
            //printf("boat: %s length: %d column: %c row: %d orientation: %c\n", type, len, col, row, orient);
            error = AddBoat(type, len, col, row, orient, player);
            X_counter += len;
            boatcounter ++;
            if (error == false){
                //printf("Boat added correctly\n");
            }
            else {
                printf("Error: Something with the boat settings went wrong\nUse line 142 for debuging the txt");
                exit(1);
            }
            counter = 1;
        }
        fclose(files);
    }
    //printf("Player: %d X\nPlayer boats: %d\n", X_counter, boatcounter);
    return boatcounter;
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

    printf("\nShoot your enemy! exit game(e)\n");
    fgets(user_input, 100, stdin);
    
    if(user_input[0]==101){
        exit(0);
    }
    if (strlen(user_input) > 4){
        printf("Error: invalid input\n");
        return false;
    }

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
    bool pass_turn = true;

    bool inputcheck;
    bool shootcheck;

    int pone_shoots = 0;
    int ptwo_shoots = 0;

    int pone_TakenDown = 0;
    int ptwo_TakenDown = 0;
    PrintBoard(player1field);

    while (continue_game) {
        char user_input[5];
        int inputrow;
        int inputcol;
        
        printf("P1 Boats taken down: %d\n", pone_TakenDown);

        if (player_one_turn){
            printf("\nTurno del jugador 1:\n");
            inputcheck = UserInput(user_input);
            inputrow = Row(inputrow, user_input);
            inputcol = Columns(inputcol,user_input);
            shootcheck = VerifyShoot(inputrow,inputcol,player1field,playertwo, pone_shoots, pone_TakenDown);

            if (inputcheck == false || shootcheck == false){
                player_one_turn = true;
                pass_turn = false;
            }
            else{
                player_one_turn = false;
                pass_turn = true;
                PrintBoard(player2field);
            }
        }
        else {
            while (true){
                printf("\nTurno del jugador 2:\n");
                inputcheck = UserInput(user_input);
                inputrow = Row(inputrow, user_input);
                inputcol = Columns(inputcol,user_input);
                shootcheck = VerifyShoot(inputrow,inputcol,player2field,playerone, ptwo_shoots, ptwo_TakenDown);
                if (inputcheck){
                    break;
                }
            }
            if (inputcheck == false || shootcheck == false){
                player_one_turn = false;
                pass_turn = false;
            }
            else{
                player_one_turn = true;
                pass_turn = true;
                PrintBoard(player1field);
            }
        }
    }
}

void AutomatedGame(char player1field[10][10],char player2field[10][10],char playerone[10][10],char playertwo[10][10]){
    bool continue_game = true;
    bool player_one_turn = true;
    bool check_automated_shot = true;
    bool pass_turn = true;

    int pone_shoots = 0;
    int ptwo_shoots = 0;

    int pone_TakenDown = 0;
    int ptwo_TakenDown = 0;

    bool inputcheck;
    bool shootcheck;

    srand(time(0));

    while (continue_game) {
        char user_input[4];
        int inputrow;
        int inputcol;

        int pcinputrow;
        int pcinputcol;

        printf("P1 Boats taken down: %d\n", pone_TakenDown);
        
        if (player_one_turn){
            printf("\nTurno del jugador 1:\n");
            inputcheck = UserInput(user_input);
            inputrow = Row(inputrow, user_input);
            inputcol = Columns(inputcol,user_input);
            shootcheck = VerifyShoot(inputrow,inputcol,player1field,playertwo, pone_shoots, pone_TakenDown);

            if (inputcheck == false || shootcheck == false){
                player_one_turn = true;
                pass_turn = false;
            }
            else{
                player_one_turn = false;
                pass_turn = true;
                PrintBoard(player2field);
            }
        }
        else {
        	printf("\nPC plays:\n");
            while (true)
            {
                pcinputrow = rand()%9;
                pcinputcol = rand()%9;
                check_automated_shot = VerifyShoot(inputrow,inputcol,player2field,playerone, ptwo_shoots, ptwo_TakenDown); //Que verifique el tiro
                if (check_automated_shot == true){
                    break;
                }
            }
            PrintBoard(player1field);
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
bool VerifyShoot(int inputrow, int inputcols, char player[10][10], char player_enemy[10][10], int player_shoot, int takendown){
    PrintBoard(player_enemy);
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

                int enemyX;
                int playerX;

                enemyX = BoatDown(inputrow, inputcols, player_enemy);
                playerX = BoatDown(inputrow, inputcols, player);

                printf("Enemy X: %d\nPlayer X: %d\n", enemyX, playerX);
                if (enemyX == playerX){
                    printf("Boat Down!!");
                    takendown ++;
                }
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

int BoatDown(int inputrow, int inputcols, char player_enemy[10][10]){
    int counter;
    int boats_X = 1;
    int boats__ = 0;
    bool space = false;

    if (inputrow < 9){ //checkea si hay X abajo
        counter = 1;
        if (player_enemy[inputrow + counter][inputcols] == 88){
            while (true) {
                if (player_enemy[inputrow + counter][inputcols] == 95){ 
                    boats__ ++;
                    space = false;
                    break;
                }
                else if (player_enemy[inputrow + counter][inputcols] == 46) {
                    break;
                }
                else if (player_enemy[inputrow + counter][inputcols] == 88) {
                    boats_X ++;
                }
                else {
                    break;
                }
                counter ++;
            }
        }
    }
    if (inputcols > 0) { //checkea si hay X arriba
        counter = 1;
        if (player_enemy[inputrow - counter][inputcols] == 88){ // izquierda
            while (true) {
                if (player_enemy[inputrow - counter][inputcols] == 95){
                    boats__ ++;
                    space = false;
                    break;
                }
                else if (player_enemy[inputrow - counter][inputcols] == 46) {
                    break;
                }
                else if (player_enemy[inputrow - counter][inputcols] == 88) {
                    boats_X ++;
                }
                else {
                    break;
                }
                counter ++;
            }
        }
    }
    if (inputcols < 9){ //checkea si hay X a la derecha
        counter = 1;
        if (player_enemy[inputrow][inputcols + counter] == 88){ // ve si a la derecha hay X
            while (true) {
                if (player_enemy[inputrow][inputcols + counter] == 95){ 
                    boats__ ++;
                    space = false;
                    break;
                }
                else if (player_enemy[inputrow][inputcols + counter] == 46) {
                    break;
                }
                else if (player_enemy[inputrow][inputcols + counter] == 88) {
                    boats_X ++;
                }
                else {
                    break;
                }
                counter ++;
            }
        }
    }
    if (inputcols > 0) { //checkea si hay X a la izquierda
        counter = 1;
        if (player_enemy[inputrow][inputcols - counter] == 88){ // izquierda
            while (true) {
                if (player_enemy[inputrow][inputcols - counter] == 95){
                    boats__ ++;
                    space = false;
                    break;
                }
                else if (player_enemy[inputrow][inputcols - counter] == 46) {
                    break;
                }
                else if (player_enemy[inputrow][inputcols - counter] == 88) {
                    boats_X ++;
                }
                else {
                    break;
                }
                counter ++;
            }
        }
    }
    return boats_X;
}


// Funciones de parametros
int Row(int row, char user_input[4]){
	return user_input[2]-48;
}

int Columns(int col, char user_input[4]){
	return (int)user_input[0]-65;
}