# include "graph.h"
# include "tsp.h"
# include <stdio.h>
# include <time.h>

# define SIZE 1200
const double INF = 1E50; 
int s[SIZE][cnt_city]; 
double cost[SIZE];

int main() {
	initlization();
	
	srand((unsigned) time(NULL));
	generate_city();

	int i, j = 0;
	
	int generations = 520;

	for(i=0; i<SIZE; i++) {
		generate_random(s[i]);
		calculate(s[i],&cost[i]);
	}
	
	while ( generations -- ) {
		for(i=0; i<SIZE; i++)
			if(cost[i] < cost[j]) j=i;
		draw_path(s[j]);
		for(i=0; i<SIZE; i++)
			if(i!=j) {
				gen_next(s[j],s[i]);
				calculate(s[i],&cost[i]);
				if(cost[j]>=cost[i])
				printf("%lf\n",cost[j]-cost[i]);
			}
	}
	close_graph();
}
