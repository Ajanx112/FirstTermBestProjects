#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//autosolve is commented out because it is a bit problematic
//maybe i shouldn't have used pointers and recursion at the same time on auto-solve
//it is like the hardest c topics cross-overed

#define N 50//puzzle board indice size
#define WORDN 80//word list count
//WORDN is actually not that necessary because we are using the difficulty selection for all the inner loops
#define HARDEST 20//biggest difficulty selection for static arrays if another larger difficulty is added change this
#define LONGEST 11//longest word for static arrays if a longer word is added change this
#define EMPTY ' '

//i tried to push the limits and make a valid word puzzle generator that will also fill the blank 2d array.
//The maze is always printed validly. But the solutions can sometimes be problematic.
//It was very hard to undo an invalid move so the answer sheet is a bit buggy but you can be sure that the maze is valid with some traps
//exp: RESPONSIBLICE seems like an invalid generation but there is a full "RESPONSIBLE" word in the maze GUARANTEED

char words[WORDN+1][LONGEST]={//generated word list from web
{"ice"},//0
{"home"},
{"expand"},
{"passenger"},
{"earn"},
{"hospital"},
{"chalk"},
{"tower"},
{"letter"},
{"efficient"},
{"clever"},//10
{"stop"},
{"view"},
{"brush"},
{"straw"},
{"month"},
{"look"},
{"clap"},
{"giant"},
{"github"},
{"captain"},//20
{"trust"},
{"seal"},
{"ambiguous"},
{"face"},
{"fearful"},
{"functional"},
{"cuddle"},
{"promise"},
{"mysterious"},
{"sponge"},//30
{"venom"},
{"tidy"},
{"doubt"},
{"fool"},
{"invincible"},
{"gray"},
{"mark"},
{"wiggle"},
{"number"},
{"response"},//40
{"team"},
{"shelter"},
{"curve"},
{"cute"},
{"tiger"},
{"past"},
{"sleep"},
{"government"},
{"thought"},
{"wire"},//50
{"false"},
{"miss"},
{"judge"},
{"nose"},
{"teeth"},
{"arrest"},
{"motion"},
{"nest"},
{"night"},
{"point"},//60
{"fruit"},
{"leg"},
{"fuzzy"},
{"outgoing"},
{"quirky"},
{"doll"},
{"country"},
{"stock"},
{"educated"},
{"meal"},//70
{"door"},
{"grin"},
{"class"},
{"sky"},
{"shake"},
{"bounty"},
{"cabbage"},
{"honey"},
{"souffle"},//79
};

char wordlist[HARDEST][LONGEST];//selected after select_mode

char puzzle[N][N];//our puzzle matrix
char solvedpuzzle[N][N];//our unshuffled puzzle matrix
int rwi[HARDEST]={};//for a better and non repetitive random generator rwi:Random Word Index

void first_fill()//i actually don't know if it is possible to fill a 2D array without loops so here is our empty-fill loop
{
	int i,j;
	for(i=0;i<N;++i){
		for(j=0;j<N;++j){
			puzzle[i][j]=EMPTY;
		}
	}
}

int select_mode()//difficulty selection
{
	int easy=7;
	int med=15;
	int hard=20;
	
	printf("Hello Welcome to a wordpuzzle game designed for all the grandpa's out there.\n");
	printf("Please select a mode:\n");
	printf("1-Easy: %d random words\n",easy);
	printf("2-Medium: %d random words\n",med);
	printf("3-Hard: %d random words\n",hard);
	int select;
	scanf("%d",&select);
	switch(select){
		case 1:
			printf("Easy mode selected\n");
			Sleep(200);
			return easy;
		case 2:
			printf("Medium mode selected\n");
			Sleep(200);
			return med;
		case 3:
			printf("Hard mode selected\n");
			Sleep(200);
			return hard;
		default:
			printf("Default mode selected\n");
			Sleep(200);
			return med;
		};
		return -1;
}

void rwi_randomizer(int selection)//in order to prevent a word being generated twice
{
	int i=0,j,count=0;
	int random;
	while(i<selection){
		another_one:
		random = rand()%WORDN;
		for(j=0;j<count;++j){
			if(random==rwi[j])
				goto another_one;
		}
		rwi[i]=random;
		++count;
		++i;
	}
}

void word_randomizer(int selection)//selects random words from our word list with respect to our difficulty settings
{
	int i,j;
	for(i=0;i<selection;++i){
		for(j=0;words[rwi[i]][j]!=0;++j){
			wordlist[i][j]=words[rwi[i]][j];
		}
	}
}

