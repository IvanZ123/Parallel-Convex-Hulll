#include<iostream>
#include<stdio.h>
#include<vector> 
#include<math.h>
#include <initializer_list>
#include "ch_helper.h"
#include <bits/stdc++.h> 
#include <unordered_set>
using namespace std;


int compare(Point p0, Point p1, Point p2)
{
	int orient = orientation(p0, p1, p2);
	if (orient == 0 && p1 != p0 && p2 != p1 && p2 != p0)
		return (dist(p0, p2) >= dist(p0, p1))? -1 : 0;
	return (orient == 1)? -1: 1;
}


struct MyHashFunction
{
	size_t operator()(const Point& p) const
	{
		return (hash<int>()(p.x))^(hash<int>()(p.y));
	}

};

// wrapping algorithm for convex hull
// hull is vector for the convex hull result, n is number of points
void wrappingCH(unordered_set<Point,MyHashFunction> *hull, Point points[], int n)
{
	if(n<3) return;
	int l = 0;

	for(int i = 1; i < n; i++)
	{
		if (points[i].x<points[l].x) l = i;
	}


	int p = l,q;
	do
	{
		hull->insert(points[p]);
		//find most counterclock wise point q
		q = (p+1)%n;
		for(int i = 0; i<n;i++)
		{
			if(compare(points[p],points[i],points[q])==-1 )
			{
				if(hull->find(points[i]) == hull->end()) q = i;
				else continue;
			}
		}
		p = q;
	}while(p!=l);
}

  
// Driver program to test above functions 
int main() 
{ 
    // Point points[] = {{0, 3}, {2, 2}, {1, 1}, {2, 1}, {3, 0}, {0, 0}, {3, 3}};
    Point points[] = {{0, 0}, {0, 1}, {0,2}, {0, 3}, {0,5}, {0,4}, {1, 0}, {2, 0}, {3, 0}, {5, 0}, {4, 0}}; 

    unordered_set<Point,MyHashFunction> hull;
    int n = sizeof(points)/sizeof(points[0]); 
    cout<<"n="<<n<<endl;
    wrappingCH(&hull,points, n); 

      for(auto e:hull)
    {
    	cout << "(" << e.x<<", "<< e.y<<")" << endl; 
    }

} 