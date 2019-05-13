#include "para_helper.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <unordered_set>
#include <iterator>
#include <time.h>
#include <omp.h>
using namespace std;

ll n=1000;
Point points[1000];

struct MyHashFunction
{
	size_t operator()(const Point& p) const
	{
		return (hash<ll>()(p.x))^(hash<ll>()(p.y));
	}

};

void brute(unordered_set<Point,MyHashFunction> *hull, Point points[], ll n)
{
	if(n < 3) return;
	for(ll i = 0; i < n; i++)
	{
		for(ll j = 0; j<n; j++)
		{
			if(i == j) continue;
			bool allsameside = true;
			for(ll k = 0; k < n; k++)
			{
				if(k==i||k==j) continue;
				if( orientation(points[i], points[j], points[k] ) == 2) allsameside = false;
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
    unordered_set<Point,MyHashFunction> hull;;

    clock_t startTime,endTime;
    for(ll i=0;i<n;i++){
      points[i].x=rand()%n;
      points[i].y=rand()%n;
    }

    //Runtime for serial Wrapping
	startTime = clock();
    brute(&hull, points, n);
	endTime = clock();
	for(auto e:hull)
    {
    	cout << "(" << e.x<<", "<< e.y<<")" << endl; 
    }
	cout<<"serial size "<< hull.size()<<endl;
	cout << "Totle Serial Time : " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;



    return 0;

} 