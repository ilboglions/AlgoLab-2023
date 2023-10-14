#include <iostream>

void solve();
int main(){
  int t;
  std::cin>>t;
  while(t--)
    solve();
}

void solve(){
  int n;
  int sum=0;
  int tmp;
  int even, odd;
  even = 0;
  odd  = 0;
  std::cin>>n;
  while(n--){
    std::cin>>tmp;
    sum += tmp;
    if(sum % 2)
      odd++;
    else{
      even++;
    }
  }
  std::cout<< odd *(odd-1)/2 + even*(even-1)/2 + even<<std::endl;
}