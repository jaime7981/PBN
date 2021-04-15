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
void Game(char filename1[10],char filename2[10],char player1field[10][10],char player2field[10][10],char playerone[10][10],char playertwo[10][10], int Counters[2]);
void AutomatedGame(char filenam1[10],char filename2[10],char player1field[10][10],char player2field[10][10],char playerone[10][10],char playertwo[10][10], int Counters[2]);
void BoardAux(char player[10][10]); 
bool VerifyShoot(int inputrow, int inputcols, char player[10][10], char player_enemy[10][10]);
int BoatDown(char filename_enemy[10],int inputrow, int inputcols, char player_enemy[10][10],char playerfield[10][10], int *playerX);
int Row(int row, char user_input[5]);
int Columns(int col, char user_input[5]);



FILE *files;

int main(int argc, char *argv[]){
    char *gamemode;
    char *p1name;
    char *p2name;
    char str1[MAXCHAR];
    char *txt=".txt";
    int p1_boatcounter = 0;
    int p2_boatcounter = 0;
    int p1_X_counter = 0;
    int p2_X_counter = 0;

    if (argc == 4){
        gamemode = argv[1]; //modo de juego
        p1name = argv[2]; //archivo player1
        p2name = argv[3];//archivo player2/Pc
	    strcpy(str1,p1name);//para formato .txt  
	    strcat(str1,txt);
	    strcat(p2name,txt);

        char playerone[10][10];//para tablero con barcos
        p1_boatcounter = OpenFile(str1, playerone); //cantidad de barcos
        //PrintBoard(playerone);
        //printf("Cantidad barcos p1: %d, cantidad de X: %d\n",p1_boatcounter,p1_X_counter);
        char player1field[10][10];//para tablero de ataque
        BoardAux(player1field); 

        char playertwo[10][10];
        p2_boatcounter = OpenFile(p2name, playertwo);
        //printf("Cantidad barcos p2: %d, cantidad de X: %d\n",p2_boatcounter,p2_X_counter);
        //PrintBoard(playertwo);
        char player2field[10][10];
        BoardAux(player2field);

        int Counters[2] = {p1_boatcounter, p2_boatcounter};

        if (gamemode[1] == *"a"){
            printf("Gamemode: Automated\n");
            AutomatedGame(str1,p2name,player1field,player2field,playerone,playertwo, Counters);
            
        }
        else if (gamemode[1] == *"v"){
            printf("Gamemode: Vesus\n");
            Game(str1,p2name,player1field,player2field,playerone,playertwo, Counters);
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
    system("pause");
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
        BoardAux(player);

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
    //*p_X_counter = X_counter; 
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

bool UserInput(char user_input[4]){

    printf("\nShoot your enemy! exit game(s)\n");
    fgets(user_input, 100, stdin);
    
    if(user_input[0]==115){ // 115 es s
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

void Game(char filename1[10],char filename2[10],char player1field[10][10],char player2field[10][10],char playerone[10][10],char playertwo[10][10], int Counters[2]){
    bool continue_game = true;
    bool player_one_turn = true;
    bool pass_turn = true;

    bool inputcheck;
    bool shootcheck;
    
    int p1boatdown=0;
    int p2boatdown=0;
    //PrintBoard(player1field);
    while (continue_game) {
        char user_input[5];
        int inputrow;
        int inputcol;
        int enemyX;
        int playerX=1;
        bool won=false;
        if (player_one_turn){
            printf("\nTurno del jugador 1:\n");
            PrintBoard(player1field);
            inputcheck = UserInput(user_input);
            inputrow = Row(inputrow, user_input);
            inputcol = Columns(inputcol,user_input);
            shootcheck = VerifyShoot(inputrow, inputcol, player1field, playertwo);

            if (inputcheck == false || shootcheck == false){
                player_one_turn = true;
                pass_turn = false;
            }
            else{
                enemyX= BoatDown(filename2,inputrow,inputcol,playertwo,player1field,&playerX);//Cantidad de X del bote
                //printf("Largo barco enemigo: %d. Lo que he abatido: %d\n",enemyX, playerX);
                if(enemyX==playerX){
                    printf("Hundido!\n");
                    printf("--------------------------\n");
                    p1boatdown++;
                    if(p1boatdown>=Counters[0]&& p2boatdown<=Counters[1]){
                        printf("Jugador 1 Gana\n");
                        printf("Boats\n");
                        printf("Player1:\n");
                        PrintBoard(playerone);
                        printf("\n");
                        printf("Player 2:\n");
                        PrintBoard(playertwo);
                        exit(0);
                    }
                }
                else{
                	printf("--------------------------\n");
                }
                player_one_turn = false;
                pass_turn = true;
                //PrintBoard(player2field);
            }
        }
        else {
            printf("\nTurno del jugador 2:\n");
            PrintBoard(player2field);
            inputcheck = UserInput(user_input);
            inputrow = Row(inputrow, user_input);
            inputcol = Columns(inputcol,user_input);
            shootcheck = VerifyShoot(inputrow, inputcol, player2field, playerone);
            if (inputcheck == false || shootcheck == false){
                player_one_turn = false;
                pass_turn = false;
            }
	    else{
                enemyX= BoatDown(filename1,inputrow,inputcol,playerone,player2field,&playerX);//Cantidad de X del bote
                //printf("Largo barco enemigo: %d. Lo que he abatido: %d\n",enemyX, playerX);
                
                if(enemyX==playerX){
                    printf("Hundido!\n");
                    printf("--------------------------\n");
                    p1boatdown++;
                    
                    if(p1boatdown<=Counters[0] && p2boatdown>=Counters[2]){
                    	printf("Jugador 2 Gana\n");
                        printf("Boats\n");
                        printf("Player2:\n");
                        PrintBoard(playertwo);
                        printf("\n");
                        printf("Player 1:\n");
                        PrintBoard(playerone);
                    	exit(0);
                    }
                }
                else{
                	printf("--------------------------\n");
                }
                player_one_turn = true;
		pass_turn = true;
	   }
                  
        }
    }
}

void AutomatedGame(char filename1[10], char filename2[10],char player1field[10][10],char player2field[10][10],char playerone[10][10],char playertwo[10][10], int Counters[2]){
    bool continue_game = true;
    bool player_one_turn = true;
    bool check_automated_shot = true;
    bool pass_turn = true;

    int p1boatdown = 0;
    int pcboatdown = 0;

    int p1_Xs = 0;
    int p2_Xs = 0;

    bool inputcheck;
    bool shootcheck;

    srand(time(0));
    //PrintBoard(player1field);

    while (continue_game) {
        char user_input[4];
        int inputrow;
        int inputcol;
	int enemyX;
	int playerX=1;
        int pcinputrow;
        int pcinputcol;
        
        if (player_one_turn){
            printf("\nTurno del jugador 1:\n");
            PrintBoard(player1field);
            inputcheck = UserInput(user_input);
            inputrow = Row(inputrow, user_input);
            inputcol = Columns(inputcol,user_input);
            shootcheck = VerifyShoot(inputrow, inputcol, player1field, playertwo);

            if (inputcheck == false || shootcheck == false){
                player_one_turn = true;
                pass_turn = false;
            }
            else{
            
            	enemyX= BoatDown(filename2,inputrow,inputcol,playertwo,player1field,&playerX);
            	//printf("Largo barco enemigo: %d. LO que ha abatido: %d\n",enemyX,playerX);
            	
            	if(enemyX==playerX){
            		printf("Hundido!\n");
            		printf("--------------------------\n");
            		p1boatdown++;
            		if(p1boatdown>=Counters[0] && pcboatdown<=Counters[1]){
            			printf("Jugador 1 Gana\n");
                        	printf("Boats\n");
                        	printf("Player1:\n");
                        	PrintBoard(playerone);
                        	printf("\n");
                        	printf("PC player:\n");
                        	PrintBoard(playertwo);
            			exit(0);
            		}
            	}
            	else{
            		printf("--------------------------\n");
            	}
            	player_one_turn= false;
            	pass_turn= true;
            }
         }
         else{
         	printf("\nPc plays:\n");
         	while(true){
         		pcinputrow= rand()%9;
         		pcinputcol= rand()%9;
         		check_automated_shot= VerifyShoot(pcinputrow, pcinputcol, player2field, playerone);
         		if(check_automated_shot==true){
         			break;
         		}
         	}
         	
         	enemyX=BoatDown(filename1,pcinputrow,pcinputcol,playerone,player2field,&playerX);
         	//printf("Largo barco enemigo: %d. LO abatido: %d",enemyX, playerX);
         	
         	if(enemyX==playerX){
         		printf("Hundido!\n");
         		printf("--------------------------\n");
         		pcboatdown++;
         		if(p1boatdown>=Counters[0] && pcboatdown<=Counters[1]){
         			printf("La maquina Gana\n");
                    		printf("Boats\n");
                    		printf("PC player:\n");
                    		PrintBoard(playertwo);
                    		printf("\n");
                    		printf("Player 1:\n");
                    		PrintBoard(playerone);
         			exit(0);
         		}
         	}
         	else{
         		printf("--------------------------\n");
         	}
         	//PrintBoard(player1field);
         	player_one_turn= true;//Cambia turno
         	pass_turn=true;
         	//PrintBoard(player2field);
         }     
     }  
}


bool VerifyShoot(int inputrow, int inputcols, char player[10][10], char player_enemy[10][10]){
	if(player_enemy[inputrow][inputcols]==95){//No le achunto  //95 es _
		if(player[inputrow][inputcols]==95){//Que verifique que no haya marcado la misma posicion antes
			printf("Agua!\n");
			printf("\n");
			//printf("--------------------------\n");
			printf("\n");
			player[inputrow][inputcols]=*".";
		}
		else{
			printf("Ya disparaste en esa zona!\n");
			printf("\n");
			//printf("--------------------------\n");
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
				player[inputrow][inputcols]=*"X";
			}
			else{
			printf("Ya disparaste en esa zona!\n");
			printf("\n");
			//printf("--------------------------\n");
			printf("\n");
            return false;
			}
		}
	}
    return true;
}

int BoatDown(char filename_enemy[10],int inputrow, int inputcols, char player_enemy[10][10],char playerfield[10][10], int *playerX){
    char str[MAXCHAR];
    files = fopen(filename_enemy, "r");
    int enemyX = 0;
    int boats__ = 0;
    bool space = false;

    while (fgets(str, MAXCHAR, files) != NULL){
        int counter=1;
        char type[15];
        int len;
        char col;
        int row;
        char orient;
        bool boat;
        char onlyboat[10][10];
        BoardAux(onlyboat);

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
        boat= AddBoat(type, len, col, row, orient, onlyboat);

        if(onlyboat[inputrow][inputcols]==88){//Si el barco en la posicion que ingrese, calza con uno de los enemigos...
            enemyX=len;//Este va a ser el largo del barco enemigo
         
            if(orient==104){//Si la orientacion es horizontal h
                if(inputcols<9){
          
                    int c1=1;
                    if (playerfield[inputrow][inputcols + c1] == 88){//Si es que a la derecha hay una X
                        while(true){
                            if (playerfield[inputrow][inputcols + c1] == 95){ 
                                boats__ = boats__ + 1;
                                space = false;
                                break;
                            }
                           else if (playerfield[inputrow][inputcols + c1] == 46) {
                                break;
                             }
                            else if (playerfield[inputrow][inputcols + c1] == 88) {
                                *playerX= *playerX +1;
                            }
                            else {
                                 break;
                             }
                             c1++; 
                        }
                        
                    }
                }
                if(inputcols>0){
                    int c2=1;
                    if (playerfield[inputrow][inputcols - c2] == 88){//Si es que a la izquierda hay una X
                        while(true){
                            if (playerfield[inputrow][inputcols - c2] == 95){ 
                                boats__ = boats__ + 1;
                                space = false;
                                break;
                            }
                           else if (playerfield[inputrow][inputcols - c2] == 46) {
                                break;
                             }
                            else if (playerfield[inputrow][inputcols - c2] == 88) {
                                *playerX= *playerX +1;
                            }
                            else {
                                 break;
                             }
                             c2++; 
                        }
                        
                    }
                }
            }
            else{
                if(inputrow > 0){ //checkea si hay X arriba
       
                    int c3 = 1;
                    if (playerfield[inputrow - c3][inputcols] == 88){ // arriba
          
                        while (true) {
                            if (playerfield[inputrow - c3][inputcols] == 95){
                                boats__ = boats__ + 1;
                                space = false;
                                break;
                            }
                            else if (playerfield[inputrow - c3][inputcols] == 46) {
                                break;
                            }
                             else if (playerfield[inputrow - c3][inputcols] == 88) {
                                *playerX= *playerX +1;
                             }
                        
                            else {
                                break;
                            }
                            c3++;
                        }
                    }
                }
                if(inputrow<9){
                    int c4=1;
                    if(playerfield[inputrow+c4][inputcols]==88){
                        while(true){
                            if(playerfield[inputrow + c4][inputcols]==95){
                                boats__=boats__+ 1;
                                space=false;
                                break;
                            }
                            else if (playerfield[inputrow + c4][inputcols] == 46) {
                                break;
                            }
                            else if (playerfield[inputrow - c4][inputcols] == 88) {
                                *playerX= *playerX +1;
                            }
                            else {
                                break;
                            }
                            c4++;
                        }
                    }
                }

            }
        }
        else{
            counter=1;
        
        }
     
   
    }
    fclose(files);
    return enemyX;
}


int Row(int row, char user_input[4]){
	return user_input[2]-48;
}

int Columns(int col, char user_input[4]){
	return (int)user_input[0]-65;
}






