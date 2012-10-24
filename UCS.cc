//Uniformed cost search
#include <iostream.h>
#include <stdlib.h>
#include <string.h>
#include <stack.h>
#include <queue.h>
#include <vector.h>

#define FREE 	10001
#define START	10002
#define END		10003
#define USED	10004
#define PATH	10005



void UCS(int **grid, int w, int h, bool bottomFavor,int stats);

//structure to refer a point
struct Points{
	int x;
	int y;
	float cost;
};
	
//It checks if 2 Points type variable have same x and y coordinate
bool CheckPoints(Points p1,Points p2)
	{
		
		if(p2.x==p1.x && p2.y==p1.y)
			return true;
			
		return false;
	}	
	
//class to compare the cost of 2 Points type varialble
class ComparePoints{
	
	public:
		
	bool operator()(const Points& p1,const Points& p2) const	//returns true if new points cost is less
    {
		if (p1.cost >= p2.cost) return true;	
		return false;
    }
	
	
};

void UCS(int **grid, int w, int h, bool bottomFavor,int stats)	//function UCS
{
	priority_queue<Points,vector<Points>,ComparePoints> pq;		//priority queue
	int nodesExpanded=0;
	Points start, end, temp1,temp2;
	int x,y,temp,temp3;
	
	for(int i=0;i<h;i++)		//initializing start and end points
		for(int j=0; j<w; j++)
			if(grid[i][j]==START)
			{
				start.x=j;
				start.y=i;
				start.cost=0;
			}
			else if(grid[i][j]==END)
			{
				end.x=j;
				end.y=i;
			}
			
	pq.push(start);
	
	while( ! pq.empty())	//run until queue is empty 
	{
		temp1=pq.top();
		pq.pop();
		x=temp1.x;
		y=temp1.y;
		temp=y*100 + x;
		temp2.cost=temp1.cost + 1;
		//cout<<"\nExpanding y:"<<y<<" x:"<<x<<" cost:"<<temp1.cost;
		nodesExpanded++;
		if(y > 0)							//validating if the point will be valid
		{
			if(grid[y-1][x]==FREE || grid[y-1][x]==END)	//if point is free or is end 
			{
				
				grid[y-1][x]=temp;
				temp2.x=x;
				temp2.y=y-1;
				if(bottomFavor)		
					temp2.cost=temp1.cost + 1 + temp2.y*0.1;
		
				pq.push(temp2);
				if(CheckPoints(end,temp2))	//if end point then break
					break;
			}
		}		
		if(y < h-1)		//similar to earlier
			if(grid[y+1][x]==FREE || grid[y+1][x]==END)
			{
				
				grid[y+1][x]=temp;
				temp2.x=x;
				temp2.y=y+1;
				if(bottomFavor)
					temp2.cost=temp1.cost + 1 + temp2.y*0.1;
				pq.push(temp2);
				if(CheckPoints(end,temp2))
					break;
			}
			
		if(x>0)
			if(grid[y][x-1]==FREE || grid[y][x-1]==END)
			{
				
				grid[y][x-1]=temp;
				temp2.x=x-1;
				temp2.y=y;
				if(bottomFavor)
					temp2.cost=temp1.cost + 1 + temp2.y*0.1;
				pq.push(temp2);
				if(CheckPoints(end,temp2))
					break;
			}
			
		if(x < w-1)
			if(grid[y][x+1]==FREE || grid[y][x+1]==END)
			{
				
				grid[y][x+1]=temp;
				temp2.x=x+1;
				temp2.y=y;
				if(bottomFavor)
					temp2.cost=temp1.cost + 1 + temp2.y*0.1;
				pq.push(temp2);
				if(CheckPoints(end,temp2))
					break;
			}
		
	
	
	}
	
	if(pq.empty())	//check if end point if found or not
	{
		cout<<"NOT FOUND\n";
		for(int i=0;i<h;i++)
			for(int j=0; j<w; j++)
				if(grid[i][j]!=START && grid[i][j]!=USED)
					grid[i][j]=FREE;
		grid[end.y][end.x]=END;
	}
	else
	{
		stack<int> Path;	//creating a stack
		int nodesOnPath=0;
		cout<<"Found Path\n";
		temp=end.y*100+end.x;
		while(temp!=(start.y*100+start.x))	//back traversing the path found
		{
			Path.push(temp);
			temp3=grid[temp/100][temp%100];
			grid[temp/100][temp%100]=PATH;
			temp=temp3;	
		}
		Path.push(temp);
		grid[start.y][start.x]=START;
		grid[end.y][end.x]=END;
		
		while(!Path.empty())	// printing the path
		{
			temp=Path.top();
			Path.pop();
			nodesOnPath++;
			cout<<"("<<temp%100 <<","<<temp/100<<")\n";
		}
		if(stats)	//printing the stats if required
		{
			cout<<"Nodes Expanded: "<<nodesExpanded<<endl;
			cout<<"Nodes on Path: "<<nodesOnPath<<endl;
			cout<<"Ratio: "<<nodesOnPath/(double)nodesExpanded<<endl;
		}
	}
}
