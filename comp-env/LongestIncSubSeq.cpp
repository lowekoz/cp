#ifndef __SKELETON
#include <bits/stdc++.h>
using namespace std;
#endif

/*
Decscription: O(nlogn) longest (strctly) inc. sequence

Core idea: arr of pairs - initial sequence el with its original index 
and sort by el in increasing order.

Maintain max segmenttree. Go thru sorted arr left to right.
This order assures that smaller elements gets processed prior, and will be available for
upcomining larger elements, hence with regards to magnitude all elements in the segtree is 
adequate to the nxt. 
Finding max sequence len by only looking to the left of current el idx 
assures current el comes after in order in original seq.

Reconstruct path by saving cameFrom array; When evaluating an element, save which 
original idx we are evaluating in the node.
That way, for later elements that are evaluated, fetching the node conatining max len, we also
have what prior index was evaluated to create this max-len, so for the element we are evaluating
now we can store cameFrom[currentIdx] = node.evaluatedIdx

Extra: Skip preprocess if only increasing sequence, no need to scatter. unnecessary long long!
Status: tested. https://liu.kattis.com/problems/longincsubseq

TODO - ta bort scatter() call om ej Strictly inc.
TODO - IncreasingSeq()
*/


struct nod {
    long long max_len;
    long long my_position;

    nod() : max_len(0), my_position(-1) {};
};

struct SegmentTree {
    long long bp;
    vector<nod> heap;
    vector<long long> cameFrom; //to reconstruct path

    SegmentTree(long long len) {
        bp = pow(2, ceil(log2(len)));

        for (long long i = 0; i < 2 * bp; i++) {
            heap.push_back(nod()); 
        }
        for (long long i = 0; i < len; i++) {
            cameFrom.push_back(-1);
        }

        //build(); nothing to build really
    }

    array<long long, 2> fetch(long long l, long long r) {
        //get {max_len, priorIdx}
        l += bp;
        r += bp;
        long long ans = 0; //mx_len
        //viktig 
        long long cameFrom = -1; //also in best node we find
        while (l <= r) {
            if (l & 1) {
                if (ans < max(ans, heap[l].max_len)) {
                    ans = max(ans, heap[l].max_len);
                    cameFrom = heap[l].my_position;
                }
                l += 1;
            }
            if (!(r & 1)) {
                if (ans < max(ans, heap[r].max_len)) {
                    ans = max(ans, heap[r].max_len);
                    cameFrom = heap[r].my_position;
                }
                r -= 1;
            }
            r /= 2;
            l /= 2;
        }
        return { ans,cameFrom };
    }

    void update(long long idx) {
        //evaluate idx
        long long hidx = idx + bp;
        array<long long, 2> res = fetch(0, idx - 1); //mx,prior el in seq.
        heap[hidx].my_position = idx;
        heap[hidx].max_len = res[0] + 1; //best plus myself
         
        //all we need to reconstruct, bästa tidigare sekvens att välja på 
        cameFrom[idx] = res[1];

        //update seg tree
        while (hidx > 1) {
            hidx /= 2;
            if (heap[hidx << 1].max_len >= heap[hidx << 1 | 1].max_len) {
                heap[hidx].max_len = heap[hidx << 1].max_len;
                heap[hidx].my_position = heap[hidx << 1].my_position;
            }
            else {
                heap[hidx].max_len = heap[hidx << 1 | 1].max_len;
                heap[hidx].my_position = heap[hidx << 1 | 1].my_position;
            }
        }
    }

    //debug
    void print_tree() {
        //1, 2-3, 4-7 osv.
        long long startIdx = 1;
        long long inc = 1;
        while (startIdx <= bp) {
            for (long long i = 0; i < inc; i++) {
                cout << " ( " << heap[startIdx + i].max_len << " " << heap[startIdx + i].my_position << " ) ";
            }
            cout << endl;
            startIdx += inc;
            inc = inc << 1;
        }
    }
};

//for strictly increasing, scale up space for same value elements
void scatter(vector<long long>& v) {
    map<long long, long long> met_so_far;
    long long f = 100001; //buf
    //notera bakifrån fram ordning s.a. större -> mindre för samma el x
    for (long long i = (long long)v.size() - 1; i >= 0; i--) {
        long long current = v[i];
        if (met_so_far.count(current) == 0) {
            met_so_far[current] = 1;
        }
        else {
            met_so_far[current] += 1;
        }

        v[i] *= f;
        v[i] += met_so_far[current] - 1;
    }
}

bool mySort(pair<long long, long long>& r, pair<long long, long long>& rr) {
    //true när ska r komma före rr
    if (r.first < rr.first) return true;
    return false;
}

void IncreasingSeq(vector<long long>& v) {
    scatter(v); //@@@@@Strictly! remove if only increasing seq
    vector<pair<long long, long long>> with_orig_idx;
    for (long long i = 0; i < (long long)v.size(); i++) {
        with_orig_idx.push_back({ v[i],i });
    }
    sort(with_orig_idx.begin(), with_orig_idx.end(), mySort);
    SegmentTree t((long long)v.size());
    for (auto& el : with_orig_idx) {
        //val , idx
        t.update(el.second); //evaluate each el
    }

    //reconstruct path
    vector<long long> path(t.heap[1].max_len); //var mx len ligger
    long long idx = t.heap[1].my_position;
    long long back_point = t.heap[1].max_len - 1;
    while (idx != -1) {
        path[back_point] = idx;
        idx = t.cameFrom[idx];
        back_point -= 1;
    }
    //optional how to handle output
    cout << t.heap[1].max_len << "\n";
    for (auto& el : path) {
        cout << el << " ";
    }cout << "\n";
}
