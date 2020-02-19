#include "stdio.h"
#include "stdbool.h"
#include "stdlib.h"
#include "printdel.h"

#define SIZER 25 //row
#define SIZEC 50 //column
#define SCREEN_WIDTH 150
#define SPACE (SCREEN_WIDTH-SIZEC)/2

#define WALL '\xDB'
#define MAN 'O'
#define ENEMY 'T'
#define EMPTY ' '
#define BOMB 'X'

int alive=1;//bool
int restart=0;// bool for quick restart

int head_i,head_j;//Our current position
int enemy_count=0;//enemy index storage
int enemies[2][(SIZER-1)*(SIZEC-1)];
int bomb_count=0;
int bombs[2][(SIZER-1)*(SIZEC-1)];

int points=0;//SCORE WILL BE IMPLEMENTED
int difficulty=20;//!!!!
int bombspawn = 50;


typedef enum{w,m,x,e,b} Pixel;//wall man enemy empty bomb
Pixel game[SIZER][SIZEC];//game table


//Position enemies[(SIZER-1)*(SIZEC-1)];//enemy index storage array !!!ASK THE TEACHER
//int enemy_i,enemy_j;//enemy index storage
//typedef int Position[2];//enemy index storage !!!ASK THE TEACHER



void begin()//intro and difficulty screen
{
	int selection=0;
	int d20;
	d20 = 1 + rand()%20;
	textAlligner(60);
	print("INITIATING GAME.EXE...\n",100);
	printf("Hello! Welcome to my unfinished game.\nPlease select a difficulty:\n");
	printf("1-I am a coward even in a cmd game\n2-I don't have intellectual abilities just give me the default\n3-I carry Kali Linux in my usb drive\n");
	printf("0-Custom Spawn Rate\n");
	sleep(1);
	printf("You rolled %d\n",d20);
	error:
	scanf("%d",&selection);
	if(d20==13){
		printf("You rolled the unlucky number good luck because you will need it\n");
		goto hard;
	}
	switch(selection){
		case 1:
			difficulty=15;
			printf("Easy mode engaged. Spawn chance:%d%%\n",difficulty);
			sleep(1);
			system("cls");
			break;
		case 2:
			difficulty=30;
			printf("Normal mode engaged. Spawn chance:%d%%\n",difficulty);
			sleep(1);
			system("cls");
			break;
		case 3:
			hard:
			difficulty=50;
			printf("Hard mode engaged. Spawn chance:%d%%\n",difficulty);
			sleep(1);
			system("cls");
			break;
		case 0:
			invalid:
			printf("Please type in the spawn rate(x%%):\n");
			scanf("%d",&difficulty);
			if(difficulty==0){
				printf("What a boring game :(\n");
			}
			else if(difficulty<0||difficulty>100){
				printf("INVALID!!! Select Again\n");
				goto invalid;
			}
			printf("Custom mode engaged. Spawn chance:%d%%\n",difficulty);
			sleep(1);
			system("cls");
			break;
			
		default:
			printf("ERROR!!! SELECT AGAIN");
			goto error;
	};
}

void fill_game()//the first function to be called fills the empty game table with macros
{	
	int i,j;
	
	for(i=0;i<SIZER;++i){
		for(j=0;j<SIZEC;++j){
			if(i==0||i==SIZER-1||j==0||j==SIZEC-1){
				game[i][j]=w;
			}
			else{
				game[i][j]=e;
			}
		}
	}
	head_i = 1 + (rand() % (SIZER-2));
	head_j = 1 + (rand() % (SIZEC-2));
	game[head_i][head_j]=m;//man
}

void enemy_spawn()//spawns random enemies
{
	int chance;
	int enemy_i,enemy_j;
	chance = rand() % 101;
	if(chance<difficulty){
		enemy_i= 1 + (rand() % (SIZER-2));
		enemy_j= 1 + (rand() % (SIZEC-2));
		game[enemy_i][enemy_j]=x;
		enemies[0][enemy_count]=enemy_i;
		enemies[1][enemy_count]=enemy_j;
		++enemy_count;
	}
}

void bomb_spawn()//3 bombs max?
{
	int chance;
	int bomb_i,bomb_j;
	chance = rand() % 101;
	if(chance<bombspawn){
		bomb_i= 1 + (rand() % (SIZER-2));
		bomb_j= 1 + (rand() % (SIZEC-2));
		game[bomb_i][bomb_j]=b;
		bombs[0][bomb_count]=bomb_i;
		bombs[1][bomb_count]=bomb_j;
		++bomb_count;
	}
}

void print_game()//game print
{
/*
	int i,j;
	for(i=0;i<SIZER;++i){
		for(j=0;j<SIZEC;++j){
			if(j==0)
				textAlligner(SPACE);//OPTIONAL!!!
			if(game[i][j]==w)
				printf(WALL);
			else if(game[i][j]==m)
				printf(MAN);
			else if(game[i][j]==x)
				printf(ENEMY);
			else if(game[i][j]==e)
				printf(EMPTY);
			if(j==SIZEC-1)
				printf("\n");
		}
	}
	*/
	int i,j;
    char line[SIZEC + 1];
    for(i=0;i<SIZER;++i){
        for(j=0;j<SIZEC;++j){
            if(game[i][j]==w)
                line[j] = WALL;
            else if(game[i][j]==m)
                line[j] = MAN;
            else if(game[i][j]==x)
                line[j] = ENEMY;
            else if(game[i][j]==e)
                line[j] = EMPTY;
            else if(game[i][j]==b)
            	line[j] = BOMB;
        }
        line[SIZEC] = '\0';
        textAlligner(50);
        printf("%s\n", line);
    }
}

