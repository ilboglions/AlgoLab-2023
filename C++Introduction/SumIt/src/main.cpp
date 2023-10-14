#include <iostream>
using namespace std;

int main(){
  int t;
  int temp;
  cin >> t;
  while(t--){
    int n;
    cin>>n;
    int sum=0;
    while(n--){
      cin >> temp;
      sum += temp;
    }
    cout << sum << endl;
  }
}