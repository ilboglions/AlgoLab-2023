#include <iostream>
#include <vector>

using std::vector;
void solve();

int main(){
  int t;
  std::cin>>t;
  while(t--)
    solve();
}
void solve(){
  int n;
  std::cin>>n;
  vector<vector<int> > matrix(n+1, vector<int>(n+1,0));
  int counter = 0;
  int j1,j2,i;
  int tmp;
  int prevleft, prevtop, prevangular;
  int even, odd;
  for(i=1; i <= n; i++){
    for(int j=1; j <= n; j++){
      prevleft = matrix[i][j-1];
      prevtop = matrix[i-1][j];
      prevangular = matrix[i-1][j-1];
      std::cin>>tmp;
      matrix[i][j]= (tmp + prevleft + prevtop - prevangular)%2;
    }
  }
  for(j1=1; j1 <= n; j1++){
    for(j2=j1; j2<= n; j2++){
        even=0;
        odd=0;
        for(int i=1; i <= n; i++){
            if((matrix[i][j2]-matrix[i][j1-1]) % 2)
                odd++;
            else
                even++;
        }
        counter += odd*(odd-1)/2 + even*(even-1)/2 + even; 
    }
  }
  std::cout<<counter<<std::endl;
}