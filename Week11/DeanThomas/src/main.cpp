#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <vector>
#include <queue>
#include <map>
using namespace std;
typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Vertex_handle Vertex_handle;
typedef Triangulation::Face_handle Face_handle;
typedef K::Point_2 P;
using CGAL::squared_distance;
typedef pair<Face_handle, K::FT> face_capacity;
struct comparator {
    bool operator() (const pair<Face_handle, K::FT> & a , const pair<Face_handle, K::FT> & b) const{
        return a.second < b.second;}
};
void get_escapes(const Triangulation & t, unordered_map < Face_handle, K::FT > & escapes){
    unordered_map < Face_handle , K::FT > already_added;
    P center;
    Face_handle neighbor;
    K::FT distance, tmp;
    priority_queue <face_capacity, vector<face_capacity>, comparator > pq;
    for(Face_handle fh: t.finite_face_handles()){
        center = t.dual(fh);
        neighbor = t.locate(center);
        distance = squared_distance(center, fh->vertex(0)->point());
        for(int i=0; i < 3; i++){
            neighbor = fh->neighbor(i);
            if(t.is_infinite(neighbor)){
                distance = max( distance, squared_distance(fh->vertex((i+1)%3)->point(), fh->vertex((i+2)%3)->point()));
            }
        }
        pq.push(make_pair(fh, distance));
        already_added.insert(make_pair(fh, distance));
    }
    while(pq.size()){
        auto elem = pq.top();
        Face_handle f = elem.first;
        distance = elem.second;
        pq.pop();
        if(escapes.find(f) == escapes.end()){
            escapes.insert(make_pair(f, distance));
        }
        for(int i=0; i < 3; i++){
            neighbor = f->neighbor(i);
            if(!t.is_infinite(neighbor) && escapes.find(neighbor) == escapes.end()){
                tmp = min(distance, squared_distance(f->vertex((i+1)%3)->point(), f->vertex((i+2)%3)->point()));
                auto finder = already_added.find(neighbor);
                if( tmp > finder->second){
                    pq.push(make_pair(neighbor, tmp));
                    finder->second = tmp;
                }
            }
        }
    }
}
void solve(){
    int n,m; double d,x,y,s; cin>>n>>m>>d;
    P origin = P(0,0), nearest;
    vector <P> dementors(n);
    vector <P> fugitives(m);
    vector <K::FT> distances(m);
    vector <K::FT> doubledistances(m);
    unordered_map < Face_handle, K::FT > escapes;
    for(int i=0; i < n; i++){
        cin>>x>>y;
        dementors[i] = P(x,y);
    }
    Triangulation t(dementors.begin(), dementors.end());
    get_escapes(t, escapes);
    for(int i=0; i < m; i++){
        cin>>x>>y>>s;
        fugitives[i]=P(x,y);
        distances[i] = squared_distance(P(s+d, 0), origin);
        doubledistances[i]= (K::FT)4* distances[i];
    }
    for(int i=0; i < m; i++){
        nearest = t.nearest_vertex(fugitives[i])->point();
        if(squared_distance(nearest,fugitives[i]) < distances[i]){ cout<<"n"; continue;}
        auto finder = escapes.find(t.locate(fugitives[i]));
        if(finder == escapes.end() || doubledistances[i] <= finder->second) cout<<"y";
        else cout<<"n";
    } cout<<"\n";
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