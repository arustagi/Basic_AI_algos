//A-star seach
//Most of the staments like checking points and printing the final path are same, so please refer UCS.cc for comments
#include <iostream.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <queue.h>
#include <vector.h>
#include <stack.h>
#define FREE 	10001
#define START	10002
#define END		10003
#define USED	10004
#define PATH	10005



void Astar(int **grid, int w, int h, bool bottomFavor,bool myhn,int stats,int iMD);

struct Point{
	int x;
	int y;
	float gn;
	float hn;
};
	
bool CheckPoint(Point p1,Point p2)
	{
		
		if(p2.x==p1.x && p2.y==p1.y)
			return true;
			
		return false;
	}	
	
class ComparePoint{
	
	public:
		
	bool operator()(const Point& p1,const Point& p2) const
    {
		if ( p1.gn + p1.hn >= p2.gn + p2.hn) return true;
		return false;
    }
	
	
};

bool ImpvMD(int x, int y, int **grid, Point end)
{
	int temp1,temp2;
	if(end.x == x)
	{
		if(end.y>y)
		{
			temp1=y;
			temp2=end.y;
		}
		else
		{
			temp2=y;
			temp1=end.y;
		}
		for(;temp1<temp2;temp1++)
			if(grid[temp1][x]==USED)
				return true;
	}
	
	if(end.y == y)
	{
		if(end.x>x)
		{
			temp1=x;
			temp2=end.x;
		}
		else
		{
			temp2=x;
			temp1=end.x;
		}
		for(;temp1<temp2;temp1++)
			if(grid[y][temp1]==USED)
				return true;
	}
	
	
	return false;
}

