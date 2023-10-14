#include <iostream>
#include <set>


int main(){
  int t;
  int q;
  int a,b;
  std::set<int> s;
  
  
  std::cin>>t;
  while(t--){
    s.clear();
    std::cin>>q;
    while(q--){
      std::cin>>a>>b;
      if(!a){
        s.insert(b);
      }
      else{
        s.erase(b);
      }
    }
    if(!s.empty()){
      for(int tmp: s)
        std::cout<<tmp<<" ";
      std::cout<<"\n";
    }
    else{
      std::cout<<"Empty\n";
    }
  }
}