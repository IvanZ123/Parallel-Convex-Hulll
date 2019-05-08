#include<iostream>
#include<stdio.h>
#include<vector> 
#include<math.h>
#include <initializer_list>
#include "ch_helper.h"
#include <bits/stdc++.h> 
using namespace std;

// //https://www.geeksforgeeks.org/convex-hull-set-1-jarviss-algorithm-or-wrapping/
// class Point
// {
// public:
// 	int x, y;
// 	friend bool operator!= (Point& p1, Point& p2){
// 		return (!(p1.x==p2.x && p1.y==p2.y));
// 	}
// };

// //to find the orientation of points a,b and c. 
// //collinear(0), clockwise(1), counterclockwise(-1)
// int orientation(Point a, Point b, Point c)
// {
// 	int v = (b.y-a.y)*(c.x-b.x)-(b.x-a.x)*(c.y-b.y); //use the slope idea
// 	if(v==0) return 0;
// 	else return (v>0)? 1:-1;
// }


// int dist(Point p1, Point p2)
// {
// 	return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
// }

int compare(Point p0, Point p1, Point p2)
{
	int orient = orientation(p0, p1, p2);
	if (orient == 0 && p1 != p0 && p2 != p1)
		return (dist(p0, p2) >= dist(p0, p1))? -1 : 1;
	return (orient == 1)? -1: 1;
}



// wrapping algorithm for convex hull
// hull is vector for the convex hull result, n is number of points
void wrappingCH(vector<Point> *hull, Point points[], int n)
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
		hull->push_back(points[p]);
		// cout<<"push_back "<<points[p].x<<" "<<points[p].y<<endl;
		// hull->insert(points[p]);
		//find most counterclock wise point q
		q = (p+1)%n;
		// cout<<"q= "<<q<<endl;
		for(int i = 0; i<n;i++)
		{
			// if(i == p or i == q) continue;
			if(compare(points[p],points[i],points[q])==-1 )
			{
				// cout<<"i= "<<i<<" x = "<<points[i].x<<" y = "<<points[i].y<<endl;
				// cout<<"q= "<<q<<" x = "<<points[q].x<<" y = "<<points[q].y<<endl;
				// if(hull->find(points[i])) continue;
				q = i;

			}
		}
		p = q;
		cout<<"p= "<<p<<endl;
	}while(p!=l);
}

  
// Driver program to test above functions 
int main() 
{ 
    // Point points[] = {{0, 3}, {2, 2}, {1, 1}, {2, 1}, {3, 0}, {0, 0}, {3, 3}};
    Point points[] = {{0, 0}, {0, 1}, {0,2}, {0, 3}, {0,5}, {0,4}, {1, 0}, {2, 0}, {3, 0}, {5, 0}, {4, 0}}; 
    std::vector<Point> hull;
    // unordered_set<Point> stringSet;
    int n = sizeof(points)/sizeof(points[0]); 
    cout<<"n="<<n<<endl;
    wrappingCH(&hull,points, n); 
    // cout<<"out"<<endl;
    for(int i = 0; i < hull.size(); i++)
    {
    	 cout << "(" << hull[i].x << ", "
              << hull[i].y << ")\n"; 
    }
    // unordered_set<string> :: iterator itr; 
    // for (itr = stringSet.begin(); itr != stringSet.end(); itr++) 
    //     cout << (*itr) << endl; 
    return 0; 
} 