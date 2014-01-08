# include "graph.h"
# define bool char
# define true 1
# define false 0

int initlization() {

	file = open("/dev/fb0", O_RDWR);
	if ( file < 0 ) {
		printf("Open /dev/fb0 error!\n");
		return 1;
	}
	
	if (ioctl(file, FBIOGET_FSCREENINFO, &finfo)) {
		printf("read fixed info error!\n");
		return 2;
	}
	
	if (ioctl(file, FBIOGET_VSCREENINFO, &vinfo)) {
		printf("read variable info error!\n");
		return 2;
	}
	
	screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel >> 3;
	
	pointer = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, file, 0);
}

void put_pixel(int i,int j,int R,int G,int B,int A)
{
# define SPECIAL_MODE
# ifdef SPECIAL_MODE
	i += 180;
# endif
	if ( i < 0 || j < 0 || i > 900 || j > 700 ) {
		printf("ERROR");
		return;
	}
	location = i * (vinfo.bits_per_pixel >> 3) + j * finfo.line_length;
	*(pointer + location) = R;
	*(pointer + location+1) = G;
	*(pointer + location+2) = B;
	*(pointer + location+3) = A;
}

void close_graph()
{
	munmap(pointer, screensize);
	close(file);
}

void put_circle(int x,int y,int r) {
	int i, j;
	for(i=x-r; i<=x+r; i++)
		for(j=y-r; j<=y+r; j++)
			if((i-x)*(i-x) + (j-y)*(j-y) <= r*r)
				put_pixel(i,j,0xff,0xff,0xff,0);
}

int temp_variable;
# define swap(a,b) temp_variable = a, a = b , b = temp_variable

void put_line(int x0,int y0,int x1,int y1) {
	bool steep = (abs(y1-y0) > abs(x1-x0));
	if (steep) swap(x0,y0), swap(x1,y1);
	if (x0>x1) swap(x0,x1), swap(y0,y1);
	int delx = x1 - x0;
	int dely = abs(y1 - y0);
	float error = 0;
	float derror = 1.0 * dely / delx;
	int ystep = ((y0<y1)?1:-1);
	int x, y = y0;
	for(x = x0; x <= x1; x++) {
		if (steep) put_pixel(y,x,0x3f,0x3f,0x3f,0);
		else put_pixel(x,y,0x3f,0x3f,0x3f,0);
		error += derror;
		if (error >= 0.5f) {
			y += ystep;
			error -= 1.0;
		}
	}
}
