import java.util.*;

class HashTable{
    
    int[] key;
    //Object[] content;
    SimpleTabulationHash hash;
    
    HashTable(long universeSize, int sizeBit){
        key = new int[1<<sizeBit];
        //content = new Object[1<<sizeBit];
        Arrays.fill(key, -1);
        hash = new SimpleTabulationHash(universeSize, sizeBit);
    }
    
    //returns index if found, -1 if not
    int contains(int x){
        int hashValue = hash.hashCode(x);
        for(int i=hashValue;;i++){
            if(i == key.length) i = 0;
            if(key[i] == -1) return -1;
            if(key[i] == x) return i;
        }
        return -1;
    }
    
    void add(int x){
        int hashValue = hash.hashCode();
        for(int i=hashValue;;i++){
            if(i == key.length) i = 0;
            if(key[i] == -1){
                key[i] = x;
                return;
            }
        }
    }
    
}

class SimpleTabulationHash{

    final static int bit = 16, mask = 1<<bit;    
    int C;
    int[][] table;
    
    SimpleTabulationHash(long universeSize, int tableBit){ // table size is givin in 2^n
        C = 0;
        while(universeSize > 0){
            universeSize /= mask;
            C++;
        }
        table = new int[C][mask];
        Random random = new Random():
        int cutoff = 32-tableBit;
        for(int i=0;i<C;i++){
            for(int j=0;j<mask;j++) table[i][j] = random.nextInt()>>cutoff;
        }
    }
    
    int hashCode(long x){
        int result = 0;
        for(int i=0;i<C;i++){
            result ^= table[i][x&mask];
            x >>= 16;
        }
        return result;
    }
    
}
