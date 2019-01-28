#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <math.h>


int draw(int feldHoriz[9][10], int feldVertik[10][9]);
int test(int feldHoriz[9][10], int feldVertik[10][9], int x, int y, int f);
int ende(int feldKreuz[8][8]);
int play(int feldHoriz[9][10], int feldVertik[10][9], int feldKreuz[8][8], int player, int* beenden);
int fertig(int feldHoriz[9][10], int feldVertik[10][9], int feldKreuz[8][8], int player, int playerpkt1, int playerpkt2);


int j,i,a, playerpkt1, playerpkt2;
int main(int argc, char* argv[]) {
	int show_menu = 1;
	int eingabe = 0;
	playerpkt1 = 0;
	playerpkt2 = 0;

    int feldHoriz[9][10];                      //HORIZONTALE STRICHE
        for(i=0;i<9;i++){
            for(j=0;j<10;j++){
                feldHoriz[i][j]=1;
        }
    }
    int feldVertik[10][9];                      //VERTIKALE STRICHE
        for(i=0;i<10;i++){
            for(j=0;j<9;j++){
                feldVertik[i][j]=2;
        }
    }
    int feldKreuz[8][8];                       //MITTELKREUZ BZW. FELD-SPIELER-PUNKTZUWEISUNG
        for(i=0;i<8;i++){
            for(j=0;j<8;j++){
                feldKreuz[i][j]=4;
            }
        }



    while(show_menu != 0) {
		system("cls");
		printf("1) start\n2) beenden\n");
		scanf("%d",&eingabe);

		if(eingabe == 2) {
			return 0;
		}
		if(eingabe == 1) {
			int player = 1;
			int end = 0;
			int beenden = 0;
			while(ende(feldKreuz) != 0 && beenden == 0 &&  (end == 0 || end == 2) ) {
				player = play(feldHoriz, feldVertik, feldKreuz, player,&beenden);
				end = fertig(feldHoriz, feldVertik, feldKreuz, player - 1, playerpkt1, playerpkt2);
                if(end == 2){
                    if(player==1){playerpkt2++;}
                    if(player==2){playerpkt1++;}
                }
			}
			if(beenden == 0) {
				system("cls");
                draw(feldHoriz, feldVertik);
				if(player == 2) {
					player = 1;
				} else {
					player = 2;
				}
				printf("\nSpiel Beendet!");
				printf("\nHier die Punkte:");

                        printf("\nSpieler 1   %d Punkte\nSpieler 2  %d Punkte",playerpkt1, playerpkt2);

				system("Pause >NUL");
			}
			for(int i = 0; i < 8; i++) {
				for(int j = 0; j < 8; j++) {
					feldKreuz[i][j] = 4;
				}
			}

                for(i=0;i<9;i++){
                    for(j=0;j<10;j++){
                        feldHoriz[i][j]=1;
                }
            }

                for(i=0;i<10;i++){
                    for(j=0;j<9;j++){
                        feldVertik[i][j]=2;
                }
            }
            }
	}

 return 1;
}

int draw(int feldHoriz[9][10], int feldVertik[10][9]){
    for(i=0;i<9;i++){                       //TEST ZEICHNEN DER FELDER
        for(j=0;j<8;j++){
        printf("%d",feldHoriz[i][j]);
            }
    printf("\n");
    for(j=0;j<9;j++){
        if(i<8){    //Damit die letzte zeile Horizontal wird
                printf("%d",feldVertik[i][j]);}
        }
    printf("\n");
}//printf("%d",feldHoriz[i][j]);
return 1;
}

int fertig(int feldHoriz[9][10], int feldVertik[10][9], int feldKreuz[8][8], int player, int playerpkt1, int playerpkt2){
	if(player == 0) {
		player = 2;
	}
    for(i=0;i<9;i++){
        for(j=0;j<8;j++){
            if(feldHoriz[i][j]==0 && feldHoriz[i+1][j]==0 && feldVertik[i][j]==0 && feldVertik[i][j+1]==0 && feldKreuz[i][j]!=0){
                feldKreuz[i][j] = 0;
                    return 2;

}}}
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            if(feldKreuz[i][j]==4){
                return 0;
            }
        }
    }
   // return player;
	//Spiel beendet
	return 1;
}

int play(int feldHoriz[9][10], int feldVertik[10][9], int feldKreuz[8][8], int player, int* beenden){  // FEHLER HIER!!!!!!!
	int x = 0;
	int y = 0;
	int f = 0;
	int geht = 0;
	system("cls");
	draw(feldHoriz, feldVertik);
	printf("\nSpieler %d\nx = ",player);
	scanf("%d",&y);
	fflush(stdin);
	printf("y = ");
	scanf("%d",&x);
    printf("press 8 for horizontal, 9 for vertikal\n");
	scanf("%d",&f);
	fflush(stdin);
	if(x == 999 && y == 999) {
		*beenden = 1;
		return 0;
	}
	if(x < 10 && x > 0 && y < 10 && y > 0 && f<10 && f>7) {
		geht = test(feldHoriz,feldVertik,x,y,f);// printf("\n%d\n", geht);system("pause");
	} else {
		geht = 0;

	}

	if(geht == 0){player--;}
        if(f==9 && geht == 1){
            feldVertik[x - 1][y - 1] = 0;
            }

        if(f==8 && geht == 1){
            feldHoriz[x - 1][y - 1] = 0;
            }


	player++;
	if(player == 3) {
		player = 1;
	}
	return player;
}


int test(int feldHoriz[9][10], int feldVertik[10][9], int x, int y, int f){
 	if(f == 8 && feldHoriz[x - 1][y - 1] == 0) {
		return 0;
	}


    if(f==9 && feldVertik[x - 1][y - 1] == 0) {
		return 0;
    }
        return 1;}


int ende(int feldKreuz[8][8]){
	int null = 0;
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			if(feldKreuz[i][j] == 4) {
				null++;
			}
		}
	}
	return null;
}
