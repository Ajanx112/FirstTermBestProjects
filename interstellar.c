//i tried to use the goto command that i recently learned so i hope it doesn't brake any computers
#include <stdio.h>
#include <time.h>//srand(time(NULLL))
#include <stdlib.h>//is useful i guess
#include <math.h>//abs function is better than the one that i wrote so...
#include <string.h>//strlen
#include <unistd.h>//sleep
//for an easier gameplay in planet 4 and 5 whole repetition is considered as 1 hour not every move

int passed_hour;
int fuel=2500;
int planets[9][2]={{0,0},{30,0},{210,0},{270,0},{720,0},{610,0},{580,0},{790,0},{1000,0}};//Earth,Planet1,2,3,4,5,6,7,X
int done[8]={0,0,0,0,0,0,0,0};//to see completed levels
int life=0,lifeflag=1;//will be assigned to multidim array's second element
int current_planet=0;//to do the fuel calcs
int selection;//global var because parameters are boring
int typing_delay=60;//used in custom print func

//custom library that i created. Basically an Undertale typing style rip-off to make things look cooler P.S. see begin()
void print(char word[],int time){//string and typing delay in miliseconds
	int i;
	for(i=0;strlen(word)>i;i++){
		printf("%c",word[i]);
		fflush(stdout);
		Sleep(time);
	}
}

void del(int how_many_digits,int time){//how many chars and typing delay
	int i;
	for(i=0;how_many_digits>i;i++){
		printf("\b \b");
		fflush(stdout);
		Sleep(time);
	}
}
//custom library ends


void planet_1(){//Hi-Lo
	current_planet=1;
	if(planets[1][1]==1)
		lifeflag=0;
	print("You arrive at Planet 1.\nOnce you take a step forward, you immediately feel an incredible pain in your eyes.\n",typing_delay);
	print("While you are trying to cope with the pain. You remember your NASA training.\nPlanet 1 has a poisonous gas that non-permanently blinds any foreign creature.\n",typing_delay);
	print("In order to survive you need to rub your eyes a certain time.\nBut as you were asleep during that NASA course you have to find that number by trial and error\n",typing_delay);
	print("You remember the range of 1-10, and you know that the AI on your space suit will assist you on your trials.\n",typing_delay);
	print("How many times are you suppose to rub?\n",typing_delay);
	int guess;
	int tries=0;
	int hidden = 1 + rand() % 10 ;
	while(1){
		tries++;
		print("Your guess:\n",typing_delay);
		scanf("%d",&guess);
		
		if(tries==1&&guess==hidden){
		print("Wow you got lucky! You can see again\n",typing_delay);
		break;
		}
		
		if(guess==hidden){
			print("You finally found it you can see again!!!\n",typing_delay);
			break;
		}
			
		else if(guess>hidden){
			
			if(guess-hidden>6)
				print("VERY High\n",typing_delay);
			else
				print("High\n",typing_delay);
		}
		
		else if(guess<hidden){
			
			if(abs(guess-hidden>6))
				print("VERY Low\n",typing_delay);
			else
				print("Low\n",typing_delay);
		}

	}
	passed_hour+=60000*tries;
	print("You open your eyes and take a look at the planet\n",typing_delay);
	done[0]=1;
}

void planet_2(){//Evil Hi-lo
	if(planets[2][1]==1)
		lifeflag=0;
	current_planet=2;
	print("While you were getting closer to Planet 2. Your ship's gps system starts beeping. LOUDLY.\n",typing_delay);
	print("Turns out you accidentally drove the ship in an astreoid field.*Facepalms*\n",typing_delay);
	print("In order to open the computer's case and take a look for the cause of the problem.\nYou need to remember the 1 digit password.(1-10)\n",typing_delay);
	print("Because the NASA knew you were too stupid to keep that in mind they also implemented it in your ship's AI.\n",typing_delay);
	print("But the AI is also shortwiring(Yes,that is your diagnosis) It sometimes gives wrong answers to your questions.\n",typing_delay);
	print("Now it is time to act. What was the password?\n",typing_delay);
	int chance;
	int guess;
	int tries=0;
	int hidden = 1 + rand() % 10 ;
	while(1){
		
		tries++;
		
		chance = rand() % 2;
		
		print("Your guess:\n",typing_delay);
		scanf("%d",&guess);
		
		if(tries==1&&guess==hidden){
			print("Wow you got lucky and was able to guess the password in 1 try. I suppose you weren't that stupid.\n",typing_delay);
			break;
		}
		
		if(guess==hidden){
			print("You found it!! And you were clever enough to give the computer's motherboard a smash. Which seems to surprisingly work.\n",typing_delay);
			break;
		}
		if(guess>hidden){
			if(chance)
				print("High\n",typing_delay);
			else
				print("Low\n",typing_delay);
		}
		else if(guess<hidden){
			if(chance)
				print("Low\n",typing_delay);
			else
				print("High\n",typing_delay);
		}
	}
	passed_hour+=20000*tries;
	print("You dock the ship and take a look at the Planet.\n",typing_delay);
	done[1]=1;
}

