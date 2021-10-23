import java.io.PrintWriter;
import java.util.Scanner;

public class pizza {
    private static class Solver {
        int N;
        double S, h, w;

        void solve(int testNumber, Scanner s, PrintWriter out) {
            N = s.nextInt();
            S = s.nextDouble();

            // Determine height and width of box
            h = S * Math.sqrt(3.0) / 2.0;
            w = S + (S / 2) * (N - 1);
            out.printf("Order #%d: %.3f%n", testNumber, h * w);
        }
    }

    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        PrintWriter out = new PrintWriter(System.out);
        Solver solver = new Solver();
        int T = s.nextInt();
        for (int t = 1; t <= T; t++) {
            solver.solve(t, s, out);
        }
        s.close();
        out.close();
    }
}
