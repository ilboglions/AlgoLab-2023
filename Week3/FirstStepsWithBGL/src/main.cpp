#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<
    boost::vecS, 
    boost::vecS, 
    boost::undirectedS,
    boost::no_property,
    boost::property<boost::edge_weight_t, int>
> weighted_graph;

typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor vertex_desc;

void solve();

int main(){
    std::ios_base::sync_with_stdio(false);
    int t;
    std::cin>>t;
    while(t--){
        solve();
    }
}

void solve(){
    int m,n;
    std::cin>>n>>m;
    weighted_graph G(n);
    std::vector<int> dist_map(n); 
    int a,b,c;
    for(int i=0; i < m; i++){
        std::cin>>a>>b>>c;
        boost::add_edge(a,b,c,G);
    }
    std::vector<edge_desc> mst;
    boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));
    int res = 0;
    for(edge_desc it : mst){
        res += get(boost::edge_weight_t(), G, it);
    }
    boost::dijkstra_shortest_paths(G, 0, 
        boost::distance_map(boost::make_iterator_property_map(dist_map.begin(),boost::get(boost::vertex_index, G))));
    int max=0;
    for(int i: dist_map)
        max = std::max(max, i);
        
    std::cout<<res<<" "<<max<<"\n";
}