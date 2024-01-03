public class Std_IO {

    public static void println_int(String str, String val) {
            if (!str.contains("{}")) {
                throw new IllegalArgumentException("Format string is not contains {}");
            }
            System.out.println(str.replace("{}", val);
        }

    public static void println_int(String str, int value) {
        if (!str.contains("{}")) {
            throw new IllegalArgumentException("Format string is not contains {}");
        }
        System.out.println(str.replace("{}", String.valueOf(value)));
    }

    public static void println_float(String str, float value) {
        if (!str.contains("{}")) {
            throw new IllegalArgumentException("Format string is not contains {}");
        }
        System.out.println(str.replace("{}", String.valueOf(value)));
    }

    public static void println_char(String str, char ch) {
        if (!str.contains("{}")) {
            throw new IllegalArgumentException("Format string is not contains {}");
        }
        System.out.println(str.replace("{}", String.valueOf(ch)));
    }

    public static void println_bool(String str, boolean b) {
        if (!str.contains("{}")) {
            throw new IllegalArgumentException("Format string is not contains {}");
        }
        System.out.println(str.replace("{}", String.valueOf(b)));
    }


    public static String read(){
        java.util.Scanner in = new java.util.Scanner(System.in);
        return in.nextLine();
    }

    public static int read_int(){
        java.util.Scanner in = new java.util.Scanner(System.in);
        return in.nextInt();
    }

    public static float read_float(){
        java.util.Scanner in = new java.util.Scanner(System.in);
        return in.nextFloat();
    }

    public static char read_char(){
        java.util.Scanner in = new java.util.Scanner(System.in);
        return in.next().charAt(0);
    }

}