void planet_3(){//Sum thing
	if(planets[3][1]==1)
		lifeflag=0;
	current_planet=3;	
	
	print("You get really bored while traveling... Especially when you are the only humanbeing in space heading to Planet 3.\n",typing_delay);
	print("You decide to solve some brainteaser on the go from the newspaper you carried with you to outer space(Seriously though)\n",typing_delay);
	print("Be careful though newspaper puzzles are designed to engage old guys,\ntherefore you may lose too much time on this planet if you aren't able to give correct answers.\n",typing_delay);
	print("Here is the puzzle:\nTry to reach a certain number only by typing in 2,3,5. Your inputs will be added cummulatively\n",typing_delay);
	int num,sum=0;
	int tries=0;
	int reach;
	try_again:
	reach = 7 + (rand() % 18);
	printf("Your number is: %d\n",reach);
	while(sum<reach){
		scanf("%d",&num);
		sum+=num;
	}
	
	if(sum==reach){
		++tries;
		printf("You solved %d puzzles got bored and throw the newspaper away.\n",tries);
	}
	else{
		++tries;
		print("You exceeded the number. And no we don't have erasers in the outer space\n Try another one...\n",typing_delay);
		goto try_again;
	}
	print("You succesfully reached planet 3\n",typing_delay);
	passed_hour+=tries*1200000;
	done[2]=1;
}

void planet_4(){//dice rolling auto-game planet
	if(planets[4][1]==1)
		lifeflag=0;
	current_planet=4;	
	int tries=1;
	int bestof3=0;
	int turn=0;
	int du,dc;//dice_user dice_computer
	print("While thinking how unqualified you are for this mission. Suddenly a big red button catch your eye.\n",typing_delay);
	print("'Super Fast Travel Button Don't Press' is written on it.\n",typing_delay);
	print("You asked the AI about it and it responds by saying:\n",typing_delay);
	print("'We are already in Planet 4's orbit why would you even want to press that. It is just a big waste of time'\n",typing_delay);
	print("AI knows you even better than you. So it puts a randomizer style lock on the button.\n",typing_delay);
	print("You will roll some dice and see in how many trials you can beat the AI.\n",typing_delay);
	sleep(1);
	lost:
	while(turn<3){
		++turn;
		du=1+(rand()%6);
		dc=1+(rand()%6);
		printf("Round: %d/3 You rolled: %d Pc rolled: %d  ",turn,du,dc);
		if(du==dc){
			print("Draw\n",typing_delay);
		}
		else if(du>dc){
			print("You won this round\n",typing_delay);
			++bestof3;
		}
		else{
			print("You lost this round\n",typing_delay);
			--bestof3;
		}
		sleep(1);
	}
	
	if(turn==3&&bestof3>0){
		print("You won and press the button\nTurns out NASA was clever enough to deactivate the button before giving the ship to you.\n",typing_delay);
		}
	else if(turn==3&&bestof3<=0){
		print("AI won this best of 3. You force it to play with you again.\n",typing_delay);
		turn=0;
		++tries;
		bestof3=0;
		goto lost;
		}
	passed_hour+=tries*35000;
	done[3]=1;
}

