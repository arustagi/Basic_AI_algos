//breadth-first search
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

void BFS(int **grid, int w, int h,int stats);

struct node{
	int data;
	struct node *next;
};

//queues implementation
class Queue{
private:
	
	struct node *start; 	//start of queue
	struct node *end;		//end of queue
public:
	Queue()
	{
		start=NULL;
		end=NULL;
	}
	
	bool IsEmpty()
	{
		if(start)
			return 0;
		else
			return 1;
	}
	
	void Enqueue(int data)
	{
		struct node *temp= (struct node*)malloc(sizeof(struct node));
		if(temp == NULL)
		{
			cout<<"Memory full, can't allocate memory";
			exit(0);
		}
		temp->data=data;
		temp->next=NULL;
		if(! start)	//if first element in queue
		{
			start=temp;
			end=temp;
		}
		else	//if one or more elements are present
		{
			end->next=temp;
			end=temp;
		}
		
	}
	
	int Dequeue()
	{
		struct node *temp;
		int data;
		temp=start;
		
		if(start==NULL)
		{
			printf("Nothing in queue");
			return -1;
		}
		
		if(start != end)
		{
			start=start->next;
		}
		else
		{
			start=NULL;
			end=NULL;
		}
		
		data=temp->data;
		free(temp);
		
		return data;
	}
	
	void Print()
	{
		struct node *temp;
		temp=start;
		cout<<"\n";
		while(temp != NULL)
		{
			cout<<" "<<temp->data;
			temp=temp->next;
		}
		cout<<"\n";
	}
};



void BFS(int **grid, int w, int h,int stats)
{
	Queue BFSq;
	int start, end;
	int x,y,temp,temp2;
	int nodesExpanded=0;
	for(int i=0;i<h;i++)
		for(int j=0; j<w; j++)
			if(grid[i][j]==START)
				start=i*100+j;
			else if(grid[i][j]==END)
				end=i*100+j;
			
	BFSq.Enqueue(start);
	//
	
	while(! BFSq.IsEmpty())
	{
		temp=BFSq.Dequeue();
		x=temp%100;
		y=temp/100;
		//cout<<"\nExpanding y:"<<y<<" x:"<<x;
		nodesExpanded++;
		if(y > 0)
		{
			if(grid[y-1][x]==FREE || grid[y-1][x]==END)
			{
				grid[y-1][x]=temp;
				BFSq.Enqueue((y-1)*100 + x);
				
				if(((y-1)*100 + x)==end)
					break;
			}
		}		
		if(y < h-1)
			if(grid[y+1][x]==FREE || grid[y+1][x]==END)
			{
				grid[y+1][x]=temp;
				BFSq.Enqueue((y+1)*100 + x);
				
				if(((y+1)*100 + x)==end)
					break;
			}
			
		if(x>0)
			if(grid[y][x-1]==FREE || grid[y][x-1]==END)
			{
				grid[y][x-1]=temp;
				BFSq.Enqueue(y*100 + x-1);	
				
				if((y*100 + x-1)==end)
					break;
			}
			
		if(x < w-1)
			if(grid[y][x+1]==FREE || grid[y][x+1]==END)
			{
				grid[y][x+1]=temp;
				BFSq.Enqueue(y*100 + x+1);
				
				if((y*100 + x+1)==end)
					break;
			}
	}
	
	/*BFSq.Print();
	printf("Printing GRID :\n");
	for(int i=h-1;i>=0;i--)
	{
		for(int j=0;j<w;j++)
			printf(" %6d ",grid[i][j]);
		printf("\n");
		
	}*/
	
	if(BFSq.IsEmpty())
	{
		cout<<"NOT FOUND\n";
		for(int i=0;i<h;i++)
			for(int j=0; j<w; j++)
				if(grid[i][j]!=START && grid[i][j]!=USED ) 
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

