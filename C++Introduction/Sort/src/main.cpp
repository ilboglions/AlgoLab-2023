#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

int main(){
  int t;
  int n;
  int x;
  vector<int> numbers;
  
  std::cin>>t;
  while(t--){
    std::cin>>n;
    numbers.clear();
    while(n--){
      int tmp;
      std::cin>>tmp;
      numbers.push_back(tmp);
    }
    std::cin>>x;
    if(x){
      std::sort(numbers.begin(), numbers.end(),  std::greater<int>());
    }
    else{
      std::sort(numbers.begin(), numbers.end());
    }
    for(int i:numbers){
      std::cout<<i<<" ";
    }
    std::cout<<"\n";
  }
}