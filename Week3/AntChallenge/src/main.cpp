#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
using std::vector;


typedef boost::adjacency_list<
    boost::vecS, 
    boost::vecS, 
    boost::undirectedS,
    boost::no_property,
    boost::property<boost::edge_weight_t, int >
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
    int n,e,s,a,b;
    int source, target;
    std::cin>>n>>e>>s>>a>>b;
    int tmp;
    int hive;
    weighted_graph G(n);
    vector< vector <int> > graphmap(n, vector<int> (n, INT_MAX));
    vector<weighted_graph> networks(s, weighted_graph (n));
    vector<int> hives(s);

    for(int i=0; i < e; i++){
        std::cin>>source>>target;
        for(int j=0; j < s; j++){
            std::cin>>tmp; 
            boost::add_edge(source, target, tmp, networks[j]);
        }
    }
    
    std::vector<edge_desc> mst;
    for(int i=0; i < s; i++){
        std::cin>>hive;
        mst.clear();
        boost::kruskal_minimum_spanning_tree(networks[i], std::back_inserter(mst));
        for(edge_desc it : mst){
            source = boost::source(it, networks[i]);
            target = boost::target(it, networks[i]);
            if(source > target)
                std::swap(source, target);
            graphmap[source][target] = std::min(graphmap[source][target] , get(boost::edge_weight_t(), networks[i], it));
        }
    }
    for(int i=0; i < n; i++){
        for(int j=i+1; j < n; j++){
            if(graphmap[i][j] != INT_MAX){
                boost::add_edge(i,j, graphmap[i][j], G);
            }
        }
    }
    vector<int> dist_map(n);
    boost::dijkstra_shortest_paths(G, a, boost::distance_map(boost::make_iterator_property_map(dist_map.begin(), boost::get(boost::vertex_index, G))));
    std::cout<<dist_map[b]<<"\n";
}
