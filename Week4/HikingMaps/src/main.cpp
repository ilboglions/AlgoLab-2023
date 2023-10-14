#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/enum.h>
#include <vector>
#include<tuple>

using std::vector;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef std::tuple<P, P, P, P, P, P> T;

bool add(vector<int> &, vector<int> &);
bool remove(vector<int> &, vector<int> &);
int isinside(const P & , const T &);
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
    int m,n;
    int tmp, tmp2;
    int a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12;
    std::cin>>m>>n;
    vector<P> points(m);
    vector < vector <int> > covers(n, vector<int>(m-1, 0)); 
    for(int i=0;  i <m; i++){
        std::cin>>a1>>a2;
        points[i] = P(a1,a2);
    }
    int lim = m-1;
    for(int i=0; i < n; i++){
        std::cin>>a1>>a2>>a3>>a4>>a5>>a6>>a7>>a8>>a9>>a10>>a11>>a12;
        T triangle =  std::make_tuple(P(a1,a2), P(a3,a4), P(a5,a6), P(a7,a8), P(a9,a10), P(a11, a12)); 
        tmp = isinside(points[0], triangle);
        for(int j=0; j < lim; j++){
            tmp2 = isinside(points[j+1], triangle);
            covers[i][j] = std::min(tmp, tmp2);
            tmp = tmp2;
        }
    }
    vector<int> actual(m-1, 0);
    int right = 0;
    int left = 0;
    int min = n;
    while(right < n){
        if(add(actual, covers[right])){
            while(left < right && remove(actual, covers[left])){
                left++;
            }
            min= std::min(min, right-left +1 );
            left++;
        }
        right++;
    }
    std::cout<<min<<"\n";
}

int isinside(const P & point , const T & triangle){
    CGAL::Sign res;
    res = CGAL::orientation(std::get<0>(triangle), std::get<1>(triangle), point);
    if(res != CGAL::orientation(std::get<0>(triangle), std::get<1>(triangle), std::get<2>(triangle)) && res != CGAL::COLLINEAR){
        return 0;
    }
    res = CGAL::orientation(std::get<2>(triangle), std::get<3>(triangle), point);
    if(res != CGAL::orientation(std::get<2>(triangle), std::get<3>(triangle), std::get<4>(triangle)) && res != CGAL::COLLINEAR){
        return 0;
    }
    res = CGAL::orientation(std::get<4>(triangle), std::get<5>(triangle), point);
    if(res != CGAL::orientation(std::get<4>(triangle), std::get<5>(triangle), std::get<0>(triangle)) && res != CGAL::COLLINEAR){
        return 0;
    }
    return 1;
}

bool add(vector<int> & container, vector<int> & toadd){
    bool result = true;
    int size = container.size();
    for(int i=0; i < size; i++){
        container[i] += toadd[i];
        if(!container[i])
            result= false;
    }
    return result;
}
bool remove(vector<int> & container, vector<int> & toremove){
    bool result = true;
    int size = container.size();
    for(int i=0; i < size; i++){
        container[i] -= toremove[i];
        if(!container[i])
            result= false;
    }
    return result;
}