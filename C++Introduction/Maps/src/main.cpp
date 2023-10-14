
#include <iostream>
#include <vector>
#include <algorithm> 
#include <map>

int main (){
  int t;
  int q;
  int a;
  std::string b;
  std::string s;

  std::multimap<std::string,int> m;
  std::multimap<std::string,int>::iterator it1, it2;
  std::vector<int> v;
  
  std::cin>>t;
  while(t--){
    v.clear();
    m.clear();
    std::cin>>q;
    for(int i=0; i < q; i++){
      std::cin>>a>>b;
      if(a){
        m.insert(std::pair<std::string,int>(b,a));
      }
      else{
        m.erase(b);
      }
    }
    std::cin>>s;
    it1 = m.lower_bound(s);
    it2 = m.upper_bound(s);
    if(it1 != m.end()){
      while(it1!=it2){
        v.push_back((*it1).second);
        it1++;
      }
      std::sort(v.begin(), v.end());
      for(int tmp: v)
        std::cout<<tmp<<" ";
      std::cout<<"\n";
    }
    else{
      std::cout<<"Empty\n";
    }
  }
}