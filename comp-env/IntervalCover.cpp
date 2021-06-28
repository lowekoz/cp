#ifndef __SEKELETON
#include <bits/stdc++.h>
using namespace std;
#endif

//verifierad mot https://open.kattis.com/problems/grass

//längsta längsta är inte nödv. bästa för givet interval A,B, kan finnas kortare
//förutsätter en osorterad lista med pair<typeX,typeX>

//om ta fram faktisk väg - skriv om varje pair med deras index till intevallet... reconstruct

template<typename T>
int cover_interval(vector<pair<T,T>>& v, T& start, T& end){
    //inclusive cover - not reconstructing

    sort(v.begin(),v.end()); //per default first item, else must type func urself

    //among possible, pick the one getting us furthest.
    T boundry_nxt = start;
    pair<T,T> best = v[0]; //initial
    v.push_back({INT32_MAX,INT32_MAX}); //for convinience in iter with alst el
    int ans = 0; //tänk varje gång vi spikar ett intervall -> skulle lag till den i lista - done

    for(int i = 0; i < (int)v.size()-1; i++){

        //gap in cover -> imposs
        if(v[i].first > boundry_nxt){
            return -1;
        }

        //better best
        if(v[i].second > best.second){
            best = v[i];
        }

        //check if done
        if(best.second >= end){
            ans += 1;
            return ans;
        }

        //nxt boundry
        if(v[i+1].first > boundry_nxt){
            boundry_nxt = best.second;
            ans += 1;
        }
    }

    return -1; //if didnt make it all the way but continuous seg
}
