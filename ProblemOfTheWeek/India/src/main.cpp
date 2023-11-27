#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph;
typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; 

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
void solve(){
    int c,g,b,k,a;
    std::cin>>c>>g>>b>>k>>a;
    int x,y,d,edge_capacity;
    graph G(c);
    edge_adder adder(G);
    auto c_map = boost::get(boost::edge_capacity, G);
    auto rc_map = boost::get(boost::edge_residual_capacity, G);
    for(int i=0; i < g; i++){
        std::cin>>x>>y>>d>>edge_capacity;
        adder.add_edge(x,y, edge_capacity, d);
    }
    adder.add_edge(c, k, INT_MAX, 0);
    boost::successive_shortest_path_nonnegative_weights(G, c, a);
    int max_flow = 0;
    out_edge_it e, eend;
    for(boost::tie(e, eend) = boost::out_edges(boost::vertex(c ,G), G); e != eend; ++e) {
        max_flow += c_map[*e] - rc_map[*e];  
    }
    int iterations = 1;
    int left = 0, right = max_flow, res=0;
    int mid, cost_tmp;
    while(left <= right){
        mid = (right + left )/2;
        adder.add_edge(c+iterations, k, mid, 0);
        boost::successive_shortest_path_nonnegative_weights(G, c+iterations, a);
        cost_tmp = boost::find_flow_cost(G);
        if(cost_tmp <= b){
            res = iterations;
            left = mid+1;
        }
        else{
            right = mid-1;
        }
        iterations++;
    }
    int final_flow = 0;
    if(res){
        boost::successive_shortest_path_nonnegative_weights(G, c+res, a);
        cost_tmp = boost::find_flow_cost(G);
        for(boost::tie(e, eend) = boost::out_edges(boost::vertex(c+res,G), G); e != eend; ++e) {
            final_flow += c_map[*e] - rc_map[*e];  
        }
    }
    std::cout<<final_flow<<"\n";
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