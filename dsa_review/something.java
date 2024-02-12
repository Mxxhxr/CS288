import java.util.Scanner;

public class Hello {

    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        String name;

        System.out.println("Enter name");
        name = s.next();

        System.out.println("The name is: " + name);
    }
}
