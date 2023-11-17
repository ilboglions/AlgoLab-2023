#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/nearest_neighbor_delaunay_2.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <utility>
#include <vector>
using std::vector;
using std::pair;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef std::size_t Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Triangulation;
typedef K::Point_2 P;
typedef Triangulation::Vertex_handle Vertex_handle;
typedef Triangulation::Edge Edge;
typedef K::Point_2 P;
typedef std::pair<P,Index> IPoint;
typedef boost::disjoint_sets_with_storage<> Union_find;

void solve();
long getEdgeLength(const Edge & e){
    return squared_distance(e.first->vertex((e.second + 1) % 3)->point(), e.first->vertex((e.second + 2) % 3)->point());
}
bool compareEdges(const Edge & e1, const Edge & e2){
    return getEdgeLength(e1) < getEdgeLength(e2);
}
long squared_distance(const P & p1, const P & p2){
    return ((p1.x()-p2.x())*(p1.x()-p2.x())) + ((p1.y()-p2.y())*(p1.y()-p2.y()));
}
void connectelems(vector<Edge> & edges, const long s, Union_find & uf){
    long distance;
    Index i1,i2;
    Vertex_handle v1,v2;
    for(Edge e : edges){
        v1 = e.first->vertex((e.second + 1) % 3);
        v2 = e.first->vertex((e.second + 2) % 3);
        i1 = uf.find_set(v1->info());
        i2 = uf.find_set(v2->info());
        if(i1 != i2){
            distance = squared_distance(v1->point(), v2->point());
            if(distance <= s)
                uf.link(i1, i2); 
        }
    }
}
int evaluatesolution(const vector< pair<long, Vertex_handle> > & elems, const Triangulation & t, Union_find & uf, long s, int n){
    vector<int> res(n,0);
    int max=0;
    Index i;
    for(auto p: elems){
        if(p.first <= s){
            i=uf.find_set(p.second->info());
            res[i]++;
            max = std::max(max, res[i]);
        }
    }
    return max;
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
void solve(){
    vector< long > distances;
    int n,m;
    long s;
    int k;
    std::cin>>n>>m>>s>>k;
    Triangulation t;
    int x,y;
    int res;
    P tmp;
    long dist;
    Vertex_handle nearest;
    vector < pair<long, Vertex_handle> > bones(m);
    vector < IPoint > trees(n);
    vector < Edge > edges;
    Union_find uf(n);
    for(int i=0; i < n; i++){
        std::cin>>x>>y;
        trees[i] = std::make_pair(P(x,y),i);
    }
    t.insert(trees.begin(), trees.end());
    for(int i=0; i <m ; i++){
        std::cin>>x>>y;
        tmp = P(x,y);
        nearest = t.nearest_vertex(tmp);
        dist = 4*squared_distance(nearest->point(),tmp);
        bones[i] = std::make_pair(dist, nearest);
        distances.push_back(dist);
    }
    for(Edge e: t.finite_edges()){
        edges.push_back(e);
        distances.push_back(getEdgeLength(e));
    }
    std::sort(distances.begin(), distances.end());
    connectelems(edges,s, uf);
    res = evaluatesolution(bones,t, uf, s,n);
    std::cout<<res<<" ";
    int start =0;
    int end = distances.size()-1;
    int mid;
    long b;
    long value;
    while(start <= end){
        mid = (start+end)/2;
        Union_find uf_temp(n);
        b = distances[mid];
        connectelems(edges, b, uf_temp);
        res = evaluatesolution(bones, t, uf_temp, b, n);
        if(res >= k){
            value = b;
            end = mid-1;
        }
        else{
            start = mid+1;
        }
    }
    std::cout<<std::setprecision(0)<<std::fixed<<value<<"\n";
}