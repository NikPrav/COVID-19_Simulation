// Has an accompanying python program, using which one can plot the graph
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
 
#define MAX_VERTICES 10000
#define MAX_EDGES 50
// MAX_EDGES is taken as 50 , otherwise, the simulation ends too soon
// Modified vertex datatype, for faster access
 struct vertex{
    char type;
    int index;
    struct vertex** ver;
};

typedef struct vertex vertex;

struct heap
{
	int pr;
	vertex* node;
	char type;
};

struct list{
	vertex* ver;
	struct list* next;
};


typedef struct heap heap;

typedef struct list list;

int size = 4;
int numberOfVertices;
int maxNumberOfEdges;

vertex* create(){
 
    /*number of nodes in a graph*/
    srand ( time(NULL) );
    
 	// numberOfVertices = MAX_VERTICES;
    /*number of maximum edges a vertex can have*/
    srand ( time(NULL) );
    
    // maxNumberOfEdges = 9;
    /*graphs is 2 dimensional array of pointers*/
    if( numberOfVertices == 0)
        numberOfVertices++;
    vertex *graph;
    printf("Total No. of people to be simulated = %d, Max # of Edges = %d\n",numberOfVertices, maxNumberOfEdges);
 
    /*generate a dynamic array of random size*/
    if ((graph = (vertex *) malloc(sizeof(vertex) * numberOfVertices)) == NULL){
        printf("Could not allocate memory for graph\n");
        exit(1);
    }
 
    /*generate space for edges*/
    int vertexCounter = 0;
    /*generate space for vertices*/
    int edgeCounter = 0;
 
    for (vertexCounter = 0; vertexCounter < numberOfVertices; vertexCounter++){
        if ((graph[vertexCounter].ver = (vertex **) malloc(sizeof(vertex *) * maxNumberOfEdges)) == NULL){
            printf("Could not allocate memory for edges\n");
            exit(1);
        }
        graph[vertexCounter].type = 'S';
        graph[vertexCounter].index = vertexCounter;
        // printf("%d\n",graph[vertexCounter].index );
        for (edgeCounter = 0; edgeCounter < maxNumberOfEdges; edgeCounter++){
            if ((graph[vertexCounter].ver[edgeCounter] = (vertex *) malloc(sizeof(vertex))) == NULL){
                printf("Could not allocate memory for vertex\n");
                exit(1);
            }

        }
    }
 	vertex temp;
 	temp.index = -1;
    /*start linking the graph. All vetrices need not have same number of links*/
    vertexCounter = 0;edgeCounter = 0;
    for (vertexCounter = 0; vertexCounter < numberOfVertices; vertexCounter++){
        
            int x = rand() % maxNumberOfEdges;
            // printf("x = %d\n",x );
            int i =0;
            for (i = 0;i < x;++i){ /*link the vertices*/
                int linkedVertex = rand() % numberOfVertices;
                graph[vertexCounter].ver[i] = &graph[linkedVertex];
            }
            for(;i < maxNumberOfEdges; ++i){ /*make the link NULL*/
                graph[vertexCounter].ver[i] = NULL;
            }
    }
    return graph;
}



heap* allocate(heap* node, int size){
	heap* new = (heap*)malloc(size*sizeof(heap));
	for (int i = 1; i <= size/2; ++i)
	{
		new[i] = node[i];
	}
	free(node);
	return new;
}

heap* insert(heap* node,int* end,int val,vertex* nd,char type){
	++(*end);
	if((*end) >= size){			// Allocates memory, in case more is required
		node = allocate(node, size*2);
		size  = size*2;
	}
	node[*end].pr = val;
	int i = (*end);
	while(i > 1 && (node[i].pr < node[i/2].pr) ){
		node[i] = node[i/2];
		i = i/2;
	}
	node[i].pr = val;
	node[i].node = nd;
	node[i].type = type;
	return node;
}