void planet_5(){//Rock Paper Scissor 1,2,3
	if(planets[5][1]==1)
		lifeflag=0;	
	current_planet=5;
	int tries=1;
	int bestof3=0;
	int turn=0;
	int dc,userinp;//dice_computer
	print("Wow... This trip went better than anyone would have imagined.\n",typing_delay);
	print("After you succesfully dock to Planet 5\nYou see an roundly shaped gray object on the ground.",typing_delay);
	print("However when you take a step forward towards it. It changes it's shape into a flat white object.\n",typing_delay);
	print("With evey move you make it switches between it's forms.\n",typing_delay);
	print("You realize how bad this planet's scenario is written and decide to hop right into the RPS game.\n",typing_delay);
	lost:
	while(turn<3){
		++turn;
		dc=1+(rand()%3);
		print("Please choose one: Rock(1),Paper(2),Scissors(3)\n",typing_delay);
		scanf("%d",&userinp);
		printf("Round %d/3:You chose: %d Mysterious object chose: %d  ",turn,userinp,dc);
		if(userinp==dc){
			print("Draw\n",typing_delay);
		}
		else if(userinp==1){
			if(dc==2){
			print("You lost this round\n",typing_delay);
			--bestof3;
			}
			else{
				print("You won this round\n",typing_delay);
				++bestof3;
			}
		}
		else if(userinp==2){
			if(dc==3){
			print("You lost this round\n",typing_delay);
			--bestof3;
			}
			else{
				print("You won this round\n",typing_delay);
				++bestof3;
			}
		}
		else if(userinp==3){
			if(dc==1){
			print("You lost this round\n",typing_delay);
			--bestof3;
			}
			else{
				print("You won this round\n",typing_delay);
				++bestof3;
			}
		}
		sleep(1);
	}
	
	if(turn==3&&bestof3>0){
		print("You won and make the object CRY. Are you happy now. You shouldn't be. It is a bad behaviour.\n",typing_delay);
		}
	else if(turn==3&&bestof3<0){
		print("Mysterious object won and greeted you. However you are too greedy for a win so you force it to play until you win.\n",typing_delay);
		turn=0;
		++tries;
		bestof3=0;
		goto lost;
		}
	passed_hour+=tries*100000;
	done[4]=1;
}

void planet_6(){//hard to code binary thing
	if(planets[6][1]==1)
		lifeflag=0;
	current_planet=6;	
	int rnd,input,digit;
	int tries=1;
	int i,j;
	int binary[10]={};
	print("When you reach the Planet 6 you see that it is the exact imitation of the planet on the 'Hitchikers Guide To The Galaxy'\n",typing_delay);
	print("While thinking how bad and overrated that movie/book series was.\nYou also see the super-computer grining at you from the mountains.\n",typing_delay);
	print("You decide to ask it a personal question before you check if there is life on this planet or not.\n",typing_delay);
	print("Turns out that computer has no kind of compiler/assembler and you have to type your question in binary...\n",typing_delay);
	wrong:
	rnd= 1 + (rand() % 255);
	printf("Choosen number is:%d\n",rnd);
	for(i=0;rnd>0;i++){
		binary[i]=rnd%2;
		rnd=rnd/2;
	}
	for(j=1;j<=3;++j){
		digit=rand()%i;
		printf("Please type the %d. digit from right(0 indexed) Q:%d/3\n",digit,j);
		scanf("%d",&input);
		if(input==binary[digit]){
			print("Correct\n",typing_delay);
		}
		else{
			print("Super pc gave a blue screen... Restarting.\n",typing_delay);
			++tries;
			goto wrong;
		}		
	}
	print("You asked your question which was too embarrasing to share with the player.\nAnd turns out computer outputs 42 no matter what.\n",typing_delay);
	print("*Dissappointedly takes a last glance at the planet to see any kind of life*\n",typing_delay);
	passed_hour+=tries*80000;
	done[5]=1;
}

void planet_7(){//quick maths big shaq
	if(planets[7][1]==1)
		lifeflag=0;	
	current_planet=7;
	int rnd1,rnd2,multip,input;
	int flag=1;//i thought goto may break the time thing so we are using a flag now
	print("Appearently AIs can get bored too.\nSo after the AI mocking you about how stupid you are on the road to Planet 7.\nYou decide to solve a quick math quiz to show the AI your capabilities.\n",typing_delay);
	print("(Why would you even challenge a computer in maths i mean. Whatever.)\n",typing_delay);
	print("Your timer will start in 3 seconds.\n",typing_delay);
	printf("3 ");
	sleep(1);
	printf("2 ");
	sleep(1);
	printf("1 ");
	sleep(1);
	printf("GO!!!\n");
	//thx to stackoverflow here is our time interval calculator
	clock_t start, end;
    double cpu_time_used;
    start = clock();
    while(flag){
		rnd1=10+rand()%21;
		rnd2=10+rand()%21;
		multip=rnd1*rnd2;
		printf("%d*%d=?\n",rnd1,rnd2);
		scanf("%d",&input);
    	if(input==multip){
    		flag=0;
    		printf("Correct! but AI doesn't seem to be impressed.\n");
		}
		else
			printf("*AI mocks you*\n");
	}
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    print("You embarresedly dock to Planet 7\n",typing_delay);
    printf("You spent:%llf seconds here which is equal to %d hours\n",cpu_time_used,(int)cpu_time_used);
    passed_hour+=25000*(int)cpu_time_used;
    done[6]=1;
}

