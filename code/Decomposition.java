static class Decomposition{

    Map<BigInteger, Integer> prime;
    Random random;

    Decomposition(String x){
        prime = new HashMap<>();
        random = new Random();
        BigInteger in = new BigInteger(x);
        int twos = 0;
        while(!in.testBit(0)){
            in = in.shiftRight(1);
            twos++;
        }
        if(twos > 0) prime.put(BigInteger.valueOf(2), twos);
        peel(in);
    }

    void peel(BigInteger x){
        System.out.println("peel "+x);
        if(x.equals(BigInteger.ONE)) return;
        if(x.isProbablePrime(100)){
            Integer temp = prime.put(x, 1);
            if(temp!=null) prime.put(x, temp+1);
            return;
        }
        BigInteger a, b, c, next;
        do{
            a = b = new BigInteger(x.bitLength()+5, random).mod(x);
            c = new BigInteger(x.bitLength()+5, random).mod(x);
            if(c.equals(BigInteger.ZERO)) c = BigInteger.ONE;
            do{
                a = f(a, c, x);
                b = f(f(b, c, x), c, x);
                next = x.gcd(a.subtract(b).abs());
            }while(next.equals(BigInteger.ONE));
        }while(next.equals(x));
        peel(next);
        peel(x.divide(next));
    }

    BigInteger f(BigInteger x, BigInteger c, BigInteger n){
        return x.multiply(x).add(c).mod(n);
    }

}
