#include <iostream>
#include <string>
using namespace std;

int main(){
  int t;
  cin >>t;
  char tmp;
  int lena, lenb;
  while(t--){
    string a,b;
    cin >> a >> b;
    lena=a.length();
    lenb=b.length();
    cout << lena << " " << lenb <<endl;
    cout << a +b <<endl;
    for(int i=0; i < lena/2; i++){
      tmp=a[i];
      a[i] = a[lena-i-1];
      a[lena-i-1] = tmp;
    }
    for(int i=0; i < lenb/2; i++){
      tmp=b[i];
      b[i] = b[lenb-i-1];
      b[lenb-i-1] = tmp;
    }
    
    tmp = a[0];
    a[0]=b[0];
    b[0]=tmp;
    cout << a << " "<< b <<endl;
  }
}