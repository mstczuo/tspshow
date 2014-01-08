# ifndef TSP_HEAD_FILE
# define TSP_HEAD_FILE

# include "graph.h"

# define cnt_city 30

# define bool char
# define true 1
# define false 0

int x[cnt_city], y[cnt_city];

void generate_random(int c[]);

void gen_next(const int p[],int s[]);

void calculate(int s[],double *cost);

void draw_path(const int p[]);
# endif
