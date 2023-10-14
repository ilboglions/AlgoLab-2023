#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
using std::vector;
using std::string;
using std::unordered_set;
typedef boost::adjacency_list<
    boost::vecS, 
    boost::vecS, 
    boost::undirectedS
> graph;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;
const vertex_desc NULL_VERTEX = boost::graph_traits<graph>::null_vertex();

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
    int n,c,f;
    std::cin>>n>>c>>f;
    graph G(n);
    string tmp;
    int common;
    std::vector<vertex_desc> mate_map(n);
    
    vector< unordered_set<string> > charact(n, unordered_set<string>());
    for( int i=0; i < n; i++){
        for(int j=0; j < c; j++){
            std::cin>>tmp;
            charact[i].insert(tmp);
        }
    }
    for(int i=0; i<n; i++){
        for(int j=i+1; j < n; j++){
            common=0;
            for(string a: charact[i]){
                if(charact[j].find(a) != charact[j].end()){
                    common++;
                }
            }
            if(common > f){
                boost::add_edge(i,j,G);
            }
        }
    }
    boost::edmonds_maximum_cardinality_matching(G, boost::make_iterator_property_map(mate_map.begin(),
                                                   boost::get(boost::vertex_index, G))
                                                );

    for(int i=0; i < n; i++){
        if(mate_map[i] >= n){
            std::cout<<"optimal\n";
            return;
        }
    }
    std::cout<<"not optimal\n";
}