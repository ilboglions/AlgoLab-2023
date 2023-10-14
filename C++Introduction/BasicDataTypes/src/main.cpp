///1
#include <iostream>
#include <iomanip>
using namespace std;


int main(){
  int t;
  cin >> t;
  while(t--){
    int a;
    long long b;
    string c;
    double d;
    cout << setprecision(2);
    cin >> a >> b >> c >> d;
    cout << a <<" ";
    cout << b <<" ";
    cout << c << " ";
    cout << fixed << d << endl;
  }
}