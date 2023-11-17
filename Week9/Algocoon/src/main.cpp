#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>
using std::vector;
typedef  boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
  boost::property<boost::edge_capacity_t, long,
    boost::property<boost::edge_residual_capacity_t, long,
      boost::property<boost::edge_reverse_t, traits::edge_descriptor> > > >  graph;
typedef  boost::graph_traits<graph>::edge_descriptor      edge_desc;
typedef  boost::graph_traits<graph>::out_edge_iterator      out_edge_it;
typedef  boost::graph_traits<graph>::vertex_descriptor      vert_desc;
class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};
void build_graph(graph & G, const vector<vector<int> > & limbs, int n){
    edge_adder adder(G);
    for(int i=0; i < n; i++){
        for(int j=0; j < n; j++){
            if(limbs[i][j]){
                adder.add_edge(i,j, limbs[i][j]);
            }
        }
    }
}
void solve() {
  int n,m;
    std::cin>>n>>m;
    int a,b,c;
    vector< vector<int> > limbs(n, vector<int>(n,0));
    for(int i=0; i < m; i++){
        std::cin>>a>>b>>c;
        limbs[a][b] += c;
    }
    graph G(n);
    build_graph(G, limbs,n);
    vector<int> sinks;
    int mincut = INT_MAX;
    int flow;
    for(int i=1; i < n; i++){
        flow = boost::push_relabel_max_flow(G, 0,i);
        mincut = std::min(mincut, flow);
        flow = boost::push_relabel_max_flow(G, i,0);
        mincut = std::min(mincut, flow);
    }
    std::cout<<mincut<<"\n";
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