#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>
using namespace std;
#define OFFSET 1024
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; 
typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef traits::vertex_descriptor                               vertex_desc;
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
    c_map[rev_e] = 0; 
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   
    w_map[rev_e] = -cost;  
  }
};

void solve(){
    int n, pg, ph, eg, eh, fg, fh, sg, sh;
    cin>>n>>pg>>ph>>eg>>eh>>fg>>fh>>sg>>sh;
    int preference;
    int numcities = pg+ph;
    graph G(numcities+n*2);
    const vertex_desc v_source = boost::add_vertex(G);
    const vertex_desc v_sink = boost::add_vertex(G);
    auto c_map = boost::get(boost::edge_capacity, G);
    auto rc_map = boost::get(boost::edge_residual_capacity, G);
    int u,v,c;
    edge_adder adder(G);
    for(int i=0; i < n; i++){
        cin>>preference;
        adder.add_edge(numcities+i, numcities+i+n, 1, OFFSET - preference);
    }
    for(int i=0; i < eg; i++){
        cin>>u>>v>>c;
        adder.add_edge(u,v, c, 0);
    }
    for(int i=0; i < eh; i++){
        cin>>u>>v>>c;
        adder.add_edge(pg+v, pg+u ,c,0);
    }
    for(int i=0; i < fg; i++){
        cin>>u>>v>>c;
        adder.add_edge(u, numcities+v, c, 0);
    }
    for(int i=0; i < fh; i++){
        cin>>u>>v>>c;
        adder.add_edge(numcities+ v + n, pg + u, c, 0);
    }
    adder.add_edge(v_source, 0, sg, 0);
    adder.add_edge(pg, v_sink, sh, 0);
    boost::successive_shortest_path_nonnegative_weights(G, v_source, v_sink);
    int cost = boost::find_flow_cost(G);
    int flow = 0;
    out_edge_it e, eend;
    for(boost::tie(e, eend) = boost::out_edges(boost::vertex(v_source,G), G); e != eend; ++e) 
        flow += c_map[*e] - rc_map[*e];     
    
    cost = (flow * OFFSET)-cost;
    cout<<flow<<" "<<cost<<"\n";
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin>>t;
    while(t--){
        solve();
    }
}

