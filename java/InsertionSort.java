import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;

public class InsertionSort {

	public static void insertionSort(ArrayList<String> S) {
		for(int i = 1; i < S.size(); ++i) {
			String v = S.get(i);
			int j = i-1;
			while( (0 <= j) && ((v.compareTo(S.get(j))) < 0) ) {
				S.set(j+1, S.get(j));
				--j;
			}
			S.set(j+1, v);
		}
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
		insertionSort(strings);
		System.out.println("Done! In "
											 + (System.currentTimeMillis() - start)
											 + " milliseconds.");

		try {
			pw = new PrintWriter
				(new BufferedWriter(new FileWriter("[INSERTSORTED]" + args[0], true)));
			for(String s : strings) pw.write(s + "\n");
			pw.close();
		} catch(IOException e) {
			System.out.println("Problem writing to file.");
			System.exit(0);
		}
	}
}
