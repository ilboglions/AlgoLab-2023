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
using vertex_desc = boost::graph_traits<graph>::vertex_descriptor;

vector < std::pair<int,int> > directions ={{1,2},{-1,2}, {2,1},{-2,1},{-1,-2},{2,-1},{1,-2}, {-2,-1}};

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
void add_connections(edge_adder & adder,  int row, int col, int dim){
    int pos = (row*dim)+col;
    int rown, coln;
    for(const auto dir: directions){
        rown = row + dir.first;
        coln = col + dir.second;
        if(rown >=0 && rown < dim && coln >= 0 && coln < dim){
            adder.add_edge(pos, (rown*dim)+coln, 1);
        }
    }
}
void solve(){
    int n;
    int pos;
    std::cin>>n;
    int curr;
    int dim = n*n;
    vector < bool > exists(dim,false);
    graph G(dim);
    auto rc_map = boost::get(boost::edge_residual_capacity, G);
    const vertex_desc v_source = boost::add_vertex(G);
    const vertex_desc v_sink = boost::add_vertex(G);
    edge_adder adder(G);
    for(int i=0; i < n; i++){
        for(int j=0; j < n; j++){
            std::cin>>pos;
            if(pos){
                curr = i*n +j;
                exists[curr]=true;
            }
        }
    }
    for(int i=0; i< n; i++){
        for(int j=0; j<n; j++){
            curr = i*n +j;
            if(exists[curr]){
                if((i+j) % 2){
                    adder.add_edge(v_source, curr, 1);
                    add_connections(adder, i, j, n);
                }
                else{
                    adder.add_edge(curr, v_sink, 1);
                }
            }
        }
    }
    long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
    std::vector<bool> vis(dim +2 , false);
    vis[dim]=true;
    std::queue<int> Q;
    Q.push(dim);
    while (!Q.empty()) {
        const int u = Q.front();
        Q.pop();
        out_edge_it ebeg, eend;
        for (boost::tie(ebeg, eend) = boost::out_edges(u, G); ebeg != eend; ++ebeg) {
        const int v = boost::target(*ebeg, G);
        if (rc_map[*ebeg] == 0 || vis[v]) continue;
        vis[v] = true;
        Q.push(v);
        }
    }
    int sum=0;
    int row, col;
    for(int i=0; i < dim; i++){
        row = i/n;
        col = i % n;
        if((row+col)%2)
            {if(vis[i] && exists[i]) sum++;}
        else
            {if(!vis[i] && exists[i]) sum++;}
    }
    std::cout<<sum<<"\n";
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