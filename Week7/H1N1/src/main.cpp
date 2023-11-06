#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_2.h>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <math.h>

using std::vector;
using std::set;
using std::pair;
using std::make_pair;
using std::map;
using std::sqrt;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Face_handle Face_handle;
typedef K::Point_2 P;
typedef pair < Face_handle, double > face_capacity;


double floor_to_double(const K::FT& x)
{
double a = std::floor(CGAL::to_double(x));
while (a > x) a -= 1;
while (a+1 <= x) a += 1;
return a;
}

struct comparator {
    bool operator() (const face_capacity &p1, const face_capacity &p2) const{
        return p1.second >= p2.second;
    }
};

void solve(int &n);

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n;
    std::cin>>n;
    while(n){
        solve(n);
        std::cin>>n;
    }
}

void solve(int & n){
    P vertex;
    P newlocation;
    int m;
    double x,y, x2,y2;
    Triangulation t;
    Face_handle neightbor;
    vector<P> points(n);
    for(int i=0; i < n; i++){
        std::cin>>x>>y;
        points[i]= P(x,y);
    }
    t.insert(points.begin(), points.end());
    std::cin>>m;
    vector<P> users(m);
    vector<double> distances(m);
    set < face_capacity , comparator> toinsert;
    set < Face_handle> inserted;
    map < Face_handle, double>   faces;
    Face_handle f;  
    for(int i=0; i < m; i++){
        std::cin>>x>>y>>distances[i];
        users[i] = P(x,y);   
    }
    double capacity;
    for (Face_handle fi : t.finite_face_handles()) {
        capacity = 0;
        for(int i=0; i < 3; i++){
            neightbor = fi->neighbor(i);
            if(t.is_infinite(neightbor)){
                x = fi->vertex((i+1)%3)->point().x();
                y = fi->vertex((i+1)%3)->point().y();
                x2= fi->vertex((i+2)%3)->point().x();
                y2= fi->vertex((i+2)%3)->point().y();
                capacity = std::max(capacity, ((x-x2)*(x-x2) + (y-y2)*(y-y2))/4);
            }
        }
        if(capacity){   
            toinsert.insert(make_pair(fi, capacity));
        }
    }
    while(toinsert.size()){
        auto elem = toinsert.begin();
        f = elem->first;
        if(inserted.find(f) == inserted.end()){
            faces.insert(make_pair(elem->first, elem->second));
            inserted.insert(f);
            for(int i=0; i <3; i++){
                neightbor = f->neighbor(i);
                if(!t.is_infinite(neightbor) && inserted.find(neightbor) == inserted.end()){
                    x = f->vertex((i+1)%3)->point().x();
                    y = f->vertex((i+1)%3)->point().y();
                    x2= f->vertex((i+2)%3)->point().x();
                    y2= f->vertex((i+2)%3)->point().y();
                    capacity = std::min(elem->second, ((x-x2)*(x-x2) + (y-y2)*(y-y2))/4);
                    toinsert.insert(make_pair(neightbor, capacity));
                }
            }
        }
        toinsert.erase(elem);
    }
    for(int i=0; i < m; i++){
        newlocation = users[i];
        vertex = t.nearest_vertex(newlocation)->point();
        if(floor_to_double(CGAL::squared_distance(newlocation, vertex)) < (double)distances[i]){
            std::cout<<"n";
        }
        else{
            f = t.locate(newlocation);
            if(f != nullptr){
                auto finder = faces.find(f);
                if(t.is_infinite(f) || (finder != faces.end()  && finder->second >= (double)distances[i])){
                    std::cout<<"y";
                }
                else{
                    std::cout<<"n";
                }
            }
        }
    }
    std::cout<<"\n";      
}
