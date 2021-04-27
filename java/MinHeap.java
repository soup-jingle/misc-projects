import java.util.*;


public class MinHeap {

	public static void minHeapify(ArrayList<Graph.Node> S, int i, int j) {
		int r = i;
		int child;
		while ((child = (2 * r + 1)) <= j) {
			if ((child + 1 <= j)
					&& ( S.get(child + 1).weight < S.get(child).weight ))
				++child;
			if (S.get(child).weight < S.get(r).weight) {
				swap(S, r, child);
				r = child;
			}
			else return;
		}
	}
	
	public static void buildMinHeap(ArrayList<Graph.Node> S, int i) {
		int j = i / 2 - 1;
		while (0 <= j) {
			minHeapify(S, j, i - 1);
			--j;
		}
	}
	
	public static void heapSort(ArrayList<Graph.Node> S) {
		int last = S.size();
		buildMinHeap(S, last);
		--last;
		while (0 < last) {
			swap(S, 0, last);
			--last;
			minHeapify(S, 0, last);
		}
	}
	
	public static void swap(ArrayList<Graph.Node> S, int a, int b) {
		Graph.Node temp = S.get(a);
		S.set(a, S.get(b));
		S.set(b, temp);
	}
}
