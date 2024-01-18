public class RTL {

    public static void println_int(String str, String val) {
        if (!str.contains("{}")) {
            throw new IllegalArgumentException("Format string is not contains {}");
        }
        System.out.println(str.replace("{}", val));
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

    public static void println_bool(String str, int b_int) {
        boolean b = b_int > 0;
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

    public static char charAt(String s, int index){
        return s.charAt(index);
    }

    /***
     * Сравнение первой и второй строки
     * @param s1 - первая строка
     * @param s2 - вторая строка
     * @return true если первая строка лексиграфически больше второй, false если равна или лексиграфически меньше второй
     */
    public static boolean isBigger(String s1, String s2){
        return s1.compareTo(s2) < 0;
    }

    /***
     * Сравнение первой и второй строки
     * @param s1 - первая строка
     * @param s2 - вторая строка
     * @return true если первая строка лексиграфически меньше второй, false если равна или лексиграфически больше второй
     */
    public static boolean isLower(String s1, String s2){
        return s1.compareTo(s2) > 0;
    }

    /***
     * Сравнение первой и второй строки
     * @param s1 - первая строка
     * @param s2 - вторая строка
     * @return true если первая строка лексикографически равна со второй, false если лексикографически не равна второй
     */
    public static boolean isEqual(String s1, String s2){
        return s1.compareTo(s2) == 0;
    }
}

