#ifndef CH_HELPER_H
#define CH_HELPER_H

class Point
{
public:
	int x, y;
	friend bool operator!= (Point& p1, Point& p2){
		return (!(p1.x==p2.x && p1.y==p2.y));
	}
	friend bool operator== (Point& p1, Point& p2){
		return (p1.x==p2.x && p1.y==p2.y);
	}
};

int orientation(Point a, Point b, Point c);

int dist(Point p1, Point p2);


#endif 