// Deletes an event from the priority queue
heap* delete(heap* node,int* end){
	heap val = node[*end];
	node[1] = val;
	--(*end);
	int i = 1;
	if((*end) < ((size/2))){		//Saves memory, in case more than half memory is free
		node = allocate(node,size);
		size = size/2;
	}
	// Seeks out the place to insert the queue
	while(i <= ((*end)/2) && (val.pr > node[2*i].pr || val.pr > node[2*i+1].pr) ){
		if(node[2*i].pr < node[2*i+1].pr){
			node[i] = node[2*i];
			i = 2*i;
		}
		else{
			node[i] = node[2*i + 1];
			i = 2*i + 1;
		}
	}
	node[i] = val;
	return node;
}

// This displays the priority queue
void DisplayHeap(heap* node,int end){
	for (int i = 1; i <= end; ++i)
	{
		int j = 0;
		printf("%d:",node[i].pr );
		printf("! ");
		while(node[i].node -> ver[j] != NULL && j < maxNumberOfEdges){
			printf("%d%c ",node[i].node -> ver[j] -> index,node[i].type);
			++j;
		}
		printf("     ");
	}
	printf("\n");
}



int findDays(double x){
	int i = 0;
	// srand ( time(0) );
	int prob = rand() % 100;
	while(prob > x*100){
		prob = rand() % 100;
		++i;
	}
	return i;
}

