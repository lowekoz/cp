#ifndef __SKELETON
#include <bits/stdc++.h>
using namespace std;
#endif

bool primeCheck(int p){
    //actually unnecessary for sieve
    if(p == 2){
        return true;
    }
    int i = 3;

    //gör sökning <= sqrt p, om delare minst en i det området
    while(pow(i,2) <= p){
        if(p % i == 0){
            return false;
        }
        i += 2;
    }
    return true;
}


void primeSieve(int max, vector<int>& primes){
    //ta fram primes upp till inkluderat max
    vector<bool> sieve(max+1,1);
    int num = 2;
    while(num <= max){
        if(!(sieve[num])){
            //om markerad false i sieve
            //-> inte prime gör inget
        }else{

            primes.push_back(num);
            //behöver inte cheka om prim ju, redan markerat alla med true.
            for(int i = num; i <= max; i+= num){
                sieve[i] = 0;
            }
            /*
            if(primeCheck(num)){
                //om prime -> uppdatera sieve
                for(int i = num; i <= max; i+= num){
                    sieve[i] = 0;
                }
            }
            */
        }
        num += 1;
    }
}

void generateFactors(int p, map<int,int>& factors_to_p, vector<int>& PRIMES){
    int i = 0; //iter genom primes -> se till det finns primes >= sqrt av p.
    while(p != 1){
        //samtidigt som hittar faktorer reducera p
        if (pow(PRIMES[i],2) > p){

            //om kvarstående e prime, ex: 10 -> 5, vid nästa iter 3*3 = 9, men p = 5 och ej 1
            if(p > 1){

                if(factors_to_p.count(p)){
                    factors_to_p[p] += 1;
                }else{
                    factors_to_p[p] = 1;
                }
            }

            return;
        }

        while(p % PRIMES[i] == 0){
            p /= PRIMES[i];

            if(factors_to_p.count(PRIMES[i])){
                factors_to_p[PRIMES[i]] += 1;
            }else{
                factors_to_p[PRIMES[i]] = 1;
            }

        }
        i += 1;
    }
    return;
}
