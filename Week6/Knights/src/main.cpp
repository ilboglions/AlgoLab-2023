#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

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
    int m,n,k,c;
    int a,b;
    std::cin>>m>>n>>k>>c;
    graph G(2*m*n);
    int offset = m*n;
    int enterpos;
    int exitpos;
    int side;
    const vertex_desc v_source = boost::add_vertex(G);
    const vertex_desc v_sink = boost::add_vertex(G);
    edge_adder adder(G);
    for(int i=0; i < n; i++){ //iterates through rows
        for(int j=0; j < m; j++){ //iterates through columns
            side = 0;
            enterpos = (i*m)+j;
            exitpos = enterpos+offset;
            adder.add_edge(enterpos, exitpos, c);
            if(i){ //not first row
                adder.add_edge(exitpos, enterpos-m , 1); //previous row
            }else{
                side++;
            }
            if(i != n-1){
                adder.add_edge(exitpos, enterpos+m , 1); //next row
            }else{
                side++;
            }
            if(j){
                adder.add_edge(exitpos, enterpos-1 , 1); //previous col
            }
            else{
                side++;
            }
            if(j != m-1){
                adder.add_edge(exitpos, enterpos+1 , 1); //next col
            }else{
                side++;
            }
            if(side){
                adder.add_edge(exitpos, v_sink, side);
            }
        }
    }
    for(int i=0; i < k; i++){
        std::cin>>b>>a;
        adder.add_edge(v_source, (a*m)+b, 1);
    }
    long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
    std::cout<<flow<<"\n";
}