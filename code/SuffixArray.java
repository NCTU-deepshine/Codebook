import java.io.*;
import java.util.*;

public class Main{

    static int n, m, k;
    static ArrayList<Edge> edgesA, edgesB;
    static DisjointSet[][][] now, next;
    final static boolean GP = true;

    public static void main(String[] args){
        Scan scan = new Scan();
        while(true){
            n = scan.nextInt();
            m = scan.nextInt();
            k = scan.nextInt();
            if(n==0 && m==0 && k==0) break;
            edgesA = new ArrayList<Edge>();
            edgesB = new ArrayList<Edge>();
            int counterA = 0, counterB = 0;
            for(int i=0;i<m;i++){
                int u = scan.nextInt()-1;
                int v = scan.nextInt()-1;
                int c = scan.nextInt();
                int p = 0;
                if(GP) p = scan.nextInt();
                String which = scan.next();
                if(which.charAt(0) == 'A'){
                    edgesA.add(new Edge(u, v, c, p));
                    counterA++;
                }
                else{
                    edgesB.add(new Edge(u, v, c, p));
                    counterB++;
                }
            }

            now = new DisjointSet[counterA+1][counterB+1][k+1];
            next = new DisjointSet[counterA+1][counterB+1][k+1];
            for(int i=0;i<=counterA;i++){
                for(int j=0;j<=counterB;j++){
                    for(int l=0;l<=k;l++) next[i][j][l] = null;
                }
            }
            next[0][0][0] = new DisjointSet(n);
            Collections.sort(edgesA);
            Collections.sort(edgesB);

            for(int connect=1;connect<n;connect++){
                System.err.println("connected : "+connect);
                DisjointSet[][][] temp = now;
                now = next;
                next = temp;
                for(int i=0;i<=counterA;i++){
                    for(int j=0;j<=counterB;j++){
                        for(int l=0;l<=k;l++) next[i][j][l] = null;
                    }
                }
                for(int a=0;a<=counterA;a++){
                    for(int b=0;b<=counterB;b++){
                        for(int l=0;l<=k;l++){
                            System.err.println(a+" "+b+" "+l);
                            DisjointSet nowSet = now[a][b][l], nextSet;
                            Edge nowEdge = null;
                            if(now[a][b][l] == null) continue;
                            //choose company A
                            if(l < k){
                                int i;
                                for(i=a;i<counterA;i++){
                                    nowEdge = edgesA.get(i);
                                    if(!nowSet.isLinked(nowEdge)) break;
                                }
                                if(i < counterA){
                                    if(next[i+1][b][l+1]==null || next[i+1][b][l+1].cost > nowSet.cost+nowEdge.c){
                                        System.err.printf("edge chosen : %d -> %d, %d%n", nowEdge.u, nowEdge.v, nowEdge.c);
                                        nextSet = next[i+1][b][l+1] = new DisjointSet(nowSet);
                                        nextSet.union(nowEdge);
                                        System.err.printf("chart : next[%d][%d][%d] = %d%n", i+1, b, l+1, next[i+1][b][l+1].cost);
                                    }
                                }
                            }
                            //choose company B
                            boolean debug = connect==5;
                            if(true){
                                int i;
                                for(i=b;i<counterB;i++){
                                    nowEdge = edgesB.get(i);
                                    if(!nowSet.isLinked(nowEdge)) break;
                                }
                                if(debug) System.err.println("DEBUGGGGG! i = "+i);
                                if(i < counterB){
                                    if(debug) System.err.println("DEBUGGGGG! cost = "+(nowSet.cost+nowEdge.c));
                                    if(next[a][i+1][l]==null || next[a][i+1][l].cost > nowSet.cost+nowEdge.c){
                                        System.err.printf("edge chosen : %d -> %d, %d%n", nowEdge.u, nowEdge.v, nowEdge.c);
                                        nextSet = next[a][i+1][l] = new DisjointSet(nowSet);
                                        nextSet.union(nowEdge);
                                        System.err.printf("chart : next[%d][%d][%d] = %d%n", a, i+1, l, next[a][i+1][l].cost);
                                    }
                                }
                            }
                        }
                    }
                }    
            }
            //System.err.println("counter A : "+counterA+", counterB : "+counterB+", k : "+k); 
            int result = Integer.MAX_VALUE;
            for(int a=0;a<=counterA;a++){
                for(int b=0;b<=counterB;b++){
                    for(int l=0;l<=k;l++){
                        if(next[a][b][l] == null) continue;
                        System.err.println("found solution : "+next[a][b][l].cost);
                        result = Math.min(result, next[a][b][l].cost);   
                    }
                }
            }
            if(result == Integer.MAX_VALUE) System.out.println(-1);
            else System.out.println(result);
        }
    }

    static class DisjointSet{
        int[] dset;
        int cost;

        DisjointSet(int n){
            dset = new int[n];
            Arrays.fill(dset, -1);
            cost = 0;
        }

        DisjointSet(DisjointSet rhs){
            dset = Arrays.copyOf(rhs.dset, rhs.dset.length);
            cost = rhs.cost;
        }

        boolean isLinked(Edge e){
            return find(e.u) == find(e.v);
        }

        int find(int x){
            if(dset[x] < 0) return x;
            return dset[x] = find(dset[x]);
        }

        void union(Edge e){
            dset[find(e.v)] = find(e.u);
            cost += e.c;
        }

    }

    static class Edge implements Comparable<Edge>{
        int u, v, c, p;

        Edge(int u, int v, int c, int p){
            this.u = u;
            this.v = v;
            this.c = c;
            this.p = p;
        }

        public int compareTo(Edge rhs){
            if(c==rhs.c) return p-rhs.p;
            return c-rhs.c;
        }
    }

}

class Scan{

    BufferedReader buffer;
    StringTokenizer tok;

    Scan(){
        buffer = new BufferedReader(new InputStreamReader(System.in));
    }

    boolean hasNext(){
        while(tok==null || !tok.hasMoreElements()){
            try{
                tok = new StringTokenizer(buffer.readLine());
            }catch(Exception e){
                return false;
            }
        }
        return true;
    }

    String next(){
        if(hasNext()) return tok.nextToken();
        return null;
    }

    int nextInt(){
        return Integer.parseInt(next());
    }
}
