class Treap{

	int key, priority, size;
	char value;
	Treap left, right;
	boolean reversed;

	public Treap(int key, char value, int priority){
		this.key = key;
		this.value = value;
		this.priority = priority;
		left = right = null;
		reversed = false;
		size = 1;
	}

	static char get(Treap now, int key){
		push(now);
		int index =  1 + getSize(now.left);
		if(index == key) return now.value;
		if(index < key) return get(now.right, key-index);
		return get(now.left, key);
	}

	private static void push(Treap now){
		if(now==null || !now.reversed) return;
		now.reversed = false;
		Treap temp = now.left;
		now.left = now.right;
		now.right = temp;
		if(now.left != null) now.left.reversed = !now.left.reversed;
		if(now.right != null) now.right.reversed = !now.right.reversed;
	}

	static int getSize(Treap t){
		if(t==null) return 0;
		return t.size;
	}

	static void split(int key, Treap now, Treap[] result){
		if(now == null){
			result[0] = result[1] = null;
			return;
		}
		push(now);
		int index = getSize(now.left) + 1;
		if(index <= key){
			split(key-getSize(now.left)-1, now.right, result);
			now.right = result[0];
			result[0] = now;
		}else{
			split(key, now.left, result);
			now.left = result[1];
			result[1] = now;
		}
		now.size = 1 + getSize(now.left) + getSize(now.right);
	}

	static Treap merge(Treap left, Treap right){
		if(left == null) return right;
		if(right == null) return left;
		if(left.priority > right.priority){
			push(left);
			left.right = merge(left.right, right);
			left.size = 1 + getSize(left.left) + getSize(left.right);
			return left;
		}else{
			push(right);
			right.left = merge(left, right.left);
			right.size = 1 + getSize(right.left) + getSize(right.right);
			return right;
		}
	}