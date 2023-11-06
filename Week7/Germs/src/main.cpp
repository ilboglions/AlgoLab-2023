#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/nearest_neighbor_delaunay_2.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <vector>
#include <math.h>

using std::vector;
using std::min;
using std::sqrt;


typedef CGAL::Exact_predicates_inexact_constructions_kernel KI;
typedef CGAL::Delaunay_triangulation_2<KI> Triangulation;
typedef KI::Point_2 P;
typedef Triangulation::Vertex_handle Vertex_handle;

double floor_to_double(const KI::FT& x)
{
double a = std::floor(CGAL::to_double(x));
while (a > x) a -= 1;
while (a+1 <= x) a += 1;
return a;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n;
    std::cin>>n;
    double l,b,r,t;
    double x,y;
    double x2,y2;
    double closest;
    Vertex_handle other;
    while(n){
        vector<double> distances(n);
        vector < P > points(n);
        std::cin>>l>>b>>r>>t;
        for(int i=0; i < n; i++){
            std::cin>>x>>y;
            points[i] = P(x,y);
        }
        Triangulation T;
        T.insert(points.begin(), points.end());
        int i=0;
        double minimum;
        for(Vertex_handle vh : T.finite_vertex_handles()){
            other = CGAL::nearest_neighbor(T,vh);
            x= floor_to_double(vh->point().x());
            y= floor_to_double(vh->point().y());
            closest = x-l;
            closest = min(closest, r-x);
            closest = min(closest, t-y);
            closest = min(closest, y-b);
            minimum = closest;
            if(other != nullptr){
                x2 = other->point().x();
                y2 = other->point().y();
                minimum = min(minimum, std::sqrt((x-x2)*(x-x2) + (y-y2)*(y-y2))/2 );
            }
            distances[i] = minimum;
            i++;
        }
        std::sort(distances.begin(), distances.end());
        double first, fifty, all;
        first = distances[0];
        fifty = distances[n/2];
        all = distances[n-1];
        std::cout<<std::setprecision(0)<<std::fixed<<std::ceil(sqrt(first-0.5))<<" "<<std::ceil(sqrt(fifty-0.5))<<" "<<std::ceil(sqrt(all-0.5))<<"\n";
        std::cin>>n;
    }
}