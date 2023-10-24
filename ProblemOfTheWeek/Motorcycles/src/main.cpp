#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/intersections.h>
#include <vector>
#include <tuple>
#include <utility>
using std::vector;
using std::pair;
using std::tuple;
typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Ray_2 R;
typedef K::Point_2 P;
void solve();
bool compare (const pair<int, long> & a, const pair <int, long> & b){
    return a.second < b.second;
}
int main(){
    std::ios_base::sync_with_stdio(false);
    int t;
    std::cin>>t;
    while(t--){
        solve();
    }
}
void solve(){
    int n;
    long y0, x1,y1;
    std::cin>>n;
    bool toadd;
    CGAL::Sign res;
    vector < R > riders(n);
    vector <int> sortedindex(n);
    vector < int> foreverindex;
    vector < pair<int,long> > rays(n);

    for(int i=0; i < n; i++){
        std::cin>>y0>>x1>>y1;
        rays[i] = std::make_pair(i, y0);
        riders[i] = R(P((long)0, y0), P(x1, y1));
    }
    std::sort(rays.begin(), rays.end(), compare);
    for(int i=0; i < n; i++){
        sortedindex[i] = rays[i].first;
    }
    foreverindex.push_back(sortedindex[0]);
    for(int i=1; i < n; i++){
        toadd=true;
        while(foreverindex.size() && CGAL::do_intersect(riders[foreverindex.back()], riders[sortedindex[i]])){
            auto o = CGAL::intersection(riders[foreverindex.back()], riders[sortedindex[i]]);
            if (const P* op = boost::get<P>(&*o)){ 
                res = CGAL::compare_distance_to_point(*op, riders[foreverindex.back()].source(), riders[sortedindex[i]].source());
                if(res == CGAL::LARGER){
                    foreverindex.pop_back();
                }
                else{
                   toadd=false;
                   break; 
                }
            }
        }
        if(toadd){
            foreverindex.push_back(sortedindex[i]);
        }
    }
    std::sort(foreverindex.begin(), foreverindex.end());
    for(int i:foreverindex){
        std::cout<<i<<" ";
    }
    std::cout<<"\n";
}