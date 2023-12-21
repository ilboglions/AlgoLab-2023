#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
#include <utility>
#include <climits>
using namespace std;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

void dijkstra_dist(const weighted_graph &G, int s, vector<int> & dist_map) {
  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));
  return;
}
int maximum_matching(const graph &G) {
  int n = boost::num_vertices(G);
  std::vector<vertex_desc> mate_map(n);
  boost::edmonds_maximum_cardinality_matching(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  return boost::matching_size(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
}

#define MAX_DIST INT_MAX
#define LIFT 'L'
typedef pair <int, pair<int,int> > escape_route;
void solve(){
  int n,m,a,s,c,d;
  cin>>n>>m>>a>>s>>c>>d;
  char w; int x,y,z;
  int tmp;
  vector< vector<int> > distances(a, vector<int>(n));
  vector<int> shelters(s);
  auto cmp = [](const escape_route & a, const escape_route & b) { return a.first < b.first;};
  vector< escape_route> pq;
  int maxtime=0;
  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);
  edge_desc e;
  for(int i=0; i < m; i++){
    cin>>w>>x>>y>>z;
    e = boost::add_edge(x, y, G).first; weights[e]=z;
    if(w == LIFT){
      e = boost::add_edge(y, x, G).first; weights[e]=z;
    }
  }
  for(int i=0; i < a; i++){
    cin>>tmp;
    dijkstra_dist(G, tmp, distances[i]);
  }
  for(int i=0; i < s; i++){
    cin>>shelters[i];
  }
  for(int i=0; i < a; i++){
    for(int j=0; j < s; j++){
      int dist = distances[i][shelters[j]];
      if(dist < MAX_DIST){
        pq.push_back(make_pair(dist, make_pair(i, j)));
        if(c == 2){
          for(int k=0; k < a; k++){
            int dist_other = distances[k][shelters[j]];
            if(dist_other >= dist && dist_other <= dist+d){
              pq.push_back(make_pair(dist+d, make_pair(k, s+j)));
            }
          }
        }
      }
    }
  }
  sort(pq.begin(), pq.end(), cmp);
  int numnodes = c==2 ? a+s+s : a+s;
  int left = 0;
  int right = pq.size()-1;
  int mid;
  while(left <= right){
    mid = (right + left)/2;
    graph G_connections = graph(numnodes);
    for(int i=0; i <= mid; i++){
      auto route = pq[i];
      int agent = route.second.first;
      int shelter = route.second.second;
      boost::add_edge(agent, shelter+a, G_connections);
    }
    if(maximum_matching(G_connections) >= a){
      maxtime = pq[mid].first+d;
      right = mid-1;
    }
    else{
      left = mid+1;
    }
  }
  cout<<maxtime<<"\n";
}
int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t; cin>>t;
  while(t--) solve();
}