#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <vector>

using std::vector;


typedef CGAL::Exact_predicates_inexact_constructions_kernel KI;
typedef CGAL::Exact_predicates_exact_constructions_kernel KE;
typedef CGAL::Delaunay_triangulation_2<KI> Triangulation;
typedef Triangulation::Finite_faces_iterator Face_iterator;
typedef KI::Point_2 P;
typedef KE::Point_2 Pe;


double floor_to_double(const KE::FT& x)
{
double a = std::floor(CGAL::to_double(x));
while (a > x) a -= 1;
while (a+1 <= x) a += 1;
return a;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    P newlocation;
    P vertex;
    int n,m;
    int x,y;
    std::cin>>n;
    Pe tmp1, tmp2;
    while(n){
        Triangulation t;
        vector<P> points(n);
        for(int i=0; i < n; i++){
            std::cin>>x>>y;
            points[i]= P(x,y);
        }
        t.insert(points.begin(), points.end());
        std::cin>>m;
        
        for(int i=0; i < m; i++){
            std::cin>>x>>y;
            newlocation = P(x,y);
            vertex = t.nearest_vertex(newlocation)->point();
            tmp1 = Pe(vertex.x(), vertex.y());
            tmp2 = Pe(newlocation.x(), newlocation.y());
            std::cout<<std::setprecision(0)<<std::fixed<<floor_to_double(CGAL::squared_distance(tmp1, tmp2))<<"\n";
        }
        std::cin>>n;
    }
}