void valid_filler(int selection)//This is very similar to solving the puzzle so i hope it counts(Note to lecturer) Here comes the challenging part:
{
	int row;
	int col;
	
	
	int reverse_index;//As we dont know the size of the upcoming random char arrays....
	int will_be_reversed[LONGEST];//...I stored the string in an array first, and then imported them into our real puzzle array in reverse
	int tempr;//again for reversing purposes we will store the column here
	int tempc;//col reverse
	
	int bigindex=0,j;//the big while loop index that changes respect to our difficulty
	int method;//the method picker
	
	
	int count0=0;//to let the user know how many diagonal and how many row-based answers will there be in the puzzle
	int count1=0;//as there won't be any other possible direction i think its okay to hardcode them
	int count2=0;
	int count3=0;
	int count4=0;
	int count5=0;
	int count6=0;
	int count7=0;
	
	
	while(bigindex<selection){
		
		method=rand()%8;//!!!WILL CHANGE TO 8 WHEN OMNI_DIRECTION IS IMPLEMENTED
		switch(method){
			
/*case0*/	case 0://left to right
				++count0;
				try_again0:
				row=rand()%N;
				col=rand()%(N-LONGEST);//to prevent overflows(TPO)
				tempc=col;
				
				for(j=0;wordlist[bigindex][j]!='\0';++j){
					if(puzzle[row][col]==EMPTY){//TPO
						puzzle[row][col]=wordlist[bigindex][j];
						++col;
					}
					else//{
					/*	while(tempc!=col){
							puzzle[row][col]=EMPTY;
							--col;
						}
					*/	
						goto try_again0;//(TPO)
					//}
				}
				break;
				
		
/*case1*/	case 1://right to left WE ARE NOT ACTUALLY PRINTING FROM RIGHT TO LEFT WE ARE PRINTING FROM LEFT TO RIGHT BUT THE LETTERS ARE REVERSED IN ANOTHER ARRAY(Note to self)
				++count1;
				try_again1:
				reverse_index=0;
				row=rand()%N;
				col=rand()%(N-LONGEST);//(TPO)
				tempc=col;
				
				for(j=0;wordlist[bigindex][j]!='\0';++j){
					if(puzzle[row][col]==EMPTY){
						will_be_reversed[reverse_index]=wordlist[bigindex][j];//the storing phase
						++reverse_index;//reversed string size
						++col;
					}
					else
						goto try_again1;
				}
				
				col=tempc;
				for(j=reverse_index-1;j>=0;--j){//TPO (reverseindex-1)
					puzzle[row][col]=will_be_reversed[j];//switcheroo
					++col;
				}
				break;
				
		
/*case2*/	case 2://top to bot
				++count2;
				try_again2:
				row=rand()%(N-LONGEST);			
				col=rand()%N;
				tempr=row;
				
				for(j=0;wordlist[bigindex][j]!='\0';++j){
					if(puzzle[row][col]==EMPTY){
						puzzle[row][col]=wordlist[bigindex][j];
						++row;
					}
					else//{
					/*	while(tempr!=row){
							puzzle[row][col]=EMPTY;
							--row;
						}
					*/	
						goto try_again2;
					//}
				}
				break;

		
/*case3*/	case 3://bottom to top WE ARE NOT ACTUALLY PRINTING FROM BOTTOM TO TOP WE ARE PRINTING FROM TOP TO BOTTOM BUT THE LETTERS ARE REVERSED IN ANOTHER ARRAY(Note to self)
				++count3;
				try_again3:
				reverse_index=0;
				row=rand()%(N-LONGEST);			
				col=rand()%N;
				tempr=row;
				for(j=0;wordlist[bigindex][j]!='\0';++j){
					if(puzzle[row][col]==EMPTY){
						will_be_reversed[reverse_index]=wordlist[bigindex][j];
						++reverse_index;
						++row;
					}
					else
						goto try_again3;
				}
				row=tempr;
				for(j=reverse_index-1;j>=0;--j){
					puzzle[row][col]=will_be_reversed[j];
					++row;
				}
				break;
				
		
/*case4*/	case 4://topleft to botright
				++count4;
				try_again4:
				row=rand()%(N-LONGEST);
				col=rand()%(N-LONGEST);
				tempr=row;
				tempc=col;
				
				for(j=0;wordlist[bigindex][j]!='\0';++j){
					if(puzzle[row][col]==EMPTY){
						puzzle[row][col]=wordlist[bigindex][j];
						++col;
						++row;
					}
					else//{
					/*	while(tempr!=row){
							puzzle[row][tempc]=EMPTY;
							--row;
						}
						while(tempc!=col){
							puzzle[tempr][col]=EMPTY;
							--col;
						}
					*/	
						goto try_again4;
				//	}
				}
				break;
		
		
/*case5*/	case 5://botleft to topright
				++count5;
				try_again5:
				row=LONGEST+ rand() % (N-LONGEST);
				col=rand()%(N-LONGEST);
				tempr=row;
				tempc=col;
				for(j=0;wordlist[bigindex][j]!='\0';++j){
					if(puzzle[row][col]==EMPTY){
						puzzle[row][col]=wordlist[bigindex][j];
						++col;
						--row;
					}
					else//{
					/*	while(tempr!=row){
							puzzle[row][tempc]=EMPTY;
							++row;
						}
						while(tempc!=col){
							puzzle[tempr][col]=EMPTY;
							--col;
						}
					*/	
						goto try_again5;
				//	}
				}
				break;
		
		
/*case6*/	case 6://topright to botleft
				++count6;
				try_again6:
				reverse_index=0;
				row=rand()%(N-LONGEST);
				col=rand()%(N-LONGEST);
				tempr=row;
				tempc=col;
				for(j=0;wordlist[bigindex][j]!='\0';++j){
					if(puzzle[row][col]==EMPTY){
						will_be_reversed[reverse_index]=wordlist[bigindex][j];
						++col;
						--row;
						++reverse_index;
					}
					else
						goto try_again6;
				}
				row=tempr;
				col=tempc;
				for(j=reverse_index-1;j>=0;--j){
					puzzle[row][col]=will_be_reversed[j];
					++col;
					--row;
				}
				break;
		
		
/*case7*/	case 7://botright to topleft
				count7++;
				try_again7:
				reverse_index=0;
				row=LONGEST+ rand() % (N-LONGEST);
				col=rand()%(N-LONGEST);
				tempr=row;
				tempc=col;
				for(j=0;wordlist[bigindex][j]!='\0';++j){
					if(puzzle[row][col]==EMPTY){
						will_be_reversed[reverse_index]=wordlist[bigindex][j];
						++col;
						++row;
						++reverse_index;
					}
					else
						goto try_again7;
				}
				row=tempr;
				col=tempc;
				for(j=reverse_index-1;j>=0;--j){
					puzzle[row][col]=will_be_reversed[j];
					++col;
					++row;
				}
				break;
		};
		++bigindex;
	}
	
	printf("There are %d Left To Right Answers\n",count0);
	printf("There are %d Right To Left Answers\n",count1);
	printf("There are %d Top To Bottom Answers\n",count2);
	printf("There are %d Bottom To Top Answers\n",count3);
	printf("There are %d TopLeft To BottomRight Answers\n",count4);
	printf("There are %d BottomLeft To TopRight Answers\n",count5);
	printf("There are %d TopRight To BottomLeft Answers\n",count6);
	printf("There are %d BottomRight To TopLeft Answers\n",count7);
	
	
}


