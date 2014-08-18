import java.util.*;

/**
 * A magical data structure.
 * Written on 103.08.18
 */
public class Treap<K, V>{

	Random priorityGenerator;
	int time, size;
	Entry root;

	Treap(){
		root = null;
		time = size = 0;
		priorityGenerator = new Random();
	}

	Entry find(K key){
		Entry now = root;
		Comparable<? super K> cmp = (Comparable<? super K>)key;
		int situation;
		while((now != null) && (situation=cmp.compareTo(now.key)) != 0){
			if(situation == -1) now = now.lchild;
			else now = now.rchild;
		}
		return now;
	}

	Entry[] split(Comparable<? super K> cmp){
		Entry leftTree = null, rightTree = null, left = null, right = null;
		Entry current = root;
		while(current != null){
			if(cmp.compareTo(current.key) == -1){
				if(right == null){
					right = rightTree = current;
				}else{
					right = right.lchild = current;
				}
				current = current.lchild;
				right.lchild = null;
				if(current != null) current.parent = null;
			}else{
				if(left == null){
					left = leftTree = current;
				}else{
					left = left.rchild = current;
				}
				current = current.rchild;
				left.rchild = null;
				if(current != null) current.parent = null;
			}
		}
		return new Treap.Entry[]{leftTree, rightTree};
	}

	Entry merge(Entry left, Entry right){
		if(left == null) return right;
		if(right == null) return left;
		if(left.compareTo(right) == -1){
			if(right.lchild == null){
				right.lchild = left;
				left.parent = right;
			}else if(right.lchild.compareTo(left) == -1){
				Entry temp = right.lchild;
				right.lchild = left;
				left.parent = right;
				temp.parent = null;
				merge(left, temp);
			}else{
				merge(left, right.lchild);
			}
			return right;
		}else{
			if(left.rchild == null){
				left.rchild = right;
				right.parent = left;
			}else if(left.rchild.compareTo(right) == -1){
				Entry temp = left.rchild;
				left.rchild = right;
				right.parent = left;
				temp.parent = null;
				merge(temp, right);
			}else{
				merge(left.rchild, right);
			}
			return left;
		}
	}

	V puts(K key, V value){
		if(root == null){
			root = new Entry(key, value);
			size++;
			return null;
		}
		Entry position = find(key);
		if(position != null){
			V temp = position.value;
			position.value = value;
			return temp;
		}
		Entry newEntry = new Entry(key, value);
		Comparable<? super K> cmp = ((Comparable<? super K>)key);
		Entry[] subtree = split(cmp);
		newEntry = merge(subtree[0], newEntry);
		root = merge(newEntry, subtree[1]);
		size++;
		return null;
	}

	void remove(K key){
		Entry target = find(key);
		if(target == null) return;
		target.lchild.parent = target.rchild.parent = null;
		Entry child = merge(target.lchild, target.rchild);
		child.parent = target.parent;
		if(target == target.parent.lchild) target.parent.lchild = child;
		else if(target == target.parent.rchild) target.parent.rchild = child;
		else throw new AssertionError("remove fail");
		size--;
	}

	/**
	 * This is a debugger
	 * @param now the node doing a in order traversal
	 * @return the size of the subtree rooted at now
	 */
	int iterate(Entry now){
		if(now == null) return 0;
		int result = 1;
		result += iterate(now.lchild);
		result += iterate(now.rchild);
		return result;
	}

	class Entry implements Comparable<Entry>{
		Entry parent, lchild, rchild;
		Integer priority, timestamp;
		K key;
		V value;

		Entry(K key, V value){
			this.key = key;
			this.value = value;
			parent = lchild = rchild = null;
			priority = priorityGenerator.nextInt();
			timestamp = time++;
		}

		@Override
		public int compareTo(Entry rhs){
			int result = priority.compareTo(rhs.priority);
			if(result == 0) return timestamp.compareTo(rhs.timestamp);
			return result;
		}
	}

}
