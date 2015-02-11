public class SegmentTree{

	int[] input;
	Entry[] tree;
	int rank, capacity;

	SegmentTree(int[] input){
		this.input = input;
		rank = 1;
		while(1<<(rank++) < input.length);
		capacity = 1<<rank>>1;
		System.out.println("rank = "+rank+", cap = "+capacity);
		tree = new Entry[1<<rank];
		build(0, 1, capacity);
	}

	int operate(int resultL, int resultR){
		return resultL + resultR;
	}

	int build(int index, int left, int right){
		Entry now = tree[index] = new Entry(left, right, index);
		if(left == right) return now.value = input[index-1];
		int middle = (left+right) >> 1;
		return now.value = operate(build(lc(index), left, middle), build(rc(index), middle+1, right));
	}

	int query(int index, int start, int finish){
		if(tree[index].lb == start && tree[index].rb == finish) return tree[index].value;
		int middle = (tree[index].lb+tree[index].rb) >> 1;
		if(finish <= middle) return query(lc(index), start, finish);
		else if(middle < start) return query(rc(index), start, finish);
		else{
			return operate(query(lc(index), start, middle), query(rc(index), middle+1, finish));
		}
	}

	void update(int target, int value){
		int index = target-1+capacity;
		int diff = value - tree[index].value;
		maintain(index, diff);
	}

	void maintain(int index, int diff){
		tree[index].value += diff;
		if(index == 1) return;
		maintain(index<<1, diff);
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