/*This was just madness
int going_okay(char crnt_letteri,char crnt_letterj,char *pWord)//left to right
{
	int a,b,c,d,e,f,g,h;
	
	if(*pWord=='\0')
		return 1;
	else
	while(puzzle[crnt_letteri][crnt_letterj]==*pWord&&(a||b||c||d||e||f||g||h)){
	a=  going_okay(crnt_letteri,crnt_letterj+1,pWord+1);
	b=  going_okay(crnt_letteri,crnt_letterj-1,pWord+1);
	c=	going_okay(crnt_letteri+1,crnt_letterj,pWord+1);
	d=	going_okay(crnt_letteri-1,crnt_letterj,pWord+1);
	e=	going_okay(crnt_letteri+1,crnt_letterj+1,pWord+1);
	f=	going_okay(crnt_letteri+1,crnt_letterj-1,pWord+1);
	g=	going_okay(crnt_letteri-1,crnt_letterj+1,pWord+1);
	h=	going_okay(crnt_letteri-1,crnt_letterj-1,pWord+1);
	}
	return 0;
}
*/

/*
int going_okay_lr(char crnt_letteri,char crnt_letterj,char *pWord)//left to right
{
	int count=0;
	if(count==strlen(pWord))
		return 1;
	else if(puzzle[crnt_letteri][crnt_letterj]==*pWord){
		++count;
		going_okay_lr(crnt_letteri,crnt_letterj+1,pWord+1);
	}
	else
		return 0;
}

int going_okay_rl(char crnt_letteri,char crnt_letterj,char *pWord)//left to right
{
	int count=0;
	if(count==strlen(pWord))
		return 1;
	else if(puzzle[crnt_letteri][crnt_letterj]==*pWord){
		++count;
		going_okay_rl(crnt_letteri,crnt_letterj-1,pWord+1);
	}
	else
		return 0;
}

int going_okay_tb(char crnt_letteri,char crnt_letterj,char *pWord)//top to bottom
{
	int count=0;
	if(count==strlen(pWord))
		return 1;
	else if(puzzle[crnt_letteri][crnt_letterj]==*pWord){
		++count;
		going_okay_tb(crnt_letteri+1,crnt_letterj,pWord+1);
	}
	else
		return 0;
}

int going_okay_bt(char crnt_letteri,char crnt_letterj,char *pWord)//top to bottom
{
	int count=0;
	if(count==strlen(pWord))
		return 1;
	else if(puzzle[crnt_letteri][crnt_letterj]==*pWord){
		++count;
		going_okay_bt(crnt_letteri-1,crnt_letterj,pWord+1);
	}
	else
		return 0;
}

int going_okay_lTrB(char crnt_letteri,char crnt_letterj,char *pWord)//left top to right bottom
{
	int count=0;
	if(count==strlen(pWord))
		return 1;
	else if(puzzle[crnt_letteri][crnt_letterj]==*pWord){
		++count;
		going_okay_lTrB(crnt_letteri+1,crnt_letterj+1,pWord+1);
	}
	else
		return 0;
}

int going_okay_rTlB(char crnt_letteri,char crnt_letterj,char *pWord)//right top to left bottom
{
	int count=0;
	if(count==strlen(pWord))
		return 1;
	else if(puzzle[crnt_letteri][crnt_letterj]==*pWord){
		++count;
		going_okay_rTlB(crnt_letteri+1,crnt_letterj-1,pWord+1);
	}
	else
		return 0;
}

int going_okay_lBrT(char crnt_letteri,char crnt_letterj,char *pWord)//left bottom to right top
{
	int count=0;
	if(count==strlen(pWord))
		return 1;
	else if(puzzle[crnt_letteri][crnt_letterj]==*pWord){
		++count;
		going_okay_lBrT(crnt_letteri-1,crnt_letterj+1,pWord+1);
	}
	else
		return 0;
}

int going_okay_rBlT(char crnt_letteri,char crnt_letterj,char *pWord)//right bottom to left top
{
	int count=0;
	if(count==strlen(pWord))
		return 1;
	else if(puzzle[crnt_letteri][crnt_letterj]==*pWord){
		++count;
		going_okay_rBlT(crnt_letteri-1,crnt_letterj-1,pWord+1);
	}
	else
		return 0;
}
*//*
void auto_solve(int selection)
{
	int i=0,j=0,w;
	char c;
	char *pC;
	for(w=0;w<selection;++w){
		c=wordlist[w][0];
		pC=wordlist[w];
		loop:
		if(c==puzzle[i][j]){
			if(going_okay_lr(i,j,pC)||going_okay_rl(i,j,pC)||going_okay_tb(i,j,pC)||going_okay_bt(i,j,pC)||going_okay_lTrB(i,j,pC),going_okay_rTlB(i,j,pC)||going_okay_lBrT(i,j,pC)||going_okay_rBlT(i,j,pC))
		//	if(going_okay(i,j,pC))
				puzzle[i][j]-=32;
		}
		++i;
		++j;
		if(i<N&&j<N)
			goto loop;
	}
}
*/

