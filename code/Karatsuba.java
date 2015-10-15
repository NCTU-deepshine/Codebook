static class Karatsuba{

    int maxHeight;
    long[][][] buffer; //h1, l1, m1, h2, l2, m2, hh, ll, mm

    Karatsuba(int maxHeight){
        this.maxHeight = maxHeight;
        buffer = new long[maxHeight][9][];
        for(int i=6;i<maxHeight;i++){
            for(int j=0;j<6;j++) buffer[i][j] = new long[(1<<i)>>1];
            for(int j=6;j<9;j++) buffer[i][j] = new long[1<<i];
        }
    }

    void multiply(long[] a, long[] b, long[] result, int depth){
        int size = 1<<depth, mid = size>>1;
        if(depth <= 5){
            Arrays.fill(result, 0);
            for(int i=0;i<a.length;i++){
                for(int j=0;j<b.length;j++) result[i+j] += a[i]*b[j];
            }
            return;
        }
        for(int i=0;i<mid;i++){
            buffer[depth][0][i] = a[i+mid];
            buffer[depth][1][i] = a[i];
            buffer[depth][2][i] = a[i+mid] + a[i];
            buffer[depth][3][i] = b[i+mid];
            buffer[depth][4][i] = b[i];
            buffer[depth][5][i] = b[i+mid] + b[i];
        }
        multiply(buffer[depth][0], buffer[depth][3], buffer[depth][6], depth-1);
        multiply(buffer[depth][1], buffer[depth][4], buffer[depth][7], depth-1);
        multiply(buffer[depth][2], buffer[depth][5], buffer[depth][8], depth-1);
        Arrays.fill(result, 0);
        for(int i=0;i<size;i++){
            result[i+size] += buffer[depth][6][i];
            result[i] += buffer[depth][7][i];
            result[i+mid] += buffer[depth][8][i] - buffer[depth][6][i] - buffer[depth][7][i];
        }
    }

}