// Main Function
int main(int argc, char const *argv[])
{
	heap* event = (heap*)malloc(4*sizeof(heap));
	srand ( time(NULL) );
	numberOfVertices = rand() % MAX_VERTICES;
	maxNumberOfEdges = rand() % MAX_EDGES;
	int peakInfections = 0;
	int currentInfections = 0;
	int totalInfected = 0;
	int infectionTime_total = 0;
	int infectionTime_max = 0;
	int recoveryTime_total = 0;
	int recoveryTime_max = 0;
	int inf = 0;
	int rec_time = 0;
	int inf_time = 0;
	int flag = 0;	
	size = 4;
	int end = 0;
	int day = 0;
	double tau = 0.5;
	double rho = 0.2;
	int initialInfected = 1;
	int recovered = 0;
	FILE* fp = fopen("data.txt", "w"); 
	// Redundant bit of code, but done since the question called for it
	// list* Susp = NULL;
	// list* Inf = NULL;
	// list* Rec = NULL;
	
	// int yo[] = {1,2,5,7,3,9,4};
	int val;
	int x = 0;
	int samplerate = 10;
	char ch;
	printf("############Simulation Menu############\n");
	printf("To use custom parameters, press Y. Otherwise,press any key\n");
	scanf("%c",&ch);
	if(ch == 'Y'){
		printf("Enter number of people to be simulated\n");
		scanf("%d",&numberOfVertices);
		printf("Enter number of interactions between people\n");
		scanf("%d",&maxNumberOfEdges);
		while(maxNumberOfEdges>numberOfVertices && maxNumberOfEdges < 0){
			printf("Sorry, invalid entry. Try entering again\n");
			scanf("%d",&maxNumberOfEdges);
		}
		printf("Enter Initial Infected count\n");
		scanf("%d",&initialInfected);
		while(initialInfected>numberOfVertices && initialInfected < 0){
			printf("Sorry, invalid entry. Try entering again\n");
			scanf("%d",&initialInfected);
		}
		printf("Enter rho value\n");
		scanf("%lf",&rho);
		while(rho>1 && rho < 0){
			printf("Sorry, invalid entry. Try entering a value between 0 and 1\n");
			scanf("%lf",&rho);
		}
		printf("Enter tau value\n");
		scanf("%lf",&tau);
		while(tau>1 && tau < 0){
			printf("Sorry, invalid entry. Try entering a value between 0 and 1\n");
			scanf("%lf",&tau);
		}


	}
	printf("Enter number of days between which the data is printed\n");
	scanf("%d",&samplerate);
	while(samplerate < 0){
		printf("Sorry, invalid entry. Try entering again\n");
		scanf("%d",&samplerate);
	}

	vertex* graph = create();
	// Initial Infection
	for (int i = 0; i < initialInfected; ++i)	
	{
		val = rand() % 10;						// Assumes that the initial infections happen within the first 10 days		
		event = insert(event,&end,val,&graph[rand() % numberOfVertices],'I');
	}
	// Redundant
	// for (int i = 0; i < numberOfVertices; ++i)
	// {
	// 	Susp = insertLL(Susp,&graph[i]);
	// }
	while(size > 1){							// Executes till the priority queue is empty
		heap current = event[1];
		event = delete(event,&end);
		day = current.pr;
		if(day / samplerate >= x){							// Fills in the gaps, in case no events occur for more than the minimum gap
			printf("\nDay %d\n",x*samplerate);
			printf("No. of infected = %d\n",currentInfections );
			printf("Recovered = %d\n",recovered );
			++x;
			// Saving data for plotting
			fprintf(fp, "%d %d %d %d\n",x*samplerate,numberOfVertices - (currentInfections + recovered),currentInfections,recovered );
			while(day / samplerate >= x){
				printf("\nDay %d\n",x*samplerate);
				printf("No. of infected = %d\n",currentInfections );
				printf("Recovered = %d\n",recovered );
				++x;
				fprintf(fp, "%d %d %d %d\n",x*samplerate,numberOfVertices - (currentInfections + recovered),currentInfections,recovered );
			}
		}
		// fprintf(fp, "%d %d %d %d\n",x*samplerate,numberOfVertices - (currentInfections + recovered),currentInfections,recovered );
		if(day >= 300 && flag == 0){							// Stopping the simulation at 300 days, as per the question
			char choice;
			printf("The simulation has run to 300 days. Do you want to continue the simulation? Y/N\n");
			scanf("%c",&choice);
			flag = 1;
			if(choice == 'N'){
				break;
			}
		}
		if(current.type == 'I'){				// Checking for the type of event involved
			int i = 0;
			if(current.node -> type == 'S'){	// If the node is Susceptible, then try to make the node and its adjacent ones infected
				while(current.node -> ver[i]  != NULL && i < maxNumberOfEdges){
					// It might be needed to take into consideration the max days within which a node has to be infected
					if(current.node -> ver[i] -> type == 'S'){	// SImilarily, checking whether the adjacent node is susceptible or not 
						if(rand() % 100 > tau*100){
							inf_time = findDays(tau);
							infectionTime_total += inf_time;
							++inf;
							if(inf_time > infectionTime_max){		// Stores the maximum infection time
								infectionTime_max = inf_time;
							}
							val = current.pr + inf_time;			// Stores on which day the node should be infected
							event = insert(event,&end,val,current.node -> ver[i],'I');
						}
					}
					++i;	
				}
				current.node -> type = 'I';						
				++currentInfections;
				// Redundant
				// Susp = deleteLL(Susp,current.node);
				// Inf = insertLL(Inf,current.node);
				if(currentInfections > peakInfections){
					peakInfections = currentInfections;
				}
				++totalInfected;
				//  Calculating the recovery day
				rec_time = findDays(rho);
				// printf("rec time = %s\n", );
				recoveryTime_total += rec_time;					
				if(rec_time > recoveryTime_max){				// Saves the maximum recovery time
					recoveryTime_max = rec_time;
				}
				int val = current.pr + rec_time;
				event = insert(event,&end,val,current.node,'R'); // Creates the recovery event
			}
		}
		else{
			current.node -> type = 'R';							// If its a recovery event
			--currentInfections;
			++recovered;
			// Redundant
			// Inf = deleteLL(Inf,current.node);
			// Rec = insertLL(Rec,current.node);
		}
		
	}
	printf("Total no. of days simulated  is %d\n",day);
	printf("Total people simulated = %d\n",numberOfVertices );
	printf("Maximum no. of interactions per person = %d\n",maxNumberOfEdges );
	printf("Total infected = %d\n",totalInfected );
	printf("Total recovered = %d\n",recovered );
	printf("Peak infection is %d\n",peakInfections );
	printf("Average infection time = %f\n",(float)infectionTime_total / inf );
	printf("Peak Infection time = %d\n",infectionTime_max );
	printf("Average recovery time = %lf\n",(double)recoveryTime_total / recovered );
	printf("Peak Recovery time = %d\n",recoveryTime_max );
	fprintf(fp, "stop");
	fclose(fp);
	return 0;
}