void save_solution()//Saves the solved maze and capitalizes the answers
{
	int i,j;
	for(i=0;i<N;++i){
		for(j=0;j<N;++j){
			solvedpuzzle[i][j]=puzzle[i][j];
			if(solvedpuzzle[i][j]!=EMPTY)
				solvedpuzzle[i][j]-=32;
		}
	}
}

void random_filler()//does the shuffling of random chars
{
	int i,j;
	char randomchar;
	
	for(i=0;i<N;++i){
		for(j=0;j<N;++j){
			if(puzzle[i][j]==EMPTY){
				randomchar = (char)(97+ rand() % (26));
				puzzle[i][j]=randomchar;
			}
		}
	}
}

void wordlist_print(int selection)
{
	int i,j;
	for(i=0;i<selection;++i){
		for(j=0;wordlist[i][j]!='\0';++j)
			printf("%c",wordlist[i][j]);
		printf(" ");
	}
	printf("\n");
}

void print_game(char arr[][N])//basic print function with indentation
{
	int i,j;
	for(i=0;i<N;++i){
		if(i<9)//for visual purposes because 10 is 2 digits but 2 is only 1(in other words indentation purposes)
			printf(" ");
		printf("%d-",i+1);
		for(j=0;j<N;++j){
			printf("%c",arr[i][j]);
		}
		printf("\n");
	}
}

void word_puzzle()//for a clearer main
{
	srand(time(NULL));
	first_fill();
	int selection=select_mode();
	rwi_randomizer(selection);
	word_randomizer(selection);
	valid_filler(selection);
	save_solution();
	random_filler();
	print_game(puzzle);
//auto_solve(selection);
	printf("\nThe words you should find:\n");
	wordlist_print(selection);
	printf("\nPlease press any key to see the answer sheet\n");
	getch();
	print_game(solvedpuzzle);
//print_game(puzzle);
}

int main()
{
	word_puzzle();
	
	return 0;
}

