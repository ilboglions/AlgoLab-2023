#include <iostream>
#include <vector>


using std::vector;
void solve();

int main(){
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin>>t;
    while(t--){
        solve();
    }
}

void solve(){
    int n,m;
    int x,y;
    std::cin>>n>>m;
    vector<vector<int> > matrix(n);
    int r,b;
    std::cin>>r>>b;
    r--;
    b--;
    for(int tmp=0; tmp < m; tmp++){
        std::cin>>x>>y;
        matrix[x-1].push_back(y-1);
    } 

    vector<int> evendistance(n, 100000);
    vector<int> odddistance(n, -1);
    evendistance[n-1]= 0;
    odddistance[n-1]=0;
    for(int i=n-2; i >= 0; i--){
        for(int j: matrix[i]){
            if(evendistance[i] >= odddistance[j]+1)
                evendistance[i] = odddistance[j]+1;
            if(odddistance[i] <= evendistance[j]+1)
                odddistance[i] = evendistance[j]+1;         
        }
    }    
    if(evendistance[b] < evendistance[r]){
        std::cout<<1<<"\n";
    }
    else if(evendistance[b] > evendistance[r]){
        std::cout<<0<<"\n";
    }
    else if(evendistance[b]==evendistance[r] && evendistance[b]%2){
        std::cout<<0<<"\n";
    }
    else{
        std::cout<<1<<"\n";
    }

}