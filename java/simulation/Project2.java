import java.util.Random;

public class Project2 {
	
	public static void main(String[] args) {
		if(args.length < 1) {
			System.out.println("Provide argument for how many trials to run.");
			System.out.println("   (Optional: provide argument for how many times to repeat trial)\n");
			System.out.println("Usage: Project2 trials (repeat)");
			System.exit(0);
		}
		int trials = Integer.parseInt(args[0]);
		int repeats = 1;
		if(args.length > 1) {
			repeats = Integer.parseInt(args[1]);
		}
		int successes = 0;
		int total = 0;
		double x;
		double y;

		long SEED = System.currentTimeMillis();
		Random rand = new Random(SEED);
		for(int rep = 0; rep < repeats; ++rep) {
			for(int i = 0; i < trials; ++i) {
				//x = random, y = random;
				x = rand.nextDouble();
				y = rand.nextDouble();
				if(x*x+y*y <= 1) ++successes;
				++total;
			}
			double ratio = successes / (double) total;
			double approx = ratio * 4;
			double error = Math.abs(Math.PI - approx) / Math.PI;
			System.out.printf("Result (%d trials): PI=%f%n", trials, approx);
			System.out.printf("    (Off by %.5f%%)%n", error*100);
		}
	}
}
