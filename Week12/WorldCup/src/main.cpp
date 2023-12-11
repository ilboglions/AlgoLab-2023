#include <iostream>
#include <vector>
#include <unordered_set>
#include <utility>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>
using namespace std;
typedef long IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef pair < double, double> point;

double squared_distance(const point & a, const point & b){
    return (a.first - b.first)*(a.first - b.first) + (a.second - b.second)*(a.second - b.second);
}
int count_lines (const unordered_set<int> & a, const unordered_set<int> &b){
    int count = 0;
    for(int elem: a)
        if(b.find(elem) == b.end())
            count++;
    for(int elem: b)
        if(a.find(elem) == a.end())
            count++;
    return count;
}
void solve(){
    int n,m,c; cin>>n>>m>>c;
    Program lp (CGAL::SMALLER, false, 0, false, 0); 
    double x,y,r;
    int s,a, d,u;
    double squared_radius;
    vector< point > warehouse(n);
    vector< point > stadiums(m);
    vector < unordered_set<int> > contour_lines(n+m);
    vector < vector<double> > revenues(m, vector<double>(n,0));
    for(int i=0; i < n; i++){
        cin>>x>>y>>s>>a;
        warehouse[i] = make_pair(x,y);
        lp.set_b(i, s);  //DISEQUATIONS FROM 0 TO N-1th RESTRICT AMOUNT OF BEER EXPORTED FROM EACH WAREHOUSE
        for(int j=0; j < m; j++){
            lp.set_l((n*j)+i, true, 0); //THE QUANTITY EXPORTED FROM THE i WAREHOUSE TO THE j STADIUM CANNOT BE NEGATIVE
            lp.set_a((n*j)+i , i , 1); //THE i-th DISEQUATION CHECKS THAT THE TOTAL AMOUNT OF BEER EXPORTED FROM THE WAREHOUSE DOESN'T EXCEED THE SUPPLY
            lp.set_a((n*j)+i , n+j, 1); //FROM THE Nth TO THE N+M-1th DISEQUATION WE CHECK THAT THE TOTAL AMOUNT OF BEER TO THE STADIUM IS LOWER/EQUAL THAN THE DEMAND
            lp.set_a((n*j)+i, n+m+j, -1); //FROM THE N+Mth TO THE N+M+Mth DISEQUATION WE CHECK THAT THE TOAL AMOUNT OF BEER IS GREATER/EQUAL THAN THE DEMAND
            lp.set_a((n*j)+i , n + 2 * m + j, a); //FROM THE N+2Mth to the N+3Mth DISEQUATION WE CHECK THAT THE TOTAL AMOUNT OF ALCOHOL TO EACH STADIUM DOESN'T EXCEED THE MAXIMUM
        }
    }
    for(int i=0; i < m; i++){
        cin>>x>>y>>d>>u;
        stadiums[i] = make_pair(x,y);
        lp.set_b(n+i, d); //LIMIT ON THE DEMAND
        lp.set_b(n+m+i, -d); //LIMIT ON THE DEMAND
        lp.set_b(n+ 2*m + i, u*100); //UPPER LIMIT FOR ALCOHOL
    }
    for(int i=0; i < n; i++){
        for(int j=0; j < m; j++){
            cin>>revenues[j][i]; revenues[j][i] = revenues[j][i]*100;} //COMPUTE REVENUE IN CENTS PER UNIT OF ALCOHOL FROM WAREHOUSE i to STADIUM j
    }
    for(int i=0; i < c; i++){ //FOR EACH CONTOUR LINE WE CHECK IF EACH WAREHOUSE/STADIUM IS INSIDE OR NOT
        cin>>x>>y>>r; squared_radius = r*r; 
        point tmp = make_pair(x,y);
        for(int j=0; j < n; j++){
            if(squared_distance(warehouse[j], tmp) < squared_radius){
                contour_lines[j].insert(i);
            }
        }
        for(int j=0; j < m; j++){
            if(squared_distance(stadiums[j], tmp) < squared_radius){
                contour_lines[n+j].insert(i);
            }
        }
    }
    for(int i=0; i < m; i++){
        for(int j=0; j < n; j++){
            revenues[i][j] -= ((double)count_lines(contour_lines[i+n], contour_lines[j]));
            lp.set_c((n*i)+j, -revenues[i][j]);
        }
    }
    Solution sol = CGAL::solve_linear_program(lp, ET());
    if(sol.is_infeasible() || !sol.solves_linear_program(lp) || !sol.is_optimal())
        std::cout<<"RIOT!\n";
    else{
        CGAL::Quotient<ET> divide = 100;
        CGAL::Quotient<ET> res = sol.objective_value();
        long result = (long)std::floor(-CGAL::to_double((res.numerator()/(res.denominator()*divide))));
        std::cout<<result<<"\n";
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
