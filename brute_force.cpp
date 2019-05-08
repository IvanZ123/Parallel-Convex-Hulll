#include "ch_helper.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <ctime>
#include <unordered_set>
#include <iterator>
using namespace std;

struct MyHashFunction
{
	size_t operator()(const Point& p) const
	{
		return (hash<int>()(p.x))^(hash<int>()(p.y));
	}

};

void brute(unordered_set<Point,MyHashFunction> *hull, Point points[], int n)
{
	if(n < 3) return;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j<n; j++)
		{
			if(i == j) continue;
			bool allsameside = true;
			for(int k = 0; k < n; k++)
			{
				if(k==i||k==j) continue;
				if( orientation(points[i], points[j], points[k] ) == -1) allsameside = false;
			}
			if(allsameside)
			{
				if(hull->find(points[i]) == hull->end()) hull->insert(points[i]);
				if(hull->find(points[j]) ==  hull->end()) hull->insert(points[j]);
			}
		}
	}
}

int main() 
{ 
    Point points[] = {{0, 3}, {2, 2}, {1, 1}, {2, 1}, {3, 0}, {0, 0}, {3, 3}};
    // Point points[] = {{0, 0}, {0, 1}, {0,2}, {0, 3}, {0,5}, {0,4}, {1, 0}, {2, 0}, {3, 0}, {5, 0}, {4, 0}}; 
    unordered_set<Point,MyHashFunction> hull;

    int n = sizeof(points)/sizeof(points[0]); 
    cout<<"n="<<n<<endl;
    brute(&hull,points, n); 

    for(auto e:hull)
    {
    	cout << "(" << e.x<<", "<< e.y<<")" << endl; 
    }
 
    return 0; 
} 