int number_from_array(int arr[], int numdigits){//stolen from mutlu teacher week06
	int num = 0;
	int factor = 1;
	int i;
	for(i=0; i<numdigits; i++) {
		num = num + (arr[i] * factor);
		factor = factor * 10;
	}
	return num;
}

void planet_8(){//quick typing game that nobody asked for but it used to work in 90's so lets go
	if(planets[8][1]==1)
		lifeflag=0;
	current_planet=8;
	int num,input;
	int arr[9]={};
	int i;
	clock_t s,e;
    double cpu_time_used;
    print("While the coder is trying to get creative about Planet 8. You remember your only written task from NASA.\n",typing_delay);
    print("You are supposed to write the numbers you see on the screen correctly to a paper.\nOtherwise they wouldn't be able to trace you as NASA said.\n",typing_delay);
    print("Although you think it is a big giant lie and NASA is trying to make fun of you and laugh.\n",typing_delay);
	print("You still decide to do it.\n",typing_delay);
	print("The game and your timer will start in 3 seconds\n",typing_delay);
	printf("3 ");
	sleep(1);
	printf("2 ");
	sleep(1);
	printf("1 ");
	sleep(1);
	printf("GO!!! Type the number you see as fast as you can.\n");
	s = clock();
    //
    while(1){
    	for(i=0;i<9;++i)
			arr[i]=1+rand()%9;
		num = number_from_array(arr,9);
		for(i=8;i>=0;--i)
			printf("%d",arr[i]);
		printf("\n");
		scanf("%d",&input);
		if(num==input)
			break;
		else{
			printf("Wrong!! try again\n");
		}
	}
	//
	e = clock();
    cpu_time_used = ((double) (e - s)) / CLOCKS_PER_SEC;
    print("DONE! As it matters... Which doesn't.\n",typing_delay);
    printf("You spent:%llf seconds here which is equal to %d hours in this planet\n",cpu_time_used,(int)cpu_time_used);
    print("You take a look at Planet 8\n",typing_delay);
    passed_hour+=100000*(int)cpu_time_used;
    done[7]=1;
}

void rand_life(){//chooses the planet that offers life
	int index= 1 + (rand() % 8);
	planets[index][1]=1;
}

void begin(){
	print("Initiating interstellar.exe\n",150);
	printf("                                          ");
	print("A game by Hideo Kojima",100);
	del(12,80);
	print("Mustafa Cig Gokpinar\n",70);
	print("In 2019 Earth is suffering from severe h2o and food insufficiency and humanity lost their hope about the planet.\n",typing_delay);
	print("After listening Greta talking about global warming and stuff Humans get bored and decide to send a random person into\nspace to find a new planet that offers life.\n",typing_delay);
	print("And that human is appearently you...\n",typing_delay);
	print("After some free training and ice sandwiches from NASA. Now you are ready to hop on to the spaceship assigned to you and\nsave us? I guess...\n",typing_delay);
	print("Oh also don't forget that you have a certain amount of fuel and try to come back before we die.\nBecause time acts different in other planets\n",typing_delay);
	print("I mean you watched interstellar right? Yeah i also feel sad about the dying robot.\nOk cut the chit-chats you have gotta go. Hope to see you again.\n",typing_delay);
	sleep(2);
	system("pause");
	system("cls");
	rand_life();
}

