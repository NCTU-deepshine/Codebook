import java.io.*;
import java.util.*;

class SuffixArray{

    Entry[] entries;
    int[] rank;
    int length;

    SuffixArray(CharSequence S){
        length = S.length();
        rank = new int[length];
        entries = new Entry[length];
        int[] temp = new int[length];
        int counter;
        for (int i=0;i<length;i++){
            entries[i] = new Entry(i);
            entries[i].a = S.charAt(i) - 'a';
        }
        Arrays.parallelSort(entries);
        rank[entries[0].index] = temp[0] = counter = 0;
        for(int i=1;i<length;i++){
            if(entries[i].a != entries[i-1].a) counter++;
            rank[entries[i].index] = temp[i] = counter;
        }
        int step = 1;
        while(step < length){
            for(int i=0;i<length;i++){
                entries[i].a = temp[i];
                entries[i].b = rank[(entries[i].index+step)%length];
            }
            countingSort(entries);
            rank[entries[0].index] = temp[0] = counter = 0;
            for(int i=1;i<length;i++){
                if(entries[i].a != entries[i-1].a || entries[i].b != entries[i-1].b) counter++;
                rank[entries[i].index] = temp[i] = counter;
            }
            step <<= 1;
        }
    }
    
    void countingSort(Entry[] input){
        int[] counter = new int[length];
        Entry[] temp = new Entry[length];
        for(int i=0;i<length;i++) counter[input[i].b]++;
        for(int i=1;i<length;i++) counter[i] += counter[i-1];
        for(int i=length-1;i>=0;i--) temp[--counter[input[i].b]] = input[i];
        Arrays.fill(counter, 0);
        for(int i=0;i<length;i++) counter[temp[i].a]++;
        for(int i=1;i<length;i++) counter[i] += counter[i-1];
        for(int i=length-1;i>=0;i--) input[--counter[temp[i].a]] = temp[i];
    }

    class Entry implements Comparable<Entry>{

        int a, b, index;

        Entry(int index){
            this.index = index;
        }

        void assign(Entry rhs){
            a = rhs.a;
            b = rhs.b;
        }

        @Override
        public int compareTo(Entry rhs){
            return a - rhs.a;
        }

    }
    
}



