#include <iostream>
#include <vector>
#include <set>


using std::vector;
using std::set;

void visit(vector<set<int> >& , vector<int>& , vector<int>&, int, int *);

int main(){
  int t;
  int n,m,v;
  int a,b;
  vector<set<int> > graph;
  std::cin>>t;
  while(t--){
    graph.clear();
    std::cin>>n>>m>>v;
    graph.resize(n);
    vector<int> timein(n,-1);
    vector<int> timeout(n,-1);
    while(m--){
      std::cin>>a>>b;
      graph[a].insert(b);
      graph[b].insert(a);
    }
    int timer=0;
    visit(graph, timein, timeout, v, &timer);
    for(int i: timein){
      std::cout<<i<<" ";
    }
    std::cout<<"\n";
    for(int i: timeout){
      std::cout<<i<<" ";
    }
    std::cout<<"\n";
  }
}
void visit(vector<set<int> >& graph, vector<int>& in, vector<int>& out, int start, int *  currtime){
  if(in[start] != -1)
    return;
  in[start] = *currtime;
  *currtime += 1;
  for(int tmp: graph[start]){
    visit(graph, in , out, tmp, currtime);  
  }
  out[start] = * currtime;
  *currtime += 1;
}