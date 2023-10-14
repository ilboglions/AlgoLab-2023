#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

void visit(vector<vector<int> >& , vector<int>& , vector<int>&, int, int *);

int main(){
  int t;
  int n,m,v;
  int a,b;
  int tmp;
  vector<vector<int> > graph;
  std::cin>>t;
  while(t--){
    graph.clear();
    std::cin>>n>>m>>v;
    graph.resize(n);
    vector<int> distance(n,-1);
    while(m--){
      std::cin>>a>>b;
      graph[a].push_back(b);
      graph[b].push_back(a);
    }
    distance[v]=0;
    queue<int> tovisit;
    tovisit.push(v);
    while(tovisit.size()){
      tmp = tovisit.front();
      tovisit.pop();
      for(int i: graph[tmp]){
        if(distance[i] == -1){
          distance[i]=distance[tmp]+1;
          tovisit.push(i);
        }
      }
    }
    
    for(int i: distance){
      std::cout<<i<<" ";
    }
    std::cout<<"\n";
  }
}
