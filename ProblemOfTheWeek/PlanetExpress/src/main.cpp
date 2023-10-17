#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/strong_components.hpp>

using std::vector;

void solve();
typedef boost::adjacency_list<
    boost::vecS, 
    boost::vecS, 
    boost::directedS,
    boost::no_property,
    boost::property<boost::edge_weight_t, int >
> weighted_graph;

typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor vertex_desc;

int main(){
    std::ios_base::sync_with_stdio(false);
    int t;
    std::cin>>t;
    while(t--){
        solve();
    }
}

void solve(){
    int n,m,k,t;
    int u,v,c;
    int tmp;
    std::cin>>n>>m>>k>>t;
    int dimmax = 2*n;
    weighted_graph G(dimmax);
    vector<int> network(n,0);
    for(int i=0; i < t; i++){
        std::cin>>tmp;
        network[tmp] = 1;
    }
    for(int i=0; i < m; i++){
        std::cin>>u>>v>>c;
        boost::add_edge(v, u, c , G);
    }

    std::vector<int> scc_map(dimmax);
    int nscc = boost::strong_components(G,boost::make_iterator_property_map(scc_map.begin(),boost::get(boost::vertex_index, G)));
    std::vector< vector<int> > scc_lists(nscc, vector<int>());
    for(int i=0; i < n; i++){
        if(network[i])
            scc_lists[scc_map[i]].push_back(i);
    }
    int weight;
    int newnode;
    for(int i=0; i < nscc; i++){
        weight = scc_lists[i].size()-1;
        newnode = n+i;
        for(int j=0; j <= weight; j++){
            boost::add_edge(newnode, scc_lists[i][j] , weight , G);
            boost::add_edge(scc_lists[i][j] ,newnode, 0 , G);
        }
    }
    vector<int> dist_map(dimmax);
    boost::dijkstra_shortest_paths(G, n-1, boost::distance_map(boost::make_iterator_property_map(dist_map.begin(), boost::get(boost::vertex_index, G))));
    int min=INT_MAX;
    for(int i=0; i < k; i++){
        if (dist_map[i] < min){
            min = dist_map[i];
        }
    }
    if(min < 1000000)
        std::cout<<min<<"\n";
    else
        std::cout<<"no\n";
}