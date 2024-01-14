import dir.*;

public class Main {
    public static void main(String[] args) {
        String str1 = "ABCDEF";
        String str2 = "ABCDEF";
        String str3 = "ABCDEFG";
        char ch = RTL.charAt(str1,3);
        System.out.println(ch);

        boolean b1t = RTL.isEqual(str1, str2);
        boolean b2f = RTL.isEqual(str1, str3);
        boolean b3t = RTL.isBigger(str3, str1);
        boolean b4t = RTL.isLower(str1, str3);
        System.out.println(b1t + " " + b2f + " " + b3t + " " + b4t);
//        int x = 11;
//
//        if (x > 10)
//            System.out.println(x);
//           Car.ride();
//           Bus.ride();
//        Two.static_test();
//        int a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, r, s, t, q, u, x, y, z = 10;
//        double d1 = 1e12;
//        char x1 = 'c';
//        System.out.print("Message");
//        One o1 = new One();
//        Two t2 = new Two();
//        Three t3 = new Three();
//
//        int j = 0;
//        for (int i = 0; i < 4; i++){
//            if (i == 2) {
//                break;
//            }
//            j += i;
//        }
//
//        int k = 0;
//        for (int i = 0; i < 4; i++){
//            if (i % 2 == 0) {
//                continue;
//            }
//            k += i;
//        }
//
//        System.out.println(j + " " + k);
    }
}