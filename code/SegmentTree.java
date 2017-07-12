public class SegmentTree{

    int[] input;
    Entry[] tree;
    int rank, capacity;

    SegmentTree(int[] input){
        this.input = input;
        rank = 1;
        while(1<<(rank++) < input.length);
        capacity = ((1<<rank)>>1);
        tree = new Entry[1<<rank];
        build(1, 0, capacity);
    }

    int operate(int resultL, int resultR){
        return Math.max(resultL, resultR);
    }

    int build(int index, int left, int right){
        Entry now = tree[index] = new Entry(left, right, index);
        if(left+1 == right){
            if(left >= input.length) return now.value = 0;
            return now.value = input[left]; 
        }
        int middle = (left+right) >> 1;
        return now.value = operate(build(lc(index), left, middle), build(rc(index), middle, right));
    }

    int query(int start, int finish){
        return query(1, start, finish);
    }

    int query(int index, int start, int finish){
        //System.out.println("query "+index+", "+start+", "+finish);
        if(tree[index].lb == start && tree[index].rb == finish) return tree[index].value;
        int middle = (tree[index].lb+tree[index].rb) >> 1;
        if(finish <= middle) return query(lc(index), start, finish);
        else if(middle <= start) return query(rc(index), start, finish);
        else{
            return operate(query(lc(index), start, middle), query(rc(index), middle, finish));
        }
    }

    void update(int target, int value){
        int index = target+capacity;
        tree[index].value = value;
        maintain(index>>1);
    }

    void maintain(int index){
        tree[index].value = operate(tree[lc(index)].value, tree[rc(index)].value);
        if(index == 1) return;
        maintain(index>>1);
    }

    int lc(int x){
        return x<<1;
    }

    int rc(int x){
        return (x<<1)+1;
    }

    class Entry{

        int lb, rb, id; //Left Bound, Right Bound and index in Array
        int value;

        Entry(int lb, int rb, int id){
            this.lb = lb;
            this.rb = rb;
            this.id = id;
            value = -1;
        }

    }

}
