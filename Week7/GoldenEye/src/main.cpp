#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/nearest_neighbor_delaunay_2.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <algorithm>
#include <vector>
#include <utility>
using std::pair;
using std::make_pair;
using std::vector;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef std::size_t Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Triangulation;
typedef K::Point_2 P;
typedef Triangulation::Vertex_handle Vertex_handle;
typedef Triangulation::Edge Edge;
typedef pair < long, pair < Vertex_handle, Vertex_handle > > connection;
typedef std::pair<P,Index> IPoint;
typedef boost::disjoint_sets_with_storage<> Union_find;
bool connections_compare(const connection & a, const connection & b){
    return a.first < b.first;
}
void components_builder(const vector<connection> & edges, Union_find & uf, const long & max){
    Index c1,c2;
    for( connection c: edges){
        if(c.first > max){
            break;
        }
        c1 = uf.find_set(c.second.first->info());
        c2 = uf.find_set(c.second.second->info());
        if(c1 != c2){
            uf.link(c1, c2); 
        }
    }
}
long squared_distance(const P & p1, const P & p2){
    return ((p1.x()-p2.x())*(p1.x()-p2.x())) + ((p1.y()-p2.y())*(p1.y()-p2.y()));
}
long findsolution (int & n, vector<connection>& edges, vector< pair<Vertex_handle,Vertex_handle> >& missions,const int & missionsresult, vector<long> & missionsdistances, const long maxdistance){
    
    Index c1,c2;
    int m = missions.size();
    int mid;
    long power_required, minPower;
    int missions_temp;
    minPower = 0;
    int start = 0;
    int end = edges.size()-1;
    missions_temp=0;
    Union_find uf_temp(n);
    components_builder(edges, uf_temp, maxdistance);
    for(int i=0; i < m; i++){
        c1 = uf_temp.find_set(missions[i].first->info());
        c2 = uf_temp.find_set(missions[i].second->info());
        if(c1 == c2 && missionsdistances[i] <= maxdistance){
            missions_temp++;
        }
    }
    if(missionsresult <= missions_temp){
        return maxdistance;
    }
    for(int i=0; i <= end; i++){
        if(edges[i].first >= maxdistance){
            start = i;
            break;
        }
    }
    while(start <= end){
        missions_temp=0;
        mid = (start+end)/2;
        uf_temp = Union_find(n);
        power_required = edges[mid].first;
        components_builder(edges, uf_temp, power_required);
        for(int i=0; i < m; i++){
            c1 = uf_temp.find_set(missions[i].first->info());
            c2 = uf_temp.find_set(missions[i].second->info());
            if(c1 == c2 && missionsdistances[i] <= power_required){
                missions_temp++;
            }
        }
        if(missionsresult <= missions_temp){
            minPower = power_required;
            end = mid-1;
        }
        else
            start = mid+1;
    }
    return minPower; 
}
void solve(){
    int m,n;
    long p;
    std::cin>>n>>m>>p;

    vector<IPoint> points(n);
    vector< pair<Vertex_handle,Vertex_handle> > missions(m);
    vector <long> missionsdistances(m);
    long maxdistance=0;
    int missionsresult=0;
    long power_required;
    long x,y;
    long x2,y2;
    P p1,p2;
    Index c1,c2;
    Vertex_handle v1, v2;
    Triangulation t;
    vector < connection > edges_lengths;
    Union_find uf(n);

    for(Index i=0; i < (Index)n; i++){
        std::cin>>x>>y;
        points[i]= make_pair(P(x,y), i);
    }
    t.insert(points.begin(), points.end());
    for(int i=0; i < m; i++){
        std::cin>>x>>y>>x2>>y2;
        p1 = P(x,y);
        p2 = P(x2,y2);
        v1 = t.nearest_vertex(p1);
        v2 = t.nearest_vertex(p2);
        missions[i] = std::make_pair(v1, v2);
        missionsdistances[i] = std::max( squared_distance(p1, v1->point())*4, squared_distance(p2, v2->point())*4 );
        maxdistance = std::max(maxdistance, missionsdistances[i]);
    }
    for(Edge e : t.finite_edges()){
        v1 = e.first->vertex((e.second + 1) % 3);
        v2 = e.first->vertex((e.second + 2) % 3);
        power_required = squared_distance(v1->point(), v2->point());
        edges_lengths.push_back( make_pair(power_required, make_pair(v1, v2)));
    }
    std::sort(edges_lengths.begin(), edges_lengths.end(), connections_compare);
    components_builder(edges_lengths, uf, p);
    long max_set_distance = 0;
    for(int i=0; i < m; i++){
        c1 = uf.find_set(missions[i].first->info());
        c2 = uf.find_set(missions[i].second->info());
        if(missionsdistances[i] <= p && c1 == c2){
            std::cout<<"y";
            missionsresult++;
            max_set_distance= std::max(max_set_distance, missionsdistances[i]);
        }
        else{
            std::cout<<"n";
        }
    }

    std::cout<<"\n";
    long minPower = findsolution(n,edges_lengths, missions, m, missionsdistances, maxdistance);
    std::cout<<minPower<<"\n";
    minPower = findsolution(n, edges_lengths, missions, missionsresult, missionsdistances, max_set_distance);
    std::cout<<minPower<<"\n";
}
int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int t;
    std::cin>>t;
    while(t--){
        solve();
    }
}
