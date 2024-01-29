#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <queue>
using namespace std;
typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef Triangulation::Face_handle Face_handle;
typedef K::Point_2 P;

void get_escapes ( Triangulation & t, unordered_map <Face_handle, K::FT> & escapes){

  auto cmp = [](pair< Face_handle, K::FT > a, pair< Face_handle, K::FT > b) { return a.second < b.second;};
  priority_queue< pair< Face_handle, K::FT >, std::vector<pair< Face_handle, K::FT > >, decltype(cmp)> pq(cmp);
  unordered_map < Face_handle, K::FT > biggest_added;

  for(Face_handle fh : t.finite_face_handles()){
    P center = t.dual(fh);
    K::FT maximum = CGAL::squared_distance(center, fh->vertex(0)->point());
    for(int i = 0; i < 3; i++){
      if( t.is_infinite(fh->neighbor(i))){
        maximum = max(maximum, CGAL::squared_distance(fh->vertex((i+1)% 3)->point(), fh->vertex((i+2)% 3)->point()));
      }
    }
    pq.push(make_pair(fh, maximum));
    biggest_added.insert(make_pair(fh, maximum));
  }
  while(pq.size()){
    auto elem = pq.top();
    Face_handle fh = elem.first;
    K::FT distance = elem.second;
    pq.pop();
    if(escapes.find(fh) == escapes.end()){
      escapes.insert(make_pair(fh, distance));
      for(int i = 0; i < 3; i++){
        Face_handle neighbor = fh->neighbor(i);
        K::FT edge_size = CGAL::squared_distance(fh->vertex((i+1)% 3)->point(), fh->vertex((i+2)% 3)->point());
        K::FT neighbor_capacity = min(edge_size, distance);
        auto finder = biggest_added.find(neighbor);
        if( !t.is_infinite(neighbor) &&  finder->second < neighbor_capacity){
          pq.push(make_pair(neighbor, neighbor_capacity));
          finder -> second = neighbor_capacity;
        }
      }
    }
  }
}
void solve(){
  int n,m; long d; cin>>n>>m>>d;
  long x,y,s;
  P origin = P(0,0);
  vector< P > dementors(n);
  vector< P > fugitives(m);
  vector< K::FT > distances(m);
  for(int i=0; i< n; i++){
    cin>>x>>y; dementors[i]=P(x,y);
  }
  Triangulation t;
  t.insert(dementors.begin(),dementors.end());
  for(int i=0; i < m; i++){
    cin>>x>>y>>s; fugitives[i] = P(x,y); distances[i] = CGAL::squared_distance(P(s+d, 0), origin);
  }
  unordered_map < Face_handle, K::FT > escape_capacities;
  get_escapes(t, escape_capacities);
  for(int i=0; i<m; i++){
    P nearest = t.nearest_vertex(fugitives[i])->point();
    K::FT distance = CGAL::squared_distance(nearest, fugitives[i]);
    if(distance < distances[i]) {cout<<"n"; continue;}
    distance = distances[i] * ((K::FT)4);
    Face_handle face = t.locate(fugitives[i]);
    auto finder = escape_capacities.find(face);
    if(finder == escape_capacities.end() || finder->second >= distance) cout<<"y";
    else cout<<"n";
  }
  cout<<"\n";
}
int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t; cin>>t;
  while(t--) solve();
}