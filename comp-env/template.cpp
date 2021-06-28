#include <bits/stdc++.h>
using namespace std;
#define __SKELETON
#define rep(i,a,b) for (int i = a; i < b; ++i)
#define sz(x) (int)x.size()
#define trav(a, x) for (auto & a : x)
#define all(x) x.begin(), x.end()
#define pb push_back
#define ff first
#define ss second
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef long long ll;
typedef vector<ll> vll;
const double PI = 3.141592653589793238460;
const int MOD = (int)1e9 + 7;
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream& os, const T_container& v) { os << '{'; string sep; for (const T& x : v) os << sep << x, sep = ", "; return os << '}'; }
template<typename A, typename B> ostream& operator<<(ostream& os, const pair<A, B>& p) { return os << '(' << p.first << ", " << p.second << ')'; }
#define is(x) cerr << #x << " is " << x << endl;
template<typename T>
void u(vector<T>& inp_dst){
    for(auto& el : inp_dst){
        cin >> el;
    }
}

void run_case(){

}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tests; cin >> tests;

    while(tests--){
        run_case();
    }
}
