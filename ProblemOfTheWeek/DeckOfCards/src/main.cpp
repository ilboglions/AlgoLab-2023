#include <iostream>
#include <vector>
#include <cmath>

using std::vector;

void solve();

int main (){
    int t;
    std::cin>>t;
    while(t--){
        solve();
    }
}

void solve(){
    int n,k;

    std::cin>>n>>k;
    vector<int> deck(n);
    int left=0;
    int right=0;
    int sum;
    int leftres=0;
    int rightres=0;
    
    for(int i=0; i < n; i++){
        std::cin>>deck[i];
    }
    sum = deck[0];
    int mindifference = abs(sum - k);
    for(right=1; right < n && sum != k; right++){
        sum += deck[right];
        if( abs(sum-k) < mindifference){
            leftres=left;
            rightres= right;
            mindifference = abs(sum-k);
        }
        else{
            while(left < right && sum > k){
                sum -= deck[left];
                left++;
                if(abs(sum-k) < mindifference){
                    rightres=right; 
                    leftres = left;
                    mindifference = abs(sum-k);
                }
            }
        }   
    }
    std::cout<<leftres<<" "<<rightres<<"\n";
    
}