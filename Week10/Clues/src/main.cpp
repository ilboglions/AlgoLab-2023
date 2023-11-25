#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/nearest_neighbor_delaunay_2.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/bipartite.hpp>
#include <vector>
#include <utility>
using std::vector;
typedef boost::adjacency_list<
    boost::vecS, 
    boost::vecS, 
    boost::undirectedS
> graph;
typedef boost::graph_traits <graph> traits;
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
typedef std::pair< P, P > Clue;
typedef Triangulation::All_faces_iterator Face_iterator;
typedef std::vector <boost::default_color_type> partition_t;
        typedef typename boost::property_map <graph, boost::vertex_index_t>::type index_map_t;
        typedef boost::iterator_property_map <partition_t::iterator, index_map_t> partition_map_t;
long squared_distance(const P & a, const P & b){
    return ((a.x()-b.x())*(a.x()-b.x()))+((a.y()-b.y())*(a.y()-b.y()));
}
void connect (Union_find & uf, const Index a, const Index b){
    Index i1,i2;
    i1 = uf.find_set(a);
    i2 = uf.find_set(b);
    if(i1 != i2){
        uf.link(i1,i2);
    }
}
bool violatesCostraint(Triangulation t, long range){
    Vertex_handle v0,v1;
    for(Edge e: t.finite_edges()){
        v0 = e.first->vertex((e.second + 1) % 3);
        v1 = e.first->vertex((e.second + 2) % 3);
        if(squared_distance(v0->point(), v1->point()) <= range){
            return true;
        }
    }
    return false;
}
void solve(){
    int n,m;
    long r;
    std::cin>>n>>m>>r;
    long range = r*r;
    Triangulation t;
    vector < IPoint > stations(n);
    vector < Clue > clues(m);
    vector < IPoint> white;
    vector < IPoint> black;
    Vertex_handle v1,v2;
    P p1,p2;
    long x,y, x2,y2;
    for(int i=0; i < n; i++){
        std::cin>>x>>y;
        stations[i] = std::make_pair(P(x,y),i);
    }
    for(int i=0; i < m; i++){
        std::cin>>x>>y>>x2>>y2;
        clues[i] = std::make_pair(P(x,y), P(x2,y2));
    }
    t.insert(stations.begin(), stations.end());
    bool interference = false;
    Union_find uf(n);
    graph G(n);
    for(Edge e: t.finite_edges()){
        v1 = e.first->vertex((e.second + 1) % 3);
        v2 = e.first->vertex((e.second + 2) % 3);
        if(squared_distance(v1->point(), v2->point()) <= range){
            connect(uf, v1->info(), v2->info());
            boost::add_edge(v1->info(),v2->info(),G);
        }     
    }
    partition_t partition (num_vertices (G));
    partition_map_t partition_map (partition.begin (), get (boost::vertex_index, G));
    typename traits::vertex_iterator vertex_iter, vertex_end;
    if(boost::is_bipartite (G, get (boost::vertex_index, G), partition_map)){
        for (boost::tie (vertex_iter, vertex_end) = vertices (G); vertex_iter != vertex_end; ++vertex_iter){
            if(get (partition_map, *vertex_iter) == boost::color_traits <boost::default_color_type>::white ())
                white.push_back(stations[*vertex_iter]);
            else
                black.push_back(stations[*vertex_iter]);
        }
        Triangulation t_black, t_white;
        t_white.insert(white.begin(), white.end());
        t_black.insert(black.begin(), black.end());
        if( violatesCostraint(t_white, range) || violatesCostraint(t_black, range))
            interference = true;
    }
    else{
      interference = true;
    }
    if(interference){
        for(int i=0; i < m; i++)
            std::cout<<"n";
        std::cout<<"\n";
        return;
    }
    for(int i=0; i < m; i++){
        p1 = clues[i].first;
        p2 = clues[i].second;
        if(squared_distance(p1, p2) <= range) std::cout<<"y";
        else{
            v1 = t.nearest_vertex(p1);
            v2 = t.nearest_vertex(p2);
            Index i1 = uf.find_set(v1->info());
            Index i2 = uf.find_set(v2->info());
            if(squared_distance(p1, v1->point()) <= range && squared_distance(p2, v2->point()) <= range && i1 == i2){
                std::cout<<"y";
            }
            else{
                std::cout<<"n";
            }
        }
    }
    std::cout<<"\n";
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
