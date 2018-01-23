#ifndef POINT_H
#define POINT_H
#include <vector>
using namespace std;

struct Point{
    Point(int x, int y): x(x),y(y) {}
    int x; 
    int y;
};

inline int is_in(vector<Point> v, Point p){
    for(int i=0;i<v.size();++i){
        if(v[i].x==p.x&&v[i].y==p.y)
            return i;
    }
    return -1;
}

inline bool operator==(const Point& lhs, const Point& rhs)
{
        return (lhs.x==rhs.x&&lhs.y==rhs.y);
}

inline bool operator<(const Point& i, const Point& j){
    if(i.x<j.x) return true;
    if(i.x>j.x) return false;
    return i.y<j.y;
}

#endif
