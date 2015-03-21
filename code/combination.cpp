const long long MOD = 1e9+7;
const int MAX = 1e5+1;

typedef long long T;
T inverse(T mod, T b) { /* return b^(-1) mod a */
    T k[2][2], n[2][2], u1, u2;

    k[0][0] = k[1][1] = 1;
    k[0][1] = k[1][0] = 0;
    
    u1 = mod, u2 = b;
    
    while (u2) {
        T div = u1/u2;
        T remind = u1%u2;
        
        n[0][0] = k[1][0];
        n[0][1] = k[1][1];
        n[1][0] = k[0][0] - k[1][0]*div;
        n[1][1] = k[0][1] - k[1][1]*div;
        
        for (T i = 0; i < 2; ++i) {
            for (T j = 0; j < 2; ++j) {
                k[i][j] = n[i][j];
            }
        }
        u1 = u2;
        u2 = remind;
    }

    if (k[0][1] < 0) k[0][1] += mod;
    return k[0][1];
}

T C(T n, T m, T mod) {
    if (m < 0) return 0;
    if (n < m) return 0;
    T ans = 1;
    T base = min(n-m, m);

    for (T i = 0; i < base; ++i) {
        ans = ans*(n-i)%mod;
    }

    T inv = 1;
    for (T i = 1; i <= base; ++i) {
        inv = inv*i%mod;
    }
    return ans*inverse(mod, inv)%mod;
}
