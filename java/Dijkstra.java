import java.util.*;

public class Dijkstra {

	public static int[] matrixDijkstra(int[][] m) {
		int size = m[0].length;
		boolean[] sp = new boolean[size];
		int[] dist = new int[size];
		
		for(int i = 0; i < size; ++i) dist[i]=Integer.MAX_VALUE;
		dist[0]=0;

		for(int i = 0; i < size; ++i) {
			int min = matrixDijkstra_minDist(dist, sp);
			sp[min] = true;

			for(int j = 0; j < size; j++) {
				int temp = dist[i]+m[i][j];
				if((temp < dist[j]) &&
					 (!sp[j]) &&
					 (m[i][j] != 0) &&
					 (dist[i] != Integer.MAX_VALUE))
					dist[j] = temp;
			}
		}
		return dist;
	}

	private static int matrixDijkstra_minDist(int[] dist, boolean[] sp) {
		int r = Integer.MAX_VALUE;
		int index = 0;
		for(int i = 0; i < dist.length; ++i) {
			if((dist[i]<=r) && (sp[i] == false)) {
				r = dist[i];
				index = i;
			}
		}
		return index;
	}
	
	/* Min Heap ------------------------------------------------------*/
	/*
	public static HashMap<Integer, Integer> dijkstraMinHeap(Graph G, int start, int size) {
		Graph.Node u;
		HashMap<Integer,Integer> H;
		initializeSingleSource(G, start, H);
		ArrayList<Graph.Node> Q = G.nodes;
		for (int i = 0; i < size; ++i) {
			u = extractMin(G, Q);
			for (Graph.Node v : G.getNode(u).adj) {
				relax(G, u, v, H);
			}
		}
		return H;
	}
	private static Graph.Node extractMin(Graph g, ArrayList<Graph.Node> Q, HashMap<Integer,Integer> H) {
		Graph.Node m = g.getNode(Q.get(0));
		H.put(Q.get(0), Integer.MAX_VALUE);
		HeapSort.heapSort(Q);
		return m;
	}
	
	private static void initializeSingleSource(Graph G, int source, HashMap<Integer,Integer> H) {
		for (Graph.Node v : G.nodes)
			H.put(v.key, (v.key==source) ? 0 : Integer.MAX_VALUE);
	}
	
	private static void relax(Graph G, Graph.Node u, Graph.Node v, HashMap<Integer,Integer> H) {
		Graph.Edge e = new Graph.Edge(u, v);
		long newWeight = G.getNode(u).weight + G.getEdge(e).weight;
		if (G.getNode(v).weight > newWeight) {
			H.put(G.getNode(v).key, newWeight);
		}
	}
	*/
	/* Fibonacci Heap ------------------------------------------------*/
	
	public static HashMap<Integer, Integer>
		fibHeapDijkstra(HashMap<Integer, HashMap<Integer, Integer>> g,
										int s) {
		FibonacciHeap F = new FibonacciHeap();
		HashMap<Integer, FibonacciHeap.FNode> nodes = new HashMap<>();
		HashMap<Integer, Integer> H = new HashMap<>();

		for(int n : g.keySet())
			nodes.put(n, F.insert(n, Integer.MAX_VALUE));
		F.decreaseKey(nodes.get(s), 0);

		while(!F.isEmpty()) {
			FibonacciHeap.FNode temp = F.extractMin();
			H.put(temp.key, temp.value);
			for(Map.Entry<Integer, Integer> h : g.get(temp.key).entrySet()) {
				if(H.containsKey(h.getKey())) continue;
				int tMin = temp.value + h.getValue();
				FibonacciHeap.FNode d = nodes.get(h.getKey());
				if(tMin < d.value)
					F.decreaseKey(d, tMin);
			}
		}
		return H;
	}
}
