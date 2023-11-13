#include <iostream>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <vector>
#include <utility>
using std::pair;
using std::vector;
using std::make_pair;
typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
void solve();

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int t;
    std::cin>>t;
    while(t--){
        solve();
    }
}

void solve(){
    int n,m,h,w;
    std::cin>>n>>m>>h>>w;
    long x,y;
    long leftelem, rightelem;
    long posu, posd;
    int constraints = 0;
    long perimeter = -2*(h+w);
    long b_l, b_v;
    vector < pair<long,long> > old_posters(m);
    vector < pair<long,long> > new_posters(n);
    Program lp (CGAL::SMALLER, true, 1, false, 0);
    for(int i=0; i < n; i++){
        std::cin>>x>>y;
        new_posters[i] = make_pair(x,y);
    }
    for(int i=0; i < m; i++){
        std::cin>>x>>y;
        old_posters[i] = make_pair(x,y);
    }
    for(int i=0; i < n; i++){
        for(int j=i+1; j < n; j++){
            if(new_posters[i].first < new_posters[j].first){
                leftelem=i;
                rightelem=j;
            }
            else{
                leftelem=j;
                rightelem=i;
            }
            posu = w*(new_posters[rightelem].second - new_posters[leftelem].second) +  h*(new_posters[rightelem].first - new_posters[leftelem].first);
            posd = w*(new_posters[rightelem].second - new_posters[leftelem].second) -  h*(new_posters[rightelem].first - new_posters[leftelem].first);
            if(posu >= 0 && posd < 0){
                lp.set_a(leftelem,constraints, w);
                lp.set_a(rightelem,constraints, w);
                lp.set_b(constraints, 2*(new_posters[rightelem].first-new_posters[leftelem].first));
            }
            else{
                lp.set_a(leftelem,constraints, h);
                lp.set_a(rightelem,constraints, h);
                lp.set_b(constraints, std::abs(2*(new_posters[rightelem].second-new_posters[leftelem].second)));
            }
            constraints++;
        }
        b_l=LONG_MAX;
        b_v=LONG_MAX;
        for(int j=0; j < m; j++){
            if(new_posters[i].first < old_posters[j].first){
                posu = w*(old_posters[j].second - new_posters[i].second) +  h*(old_posters[j].first - new_posters[i].first);
                posd = w*(old_posters[j].second - new_posters[i].second) -  h*(old_posters[j].first - new_posters[i].first);
            }
            else{
                posu = w*(new_posters[i].second - old_posters[j].second ) +  h*(new_posters[i].first-old_posters[j].first);
                posd = w*(new_posters[i].second - old_posters[j].second ) -  h*(new_posters[i].first-old_posters[j].first);
            }
            if(posu >=0 && posd < 0){
                b_l = std::min(2*std::abs(old_posters[j].first-new_posters[i].first)-w, b_l);
            }
            else{
                b_v = std::min(2*std::abs(old_posters[j].second-new_posters[i].second)-h, b_v);
            }
        }
        if(b_l != LONG_MAX){
            lp.set_a(i,constraints, w);
            lp.set_b(constraints, b_l);
            constraints++;
        }
        if(b_v != LONG_MAX){
            lp.set_a(i,constraints, h);
            lp.set_b(constraints, b_v);
            constraints++;
        }
        lp.set_c(i, perimeter);
    }
    Solution s = CGAL::solve_linear_program(lp, ET());
    CGAL::Quotient<ET> res = s.objective_value();
    long result = -std::floor(CGAL::to_double(res));
    std::cout<<result<<"\n";
}