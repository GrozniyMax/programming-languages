import java.util.Scanner;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args) {
        System.out.print("Введите первое число");

        Scanner scanner = new Scanner(System.in);
        Integer a = scanner.nextInt();
        Integer b = scanner.nextInt();

        Multiplicator multiplicator = new Multiplicator();
        Divider divider = new Divider();

        System.out.println("Результат деления" + divider.divide(a, b));
        System.out.println("Результат умножения" + multiplicator.multiplicaate(a,b));
    }
}
