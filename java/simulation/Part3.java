import java.io.IOException;
import java.io.PrintWriter;
import java.util.Random;

public class Part3 {
	
	public static final int GREEN = 0;
	public static final int YELLOW = 1;
	public static final int ORANGE = 2;
	public static final int RED = 3;

	public static final double[] STEADY_STATE = { 1/3.0, 1/9.0, 2/9.0, 1/3.0 };
	public static final String[] STATE = { "GREEN", "YELLOW", "ORANGE", "RED" };

	public static final int TOTAL_STEPS = 4000;

	public static double[][] probTransMat = {
		{ 248/310.0,  62/310.0,         0,         0 },
		{  29/290.0, 232/290.0,  29/290.0,         0 },
		{  20/200.0,         0, 140/200.0,  40/200.0 },
		{  29/290.0,         0,         0, 261/290.0 } };
	
	public static void main(String[] args) {
		int currentState;

		int[] tally = {0, 0, 0, 0};

		long SEED = System.currentTimeMillis();
		Random rand = new Random(SEED);
		double r;
		double accum = 0;
		double value;
		String filename;
		PrintWriter writer = null;
		
		for(int i = 1; i <= 10; ++i) { // different start (G, Y, O, R)
			filename = "run" + i + ".txt";
			
			for(int x = 0; x < 4; ++x) tally[x]=0;
			currentState = getStartState(rand); // Determine start state randomly (but using steady state)
			
			try {
				writer = new PrintWriter(filename, "UTF-8");
			}
			catch(IOException e) {
				System.out.println("Cannot open file: " + filename);
				System.exit(0);
			}
			writer.println("Green, Yellow, Orange, Red");
			for(int s = 1; s <= TOTAL_STEPS+1; ++s) {
				tally[currentState]++;
				r = rand.nextDouble();
				accum = value = 0;
				for(int j = 0; j < 4; ++j) {
					value = probTransMat[currentState][j];
					if(r < accum + value) {
						currentState = j;
						break;
					}
					else {
						accum += value;
					}
				}
				// print out to file
				writer.printf("%f, %f, %f, %f%n", tally[GREEN]/(double)s, tally[YELLOW]/(double)s,
													tally[ORANGE]/(double)s, tally[RED]/(double)s);
			}
			writer.close();
		}
	}

	public static int getStartState(Random rand) {
		double d = rand.nextDouble();
		for(int i = 0; i < 4; ++i) {
			if(d < STEADY_STATE[i]) return i;
		}
		return 3;
	}
}