void movement()//player movement
{
	int chr1, chr2;
 	printf("Press any arrow key... Press R to quick restart.\n");
 	
 	chr1 = getch();
 	if(chr1==82||chr1==114){
 		restart=1;
 		return;
	}	
 	if (chr1 == 0xE0){
  		chr2 = getch();
  		switch(chr2){
			case 72:
				if(!((head_i-1<(SIZER-1)&&head_i-1>=1)&&(head_j<(SIZEC-1)&&head_j>=1)))
					break;
  	 			game[head_i][head_j]=e;
  	 			--head_i;
				game[head_i][head_j]=m;
				break;
  			 case 80:
  			 	if(!((head_i+1<(SIZER-1)&&head_i+1>=1)&&(head_j<(SIZEC-1)&&head_j>=1)))
					break;
				game[head_i][head_j]=e;
  				++head_i;
	  	 		game[head_i][head_j]=m;
     			break;
  			 case 75:
  			 	if(!((head_i<(SIZER-1)&&head_i>=1)&&(head_j-1<(SIZEC-1)&&head_j-1>=1)))
					break;
				game[head_i][head_j]=e;
				--head_j;
				game[head_i][head_j]=m;
    			break;
  	 		case 77:
  	 			if(!((head_i<(SIZER-1)&&head_i>=1)&&(head_j+1<(SIZEC-1)&&head_j+1>=1)))
					break;
				game[head_i][head_j]=e;
  	 			++head_j;
	   			game[head_i][head_j]=m;
    			break;
  		};
 	}
}

void enemy_movement()//enemy ai
{
	int i,ex,ey;
	/*
	for(i=0;i<enemy_count;++i){
		if(enemies[0][i]==head_i&&enemies[1][i]==head_j){
			alive=0;
			break;		
		}
	}
	*/
	for(i=0;i<enemy_count;++i)
	{
		ex=enemies[0][i];
		ey=enemies[1][i];
		
		if(enemies[0][i]==head_i&&enemies[1][i]==head_j){
			alive=0;
			break;		
		}
		
		if(game[ex][ey]==x){
			if(ex-head_i<0){
				game[ex][ey]=e;
				game[ex+1][ey]=x;
				++enemies[0][i];
				++ex;
			}
			else if(ex-head_i!=0){
				game[ex][ey]=e;
				game[ex-1][ey]=x;
				--enemies[0][i];
				--ex;
			}
			
			if(ey-head_j<0){
				game[ex][ey]=e;
				game[ex][ey+1]=x;
				++enemies[1][i];
				++ey;
			}
			else if(ey-head_j!=0){
				game[ex][ey]=e;
				game[ex][ey-1]=x;
				--enemies[1][i];
				--ey;
			}
		
			if(enemies[0][i]==head_i&&enemies[1][i]==head_j){
				alive=0;
				break;		
			}
		}
	}
}

void bomb_act()
{
	int i,bx,by;
	
	for(i=0;i<bomb_count;++i)
	{
		bx=bombs[0][i];
		by=bombs[1][i];
		
		if(bx==head_i&&by==head_j){
			int k,j;
			for(k=-2;i<3;++k){
				for(j=-2;j<3;++j){
					int a=0;
					for(;a<enemy_count;++a){
						if(head_i+k==enemies[0][a]&&enemies[1][a]==head_j+j){
							game[enemies[0][a]][enemies[1][a]]=e;
							enemies[0][a]=0;
							enemies[1][a]=0;
						}
					}
					
				}
			}
			bombs[0][bomb_count]=0;
			bombs[1][bomb_count]=0;
		}
	}
}

void wipe()//wipes the filled bomb and enemy array out in the case of restarting
{
	int i,j;
	for(i=0;i<2;++i){
		for(j=0;j<(SIZER-1)*(SIZEC-1);++j)
			enemies[i][j]=0;
			bombs[i][j]=0;
	}
	enemy_count=0;
	bomb_count=0;
}

void playgame()//second main
{
	srand(time(NULL));
//	begin();
	restart:
	fill_game();
	while(alive&&!restart){
		enemy_spawn();
		bomb_spawn();
		print_game();
		movement();
		bomb_act();
		enemy_movement();
		system("cls");
	}
	if(restart){
		textAlligner(50);
		printf("RESTARTING THE GAME!!!\n");
		Sleep(300);
		system("cls");
		restart=0;
		wipe();
		goto restart;//if r is pressed we are going back to start. After begin() though
	}
	
	system("cls");
	textAlligner(50);
	printf("Oopsie you died :(((. Press r to quick restart.\n");
	
	int r;//Restart
	scanf(" %c",&r);
	if(r==114||r==82){
		textAlligner(50);
		printf("RESTARTING THE GAME!!!\n");
		Sleep(300);
		system("cls");
		restart=0;
		alive=1;
		wipe();
		goto restart;
	}
	system("cls");
	textAlligner(50);
	printf("Quitting.\n");
}

int main()
{
	playgame();
	
	return 0;
}

