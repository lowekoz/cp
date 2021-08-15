

#ifndef __SKELETON
#include <bits/stdc++.h>
using namespace std;
const int MOD = (int)1e9+7;
#endif

// MOD bounded at 1e18 to guarantee non overflow problems, long long typecast before printing !
struct Mint {
    static_assert(MOD < (long long)1e10, "Custom Mint console message: assert err, MOD greater than or eq. to 1e10");
private:
    // friend kan komma åt privata variabler för externa functioner
    long long value; // om vore public

    // explicit keyword på constructor kräver format: (Mint)x förutsatt att x är long long
    // implicit conversion Mint x = 5


public:
    Mint() {
        this->value = 0;
    }

    //implicit conversion, med denna constructor kan konverta long long till Mints.
    Mint(long long init_value) {
        if (init_value < 0 || init_value > MOD) init_value %= MOD;
        this->value = init_value;
    }

    // referens, ta via pointer och behöver dereferera -> operation som tar tid.
    //Struct kopierar bara fiedls, och vi har bara en long long så borde gå ca. lika snabbt
    friend bool operator==(const Mint a, const Mint b) {
        return a.value == b.value;
    }

    // förutsätter value inom [0..MOD-1]
    bool operator!=(const Mint rhs) {
        return !(*this == rhs); // kallar på den övre func. Notera att denna metod, kan vara smidig för uppbyggnad av större structs för att maintaina logik.
        // howev. då bör du ha referenser om många fält s.a. inte onädigt mycket kopierande
    }

    bool operator<(Mint rhs) {
        return value < rhs.value;
    }

    // eftersom += antar att vi ändrar på this->value, därför &
    Mint& operator+=(const Mint rhs) {
        this->value += rhs.value;
        if ((this->value >= MOD)) this->value -= MOD;
        return *this;
    }

    // eftersom båda är Mint:s så vet vi att det räcker med att adeera MOD en gång tops om negativ
    Mint& operator-=(const Mint rhs) {
        this->value -= rhs.value;
        if ((this->value < 0)) this->value += MOD;
        return *this;
    }

    Mint& operator*=(const Mint rhs) {
        this->value *= rhs.value; //1e9*1e9 is close to max ~ 9*1e18
        if ((this->value >= MOD)) this->value %= MOD;

        //assert(); // debug and correction purposes if want implemented

        return *this;
    }

    // kongruens ekvation a/b kong. x mod m, vill åt x som i a kong. bx (mod m) är b^{-1}*a
    Mint& operator/=(const Mint rhs) {
        return *this *= rhs.getInverse();
    }

    friend Mint pow(Mint a, long long p) {
        Mint ans = 1; assert(p >= 0);
        for (; p; p /= 2, a *= a) if (p & 1) ans *= a;
        return ans;
    }

    //friend Mint pow(Mint us, long long p); // i och med detta får pow från utsidan komma åt privata variabler


    // Fermats sats för att beräkna multiplicative modulär inversen
    // a^{p-1} kong. 1 mod p om p är prim.
    // finns bara en modulär invers förutsatt att gcd(MOD,a) = 1.
    //https://blogarithms.github.io/articles/2019-01/fermats-theorem
    Mint getInverse() const {
        //value have somehow recieved a factor MOD, which unables us from calculating mod inv.
        assert(value != 0); // inverse does not exist, happens when denominator in choose function contains the term MOD in its multiplication. n-k<MOD, k<MOD
        
        // using Fermats little theorem, NOTE THAT fermats little theorem gives a number cong. 1 % MOD, therefore -2
        // example, we have A cong. 6x mod 13, now fermats holds for 6 and 13 hence 6^12 is congruent to 1 mod 13
        // hence, A*6^11 is our answer for x, bc. 6*6^11 gives 1 cong, then * A.
        return pow(*this, MOD - 2);
    }


    // för att kunna printa till stdout - alt ta value till long long
    //friend ostream& operator<<
    /*operator long long() {
            return this->value;
    }*/ // implicit conversion tillåter andra template implementerade functioner att göra assumptions om vilka types vi nu kan ta, eftersom de bara kan implicit convertas
    // dvs. är egentligen en long long men long long kan tolkas som long double och därav overload problem?

    // måste dock long long () varje gång printa
    explicit operator long long() {
        return this->value;
    }

    // const i detta sammanhang declarerat efter (), säger att det du utför function på är const qualified, därav kommer aldrig att korrigera object.
    // icke const kan convertas till const och fortsatt som om inget ändrats...
    Mint operator-() const {
        return Mint(-value);
    }
    Mint& operator--() {
        return *this -= 1; // this är Mint för vilket -= är definerat
    }
    Mint& operator++() {
        return *this += 1; // this är Mint för vilket -= är definerat
    }

    // före eller efter?
    Mint operator++(int) { Mint temp; temp.value = value++; return temp; }
    Mint operator--(int) { Mint temp; temp.value = value--; return temp; }

    // OBS! difference in order is significant
    // int + Mint != Mint + int ground level
    friend Mint operator+(Mint a, const Mint& b) { return a += b; } // implicit vänsta värdet sig själv
    friend Mint operator-(Mint a, const Mint& b) { return a -= b; }
    friend Mint operator*(Mint a, const Mint& b) { return a *= b; }
    friend Mint operator/(Mint a, const Mint& b) { return a /= b; }


    static long long choose(long long a, long long b) {

        if (b > a) return 0;
        if (a < 0 || b < 0) return 0;

        unsigned long long n = 1;
        for (int i = 1; i < a + 1; i++) {
            n *= i;
            n %= MOD;
        }

        // täljare 0?
        unsigned long long denom = 1;
        for (int i = 1; i < b + 1; i++) {
            denom *= i;
            denom %= MOD;
        }
        for (int i = 1; i < a - b + 1; i++) {
            denom *= i;
            denom %= MOD;
        }

        Mint x(n);
        Mint y(denom);
        return (x.value * (long long)y.getInverse()) % MOD;
    }

    long long getValue() {
        return value;
    }
};