// https://codeforces.com/blog/entry/62393

// FIXED RANDOM -> .count() is time since some mark in some tidsenhet, declared as static const will make it just that
// added nondetermenism!
// unordered_map<int, int, custom_hash> m;
struct custom_hash {
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        // HOWEV! if a = b mod m, then a+x = b+x mod m, so addition will not suffice -> XOR
        
        x ^= FIXED_RANDOM; // totally messes thing up : 49480813302700 runnning locally
        
        return x ^ (x >> 16); // make a smaller num with special regards to how massive itve become (avoid overflow)
        // becuase time was somewhere 35 bits lets say, removing top 16 will ensure not overflow
    }
};