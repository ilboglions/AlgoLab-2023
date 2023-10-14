#include <iostream>
#include <limits>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <algorithm>
#include <vector>

using std::vector;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Segment_2 S;
typedef K::Ray_2 R;
typedef K::Point_2 P;

double floor_to_double(const K::FT& x)
{
double a = std::floor(CGAL::to_double(x));
while (a > x) a -= 1;
while (a+1 <= x) a += 1;
return a;
}


long x,y,a,b;
long r,s,t,u;
S result;
R ray;
P source;
bool res;

void solve(int );

int main(){
    std::ios_base::sync_with_stdio(false);
    int n;
    std::cin>>n;
    while(n){
        solve(n);
        std::cin>>n;
    }
}

void solve(int n){
    std::cin>>x>>y>>a>>b;
    source = P(x,y);
    ray = R(source, P(a,b));
    res = false;
    vector<S> segments(n);
    for(int i=0; i < n; i++){
        std::cin>>r>>s>>t>>u;
        segments[i] = S(P(r,s), P(t,u));
    }
    std::random_shuffle(segments.begin(), segments.end());
    int i;
    for(i=0; i <n; i++){
        if(CGAL::do_intersect(ray, segments[i])){
            auto o = CGAL::intersection(ray,segments[i]);
            if (const P* op = boost::get<P>(&*o)){ //on a point
                   result = S(source,*op); 
                   res = true;
                   break;
            }
            else if (const S* os = boost::get<S>(&*o)){ //segment
                if(CGAL::compare_distance_to_point(source, os->source(), os->target()) == CGAL::SMALLER){
                    result =  S(source, os->source()) ;
                }
                else{
                    result =  S(source, os->target()) ;
                }
                res = true;
                break;
            }
        }
    }
    for(i++; i < n; i++){
        if(CGAL::do_intersect(result, segments[i])){
            auto o = CGAL::intersection(result,segments[i]);
            if (const P* op = boost::get<P>(&*o)){ //on a point
                   result = S(source,*op); 
            }
            else if (const S* os = boost::get<S>(&*o)){ //segment
                if(CGAL::compare_distance_to_point(source, os->source(), os->target()) == CGAL::SMALLER){
                    result =  S(source, os->source()) ;
                }
                else{
                    result =  S(source, os->target()) ;
                }
            }
        }
    }
    //RESULTS OUTPUT
    if(res){
        double res_x, res_y;
        res_x = std::floor(floor_to_double(result.target().x()));
        res_y = std::floor(floor_to_double(result.target().y()));
        std::cout<<std::setprecision(0)<<std::fixed<<res_x<<" "<<res_y<<"\n";
    }
    else{
        std::cout<<"no\n";
    }
}