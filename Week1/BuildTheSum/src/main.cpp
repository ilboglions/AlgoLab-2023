#include <iostream>

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
  int tmp;
  std::cin>>n;
  int sum=0;
  while(n--){
    std::cin>>tmp;
    sum += tmp;
  }
  std::cout<<sum<<"\n";
}