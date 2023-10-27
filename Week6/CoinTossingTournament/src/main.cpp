#include <iostream>
#include <vector>
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
    int n,m;
    int tmp;
    std::cin>>n>>m;
    int a,b,c;
    int score;
    int sum=0;
    int assignable = 0;
    graph G(n*2);
    const vertex_desc v_source = boost::add_vertex(G);
    const vertex_desc v_sink = boost::add_vertex(G);
    edge_adder adder(G);
    vector < int> points(n,0);
    vector < vector<int> > uncertaingames(n, vector<int>(n,0));
    for(int i=0; i < m ; i++){
        std::cin>>a>>b>>c;
        if(c){
            if(c==1)
                points[a]++;
            else
                points[b]++;
        }
        else{
            assignable++;
            uncertaingames[a][b]++; 
            uncertaingames[a][a]++;   
        }
    }
    for(int i=0; i < n; i++){
        if(uncertaingames[i][i])
          adder.add_edge(v_source, i , uncertaingames[i][i]);
        for(int j=0; j < n; j++){
            if(uncertaingames[i][j])
              adder.add_edge(i, j+n , uncertaingames[i][j]);
        }
        std::cin>>score;
        tmp = std::max(score-points[i],0);
        sum += tmp;
        if(tmp)
          adder.add_edge(i+n, v_sink, tmp);
    }
    long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
    if(sum == assignable && flow == (long)sum)
        std::cout<<"yes\n";
    else
        std::cout<<"no\n";
}