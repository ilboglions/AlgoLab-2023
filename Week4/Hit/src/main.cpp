#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Segment_2 S;
typedef K::Ray_2 R;
typedef K::Point_2 P;

long x,y,a,b;
long r,s,t,u;
S segment;
R ray;

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
    ray = R(P(x,y), P(a,b));
    int i;
    for(i=0; i < n; i++){
        std::cin>>r>>s>>t>>u;
        segment = S(P(r,s), P(t,u));
        if(CGAL::do_intersect(ray, segment)){
            i++;
            while(i<n){
              std::cin>>r>>s>>t>>u;
              i++;
            }
            std::cout<<"yes\n";
            return;
        }
    }
    std::cout<<"no\n";
}