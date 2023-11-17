#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>
#define MAXBID 100

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator
using edge_desc = boost::graph_traits<graph>::edge_descriptor;
using vertex_desc = boost::graph_traits<graph>::vertex_descriptor;

// Custom edge adder class
class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   // new assign cost
    w_map[rev_e] = -cost;   // new negative cost
  }
};


void solve() {
    int n,m,s;
    std::cin>>n>>m>>s;
    int offsetm = n;
    int offsets = offsetm+m;
    int capacity,cost;
    int state;
    graph G(n+m+s);  
    edge_adder adder(G);
    const vertex_desc v_source = boost::add_vertex(G);
    const vertex_desc v_sink = boost::add_vertex(G);  
    for(int i=0; i < s; i++){
        std::cin>>capacity;
        adder.add_edge(offsets+i, v_sink, capacity, 0);
    }
    for(int i=0; i < m; i++){
        std::cin>>state;
        adder.add_edge(offsetm+i, offsets+state, 1,0);
    }
    for(int i=0; i < n; i++){
        adder.add_edge(v_source, i, 1, 0);
        for(int j=0; j < m; j++){
            std::cin>>cost;
            adder.add_edge(i, offsetm+j, 1, MAXBID-cost);
        }
    }
    auto c_map = boost::get(boost::edge_capacity, G);
    auto rc_map = boost::get(boost::edge_residual_capacity, G);
    boost::successive_shortest_path_nonnegative_weights(G, v_source, v_sink);
    int flow=0;
    out_edge_it ei, ei_end;
    for(boost::tie(ei, ei_end) = boost::out_edges(boost::vertex(v_source, G), G); ei != ei_end; ei++){
        flow += c_map[*ei] - rc_map[*ei];
    }
    int profit = -boost::find_flow_cost(G) + MAXBID*flow;
    std::cout<<flow<<" "<<profit<<"\n";
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