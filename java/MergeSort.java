import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class MergeSort {

	public static ArrayList<String> merge(List<String> A,
																	 List<String> B) {
		Iterator<String> li = A.iterator();
		Iterator<String> ri = B.iterator();
		String a = li.next();
		String b = ri.next();

		ArrayList<String> C = new ArrayList<>();
		while(true) { // returning C breaks loop
			if(a.compareTo(b) <= 0) { // elt from A is smallest
				C.add(a);
				if(li.hasNext()) a = li.next();
				else {  // If A empty, just fill up C with rest of B 
					C.add(b);
					while(ri.hasNext()) {C.add(ri.next());} break;
				}
			}
			else { // elt from B is smallest
				C.add(b);
				if(ri.hasNext()) b = ri.next();
				else { // If B empty, fill up C with rest of A
					C.add(a);
					while(li.hasNext()) {C.add(li.next());} break;
				}
			}
		}
		return C;
	}

	public static ArrayList<String> mergeSort(List<String> S) {
		if(S.size() <= 1) return (new ArrayList<String>(S));
		int half = S.size() / 2;
		List<String> left = S.subList(0, half);
		//left = mergeSort(left);
		List<String> right = S.subList(half, S.size());
		//right = mergeSort(right);
		return merge(mergeSort(left), mergeSort(right));
	}

	public static void main(String[] args) {
		BufferedReader br;
		PrintWriter pw;

		String input;
		ArrayList<String> strings = new ArrayList<>();
		try {
			br = new BufferedReader(new FileReader(args[0]));
			while( (input = br.readLine()) != null) {
				strings.add(input);
			}
			br.close();
			System.out.println("Done reading from file");
		} catch(IOException e) {
				System.out.println("Problem opening file");
				System.exit(0);
		}
		System.out.println("Sorting. . .");
		long start = System.currentTimeMillis();
		strings = mergeSort(strings);
		System.out.println("Done! In "
											 + (System.currentTimeMillis() - start)
											 + " milliseconds.");

		try {
			pw = new PrintWriter
				(new BufferedWriter(new FileWriter("[MERGESORTED]" + args[0])));
			for(String s : strings) pw.write(s + "\n");
			pw.close();
		} catch(IOException e) {
			System.out.println("Problem writing to file.");
			System.exit(0);
		}
	}
}