void choose(){
	int ex_planet=0;
	what:
	printf("Please choose the planet you want to go to, 'This planet is: 1' means that you cleared that planet.\n");
	printf("Your fuel: %d\n",fuel);
	printf("1- Planet 1: %d lightyears from your current planet This planet is: %d\n",abs(planets[1][0]-planets[current_planet][0]),done[0]);
	printf("2- Planet 2: %d lightyears from your current planet This planet is: %d\n",abs(planets[2][0]-planets[current_planet][0]),done[1]);
	printf("3- Planet 3: %d lightyears from your current planet This planet is: %d\n",abs(planets[3][0]-planets[current_planet][0]),done[2]);
	printf("4- Planet 4: %d lightyears from your current planet This planet is: %d\n",abs(planets[4][0]-planets[current_planet][0]),done[3]);
	printf("5- Planet 5: %d lightyears from your current planet This planet is: %d\n",abs(planets[5][0]-planets[current_planet][0]),done[4]);
	printf("6- Planet 6: %d lightyears from your current planet This planet is: %d\n",abs(planets[6][0]-planets[current_planet][0]),done[5]);
	printf("7- Planet 7: %d lightyears from your current planet This planet is: %d\n",abs(planets[7][0]-planets[current_planet][0]),done[6]);
	printf("8- Planet 8: %d lightyears from your current planet This planet is: %d\n",abs(planets[8][0]-planets[current_planet][0]),done[7]);
	printf("0- To exit\n");
	scanf("%d",&selection);
	if((selection>8||selection<0)||(done[selection-1]==1)){
		printf("INVALID SELECTION TRY AGAIN\n");
		sleep(1);
		system("cls");
		goto what;
	}
	system("cls");
	if(selection==1){
		planet_1();
		fuel-=abs(planets[ex_planet][0]-planets[current_planet][0]);
	}
	else if(selection==2){
		planet_2();
		fuel-=abs(planets[ex_planet][0]-planets[current_planet][0]);

	}
	else if(selection==3){
		planet_3();
		fuel-=abs(planets[ex_planet][0]-planets[current_planet][0]);

	}
	else if(selection==4){
		planet_4();
		fuel-=abs(planets[ex_planet][0]-planets[current_planet][0]);

	}
	else if(selection==5){
		planet_5();
		fuel-=abs(planets[ex_planet][0]-planets[current_planet][0]);

	}
	else if(selection==6){
		planet_6();
		fuel-=abs(planets[ex_planet][0]-planets[current_planet][0]);		

	}
	else if(selection==7){
		planet_7();
		fuel-=abs(planets[ex_planet][0]-planets[current_planet][0]);		

	}
	else if(selection==8){
		planet_8();
		fuel-=abs(planets[ex_planet][0]-planets[current_planet][0]);		

	}
	else{
		printf("EXITING...\n");
		exit(0);
	}
	ex_planet=current_planet;
}

void playphase(){
	while(lifeflag){//life flag is 0 if a planet with life is completed
		if(fuel<=0){
			print("Unfortunately your fuel has run out and now you are just another corpse swinging on the outer space. I knew you weren't qualified enough to do this...\n",typing_delay);
			exit(13);
		}
		choose();
		if((passed_hour!=0)&&(lifeflag!=0)){
			printf("You spent a total time of %d earth years in the outer space.\n",passed_hour/8760);
			print("You see that it wasn't this planet that offers life.\n",typing_delay);
		}
		sleep(2);
		system("pause");
		system("cls");
	}
	if(planets[current_planet][0]>fuel){
		printf("Your fuel:%d",fuel);
		print("You raise your head and see tiny dinasours running around yes... YES!!! you scream.\n",typing_delay);
		print("After that much effort you found the planet that offers life...\n But dinasurs makes you wonder how much of the oil you wasted on this trip.\n",typing_delay);
		print("You go back to check and see the unfortunate news. There is no fuel left to go back to earth.\n",typing_delay);
		print("After struggling to send signals to earth you accidentally broke an antenna, it falls onto your head and you die alone.\n",typing_delay);
		exit(111);
	}
	else{
		if((passed_hour/8760)>=150){
			print("You found life... It was an beatiful planet. And you also had enough fuel to go back which was the greatest satisfaction you felt.\n",typing_delay);
			print("However after a long ride back to earth. You saw the nightmare you were most afraid of. The inevitable laws of physics were against you.\n",typing_delay);
			print("There was not even a single cell that is alive on earth. Because you spent:\n",typing_delay);
			printf("%d earth years. The year is now: %d\n",(passed_hour/8760),2019+(passed_hour/8760));
			print("After wandering around for a few minutes you feel sick and pass out on the ground.\n",typing_delay);
			print("Turns out Earth was destroyed due to a nuclear war.\n",typing_delay);
		}
		else{
			print("You found life... It was an beatiful planet. And you also had enough fuel to go back which was the greatest satisfaction you felt.\n",typing_delay);
			print("You put on a big big smile and turn back to your spaceship.\n",typing_delay);
			print("After a long ride even with spaceshuttles, you step on the earth once again.\n",typing_delay);
			print("The people were looking at you with a happy/surprised face.\n",typing_delay);
			print("-We knew you were gonna make it, says the indian NASA technician.\n",typing_delay);
			print("You see Morgan Freeman... He is trying to explain something to crowd but nobody seems to care.\n",typing_delay);
			print("You wave at the crowd and say your final words for today...\n",typing_delay);
			Sleep(600);
			print("NEVER GONNA GIVE YOU UP\nNEVER GONNA LET YOU DOWN\nNEVER GONNA RUN AROUND AND DESERT YOU\n",150);
			print("Humanity loses that last bit of hope.\n",typing_delay);
		}
		exit(222);
	}
	exit(1313);
}

int main(){
	system("pause");
	srand(time(NULL));
	begin();
	playphase();
	return 0;
}
