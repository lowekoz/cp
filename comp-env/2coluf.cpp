// https://codeforces.com/edu/course/2/lesson/7/2/practice/contest/289391/problem/J
// https://codeforces.com/contest/1537/problem/F
#ifndef __SKELETON
#include <bits/stdc++.h>
using namespace std;

#define ii pair<int, int>
#endif



const int N = 400005;
int repr[N]; // Group representative
int mag[N]; // Magnitude (size) of group
int parity[N]; // Parity of length of path from node to repr = parity[node]

void build(int noe){
    for(int i = 0; i < noe +1; i++){
        repr[i] = i;
        mag[i] = 1;
        parity[i] = 0; // Distance to repr (oneself) = 0
    }
}

/*
Core idea is to tweak normal DSU/UF find() so that it returns a nodes repr and its
parity to repr.
*/

// Specs. about node a -> returns: (repr to a, parity to repr from a)
ii find(int a){

    if (a == repr[a]){
        return {a,0}; // repr returns itself as repr and 0 as parity
    }
    ii info_from_above = find(repr[a]); // recurse
    repr[a] = info_from_above.first;
  
    // Want parity from currently investigating node to actual repr in parity[a]
    parity[a] = (parity[a] + info_from_above.second) % 2; // current node -> intermediary (old) repr -> actual repr
    // But in terms of parity, just simple odd/even sum check.
    // If everything is updated, and find is called - above node will have different parity
    // than myself, so parity[a] != parity from above.
    // also, if myself had more then one intermidiary (old) reprs, since the information is updated
    // top-down, it will always be as if ony two matters, me -> oldest of reprs -> actual repr
    
    // This is return val straight up parity wise - because we only move through
    // old reprs, info from above will correctly accumelate the parity of intermediary (old) repr -> actual repr
    // What is left is parity[a] which is node -> oldest repr
    return { repr[a], parity[a] }; // specs about my upstairs neighbour :)

}

// Returns True when graph is no longer 2 colrable
bool merge(int a, int b){
    ii piggod = find(a);
    ii burger = find(b);

    // if have same repr already (tree can never be non-2col) -> cycle 
    if (piggod.first == burger.first){
        // if they have same parity to repr -> exist in same blob, but still try to pair them
        if (piggod.second == burger.second){
            // ur facked mate
            return true;
        }
    }

    // Size heuristic
    if (mag[piggod.first] < mag[burger.first]){
        swap(piggod,burger);
    }

    parity[burger.first] = (burger.second + piggod.second + 1) % 2;
    // Tänk
    // repr -> new repr : parity to oneself = 0 + parity to oneself = 0 + added edge 1 => 1
    // repr -> new repr sub: parity to oneself = 0 + parity to new repr = piggod.second + added edge = 1 => 1 + piggod.second
    // repr sub -> new repr: parity to old repr = burger.second + parity to oneself = 0 + added edge 1 => 1 + burger.second
    // repr sub -> new repr sub: think backwards, p(from old repr to old repr sub) + added edge + p(new repr sub to new repr)
    // that is the new parity of old repr to new repr that will be "intemediary repr"

    // Burger getting gravity pulled
    mag[piggod.first] += mag[burger.first];
    mag[burger.first] = 0;
    repr[burger.first] = piggod.first;

    return false;
}


signed main(){

    int n,m; // nodes, edges respectively
    cin >> n >> m;
    build(n);
    int c= 0;
    while (m--){
        int f,t; cin >> f >> t;
        c += 1;
        if (merge(f,t)){
            // game over - no longer 2 col
            cout << c << endl;
            return 0;
        }
    }
    cout << "-1" << endl;


    return 0;
}
