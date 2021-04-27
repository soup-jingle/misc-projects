import java.util.*;

public class Graph {
	public static ArrayList<Node> nodes;
	public static ArrayList<Edge> edges;

	public static class Node {
		public int key;
		public int weight;
		public Node parent;
		public LinkedHashSet<Node> adj;

		public Node(int i) {
			adj = new LinkedHashSet<>();
			this.key = i;
			this.weight = Integer.MAX_VALUE;
			this.parent = null;
		}
		@Override
		public int hashCode() {
			return this.key;
		}
		@Override
		public boolean equals(Object a) {
			if (a.getClass().equals(this.getClass())) {
				return key == ((Node)a).key;
			}
			else {
				return false;
			}
		}
	}

	public static class Edge {
		public Node beg;
		public Node end;
		public int weight;

		public Edge(Node a, Node b) {
			this.beg = a;
			this.end = b;
		}

		public Edge(Node a, Node b, int weight) {
			this.beg = a;
			this.end = b;
			this.weight = weight;
		}
		@Override
		public int hashCode() {
			return (beg.hashCode() + end.hashCode());
		}
		
		@Override
		public boolean equals(Object o) {
			if (!o.getClass().equals(getClass())) {
				return false;
			} else {
				Edge x = (Edge) o;
				return (x.beg.equals(beg) && x.end.equals(end));
			}
		}
	}

	public Graph() {
		this.edges = new ArrayList<>();
		this.nodes = new ArrayList<>();
	}
	public static void addNode(int a) {
		if(!nodes.contains(new Node(a))) nodes.add(new Node(a));
	}
	public static void addEdge(Node a, Node b, int weight) {
	  edges.add(new Edge(a, b, weight));
	  nodes.get(nodes.indexOf(a)).adj.add(b);
	}
	public static Node getNode(Node a) {
		return nodes.get(nodes.indexOf(a));
	}
	public static Edge getEdge(Edge e) {
		return edges.get(edges.indexOf(e));
	}

	public static void print() {
		for(Node node : nodes) {
			System.out.print(node.key + " ");
			for(Node adj : getNode(node).adj) {
				System.out.print(adj.key + " " +
												 getEdge(new Edge(node, adj)).weight + " ");
			}
			System.out.println();
		}
	}
}
