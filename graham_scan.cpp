#include <algorithm>
#include <iostream>
#include <vector>
#include <math.h>
#include <ctime>

using namespace std;

//https://github.com/ZLsuyan/ConvexHull/blob/master/ConvexHull/Convex_hull/CH_Graham_Scan/CH_Graham_Scan/main.cpp

struct POINT {
    int x;
    int y;
};
typedef vector<POINT> PTARRAY;

bool operator==(const POINT &pt1, const POINT &pt2) {
    return (pt1.x == pt2.x && pt1.y == pt2.y);
}

bool CompareVector(const POINT &pt1, const POINT &pt2) {
    float m1 = sqrt((float)(pt1.x * pt1.x + pt1.y * pt1.y));
    float m2 = sqrt((float)(pt2.x * pt2.x + pt2.y * pt2.y));
    float v1 = pt1.x / m1, v2 = pt2.x / m2;
    return (v1 > v2 || (v1 == v2 && m1 < m2));
}

void CalcConvexHull(PTARRAY &vecSrc) {
    if (vecSrc.size() < 3) {
        return;
    }
    POINT ptBase = vecSrc.front(); 
    for (PTARRAY::iterator i = vecSrc.begin() + 1; i != vecSrc.end(); ++i) {
        //find min y (with smaller x value)
        if (i->y < ptBase.y || (i->y == ptBase.y && i->x < ptBase.x)) {
            ptBase = *i;
        }
    }
    for (PTARRAY::iterator i = vecSrc.begin(); i != vecSrc.end();) {
        //erase points identical with base point
        if (*i == ptBase) {
            i = vecSrc.erase(i);
        }
        else {
            i->x -= ptBase.x, i->y -= ptBase.y;
            ++i;
        }
    }
    //sort by vector
    sort(vecSrc.begin(), vecSrc.end(), &CompareVector);
    //erase identical vector
    vecSrc.erase(unique(vecSrc.begin(), vecSrc.end()), vecSrc.end());
    // reverse calculated
    for (PTARRAY::reverse_iterator ri = vecSrc.rbegin();
        ri != vecSrc.rend() - 1; ++ri) {
        PTARRAY::reverse_iterator riNext = ri + 1;
        ri->x -= riNext->x, ri->y -= riNext->y;
    }
    // Delete vector not on convex hull
    for (PTARRAY::iterator i = vecSrc.begin() + 1; i != vecSrc.end(); ++i) {
        //delete counter clockwise vector
        for (PTARRAY::iterator iLast = i - 1; iLast != vecSrc.begin();) {
            int v1 = i->x * iLast->y, v2 = i->y * iLast->x;
            if (v1 < v2 || (v1 == v2 && i->x * iLast->x > 0 &&
                i->y * iLast->y > 0)) {
                    break;
            }
            //delete one vector, update last vector
            i->x += iLast->x, i->y += iLast->y;
            iLast = (i = vecSrc.erase(iLast)) - 1;
        }
    }
    //use base point find location of vector points
    vecSrc.front().x += ptBase.x, vecSrc.front().y += ptBase.y;
    for (PTARRAY::iterator i = vecSrc.begin() + 1; i != vecSrc.end(); ++i) {
        i->x += (i - 1)->x, i->y += (i - 1)->y;
    }
    //add base point
    vecSrc.push_back(ptBase);
}

int main() {
    srand((unsigned)time(0));
    time_t   c_start,c_end;
    int nPtCnt = 50; //number of random points
    PTARRAY vecSrc, vecCH;

    for (int i = 0; i < nPtCnt; ++i) {
        POINT ptIn = { rand() % 101, rand() % 101 };
        vecSrc.push_back(ptIn);
        // cout << "("<<ptIn.x << ", " << ptIn.y <<")"<< endl;
    }

    c_start=clock();
    CalcConvexHull(vecSrc);
    c_end=clock();

    cout << "\nConvex Hull:\n";
    for (PTARRAY::iterator i = vecSrc.begin(); i != vecSrc.end(); ++i) {
        cout << "("<<i->x << ", " << i->y <<")"<< endl;
    }
    cout<<endl;
    cout<<"The running time is "<<difftime(c_end,c_start)/1000<<"s."<<endl;
    // system("read -p 'Press Enter to continue...' var");
    return 0;
}