void z_algorithm(string& input) {
    int z[1000005];
    memset(z, 0, sizeof(z));
    z[0] = input.size();
    int L = 0, R = 1;
    for (int i = 1; i < input.size(); ++i) {
        if (R <= i || z[i-L] >= R-i) {
            int x = ((i>=R)? i: R);
            while (x < input.size() && input[x] == input[x-i]) x++;
            z[i] = x-i;
            if (i < x) {
                L = i; 
                R = x;
            }
        }
        else {
            z[i] = z[i-L];
        }
    }
}
