# include "tsp.h"

void generate_city() {
    int i;
    for(i=0; i<cnt_city; i++) {
        x[i] = rand() % 600 + 12;
        y[i] = rand() % 600 + 12;
    }
}

void generate_random(int c[]) {
    bool a[cnt_city] = {0};
    int i, j , t, k = cnt_city;
    
    for(i=0; i<cnt_city; i++) {
        t = rand() % k--; 
        for(j=0; j<cnt_city && a[j];j++);
        for(; t && j<cnt_city; j++)
            if(a[j] == 0) t--;
        while(a[j]) j++;
        a[j] = true;
        c[i] = j;
    }
}

void change(int s[]) {
	int t[cnt_city] = {-1};
	int i , j, tp;
	for(i=0; i<cnt_city-1; i++)
		t[s[i]] = s[i+1];
	t[s[cnt_city-1]] = s[0];
	for(i=0; i<cnt_city; i++)
		if(t[i] == -1 || t[i] >= cnt_city) { 
			printf("ERROR\n"); 
			for(j = 0; j<cnt_city; j++)
				printf("%d ",t[j]);
			printf("\n");while(1); 
		}
	i = rand() % cnt_city;
	j = rand() % cnt_city;
	if(t[t[i]] != j && t[t[j]] != i && t[i] != j && t[j] != i)
		tp = t[i], t[i] = t[j], t[j] = tp;
	j = 0;
	for(i=0; i<cnt_city; i++)
		s[i] = j, j = t[j];
	int sum = 0;
	for(i=0; i<cnt_city; i++) sum += t[i];
	if ( sum != cnt_city * (cnt_city + 1) / 2 ) {
		printf("ERROR\n"); 
		for(j = 0; j<cnt_city; j++)
			printf("%d ",t[j]);
		printf("\n");while(1); 
	}
}

void gen_next(const int p[],int s[]) {

    int i, j;
    for(i=0; i<cnt_city; i++)
        s[i] = p[i];

    int rate = cnt_city / 10;
    while ( rate -- ) {
//	change(s);
//	I'ww change it again
        if(rand()%100<98) {
            i = rand() % cnt_city;
            j = rand() % cnt_city;
            int t = s[i]; s[i] = s[j]; s[j] = t;
        }
    }
}

double sqr(double dx) { return dx * dx; }

double sqrt(double t) {
    double x = 1.0;
    while(fabs(t-x*x)>=1e-6)
        x = (x + t/x) / 2.0;
    return x;
}


void calculate(int p[],double *cost) {
    int i; double t;
    *cost = 0;
    for(i=0; i<cnt_city-1; i++) {
        t = sqr(x[p[i]]-x[p[i+1]])+
            sqr(y[p[i]]-y[p[i+1]]);
        *cost += sqrt(t);
    }
    t = sqr(x[p[cnt_city-1]]-x[p[0]])+
        sqr(y[p[cnt_city-1]]-y[p[0]]);
    *cost += sqrt(t);
}

void draw_path(const int p[]) {
    system("clear");

    int i;
    for(i=0; i<cnt_city; i++) put_circle(x[i], y[i], 3);
    for(i=0; i<cnt_city-1; i++)
        put_line(x[p[i]], y[p[i]], x[p[i+1]], y[p[i+1]]);
    put_line(x[p[0]],y[p[0]],x[p[cnt_city-1]],y[p[cnt_city-1]]);
}

