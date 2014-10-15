public class SplayTree{

	Node root;
	int size;

	SplayTree(){
		root = null;
		size = 0;
	}

	public boolean containsKey(int target){
		return splay(target);
	}

	public void add(int target){
//		System.out.println("add "+target);
		if(root == null){
			root = new Node(null, target);
			return;
		}
		Node now = root;
		while(true){
			if(now.key == target) break;
			if(target<now.key){
				if(now.lchild == null){
					now.lchild = new Node(now, target);
					break;
				}else now = now.lchild;
			}else{
				if(now.rchild == null){
					now.rchild = new Node(now, target);
					break;
				}else now = now.rchild;
			}
		}
		splay(target);
	}

	public void delete(int target){
//		System.out.println("delete "+target);
		if(!containsKey(target)) return;
		Node l = root.lchild;
		Node r = root.rchild;
		if(l == null){
			root = r;
		}else l.parent = null;
		if(r == null){
			root = l;
		}else r.parent = null;
		if(root==null || root.key != target) return;
		Node lMax = l;

		while(lMax.rchild != null) lMax = lMax.rchild;
		splay(lMax.key);
		lMax.rchild = r;
	}

	private boolean splay(int target){
//		System.out.println("splay "+target);
		while(true){
			if(root == null) return false;
			if(root.key == target) return true;
			if(target<root.key){
				if(root.lchild == null) return false;
				Node l = root.lchild;
				if(l.key == target){
					root = l;
					rightRoatation(l);
					return true;
				}
				if(target<l.key){
					if(l.lchild == null) return false;
					Node a = l.lchild;
					root = a;
					rightRoatation(l);
					rightRoatation(a);
				}else{
					if(l.rchild == null) return false;
					Node b = l.rchild;
					root = b;
					leftRoatation(b);
					rightRoatation(b);
				}
			}else{
				if(root.rchild == null) return false;
				Node r = root.rchild;
				if(r.key == target){
					root = r;
					leftRoatation(r);
					return true;
				}
				if(target>r.key){
					if(r.rchild == null) return false;
					Node d = r.rchild;
					root = d;
					leftRoatation(r);
					leftRoatation(d);
				}else{
					if(r.lchild == null) return false;
					Node c = r.lchild;
					root = c;
					rightRoatation(c);
					leftRoatation(c);
				}
			}
		}
	}

	void print(Node now){
		if(now == null){
			System.out.print("-1 ");
			return;
		}
		System.out.print(now.key+" ");
		print(now.lchild);
		print(now.rchild);
	}

	void rightRoatation(Node x){
		Node r = x.parent.parent;
		Node p = x.parent;
		Node b = x.rchild;

		x.rchild = p;
		if(p != null) p.parent = x;
		if(p != null) p.lchild = b;
		if(b != null) b.parent = p;
		x.parent = r;
		if(r != null) r.lchild = x;

	}

	void leftRoatation(Node x){
		Node r = x.parent.parent;
		Node p = x.parent;
		Node b = x.lchild;


		x.lchild = p;
		if(p != null) p.parent = x;
		if(p != null) p.rchild = b;
		if(b != null) b.parent = p;
		x.parent = r;
		if(r != null) r.rchild = x;
	}

	class Node{

		Node parent, lchild, rchild;
		int key;

		Node(Node parent, int key){
			this.parent = parent;
			lchild = rchild = null;
			this.key = key;
		}
	}
}
