#ifndef GRAPH_H
#define GRAPH_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <linux/fb.h>
# include <sys/mman.h>

int file;

struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;

int screensize, location;

char * pointer;

int initlization();

void put_pixel(int i,int j,int R,int G,int B,int A);

void put_circle(int x,int y,int r);

void put_line(int x0,int y0,int x1,int y1);

void close_graph();
#endif
