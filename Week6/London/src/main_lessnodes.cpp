#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <string>
#define OFFSET 'A'
#define NUMLETTERS 26
using std::vector;
using std::string;

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
    std::cin>>h>>w;
    graph G(NUMLETTERS*2);
    const vertex_desc v_source = boost::add_vertex(G);
    const vertex_desc v_sink = boost::add_vertex(G);
    edge_adder adder(G);
    int n;
    char tmp;
    int tmpindex;
    vector< int > occurences(NUMLETTERS, 0);
    vector< vector<int> > couples(NUMLETTERS, vector<int>(NUMLETTERS,0));
    vector< vector< int > > firstpage(h, vector<int>(w));
    string message;
    std::cin>>message;
    n = message.size();
    for(char c: message){
        occurences[c - OFFSET]++;
    }
    for (int i=0; i < h; i++){
        for(int j=0; j < w; j++){
            std::cin>>tmp;
            firstpage[i][j] = tmp-OFFSET;
        }
    }
    for (int i=0; i < h; i++){
        for(int j=0; j < w; j++){
            std::cin>>tmp;
            tmpindex = firstpage[i][w-j-1];
            couples[tmpindex][tmpindex]++;
            if(tmpindex != tmp-OFFSET)
              couples[tmpindex][tmp-OFFSET]++;   
        }
    }
    for(int i=0; i < NUMLETTERS; i++){
        if(couples[i][i])
            adder.add_edge(v_source, i, couples[i][i]);
        for(int j=0; j < NUMLETTERS; j++){
            if(couples[i][j]){
                adder.add_edge(i, OFFSET+j, couples[i][j]);
            }
        }
        if(occurences[i])
            adder.add_edge(OFFSET+i, v_sink , occurences[i]);
    }
    long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
    if(flow == (long)n)
        std::cout<<"Yes\n";
    else
        std::cout<<"No\n";
}