#include <iostream.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "project1.h"

#define FREE 	10001
#define START	10002
#define END		10003
#define USED	10004
#define PATH	10005


void printGrid(int **grid,int w, int h);


int main(int argc, char *argv[])
{
	char line[40],*temp1,*temp2,*temp3;
	FILE *fr;            	/* declare the file pointer */
	char *arg;
	int **grid;
	int step=0;
	
	int whichAlgo=0; 	/*1 BFS
						  2 DFS
						  3 UCS
						  4 Astar*/
	int altC, altH,stats,iMD;
	altC=altH=stats=iMD=0;
	
//----------------------reading the commandline arguments	
	argc--,	argv++;

	while(argc>1)
	{
		arg=argv[0];
		arg++;
		if(strcmp(arg,"BFS") ==0)
		{
			if(!whichAlgo)
				whichAlgo=1;
			else
			{
				cout<<"\n Error in command line arguments. Exiting Program.\n";
				exit(0);
			}
		}
		else if(strcmp(arg,"DFS") ==0)
		{
			if(!whichAlgo)
				whichAlgo=2;
			else
			{
				cout<<"\n Error in command line arguments. Exiting Program.\n";
				exit(0);
			}
		}
		else if(strcmp(arg,"UCS") ==0)
		{
			if(!whichAlgo)
				whichAlgo=3;
			else
			{
				cout<<"\n Error in command line arguments. Exiting Program.\n";
				exit(0);
			}
		}
		else if(strcmp(arg,"Astar") ==0)
		{
			if(!whichAlgo)
				whichAlgo=4;
			else
			{
				cout<<"\n Error in command line arguments. Exiting Program.\n";
				exit(0);
			}
		}
		else if(strcmp(arg,"stats") ==0)
		{
			stats=1;
		}
		else if(strcmp(arg,"AltC") ==0)
		{
			altC=1;
		}
		else if(strcmp(arg,"AltH") ==0)
		{
			altH=1;
		}
		else if(strcmp(arg,"IMD") ==0)
		{
			iMD=1;
		}
		else
		{
			cout<<"\n Error in command line arguments. Exiting Program.\n";
			exit(0);
		}
	
		argc--; 
		argv++;
	}
	
//------------------------validating what was read 
	if(whichAlgo==0)
	{
		cout<<"\n Error in command line arguments. Exiting Program.\n";
		exit(0);
	}
	
	if(altH || iMD)
		if(whichAlgo!=4)
		{
			cout<<"\n Heuristic can only be used with Astar. Exiting Program.\n";
			exit(0);
		}
		
	if(altH && iMD)
	{
		cout<<"\n Improved mahattan distance can be used only with manhatan distance. Exiting Program.\n";
		exit(0);
	}
	
	if(altC)
		if(whichAlgo!=4 && whichAlgo!=3)
		{
			cout<<"\n Bottom favoring can only be used with Astar or UCS. Exiting Program.\n";
			exit(0);
		}
	
	
	
	
	
	fr = fopen (argv[0], "rt");  /* open the file for reading */
	
	if(fr == NULL)
	{
		cout<<"\n Error in opening file. Exiting Program.\n";
		exit(0);
	}
//----------------------------------checking the file format and if yes then saving it in the grid 2-d array
	//check if grid is in bounds of 2 to 30
	//check if point is within the grid
	//check if it does not intersects with some other
	
	int w,h,sx,sy,ex,ey,t1x,t1y,t2x,t2y;
	w=h=sx=sy=ex=ey=t1x=t1y=t2x=t2y=-1;
	int errorline=0;
	while(fgets(line, 40, fr) != NULL)
	{
		errorline++;
		for(int i=0, count=0;;i++)
		{
			if(line[i]==' ' ||line[i]=='\t' ||line[i]==','||line[i]=='\r'||line[i]=='\n')
				count++;
				
			//cout<<"\n"<<line<<"*"<<i<<" "<<count<<"\n";
			
			if(line[i]=='\0' && i==count)
			{
				cout<<"\n Error in Input File on line number "<<errorline<<". Exiting Program.\n";
				exit(0);
			}
			
			if(line[i]=='\0')
				break;
		}
		if(line[0]==',' || line[0]==' ')
		{
				cout<<"\n Error in Input File on line number "<<errorline<<". Exiting Program.\n";
				exit(0);
		
		}
		temp1=strtok(line,", \n");
		if(temp1==NULL)
		{
				cout<<"\n Error in Input File on line number "<<errorline<<". Exiting Program.\n";
				exit(0);
		
		}
		/*if(temp1)
			printf("%s",temp1);
		else
			printf("t1 is null");
			*/
		temp2=strtok(NULL,", \n");
		if(temp2==NULL)
		{
				cout<<"\n Error in Input File on line number "<<errorline<<". Exiting Program.\n";
				exit(0);
		
		}
		
		if(strlen(temp2) <=0)
		{
				cout<<"\n Error in Input File on line number "<<errorline<<". Exiting Program.\n";
				exit(0);
		
		}
		
		/*if(temp2)
			printf(" %s\n",temp2);
		else
			printf("t2 is null");
			*/
		temp3=strtok(NULL,", \n");
		//printf("<%s>",temp3);
		if(temp3 != NULL)
		{
			cout<<"\n Error in Input File on line number "<<errorline<<". Exiting Program.\n";
			exit(0);
		}
		else if(step >=3)
		{
			//t1 current position
			//t2 previous position
			t1x=atoi(temp1);
			t1y=atoi(temp2);

			if(t1x<0 || t1x>=w || t1y<0 || t1y>=h)
			{
				if(t1x==-1 && t1y==-1)
				{
					if(step==3)
					{
						cout<<"\n Error in Input File on line number "<<errorline<<". Exiting Program.\n";
						exit(0);
					}
				}
				else
				{
					cout<<"\n Error in Input File on line number "<<errorline<<". Exiting Program.\n";
					exit(0);
				}
			}
			
			if(step==3)
					step++;
			
			if(t1x ==-1 && t1y==-1)
			{
				t2x=t2y=-1;
				continue;
			}
			
			
			if(grid[t1y][t1x] != FREE)
			{
				cout<<"\n Error in Input File on line number "<<errorline<<". Exiting Program.\n";
				exit(0);
			}
			
			if(t2x != -1)	//new wire starting
			{
				if(!((t1x==t2x+1 && t1y==t2y) || (t1x==t2x-1 && t1y==t2y)||(t1x==t2x && t1y==t2y+1)||(t1x==t2x && t1y==t2y-1)))
				{
					cout<<"\n Error in Input File on line number "<<errorline<<". Exiting Program.\n";
					exit(0);			
				}
			}
			t2x=t1x;
			t2y=t1y;
			grid[t1y][t1x]=USED;
		}
		else if(step==0)
		{
			w=atoi(temp1);
			h=atoi(temp2);
			if(w<2 || w>30 || h<2 || h>30)
			{
				cout<<"\n Error in Input File on line number "<<errorline<<". Exiting Program.\n";
				exit(0);			
			}
			grid=(int **) calloc(h, sizeof(int *));
			
			for(int i=0;i<h;i++)
				grid[i]=(int *) calloc(w,sizeof(int));
				
			for(int i=0;i<h;i++)
				for(int j=0;j<w;j++)
					grid[i][j]=FREE;
			step++;
		}
		else if(step==1)
		{
			sx=atoi(temp1);
			sy=atoi(temp2);
			if(sx<0 || sx>=w || sy<0 || sy>=h)
			{
				cout<<"\n Error in Input File on line number "<<errorline<<". Exiting Program.\n";
				exit(0);			
			}
			grid[sy][sx]=START; 
			step++;
		}
		else if(step==2)
		{
			ex=atoi(temp1);
			ey=atoi(temp2);
			if(ex<0 || ex>=w || ey<0 || ey>=h)
			{
				cout<<"\n Error in Input File on line number "<<errorline<<". Exiting Program.\n";
				exit(0);			
			}
			if(grid[ey][ex]==START)
			{
				cout<<"\n Error in Input File on line number "<<errorline<<". Exiting Program.\n";
				exit(0);			
			}
			grid[ey][ex]=END; 
			step++;
		}
	}
	fclose(fr);  	/* close the file prior to exiting the routine */
	
	if(t2x!=-1 || t2y!=-1)
	{
		cout<<"\n Error in Input File on line number "<<errorline<<". Exiting Program.\n";
		exit(0);			
	}
	
//	printGrid(grid,w,h);	
	
//------------------------------calling the required function
	if(whichAlgo==1)
	{
		cout<<"Performing Breadth-First Search\n";
		BFS(grid,w,h,stats);
	}
	else if(whichAlgo==2)
	{
		cout<<"Performing Depth-First Search\n";
		DFS(grid,w,h,stats);
	}
	else if(whichAlgo==3)
	{
		cout<<"Performing Uniform-Cost Search\n";
		UCS(grid,w,h,altC,stats);
	}
	else
	{
		cout<<"Performing A* Search\n";
		Astar(grid,w,h,altC,altH,stats,iMD);
	}
	printGrid(grid,w,h);
	return 0;
}

//printing the whole grid
void printGrid(int **grid,int w, int h)
{
	cout<<"\n";
	for(int i=h-1;i>=0;i--)
	{
		for(int j=0;j<w;j++)
			if(grid[i][j]==START)
				cout<<" S ";
			else if(grid[i][j]==END)
				cout<<" E ";
			else if(grid[i][j]==USED)
				cout<<" N ";
			else if(grid[i][j]==PATH)
				cout<<" P ";
			else
				cout<<" * ";
		cout<<"\n";
		
	}
}


