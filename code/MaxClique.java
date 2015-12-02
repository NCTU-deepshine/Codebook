static class BronKerbosch{

    ArrayList<ArrayList<Integer>> list;
    ArrayList<Integer> ordering, sorted;
    boolean[][] neighbor;
    boolean[] maxClique;
    int value;

    BronKerbosch(ArrayList<ArrayList<Integer>> list){
        this.list = list;
        PriorityQueue<Entry> pq = new PriorityQueue<Entry>();
        int[] degree = new int[list.size()];
        neighbor = new boolean[list.size()][list.size()];
        for(int i=0;i<list.size();i++){
            degree[i] = list.get(i).size();
            pq.add(new Entry(i, degree[i]));
            for(int next : list.get(i)) neighbor[i][next] = true;
        }
        sorted = new ArrayList<Integer>();
        for(int i=0;i<list.size();i++) sorted.add(i);
        Collections.sort(sorted, new Cmp(degree));
        ordering = new ArrayList<Integer>();
        while(!pq.isEmpty()){
            Entry e = pq.poll();
            ordering.add(e.id);
            for(int next : list.get(e.id)) degree[next]--;
        }
        maxClique = new boolean[list.size()];
        value  = 0;
        bkInit();
    }

    void bkInit(){
        boolean[] r = new boolean[list.size()];
        boolean[] p = new boolean[list.size()];
        boolean[] x = new boolean[list.size()];
        Arrays.fill(p, true);
        for(int now : ordering){
            r[now] = true;
            bkRecusive(r, intersect(p, neighbor[now]), intersect(x, neighbor[now]));
            r[now] = false;
            p[now] = false;
            x[now] = true;
        }
    }

    void bkRecusive(boolean[] r, boolean[] p, boolean[] x){
        boolean done = true;
        for(int i=0;i<list.size();i++){
            if(p[i] || x[i]){
                done = false;
                break;
            }
        }
        if(done){
            int count = 0;
            for(int i=0;i<list.size();i++) if(r[i]) count++;
            if(count > value){
                value = count;
                maxClique = Arrays.copyOf(r, list.size());
            }
            return;
        }
        int u = 0;
        for(int uu : sorted){
            u = uu;
            if(p[u] || x[u]) break;
        }
        for(int now=0;now<list.size();now++){
            if(!p[now]) continue;
            if(neighbor[u][now]) continue;
            r[now] = true;
            bkRecusive(r, intersect(p, neighbor[now]), intersect(x, neighbor[now]));
            r[now] = p[now] = false;
            x[now] = true;
        }

    }

    boolean[] intersect(boolean[] a, boolean[] b){
        boolean[] result = new boolean[list.size()];
        for(int i=0;i<list.size();i++) result[i] = a[i] && b[i];
        return result;
    }

    static class Cmp implements Comparator<Integer>{

        int[] degree;

        Cmp(int[] degree){
            this.degree = degree;
        }

        @Override
            public int compare(Integer lhs, Integer rhs){
                return degree[lhs] - degree[rhs];
            }

    }

    class Entry implements Comparable<Entry>{

        int id, degree;

        Entry(int id, int degree){
            this.id = id;
            this.degree = degree;
        }

        @Override
            public int compareTo(Entry rhs){
                return degree - rhs.degree;
            }

    }

}
