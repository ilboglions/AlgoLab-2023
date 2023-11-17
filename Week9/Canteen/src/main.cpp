#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/find_flow_cost.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#define COSTS_RANGE 20
using traits =
    boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS>;
using graph = boost::adjacency_list<
    boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<
        boost::edge_capacity_t, long,
        boost::property<
            boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                            boost::property<boost::edge_weight_t, long>>>>>;

typedef boost::graph_traits<graph>::out_edge_iterator out_edge_it;
using edge_desc = boost::graph_traits<graph>::edge_descriptor;
using vertex_desc = boost::graph_traits<graph>::vertex_descriptor;
using out_edge_it = boost::graph_traits<graph>::out_edge_iterator;
class edge_adder {
  graph &G;
public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); 
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; 
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;      
    w_map[rev_e] = -cost;
  }
};
void solve(){
    int n;
    std::cin>>n;
    int capacity, cost;
    int sum=0;
    graph G(n);
    const vertex_desc v_source = boost::add_vertex(G);
    const vertex_desc v_sink = boost::add_vertex(G);
    edge_adder adder(G);
    for(int i=0; i < n; i++){
        std::cin>>capacity>>cost;
        adder.add_edge(v_source, i, capacity, cost);
    }
    for(int i=0; i < n; i++){
        std::cin>>capacity>>cost;
        sum += capacity;
        adder.add_edge(i,v_sink, capacity, -cost+COSTS_RANGE);
    }
    for(int i=0; i < n-1; i++){
        std::cin>>capacity>>cost;
        adder.add_edge(i, i+1, capacity, cost);
    }
    auto c_map = boost::get(boost::edge_capacity, G);
    auto rc_map = boost::get(boost::edge_residual_capacity, G);
    boost::successive_shortest_path_nonnegative_weights(G, v_source, v_sink);

    int flow=0;
    out_edge_it ei, ei_end;
    for(boost::tie(ei, ei_end) = boost::out_edges(boost::vertex(v_source, G), G); ei != ei_end; ei++){
        flow += c_map[*ei] - rc_map[*ei];
    }
    if((int)flow >= sum)
        std::cout<<"possible ";
    else
        std::cout<<"impossible ";

    int profit = -boost::find_flow_cost(G) + COSTS_RANGE*flow;
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