#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <stdbool.h>

int uplimit;//global_value
int user[4][5];//From Left To Right 0-Player count 1- Hp 2- Gold 3-Gun 4-Total Power
int crntplayer=0;//current player(playing)

void coolIntro(){
	char my_name_here[20]={"Mustafa Cig Gokpinar"};
	int i;
	printf("A Game by Hideo Kojima");
	Sleep(800);
	for(i=0;i<12;i++){//to delete until the first space after ...by
		printf("\b \b");
		fflush(stdout);
		Sleep(100);
	}
	for(i=0;i<20;i++){//to delete until the first space after ...by
		printf("%c",my_name_here[i]);
		fflush(stdout);
		Sleep(100);
	}
	printf("\n");
}

void textAlligner(int spaces){
	int i;
	for(i=0;i<spaces;i++)
		printf(" ");
}

void clearScreen(){
	Sleep(1500);
	system("cls");
}

void intro(){
	textAlligner(35);
	coolIntro();
	sleep(1);
	printf("A man\n");
	Sleep(500);
	textAlligner(1);
	printf("Walks into\n");
	Sleep(500);
	textAlligner(6);
	printf("A bar...\n");
}

//asks for the player count
//story prologue
void mainMenu(int uplimit){
	if(uplimit<=1){
		printf("A man walks into a bar...\n");
		Sleep(700);
		textAlligner(1);
		printf("Sees nobody except the bartender\n");
		Sleep(700);
		textAlligner(4);
		printf("Has a nice drink and leaves.\n");
		Sleep(700);
		textAlligner(35);
		printf("-The end-\n");
		exit(0);
	}
	else{
		printf("%d men walk into a bar\n",uplimit);
		Sleep(1000);
		printf("They ask for a drink\n");
		Sleep(1000);
		printf("The Bartenter says:\n");
		printf("I dont have enough booze for all of you. I actually have only for one.\n");
		Sleep(1800);
		printf("'Crowd goes silent for some time'\n");
		Sleep(2000);
		printf("The crowd:\n");
		printf("GUESS THE WINNER TAKES IT!\n");
		Sleep(1000);
		printf("'The Fight Begins'\n");
	}
}

int choosePlayerType(){//Character select screen
	int charselection;
		printf("Here are characters please select one and type in your choice\n");
		Sleep(300);
		choose:
		printf("1-Richie Rich  -400hp-  Balance: -190g-\n");
		Sleep(300);
		printf("2-Normal Person  -550hp-  Balance: -100g-\n");
		Sleep(300);
		printf("3-Tough guy stereotype  -700hp-  Balance: -50g-\n");
		printf("Please choose one\n");
		scanf("%d",&charselection);
		//implement a menu to go back
		if(charselection==0||(charselection>3&&charselection!=36)){
			printf("Dude what! You must choose one\n");
			goto choose;
	}
		else if(charselection==36){
			printf("Secret Character Found!!! Killa Hakan is active -9999hp- Balance: -9999g-\n ");
			sleep(2);
			return charselection;
	}
		else
			return charselection;
}

void playerCharAssigner(int charselection){//array assigner for hp and gold
	if(charselection==1){
		user[crntplayer][1]=400;
		user[crntplayer][2]=190;
	}
	else if(charselection==2){
		user[crntplayer][1]=550;
		user[crntplayer][2]=100;
	}
	else if(charselection==3){
		user[crntplayer][1]=700;
		user[crntplayer][2]=40;
	}
	else if(charselection==36){
		user[crntplayer][1]=9999;
		user[crntplayer][2]=9999;
	}
printf("Current hp: %d Current Money %d",user[crntplayer][1],user[crntplayer][2]);
Sleep(1000);
}

int chooseGun(){//Gun Shop Screen
	int gunselection;
		choose:
		printf("Here are the guns please select one and type in your choice YOUR MONEY:%d\n",user[crntplayer][2]);
		Sleep(300);
		printf("1- Revolver  50g  30dmg\n");
		Sleep(300);
		printf("2- Shotgun  80g  100dmg\n");
		Sleep(300);
		printf("3- Imaginary Hand Gun  0g  10dmg\n");
		Sleep(300);
		printf("4- 2-sided gun  120g  hits 100dmg to enemy but 80dmg to you\n");
		Sleep(300);
		printf("5- FlameThrower  200g 80dmg and 10dps for 3 turns(WIP)\n");
		Sleep(300);
		printf("99- Killa Hakan's Boxing Gloves  9999g 9999dmg\n");
		printf("Please enter:\n");
		scanf("%d",&gunselection);
		//implement a menu to go back or dont
		if(gunselection==0||(gunselection>5&&gunselection!=99))
			goto choose;
    	else if(user[crntplayer][2]>=50&&gunselection==1){
			user[crntplayer][2]-=50;
			return gunselection;}
		else if(user[crntplayer][2]>=80&&gunselection==2){
			user[crntplayer][2]-=80;
			return gunselection;}
		else if(user[crntplayer][2]>=0&&gunselection==3)
				return gunselection;
		else if(user[crntplayer][2]>=120&&gunselection==4){
			user[crntplayer][2]-=120;
			return gunselection;}
		else if(user[crntplayer][2]>=200&&gunselection==5){
			user[crntplayer][2]-=200;
			return gunselection;}
		else if(user[crntplayer][2]>=9999&&gunselection==99)
			return gunselection;
		else{
			printf("Can't Afford\n");
			Sleep(500);
			system("cls");
			goto choose;
	}
		
}

