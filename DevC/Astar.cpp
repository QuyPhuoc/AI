#include <stdio.h>
#include <conio.h>
//the number of vertices

#define N 6
#define str "ABCDEFGHIJK"
//struct for a state
struct vertex{
	int n;
	double g,h,f;
};
//display a queue
void display(vertex queue[], int k){
	for (int i = 0; i<k; i++)
		printf("(%c,%0.1f),",str[queue[i].n],queue[i].f);
}
//take a node of the minimum g in a queue
vertex pop(vertex queue[], int &k){
	vertex node = queue[0];
	int idx = 0;
	for (int i = 1; i<k; i++){
		if (node.f > queue[i].f){
			node = queue[i];
			idx = i;
		}	
	}
	for (int i = idx; i<k; i++){
		queue[i] = queue[i+1];
	}
	k = k - 1;
	return node;
}
//insert an element to a queue
void insert(vertex queue[], int &k, vertex node){
	queue[k] = node;
	k = k + 1;	
}
//check an element in the queue
bool exist(vertex queue[], int k, vertex node){
	for (int i = 0; i<k; i++){
		if (queue[i].n == node.n){
			return true;
		}
	}
	return false;
}
//take the solution
void solution(int parent[], vertex start, vertex goal){
	int path[N];
	int k = 0, node = goal.n;
	path[k++] = goal.n;
	while (node != start.n){
		node = parent[node];
		path[k++] = node;
	}
	printf("\n\n SOLUTION:");
	for (int i = k-1; i>=0; i--){
		printf("%c->",str[path[i]]);
	}
}

//Astar algorithm
void Astar(double graph[][N], double h[N], vertex start, vertex goal){	
    //struct for frontier, explored and parent
	vertex frontier[N], explored[N];
	//sizes of frontier and explores
	int size_frontier = 0, size_explored = 0;
	
	int parent[N];
    parent[start.n] = start.n;
   
    insert(frontier,size_frontier,start);
	int iter = 1;
	while (true){
		printf("\n\n -------- iteration %d -----------",iter);
		vertex node = pop(frontier,size_frontier);		
		//check goal
		if (node.n == goal.n){
			printf("\n take vertex %c -> stop.",str[node.n]);
			solution(parent,start,goal);
			printf("\n PATH -COST: %0.1f",node.f);
			return;
		}
		insert(explored,size_explored,node);
		printf("\n take vertex: %c ->",str[node.n]);		
		for (int j = 0; j<N; j++){
			if (graph[node.n][j] > 0){
				vertex child;
				child.n = j;
				child.h = h[j];			
				if (!(exist(explored,size_explored,child)||exist(frontier,size_frontier,child))){
					parent[child.n] = node.n;					
					//compute f(n) = g(n) + h(n)
					child.g = node.g + graph[node.n][j];
					child.f = child.g + child.h;
					//insert child to frontier 
					insert(frontier,size_frontier,child);					
					printf("%c, ",str[child.n]);
				}			
				else{				
					if (exist(frontier,size_frontier,child)){
						//find the index of child in the frontier
						int idx = 0;
						for (int i = 0; i < size_frontier; i++){
							if (frontier[i].n == child.n){
								idx = i;
								break;
							}
						}
						//replace the mininum node with child
						if (frontier[idx].f > node.g + graph[node.n][j] + h[j]){
							parent[child.n] = node.n;
							frontier[idx].f = node.g + graph[node.n][j] + h[j];
							printf("%c, ",str[child.n]);
						}
						else{
							printf("|");
						}
												
					}
				}
			}
		}
		printf("\n explored set:");
		display(explored,size_explored);		
		printf("\n frontier set:");
		display(frontier,size_frontier);				
	    iter++;
	}
}
//main
int main(){
	double graph[N][N] = {
        {0, 2, 7, 0, 0, 0},
        {2, 0, 0, 3, 1, 0},
        {7, 0, 0, 1, 0, 5},
        {0, 3, 1, 0, 2, 4},
        {0, 1, 0, 2, 0, 0},
        {0, 0, 5, 4, 0, 0}
    };  
    double h[N] = {6,5,4,2,3,0};
	vertex start = {0,0,6,6};
	vertex goal  = {5,0,0,0};
	
	Astar(graph,h,start,goal);
	return 0;
}