import java.util.*;

/**
 * A magical data structure.
 * Written on 103.07.24
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
		return null;
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
				right.lchild = current.parent = null;
			}else{
				if(left == null){
					left = leftTree = current;
				}else{
					left = left.rchild = current;
				}
				current = current.rchild;
				left.rchild = current.parent = null;
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
				merge(right, left.rchild);
			}
			return left;
		}
	}

	V puts(K key, V value){
		if(root == null){
			root = new Entry(key, value);
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
		return null;
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