void Astar(int **grid,const int w,const int h, bool bottomFavor,bool myhn,int stats,int iMD)
{
	priority_queue<Point,vector<Point>,ComparePoint> pq;
	
	int Cost[h][w];
	Point start, end,temp1,temp2;
	int x,y,temp,temp3;
	
	int nodesExpanded=0;
	for(int i=0;i<h;i++)
		for(int j=0; j<w; j++)
			Cost[i][j]=30000;
	
	for(int i=0;i<h;i++)
		for(int j=0; j<w; j++)
			if(grid[i][j]==START)
			{
				start.x=j;
				start.y=i;
				start.gn=0;
				start.hn=0;
			}
			else if(grid[i][j]==END)
			{
				end.x=j;
				end.y=i;
			}
			
	pq.push(start);
	
	while( ! pq.empty())
	{
		temp1=pq.top();
		pq.pop();
		x=temp1.x;
		y=temp1.y;
		temp=y*100 + x;
		
		temp2.gn=temp1.gn + 1;
		
		//cout<<"\nExpanding y:"<<y<<" x:"<<x<<" cost:"<<temp1.gn;
		nodesExpanded++;
		if(CheckPoint(end,temp1))
			break;
			
		if(y > 0)
		{
			if(grid[y-1][x]!=USED)	//grid[y-1][x]==FREE || grid[y-1][x]==END
			{
				
				
				temp2.x=x;
				temp2.y=y-1;
				if(bottomFavor)
					temp2.gn+= temp2.y*0.1;
				
				if(Cost[y-1][x]>temp2.gn)
				{
					Cost[y-1][x]=temp2.gn;
				
					grid[y-1][x]=temp;
					if(myhn)
						temp2.hn=sqrt(pow((temp2.x-end.x),2) + pow((temp2.y-end.y),2));
					else
					{
						temp2.hn=abs(temp2.x-end.x) + abs(temp2.y-end.y);
						if(iMD)
							if(ImpvMD(temp2.x,temp2.y,grid,end))
								temp2.hn+=2;
						
					}	
				/*	abs(temp2.x-end.x) + abs(temp2.y-end.y);
				else
				
					temp2.hn=abs(temp2.x-end.x) + abs(temp2.y-end.y);
					
					
				*/
					pq.push(temp2);
				}
			}
		}
		
		if(y < h-1)
			if(grid[y+1][x]!=USED)
			{
				
				temp2.x=x;
				temp2.y=y+1;
				if(bottomFavor)
					temp2.gn+= temp2.y*0.1;
				if(Cost[y+1][x]>temp2.gn)
				{
					Cost[y+1][x]=temp2.gn;
					grid[y+1][x]=temp;
					if(myhn)
						temp2.hn=sqrt(pow((temp2.x-end.x),2) + pow((temp2.y-end.y),2));
					else
					{
						temp2.hn=abs(temp2.x-end.x) + abs(temp2.y-end.y);
						if(iMD)
							if(ImpvMD(temp2.x,temp2.y,grid,end))
								temp2.hn+=2;
						
					}
				/*	abs(temp2.x-end.x) + abs(temp2.y-end.y);
				else
				
					temp2.hn=abs(temp2.x-end.x) + abs(temp2.y-end.y);
					if(myhn)
						if(ImpvMD(x,y+1,grid,end))
							temp2.hn+=2;
					*/
					pq.push(temp2);
				}
			}
			
		if(x>0)
			if(grid[y][x-1]!=USED)
			{
				
				temp2.x=x-1;
				temp2.y=y;
				if(bottomFavor)
					temp2.gn+= temp2.y*0.1;
					
				if(Cost[y][x-1]>temp2.gn)
				{
					Cost[y][x-1]=temp2.gn;
					grid[y][x-1]=temp;
					if(myhn)
						temp2.hn=sqrt(pow((temp2.x-end.x),2) + pow((temp2.y-end.y),2));
					else
					{
						temp2.hn=abs(temp2.x-end.x) + abs(temp2.y-end.y);
						if(iMD)
							if(ImpvMD(temp2.x,temp2.y,grid,end))
								temp2.hn+=2;
						
					}
				/*	abs(temp2.x-end.x) + abs(temp2.y-end.y);
				else
				
					temp2.hn=abs(temp2.x-end.x) + abs(temp2.y-end.y);
					if(myhn)
						if(ImpvMD(x-1,y,grid,end))
							temp2.hn+=2;
				*/
					pq.push(temp2);
				}
			}
			
		if(x < w-1)
			if(grid[y][x+1]!=USED)
			{
				
				temp2.x=x+1;
				temp2.y=y;
				if(bottomFavor)
					temp2.gn+= temp2.y*0.1;
				
				if(Cost[y][x+1]>temp2.gn)
				{
					Cost[y][x+1]=temp2.gn;
					grid[y][x+1]=temp;
					
					
					if(myhn)
						temp2.hn=sqrt(pow((temp2.x-end.x),2) + pow((temp2.y-end.y),2));
					else
					{
						temp2.hn=abs(temp2.x-end.x) + abs(temp2.y-end.y);
						if(iMD)
							if(ImpvMD(temp2.x,temp2.y,grid,end))
								temp2.hn+=2;
						
					}
				
				/*	abs(temp2.x-end.x) + abs(temp2.y-end.y);
				else
				
					temp2.hn=abs(temp2.x-end.x) + abs(temp2.y-end.y);
					if(myhn)
						if(ImpvMD(x+1,y,grid,end))
							temp2.hn+=2; */
				
					pq.push(temp2);
				}
			}
	}
	/*printf("count :%d\n",count);
		for(int i=h-1;i>=0;i--)
	{
		for(int j=0;j<w;j++)
			printf("%6d ",grid[i][j]);
		cout<<"\n";
	}*/
	if(pq.empty())
	{
		cout<<"NOT FOUND\n";
		for(int i=0;i<h;i++)
			for(int j=0; j<w; j++)
				if(grid[i][j]!=START && grid[i][j]!=USED)
					grid[i][j]=FREE;
		grid[end.y][end.x]=END;
		grid[start.y][start.x]=START;
	}
	else
	{
		stack<int> Path;
		int nodesOnPath=0;
		cout<<"Found Path\n";
		temp=end.y*100+end.x;
		while(temp!=(start.y*100+start.x))
		{
			Path.push(temp);
			temp3=grid[temp/100][temp%100];
			grid[temp/100][temp%100]=PATH;
			temp=temp3;	
		}
		Path.push(temp);
		grid[start.y][start.x]=START;
		grid[end.y][end.x]=END;
		
		while(!Path.empty())
		{
			temp=Path.top();
			Path.pop();
			nodesOnPath++;
			cout<<"("<<temp%100 <<","<<temp/100<<")\n";
		}
		if(stats)
		{
			cout<<"Estimated Cost (by heuristic function): ";
			if(myhn)
				cout<<sqrt(pow((double)(start.x-end.x),2) + pow((double)(start.y-end.y),2));
			else
			{
				temp=abs(start.x-end.x) + abs(start.y-end.y);
				if(iMD)
					if(ImpvMD(start.x,start.y,grid,end))
						temp+=2;
				cout<<temp;		
			}
			
			cout<<endl;
			cout<<"Nodes Expanded: "<<nodesExpanded<<endl;
			cout<<"Nodes on Path: "<<nodesOnPath<<endl;
			cout<<"Ratio: "<<nodesOnPath/(double)nodesExpanded<<endl;
		}
	}
	
	

}
