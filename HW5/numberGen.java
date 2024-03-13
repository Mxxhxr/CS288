package HW5;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class numberGen {

    public static void main(String[] args) {
        String filename = "numbers.txt";

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(filename))) {
            Random random = new Random();
            for (int i = 0; i < 100_000_000; i++) {
                int digit = random.nextInt(10); // Generate a random digit from 0 to 9
                writer.write(Integer.toString(digit));
            }
            System.out.println("Numbers generated and written to file successfully.");
        } catch (IOException e) {
            System.err.println("Error writing to file: " + e.getMessage());
        }
    }
}
