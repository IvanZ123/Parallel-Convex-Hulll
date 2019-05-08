#include "ch_helper.h"

int orientation(Point a, Point b, Point c)
{
	int v = (b.y-a.y)*(c.x-b.x)-(b.x-a.x)*(c.y-b.y); //use the slope idea
	if(v==0) 
	{
		// if(dist(a,b)>dist(a,c)) return -1;
		// else 
			return 0;
	}
	else return (v>0)? 1:-1;
}


int dist(Point p1, Point p2)
{
	return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}
