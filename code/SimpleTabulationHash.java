import java.util.*;

class HashTable{
    
    long[] key;
    Main.Entry[] content;
    SimpleTabulationHash hash;
    
    HashTable(long universeSize, int sizeBit){
        key = new long[1<<sizeBit];
        content = new Main.Entry[1<<sizeBit];
        Arrays.fill(key, -1);
        hash = new SimpleTabulationHash(universeSize, sizeBit);
    }
    
    //returns index if found, -1 if not
    int containsKey(long x){
        int hashValue = hash.hashCode(x);
        for(int i=hashValue;;i++){
            if(i == key.length) i = 0;
            if(key[i] == -1) return -1;
            if(key[i] == x) return i;
        }
    }
    
    void put(long x, Main.Entry entry){
        int hashValue = hash.hashCode(x);
        for(int i=hashValue;;i++){
            if(i == key.length) i = 0;
            if(key[i] == -1){
                key[i] = x;
                content[i] = entry;
                return;
            }
        }
    }
    
    Main.Entry get(long x){
        return content[contains(x)];
    }
    
}

class SimpleTabulationHash{

    final static int bit = 16, mask = (1<<bit)-1;    
    int C;
    int[][] table;
    
    SimpleTabulationHash(long universeSize, int tableBit){ // table size is givin in 2^n
        C = 0;
        while(universeSize > 0){
            universeSize >>= bit;
            C++;
        }
        table = new int[C][mask+1];
       // System.err.println("C = "+C);
        Random random = new Random();
        int cutmask = (1<<tableBit)-1;
        //System.err.println("tablebit: "+tableBit+", cutmask : "+cutmask);
        for(int i=0;i<C;i++){
            for(int j=0;j<=mask;j++) table[i][j] = random.nextInt()&cutmask;
        }
    }
    
    int hashCode(long x){
        int result = 0;
        for(int i=0;i<C;i++){
            result ^= table[i][(int)(x&mask)];
            x >>= bit;
        }
        return result;
    }
    
}