void playerPowerAssigner(int gunselection){//array assigner for gun and power; money decrementation
	if(gunselection==1){
		user[crntplayer][3]=1;
		user[crntplayer][4]=30;	
	}
	else if(gunselection==2){
			user[crntplayer][3]=2;
			user[crntplayer][4]=100;
	}
	else if(gunselection==3){
		user[crntplayer][3]=3;
		user[crntplayer][4]=10;
	}
	else if(gunselection==4){
			user[crntplayer][3]=4;
			user[crntplayer][4]=100;
	}
	else if(gunselection==5){
			user[crntplayer][3]=5;
			user[crntplayer][4]=80;
			user[crntplayer][2]-=200;
	}
	else if(gunselection==99){
		user[crntplayer][3]=99;
		user[crntplayer][4]=9999;
	}
printf("TOTAL DAMAGE:%d\n",user[crntplayer][4]);
Sleep(1000);
}

void currentplayerpasser(int uplimit){//crntplayer reseter if crntplayer>uplimit then it becomes 0 again
	crntplayer++;
	if(crntplayer>=uplimit)
		crntplayer=0;
}

void begin(int uplimit){//start only function
int i,charselection,gunselection;
for(i=0;i<uplimit;i++){
	printf("Welcome Fighter %d,First choose your character then buy your first weapon\n",i);
	//implement money system and printf players money
	int charselection=choosePlayerType();
	playerCharAssigner(charselection);
	system("cls");
	int gunselection=chooseGun();
	playerPowerAssigner(gunselection);
	system("cls");
	printf("Player %d done\n",i);
	Sleep(1000);
	if(i+1==uplimit)
		printf("All the players are done moving on to the fighting menu");
	else
		printf("Pass the keyboard to another user.You have 3 seconds\n");
		currentplayerpasser(uplimit);
	sleep(3);
	system("cls");
	}
}

void fightingMenu(int uplimit){// if user is dead skips if alive returns the want_to_shoot value which will be used in a hit function
int roundender=0;
while(crntplayer<uplimit&&roundender<uplimit){
	int i_wanna_shoot;
	 if(user[crntplayer][1]<=0){
		printf("You are dead player %d. Skipping your turn\n",crntplayer);
		currentplayerpasser(uplimit);
		sleep(1);
	}else{
		choose:
		printf("Currently Playing: Player %d     Your hp:%d\n",crntplayer,user[crntplayer][1]);
		printf("Please pick the player you want to hit\n");
		int j=0;
		while(j<uplimit){
			printf("%d-I want to hit Player %d\n",j,j);
			j++;
			}
		scanf("%d",&i_wanna_shoot);
		if(i_wanna_shoot==crntplayer){
			printf("Believe me you don't want to hit yourself in this game its just wrong\n");
			Sleep(800);
			system("cls");
			goto choose;
			}
		printf("You are going to hit Player %d Your damage is:%d Please confirm(1/0)\n",i_wanna_shoot,user[crntplayer][4]);
		int flag;
		scanf("%d",&flag);
		if(flag){
			printf("Proceded...\n");
			user[i_wanna_shoot][1]=user[i_wanna_shoot][1]-user[crntplayer][4];
			printf("Chosen Enemy's New Health:%d\n",user[i_wanna_shoot][1]);
			currentplayerpasser(uplimit);
			roundender++;
			Sleep(700);
			printf("Pass the keyboard to another user you have 3 seconds\n");
			sleep(3);
			system("cls");
			}
		else{
			printf("Okay please choose again.\n");
			Sleep(800);
			system("cls");
			goto choose;
			}
		}
	}
if(roundender==uplimit)
	printf("The Battle phase is gone starting the shop phase\n");
}

void shopPhase(int uplimit){
	if(user[crntplayer][1]<=0){
		printf("You are dead player %d. Skipping your turn\n",crntplayer);
		currentplayerpasser(uplimit);
		sleep(1);
	}else{
	int i;
	for(i=0;i<uplimit;i++){
	user[crntplayer][2]+=50;
	system("cls");
	printf("You earned 50g for Staying Alive\n");
	printf("Shopping Has Begun\n");
	int gunselection=chooseGun();
	playerPowerAssigner(gunselection);
	system("cls");
	printf("Player %d done\n",i);
	Sleep(1000);
	if(i+1==uplimit)
		printf("All the players are done moving on to the fighting menu\n");
	else
		printf("Pass the keyboard to another user.You have 3 seconds\n");
		currentplayerpasser(uplimit);
	sleep(3);
	system("cls");
		}
	}
}

int main(){
	intro();
	clearScreen();
	cheater:
	printf("Please select the player count:(For a healthy game this can't be more than 4)\n");
	scanf("%d",&uplimit);
	if(uplimit>4){
		printf("Unvalid player count! Please enter a number between 1 and 4");
		goto cheater;
	}else{
	clearScreen();
	mainMenu(uplimit);
	system("pause");
	system("cls");
	//First autoshop and character selection loop
	int charselection,gunselection;
	begin(uplimit);
//	fightingMenu(uplimit);
	while(1){
		if(!(
(user[0][1]>0&&user[1][1]<=0&&user[2][1]>=0&&user[3][1]>=0)
||(user[1][1]>0&&user[0][1]<=0&&user[2][1]>=0&&user[3][1]>=0)
||(user[2][1]>0&&user[1][1]<=0&&user[0][1]>=0&&user[3][1]>=0)
||(user[3][1]>0&&user[1][1]<=0&&user[2][1]>=0&&user[0][1]>=0)
)){
			fightingMenu(uplimit);
			shopPhase(uplimit);
			}
		else{
			textAlligner(10);
			printf("You Won!!!");
			Sleep(600);
			textAlligner(20);
			printf("You Won!!!");
			Sleep(600);
			textAlligner(30);
			printf("You Won!!!");
			break;	
			}	
		}
	}
	return 0;
}
