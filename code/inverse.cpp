long long inverse(long long b, long long mod=MOD) {
    long long k[2][2], n[2][2], u1, u2;

    k[0][0] = k[1][1] = 1;
    k[0][1] = k[1][0] = 0;

    u1 = mod, u2 = b;

    while (u2) {
        long long div = u1/u2;
        long long remind = u1%u2;

        n[0][0] = k[1][0];
        n[0][1] = k[1][1];
        n[1][0] = k[0][0]-k[1][0]*div;
        n[1][1] = k[0][1]-k[1][1]*div;

        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                k[i][j] = n[i][j];
            }
        }

        u1 = u2;
        u2 = remind;
    }
    while (k[0][1] < 0) k[0][1] += mod;

    if(((k[0][1]*(b%mod))%mod+mod)%mod !=1ll) printf("%lld^-1 doesn't exist under mod %lld\n",b,mod);

    return k[0][1];
}
