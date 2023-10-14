#include <iostream>
#include <vector>

int main (){
  int t;
  int n;
  int d,a,b;
  std::cin>>t;
  while(t--){
    std::cin>>n;
    std::vector<int> v(n);
    for(int i=0; i < n; i++){
      std::cin>>v[i];
    }
    std::cin>>d;
    std::cin>>a>>b;
    v.erase(v.begin()+d);
    v.erase(v.begin()+a,v.begin()+b+1);
    if(!v.empty()){
      for(int tmp: v)
        std::cout<<tmp<<" ";
      std::cout<<"\n";
    }
    else
      std::cout<<"Empty\n";
  }
}