#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int progress, lvl; 
/* progress untuk status pemain, 1 = hidup, 2 = game berakhir
lvl untuk tingkat permainan */

struct data{
	char nama[100]; // nama pemain
	int score; // menyimpan poin pemain
}board;

void map(int *n, int *m, char move){
	int i, j,b=11;
	// i dan j sebagai variable counter untuk mencetak karakter yang dijadikan map, b sebagai panjang map (baris)
	if(lvl==2){
		b=21;
	}
	srand(time(NULL)); // mengacak seed dari fungsi rand()
	int trap = rand()%2+1; // penentuan pemberian jebakan, diberi nilai rand() sehingga nilainya acak
	char over; // penempatan jebakan
	system("cls");
	if(trap == 1){
		over='a';
	}else{
		over='d';
	}
	if(over==move){
		progress=0;
	}else{
		progress=1;
	}
	for(i=0; i<b; i++){
		for(j=0; j<7; j++){
			if(j==0 || j==6){
			printf("|");
			}else if(*n==i && *m==j){
				if(progress==1){
					printf("O");
				}else if(progress==0 && i==b-1){
					printf("O");
				}else{
					printf("X");
				}
			}else if(j==2 && i%2==0 || j==4 && i%2==0 ){
				if(i==b-1){
					printf(" ");
				}else{
					printf("#");
				}
			}else if(i==b-2){
				printf("-");
			}
			else{
				printf(" ");
			}
		}
		printf("\n");
	}
}

int main(){
	char ulang, ulang2, move; /* variable ulang untuk looping permainan, ulang2 untuk memasuki level selanjutnya
	move untuk menyimpan input dari pemain*/
	int highscore=0; // untuk menyimpan nilai tertinggi dari tiap level
	printf("Input your name: ");
	gets(board.nama);
	do{
		int n=10, m=3, win; /* variabel n dan m untuk koordinat awal pemain pada map
		variabel win untuk menyimpan total poin yang diperlukan untuk mencapai kemenangan*/
		if(lvl==2){
			n=20;
		}
		win=n/2;
		board.score=0;
		system("cls"); // membersihkan layar pada program
		map(&n,&m, move); // menggambarkan map pada awal permainan
		printf("\nPress a or d to control");
		do{
		move=getch();
			if(move=='a'){
			n-=2;
			m -=1;
			map(&n,&m, move);
			m+=1;
			}else if(move=='d'){
			n-=2;
			m+=1;
			map(&n,&m, move);
			m-=1;
			}
			if(progress==1 && move=='a'|| progress==1 && move=='d'){
				board.score+=1;
			}
		}while(progress==1 && board.score!=win);
		if(highscore<=board.score){
			highscore = board.score;
		}
		
		if(board.score != win){
			printf("\nYou lose!\n");
			printf("\nYour Highscore: %d\n",highscore);
			printf("%s | Score: %d\n", board.nama, board.score);
			printf("\nPress r to play again\nPress q to quit");
			do{
				ulang=getch();
			}while(ulang!='r'&& ulang!='q');
			if(ulang=='q'){
				break;
			}
		}else{
			printf("\nYou Win!\n");
			printf("\nYour Highscore: %d\n",highscore);
			printf("%s | Score: %d\n", board.nama, board.score);
			if(lvl==2){
				break;
			}else{
				printf("Press 1 to continue to the next level\nPress 2 to quit"); 
				do{
				ulang2 = getch();	
				}while(ulang2 != '1' && ulang2 != '2');
				if(ulang2 == '1'){
					ulang='r';
					lvl=2;
					highscore=0;
				}else if(ulang2 == '2'){
					break;
				}
			}
		}		
	}while(ulang=='r');
	return 0;
}
