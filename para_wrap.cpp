#include <stack>
#include <stdlib.h>
#include <iostream>
#include <omp.h>
#include <sys/time.h>
#include <bits/stdc++.h>
#include <time.h>
#include "para_helper.h"
using namespace std;



//https://github.com/IvanZ123/Parallel_Convex_Hull

Point points[SIZE];
ll n=SIZE;


void wrapping_serial(Point points[], std::vector<Point> *hull, ll n)
{
  ll min=0;
  for(ll i=1;i<n;i++){
    if(( points[i].x<points[min].x)){
      min=i;
    }
  } 
 
  ll p=min;
  ll q;

  do{
      q=(p+1)%n;
      hull->pb(points[p]);
      for(ll i=0;i<n;i++){
        if(orientation(points[p],points[i],points[q])==2){
          q=i;
        }
      }
      p=q;
  }while(p!=min);
}

//Parallel Gift-wrapping Convexhull
void wrapping(Point points[], std::vector<Point> *hull, ll n)
{
  ll min_y=points[0].y,min=0;
  int chunk;
  // printf("enter chunk size\n");
  // cin>>chunk;
  #pragma omp parallel for
  // #pragma omp parallel for schedule(static,chunk)
  for(ll i=1;i<n;i++){
    if((points[i].x<points[min].x)){
      min=i;
    }
  } 
  ll p=min;
  ll q;

  do{
      q=(p+1)%n;
      hull->pb(points[p]);
      #pragma omp parallel for
      // #pragma omp parallel for schedule(static,chunk)
      for(ll i=0;i<n;i++){
        if(orientation(points[p],points[i],points[q])==2){
          q=i;
        }
      }
      p=q;
  }while(p!=min);
}
int main()
{
	clock_t startTime,endTime;
	double start_time, final_time;
    std::vector<Point> hull,hull_serial;

    for(int i=0;i<n;i++){
      points[i].x=rand()%n;
      points[i].y=rand()%n;
    }

    printf("set no of threads\n");
    int num_th;
    cin>>num_th;
    //Number of Threads
    omp_set_num_threads(num_th);
    //Runtime for Parallel Wrapping
    start_time = omp_get_wtime();
    wrapping(points, &hull, n);
    final_time = omp_get_wtime() - start_time;
    printf("Total time: %.6f\n",final_time);

    //Runtime for serial Wrapping
	startTime = clock();
    wrapping_serial(points, &hull_serial, n);
	endTime = clock();
	cout << "Totle Serial Time : " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    return 0;
}