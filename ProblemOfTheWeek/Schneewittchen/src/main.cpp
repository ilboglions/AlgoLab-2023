#include <iostream>
#include <vector>
#include <climits>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <map>
using namespace std;
typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
int n,m;
int costraint;
int num_dangerous;
void find_value(const vector<vector<int> > & tree, int root, vector<vector<int> > & minerals, const vector<int> & threshold, int lastdangerous, vector<vector<int> > & sondangerous){
    if(threshold[root] != -1){
        sondangerous[lastdangerous].push_back(root);
        lastdangerous = root;
    }
    for(int son: tree[root]){
        find_value(tree,son, minerals, threshold, lastdangerous, sondangerous);
        if(threshold[son] == -1){
            for(int i=0; i < m; i++){
                minerals[root][i] += minerals[son][i];}
        }
    }
}
void create_costraints(int start, Program & lp ,const vector<int> & threshold, vector<vector<int> > & son_dangerous, const vector<vector<int> >&  minerals, const unordered_map<int,int> & indices){
    int index = indices.find(start)->second;
    int costraint_total = costraint+m;
    for(int i=0; i < m; i++){
        lp.set_a(index*m + i, costraint+i, 2); lp.set_b(costraint+i, minerals[start][i]);
        lp.set_a(index*m + i, costraint_total, 2); 
    } 
    lp.set_b(costraint_total, threshold[start]);
    for(int son: son_dangerous[start]){
        int tmp = indices.find(son)->second;
        for(int i=0; i < m; i++){
            lp.set_a(tmp*m + i, costraint+i, -1); 
        }  
    }
    costraint = costraint_total+1;
    for(int son: son_dangerous[start])
        create_costraints(son, lp, threshold, son_dangerous, minerals, indices);
}
void solve(){
    cin>>n>>m;
    int u,v;
    vector <int> safety_threshold(n);
    vector <vector <int> > tree(n);
    vector < vector<int> > son_dangerous(n);
    vector < int> dangerous;
    vector <int> requirements(m); vector <int> supply(m); vector <int> price(m);
    vector < vector<int> > minerals(n, vector<int>(m));
    unordered_map < int, int> indices;

    for(int i=0; i < n; i++){
        cin>>safety_threshold[i];
        if(safety_threshold[i] != -1){
            indices.insert(make_pair(i, dangerous.size()));
            dangerous.push_back(i);
        }
        for(int j=0; j < m; j++) cin>>minerals[i][j];
    }
    num_dangerous = dangerous.size();
    for(int i=1; i < n; i++){ cin>>u>>v; tree[v].push_back(u);}
    for(int i=0; i < m; i++){ cin>>requirements[i]>>supply[i]>>price[i];}
    find_value(tree, 0 ,minerals, safety_threshold, 0, son_dangerous);
    for(int i=0; i < m; i++){ requirements[i] = max(0, requirements[i]-minerals[0][i]);}
    Program lp (CGAL::SMALLER, true, 0, false, 0); 
    costraint = 0;
    for(int son: son_dangerous[0])
        create_costraints(son, lp, safety_threshold,son_dangerous,minerals, indices);
    for(int i=0; i < m; i++){
        for(int son: son_dangerous[0]){
            int index = indices.find(son)->second;
            lp.set_a(index*m + i, costraint, 1); 
            lp.set_a(index*m + i, costraint+1, -1); 
        }
        lp.set_a((num_dangerous*m)+i, costraint, 1); lp.set_a((num_dangerous*m)+i, costraint+1, -1); 
        lp.set_b(costraint, requirements[i]); lp.set_b(costraint+1, -requirements[i]);
        costraint+=2;
        lp.set_a((num_dangerous*m)+i, costraint, 1); lp.set_b(costraint, supply[i]); costraint++;
        lp.set_c((num_dangerous*m)+i, price[i]);
    }
    Solution sol = CGAL::solve_linear_program(lp, ET());
    if(sol.is_infeasible() || !sol.solves_linear_program(lp) || !sol.is_optimal())
        cout<<"Impossible!\n";
    else{
        CGAL::Quotient<ET> res = sol.objective_value();
        int result = (int)std::floor(CGAL::to_double(res));
        cout<<result<<"\n";
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin>>t;
    while(t--){
        solve();
    }
}