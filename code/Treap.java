import java.util.*;

/**
 * A magical data structure.
 * Written on 103.08.19
 */
public class Treap<K, V>{

	Random priorityGenerator;
	int time, size;
	Entry root;

	/**
	 * Default Constructor
	 */
	Treap(){
		root = null;
		time = size = 0;
		priorityGenerator = new Random();
	}

	/**
	 * Find the Entry associated with key
	 * @param key the key of the entry you are looking for
	 * @return Entry
	 */
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

	/**
	 * Split the treap based on the key
	 * Behavior undefined if the specified key is already in the tree
	 * @param cmp Comparable based on the key
	 * @return an array consists of two elements, the left subtree and the right
	 */
	Entry[] split(Comparable<? super K> cmp){
		Entry leftTree = null, rightTree = null, left = null, right = null;
		Entry current = root;
		while(current != null){
			if(cmp.compareTo(current.key) == -1){
				if(right == null){
					right = rightTree = current;
				}else{
					current.parent = right;
					right = right.lchild = current;
				}
				current = current.lchild;
				right.lchild = null;
				if(current != null) current.parent = null;
			}else{
				if(left == null){
					left = leftTree = current;
				}else{
					current.parent = left;
					left = left.rchild = current;
				}
				current = current.rchild;
				left.rchild = null;
				if(current != null) current.parent = null;
			}
		}
		return new Treap.Entry[]{leftTree, rightTree};
	}

	/**
	 * Merge two Treaps into one.
	 * All keys of the entries in the left must be smaller than all keys of the entries in the right
	 * @param left the left Treap, it must be smaller than the right Treap
	 * @param right the right Treap, it must be greater than the left Treap
	 * @return root of the resulting Treap
	 */
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

	/**
	 * Insert a new Entry into the Treap if the key doesn't exists
	 * Else replace the value with the new one and return the old value
	 * @param key the key of the entry to be inserted or modified
	 * @param value the new value of the entry
	 * @return The original value if entry already exists, else return null;
	 */
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

	/**
	 * Remove the entry associated with the specified key
	 * return the according value upon removing
	 * @param key the key of the entry to be destroyed
	 * @return the value associated with the specified key, return null if no such key exists
	 */
	V remove(K key){
		Entry target = find(key);
		if(target == null) return null;
		if(target.lchild!=null) target.lchild.parent = null;
		if(target.rchild!=null) target.rchild.parent = null;
		Entry child = merge(target.lchild, target.rchild);
		if(child != null) child.parent = target.parent;
		if(target.parent != null){
			if(target == target.parent.lchild) target.parent.lchild = child;
			else if(target == target.parent.rchild) target.parent.rchild = child;
			else throw new AssertionError("remove fail");
		}else if(root == target) root = child;
		else throw new AssertionError("What is this?");
		size--;
		return target.value;
	}

	/**
	 * This is a debugger
	 * @param now the node doing a in order traversal
	 * @return the size of the subtree rooted at now
	 */
	int iterate(Entry now, Entry parent){
		if(now == null) return 0;
		//System.out.println("Iterate "+now.key);
		if(now.parent != parent) System.out.println("Parent Check Fail!!!");
		int result = 1;
		result += iterate(now.lchild, now);
		//System.out.println("Entry : "+now.key);
		result += iterate(now.rchild, now);
		return result;
	}

	/**
	 * The class storing all the entries of Treap
	 * each Entry consists of a key and a value and a random generated priority
	 * also stores its parent and children as well
	 */
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
