#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
using std::vector;
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

class edge_adder {
  graph &G;
 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0;
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};
void solve(){
    int n,m,k,l;
    int u,v;
    std::cin>>n>>m>>k>>l;
    vector<int> stations(k);
    vector<int> photos(l);
    graph G(2*n);
    edge_adder adder(G);
    for(int i=0; i < k; i++){
        std::cin>>stations[i];
    }
    for(int i=0; i < l; i++){
        std::cin>>photos[i];
    }
    for(int i=0; i < m; i++){
        std::cin>>u>>v;
        adder.add_edge(u,v,k);
        adder.add_edge(u+n, v+n, 1);
    }
    for(int i=0; i < l; i++){
        adder.add_edge(photos[i], photos[i]+n, 1);
    }
    const vertex_desc v_source = boost::add_vertex(G);
    const vertex_desc v_sink = boost::add_vertex(G);
    for(int i=0; i < k; i++){
        adder.add_edge(v_source, stations[i], 1);
        adder.add_edge(stations[i]+n, v_sink, 1);   
    }
    long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
    std::cout<<flow<<"\n";
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