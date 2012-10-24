//depth-first search
//Most of the staments like checking points and printing the final path are same, so please refer UCS.cc for comments
#include <iostream.h>
#include <stdlib.h>
#include <string.h>
#include <stack.h>

#define FREE 	10001
#define START	10002
#define END		10003
#define USED	10004
#define PATH	10005

int start, end;
void DFS(int **grid, int w, int h,int stats);

int DFSfunc(int **grid, int w, int h, int point)
{
	int x,y,temp;
	temp=point;
	static int nodesExpanded=0;
	x=temp%100;
	y=temp/100;
	nodesExpanded++;
	if(grid[end/100][end%100] != END)
		return nodesExpanded;
		
	if(y > 0)
	{
		if(grid[y-1][x]==FREE || grid[y-1][x]==END)
		{
			
			grid[y-1][x]=temp;
			DFSfunc(grid,w,h,(y-1)*100+x);
		}
	}
	
	if(grid[end/100][end%100] != END)
		return nodesExpanded;
		
	if(y < h-1)
		if(grid[y+1][x]==FREE || grid[y+1][x]==END)
		{
			
			grid[y+1][x]=temp;
			DFSfunc(grid,w,h,(y+1)*100+x);
		}
	
	if(grid[end/100][end%100] != END)
		return nodesExpanded;
	if(x>0)
		if(grid[y][x-1]==FREE || grid[y][x-1]==END)
		{
			
			grid[y][x-1]=temp;
			DFSfunc(grid,w,h,y*100+x-1);
		}
	
	if(grid[end/100][end%100] != END)
		return nodesExpanded;
	if(x < w-1)
		if(grid[y][x+1]==FREE || grid[y][x+1]==END)
		{
			
			grid[y][x+1]=temp;
			DFSfunc(grid,w,h,y*100+x+1);
		}
	return nodesExpanded;
}

void DFS(int **grid, int w, int h,int stats)
{
	
	
	int temp,temp2;
	int nodesExpanded;
	for(int i=0;i<h;i++)
		for(int j=0; j<w; j++)
			if(grid[i][j]==START)
				start=i*100+j;
			else if(grid[i][j]==END)
				end=i*100+j;

	nodesExpanded=DFSfunc(grid,w,h, start);
	
	
	
	
	
	if(grid[end/100][end%100] == END)
	{
		cout<<"NOT FOUND\n";
		for(int i=0;i<h;i++)
			for(int j=0; j<w; j++)
				if(grid[i][j]!=START && grid[i][j]!=USED)
					grid[i][j]=FREE;
		grid[end/100][end%100]=END;
	}
	else
	{
		stack<int> Path;
		int nodesOnPath=0;
		cout<<"Found Path\n";
		temp=end;
		while(temp!=start)
		{
			Path.push(temp);
			temp2=grid[temp/100][temp%100];
			grid[temp/100][temp%100]=PATH;
			temp=temp2;	
		}
		Path.push(temp);
		grid[start/100][start%100]=START;
		grid[end/100][end%100]=END;
		
		while(!Path.empty())
		{
			temp=Path.top();
			Path.pop();
			nodesOnPath++;
			cout<<"("<<temp%100 <<","<<temp/100<<")\n";
		}
		if(stats)
		{
			cout<<"Nodes Expanded: "<<nodesExpanded<<endl;
			cout<<"Nodes on Path: "<<nodesOnPath<<endl;
			cout<<"Ratio: "<<nodesOnPath/(double)nodesExpanded<<endl;
		}

	}
}
