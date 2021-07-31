#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

#include <bits/stdc++.h>

using namespace std;

#define __SKELETON

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;

#define rep(i,a,b) for (int i = a; i < b; ++i)
#define repr(i,a,b) for (int i = a; i >= b; --i)
#define sz(x) (int)x.size()
#define trav(a, x) for (auto & a : x)
#define all(x) x.begin(), x.end()
#define mp make_pair
#define pb push_back
#define f first
#define s second

#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<class T> using pq = priority_queue<T>;

const double PI = 3.141592653589793238460;
const int MOD = (int)1e9 + 7;

// I/O
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream& os, const T_container& v) { os << '{'; string sep; for (const T& x : v) os << sep << x, sep = ", "; return os << '}'; }
template<typename A, typename B> ostream& operator<<(ostream& os, const pair<A, B>& p) { return os << '(' << p.first << ", " << p.second << ')'; }
#define is(x) cerr << #x << " is " << x << endl;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
template<typename T>
void u(vector<T>& inp_dst){
    for(auto& el : inp_dst){
        cin >> el;
    }
}

void run_case(){

}

int main(){
    fastio;

    int tests = 1; 
    cin >> tests; // DEL
    while(tests--){
        run_case();
    }
    return 0;
}