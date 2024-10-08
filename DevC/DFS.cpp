//programmed by HOANG HUU VIET
#include <stdio.h>
#include <conio.h>
//the number of nodes
#define N 6
//display the frontier and explored sets
void display(int queue[], int k){
	for (int i = 0; i<k; i++)
		printf("%5d",queue[i]);
}
//take the top element of the frontier
int pop(int queue[], int &k){
	int node = queue[0];
	for (int i = 0; i<k; i++){
		queue[i] = queue[i+1];
	}
	k = k-1;
	return node;
}
//insert an element to the lifo queue
void insert(int queue[], int &k, int node){
	if (k == 0){
		queue[0] = node;
	}
	else{
		for (int i = k; i>0; i--){
			queue[i] = queue[i-1];
		}
		queue[0] = node;
	}
	k = k+1;
}
//check an element in the frontier and explored sets
bool exist(int queue[], int k, int node){
	for (int i = 0; i<k; i++){
		if (queue[i] == node){
			return true;
		}
	}
	return false;
}
//print solution
void solution(int parent[], int start, int goal)
{
	int path[N];
	int k = 0;
	path[k++] = goal;
	int node = goal;
	while (parent[node] != start){
		node = parent[node];
		path[k++] = node;
	}
	path[k++] = start; 
	printf("\n\n SOLUTION:");
	for (int i = k-1; i>=0; i--){
		printf("%5d",path[i]);
	}	
}

//DFS algorithm
void dfs(int graph[][N], int start, int goal)
{
	int frontier[N] = {0}, explored[N] = {0}, parent[N] = {0};
	//sizes of frontier and explores
	int n = 0, m = 0;
	int node = start;
	parent[node] = node;
	
	insert(frontier,n,node);	
	int iter = 1;
	while (true){
		
		printf("\n\n -------- iteration %d -----------",iter);
		node = pop(frontier,n);		
		insert(explored,m,node);
				
		printf("\n node: %5d ->",node);		
		for (int j = 0; j<N; j++){
			if (graph[node][j] == 1){
				int child = j;
				if (!(exist(explored,m,child)||exist(frontier,n,child))){
					parent[child] = node;
					printf("%5d",child);
					if (child == goal){						
						solution(parent,start,goal);
						return;
					}
					insert(frontier,n,child);
				}
			}
		}
		printf("\n explored set:");
		display(explored,m);		
		printf("\n frontier set:");
		display(frontier,n);		
	    iter++;
	}
}
//the main program
int main(){	
	//an example adjacency matrix 
	int graph[N][N] = {
        {0, 1, 1, 0, 0, 0},
        {1, 0, 0, 1, 1, 0},
        {1, 0, 0, 0, 1, 1},
        {0, 1, 0, 0, 1, 0},
        {0, 1, 1, 1, 0, 1},
        {0, 0, 1, 0, 1, 0}
    };  
	int start =0;
	int goal = 5;
	dfs(graph,start,goal);
	return 0;
}