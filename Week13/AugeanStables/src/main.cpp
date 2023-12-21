#include <iostream>
#include <vector> 
#include <map>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#define HOURS 24

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
using namespace std;
void solve(){
    int n; cin>>n;
    vector<int> ks(n), ls(n), ms(n);
    vector<int> ph(HOURS+1),ah(HOURS+1);
    const int H1 = 0;
    const int H2 = 1;
    const int H3 = 2;
    vector<int> previous_a(HOURS+1,-1), previous_b(HOURS+1,-1);
    Program lp (CGAL::LARGER, false , 0, false, 0); 
    int f,c,a,p,ap; 
    for(int i=0; i < n; i++){
        cin>>f>>c>>ks[i]>>ls[i]>>ms[i];
        lp.set_b(i, max(f-c, 0));
    }
    for(int i=1; i <= HOURS; i++){
        cin>>a; ah[i] = a + ah[i-1];
    }
    for(int i=1; i <= HOURS; i++){
        cin>>p; ph[i] = p + ph[i-1];
    }
    lp.set_a(H1, n, -1); lp.set_b(n, -1);
    lp.set_a(H2, n+1, -1); lp.set_b(n+1, -1);
    lp.set_a(H3, n+2, -1); lp.set_b(n+2, -1);
    int minimum = 0;
    int maximum = 2 * HOURS -1;
    int mid, res= -1;
    bool found;
    //THIS IS JUST TO VERIFY IF IT'S ALREADY IMPOSSIBLE TO SATISFY THE COSTRAINT
    for(int j=0; j < n; j++){
      lp.set_a(H1,j, ks[j] + ah[HOURS]*ah[HOURS]); lp.set_a(H2,j,ls[j] + ph[HOURS]*ph[HOURS]); lp.set_a(H3,j, ms[j] + ah[HOURS]*ph[HOURS]);
    }
    Solution s = CGAL::solve_nonnegative_linear_program(lp, ET());
    if(s.is_infeasible()){
      cout<<"Impossible!\n";
      return;
    }
    //END OF DUMB OPTIMIZATION 
    while(minimum <= maximum){
        mid = (maximum + minimum)/2;
        found = false;
        int lim = min(mid, HOURS);
        for(int i=max(0, mid-HOURS); i <= lim; i++){
            if((previous_a[i] != -1 && previous_a[i] >= (mid-i)) ||
              (previous_b[mid-i] != -1 && previous_b[mid-i] >= i)) continue;
            a = ah[i]*ah[i]; 
            p = ph[mid-i]*ph[mid-i];
            ap =  ah[i] * ph[mid-i];
            for(int j=0; j < n; j++){
                lp.set_a(H1,j, ks[j] + a); lp.set_a(H2,j,ls[j] + p); lp.set_a(H3,j, ms[j] +ap);
            }
            Solution s = CGAL::solve_nonnegative_linear_program(lp, ET());
            if(!s.is_infeasible()) {found = true; break;}
            previous_a[i] = max(previous_a[i], mid-i);
            previous_b[mid-i] = max(previous_b[mid-i], i);
        }
        if(found){
            res = mid;
            maximum = mid-1;
        }
        else{
            minimum = mid+1;
        }
    }
    if(res == -1)
        cout<<"Impossible!\n";
    else
        cout<<res<<"\n";
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin>>t;
    while (t--) solve();
}