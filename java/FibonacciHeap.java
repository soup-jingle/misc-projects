import java.util.*;

public class FibonacciHeap {
	public static class FNode {
		FNode l;
		FNode r;
		FNode p;
		FNode c;
		int children = 0;
		boolean checked = false;
		
		int key;
		int value;

		public FNode(int k) {
			this.key = k;
		}
		
		public FNode(int k, int v) {
			this.key = k;
			this.value = v;
			this.l = this;
			this.r = this;
		}
		public FNode(FNode f) {
			this.key = f.key;
			this.value = f.value;
			this.l = this;
			this.r = this;
		}
		@Override
		public int hashCode() { return this.key; }
		@Override
		public boolean equals(Object a) {
			if (a.getClass().equals(this.getClass()))
				return key == ((FNode)a).key;
			else return false;
		}
	}

  FNode root;
  int size = 0;

	public boolean isEmpty() {
		return root == null;
	}

	public int size() {
		return this.size;
	}

	public FNode root() {
		return root;
	}

	public FNode insert(int k, int v) {
		//System.out.println("Insert "+ k + ":" +v);
		FNode a = new FNode(k, v);
	  root = merge(root, a);
		++size;
		return a;
	}

	public static FibonacciHeap merge1(FibonacciHeap a, FibonacciHeap b) {
		FibonacciHeap f = new FibonacciHeap();
		f.root = merge(a.root, b.root);
		f.size = a.size + b.size;
		a.size = 0;
		b.size = 0;
		a.root = null;
		b.root = null;
		return f;
	}

	public static FNode merge(FNode a, FNode b) {
		if(a == null) {
			if(b == null) return null;
			else return b;
		}
		if(b == null) return a;

		FNode z = a.r;
		a.r = b.r;
		a.r.l = a;
		b.r = z;
		b.r.l = b;
		if(a.value < b.value) return a;
		else return b;
	}
	
	public void decreaseKey(FNode a, int v) {
		a.value = v;
		if((a.p!=null) && (a.value <= a.p.value)) cut(a);
		if(a.value <= root.value) root = a;
	}
	
	private void cut(FNode n) {
		n.checked = false;
		if (n.p == null) return;
		if (n.r != n) {
			n.r.l = n.l;
			n.l.r = n.l;
		}
		if (n.p.c == n) {
			if (n.r != n)	n.p.c = n.r;
			else n.p.c = null;
		}
		--n.p.children;
		n.l = n.r = n;
		root = merge(root, n);
		if (n.p.checked)
			cut(n.p);
		else
			n.p.checked = true;
		n.p = null;
	}
	
	public FNode extractMin() {
		if(isEmpty()) return null;
		--size;
		FNode min = root;
		if(root.r == root) root = null;
		else {
			root.l.r = root.r;
			root.r.l = root.l;
			root = root.r;
		}
		if(min.c != null) {
			FNode temp = new FNode(min.c);
			do {
				temp.p = null;
				temp = temp.r;
			} while(temp.key != min.c.key);
		}

		root = merge(root, min.c);
		if(root == null) return min;

		ArrayList<FNode> l = new ArrayList<>();
		ArrayList<FNode> unvisited = new ArrayList<>();
		FNode temp = root;
		while(!unvisited.isEmpty() && unvisited.get(0) != root) {
			unvisited.add(temp);
			temp = temp.r;
		}
		for(FNode t : unvisited) {
			while(true) {
				while(temp.children >= l.size()) l.add(null);
				if(l.get(temp.children) == null) {
					l.set(temp.children, temp);
					break;
				}
				FNode temp2 = l.get(temp.children);
				l.set(temp.children, null);
			  //FNode min;
				FNode max;
				if(temp2.value < temp.value) {
					min = temp2;
					max = temp;
				}
				else {
					min = temp;
					max = temp2;
				}
				max.r.l = max.l;
				max.l.r = max.r;
				max.r = max;
				max.l = max;
				min.c = merge(min.c, max);
				max.p = min;
				max.checked = false;
				min.children++;
				temp = min;
			}
			if(temp.value <= root.value) root = temp;
		}
		return min;
	}
}
