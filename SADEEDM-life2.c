#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

#define MAX_GAME_WIDTH 78
#define MAX_GAME_HEIGHT 50
#define NUMBER_OF_BOARDS 2

void borders(int, int);
void gameprint(int, int);
void genincrease(int, int, int);
void configset(FILE *fp, int width, int height);
int neighbourcheck(int, int, int);

char gamearray[MAX_GAME_WIDTH][MAX_GAME_HEIGHT][NUMBER_OF_BOARDS];

int main(int argc, char *argv[])
{
	int t=0;
	if (argc != 5)
	{
		fprintf(stderr,"Incorrect number of arguments. Correct number is 5");
		exit(EXIT_FAILURE);
	}
	
	FILE *fp;
	int i, j, k, width, height, gens;
	
	width=atoi(argv[2])+1;
	height=atoi(argv[3])+1;
	gens=atoi(argv[4])+1;
	
	fp = fopen(argv[1], "r");
	
	for (i=0;i<=MAX_GAME_HEIGHT; i++)
	{
		for(j=0;j<=MAX_GAME_WIDTH; j++)
		{
			for(k=0;k<NUMBER_OF_BOARDS; k++)
				{
					gamearray[j][i][k]=' ';	
				}
		}
	}
	
	borders(width, height);
	configset(fp,width, height);
	gameprint(width, height);
	
	
	for(i=1;i<gens;i++)
	{
		t++;
		genincrease(width, height, t);
		gameprint(width,height);
	}
	
	printf("Finished\n");
	
	fclose(fp);	
}

void borders(int width,int height)
{
	int i, j;
for(j=0;j<NUMBER_OF_BOARDS;j++)	
{
 gamearray[0][0][j]='*';
 gamearray[0][height][j]='*';	
 gamearray[width][0][j]='*';
 gamearray[width][height][j]='*';	
 
 
 for(i=1;i<width;i++)
	 {
		 gamearray[i][0][j]='-';
		 gamearray[i][height][j]='-';
	 }
	 
 for(i=1;i<height;i++)
	 {
		gamearray[0][i][j] ='|';
		gamearray[width][i][j] ='|';
	 }
 }
}

void gameprint(int width,int height)
{
	int i, j;

	printf("\n");
	for (i=0;i<=height; i++)
	{
		for(j=0;j<=width; j++)
		{
			printf("%c", gamearray[j][i][0]);
			
		}
		printf("\n");
	}
	printf("\n");

}

void configset(FILE *fp, int width, int height)
{
	int livecells;
	int x, y, i;
	fscanf(fp,"%i",&livecells);
	
	for(i=0;i<=livecells;i++)
	 {
    	fscanf(fp,"%i %i",&x, &y);
		gamearray[y+1][x+1][0]='0';
     }
}

void genincrease(int width, int height, int t)
{
	int i, j, neighbour;
	char age=' ', a;
	for(i=1;i<height;i++)
	{
		for(j=1;j<width;j++)
		{
			neighbour=neighbourcheck(i, j, t);
			if(gamearray[j][i][0]=='9')
			 {
				gamearray[j][i][1]='X';
			 }
			
				
			a=gamearray[j][i][0];
				 if('0'<a&&a<'9')
				 {
					gamearray[j][i][1]=gamearray[j][i][0]+1;
				 }
		     
			 
			
		
       for(age='0';age<='9';age++)
		 {
			
	    	if((gamearray[j][i][0]==age)||(gamearray[j][i][0]=='X'))
		     {
			if(neighbour<2)
				{
					gamearray[j][i][1]=' ';
				}
			if(neighbour==3||neighbour==2)
				{
					gamearray[j][i][1]=age+1;	
				}
			if(neighbour>3)
				{
					gamearray[j][i][1]=' ';
				}	
	         }
	     }
		 
		 if(gamearray[j][i][0]==' ')
		 {
 			if(neighbour==3)
 				{
 					gamearray[j][i][1]='0';
 				}
		 }
       }
			if(t==21){printf("\n");}	
	}
	
	
	
	
	for(i=1;i<height;i++)
	{
		for(j=1;j<width;j++)
			{
				gamearray[j][i][0]=gamearray[j][i][1];
			}
	}
	

}

int neighbourcheck(int i, int j, int t)
{
	int k, l, neighbour=0, b;
	for(k=-1;k<=1;k++)
			{ 
				for(l=-1;l<=1;l++)
				{
					b=gamearray[j+l][i+k][0];
					if (((b=='X')||(b=='0')||(b=='1')||(b=='2')||(b=='3')||(b=='4')||(b=='5')||(b=='6')||(b=='7')||(b=='8')||(b=='9'))&& (l!=0 || k!=0))
					{
						neighbour++;	
					}
				
				}
			}
		if(t==21){printf("%i",neighbour);}
	return neighbour;
}