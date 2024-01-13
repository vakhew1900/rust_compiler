import dir.*;

public class Main {
    public static void main(String[] args) {
        One o1 = new One();
        Two t2 = new Two();
        Three t3 = new Three();

        int j = 0;
        for (int i = 0; i < 4; i++){
            if (i == 2) {
                break;
            }
            j += i;
        }

        int k = 0;
        for (int i = 0; i < 4; i++){
            if (i % 2 == 0) {
                continue;
            }
            k += i;
        }

        System.out.println(j + " " + k);
    }
}