#include <iostream>
#include <vector>
#include <set>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>

using std::vector;
using std::set;
using std::pair;

typedef boost::adjacency_list<
    boost::vecS, 
    boost::vecS, 
    boost::undirectedS
> graph;

typedef boost::graph_traits<graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;

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
    int a,b;
    int m,n;
    std::cin>>n>>m;
    graph G(n);
    std::map<edge_desc, int> mapping;
    std::vector<edge_desc> important;
    for(int i=0; i < m; i++){
        std::cin>>a>>b;
        boost::add_edge(a,b,G);
    }
    std::vector<edge_desc> mst;
    boost::biconnected_components(G, boost::make_assoc_property_map(mapping));
    vector<int> edges(mapping.size(), 0);
    for(auto i:mapping){
        edges[i.second]++;
    }
    for(auto i : mapping ){
        if(edges[i.second] == 1){
            important.push_back(i.first);
        }
    }
    int total = important.size();
    std::cout<<total<<"\n";
    set< pair<int,int> > bridges;
    for(int i=0; i < total; i++){
       a=boost::target(important[i], G);
       b=boost::source(important[i], G);
       if(a > b){
        std::swap(a,b);
       }
       bridges.insert(std::make_pair(a,b));
    }
    for(auto p: bridges){
        std::cout<<p.first<<" "<<p.second<<"\n";
    }
}