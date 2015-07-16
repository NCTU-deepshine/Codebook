int modCombine(int x,int a,int y,int b){//ans mod x = a,ans mod y =b;

    int ans = x * (x^(-1))(mod(y)) * b + y * (y^(-1))(mod(x)) * a;
    ans %=(x*y);
    return ans;
}
