#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

typedef pair<int, int> bomb;
void solve(){
  int n; cin>>n;
  vector<int> toremove(n, 2);
  vector<int> timers(n);
  
  for(int i=0; i<n; i++)
    cin>>timers[i];
    
  for(int i=0; i <= (n-3)/2; i++){
    timers[2*i + 1] = min(timers[2*i + 1], timers[i]-1);
    timers[2*i + 2] = min(timers[2*i + 2], timers[i]-1);
  }
  auto cmp = [](bomb a, bomb b) { return a.first > b.first;};
  priority_queue<bomb, std::vector<bomb>, decltype(cmp)> pq(cmp);
  for(int i=(n-1)/2; i<n; i++) pq.push(make_pair(timers[i], i));
  int counter = 0;
  while(pq.size()){
    auto elem = pq.top();
    int current = elem.second;
    int available = elem.first;
    pq.pop();
    if(counter >= available) {
      cout<<"no\n"; return;
    }
    counter++;
    toremove[(current-1)/2]--; if(toremove[(current-1)/2] == 0) pq.push(make_pair(timers[(current-1)/2], (current-1)/2));
  }
  cout<<"yes\n";
}
int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t; cin>>t;
  while(t--) solve();
}