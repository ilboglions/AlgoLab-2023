
#include <iostream>
#include <vector>

using std::vector;
void solve();

int main(){
  int t;
  std::cin>>t;
  while(t--){
    solve();
  }
}
void solve(){
  int n;
  std::cin>>n;
  vector<int> dominos(n);
  int start = 0;
  for(int i=0; i < n ; i++){
      std::cin>>dominos[i];
      if(start >= i ){
        start = std::max(start,i + dominos[i]-1);
      }
  }
  start = std::min(n, start+1);
  std::cout<<start<<"\n";
}