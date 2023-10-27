#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#define USABLE '.'
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
    int w,h;
    char c;
    std::cin>>w>>h;
    graph G(w*h);
    edge_adder adder(G);
    int oddcells=0, evencells=0;
    int toreach;
    vector< vector <int> > garden(h, vector<int>(w, 0));

    const vertex_desc v_source = boost::add_vertex(G);
    const vertex_desc v_sink = boost::add_vertex(G);
    for(int i=0; i < h; i++){
        for (int j=0; j < w; j++){
            std::cin>>c;
            if(c == USABLE){
                garden[i][j]=1;
                if((i+j)%2){ //odd cell
                    adder.add_edge((i*w)+j, v_sink, 1);
                    oddcells++;
                }
                else{ //even cell
                    adder.add_edge(v_source, (i*w)+j , 1);
                    evencells++;
                }
            }
        }
    }
    for(int i=0; i < h; i++){
        for(int j=i%2; j < w ; j+=2){
            if(garden[i][j]){
                if(i && garden[i-1][j]){
                    adder.add_edge((i*w)+j, ((i-1)*w)+j, 1);
                }
                if(i!= h-1 && garden[i+1][j]){
                    adder.add_edge((i*w)+j, ((i+1)*w)+j, 1);
                }
                if(j && garden[i][j-1]){
                    adder.add_edge((i*w)+j, (i*w)+j-1, 1);
                }
                if(j != w-1 && garden[i][j+1]){
                    adder.add_edge((i*w)+j, (i*w)+j+1, 1);
                }
            }
        }
    }
    toreach = std::max(oddcells, evencells);
    long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
    if(flow >= (long)toreach)
        std::cout<<"yes\n";
    else
        std::cout<<"no\n";
}