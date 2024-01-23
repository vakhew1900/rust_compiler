public class RTL {
    public static void print(String str, String val) {
        if (!str.contains("{}")) {
            throw new IllegalArgumentException("Format string is not contains {}");
        }
        System.out.print(str.replace("{}", val));
    }

    public static void print_int(String str, int value) {
        if (!str.contains("{}")) {
            throw new IllegalArgumentException("Format string is not contains {}");
        }
        System.out.print(str.replace("{}", String.valueOf(value)));
    }

    public static void print_float(String str, float value) {
        if (!str.contains("{}")) {
            throw new IllegalArgumentException("Format string is not contains {}");
        }
        System.out.print(str.replace("{}", String.valueOf(value)));
    }

    public static void print_char(String str, char ch) {
        if (!str.contains("{}")) {
            throw new IllegalArgumentException("Format string is not contains {}");
        }
        System.out.print(str.replace("{}", String.valueOf(ch)));
    }

    public static void print_bool(String str, int b_int) {
        boolean b = b_int > 0;
        if (!str.contains("{}")) {
            throw new IllegalArgumentException("Format string is not contains {}");
        }
        System.out.print(str.replace("{}", String.valueOf(b)));
    }

    public static void println(String str, String val) {
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
     * @return true если первая строка лексикографически больше второй, false если равна или лексикографически меньше второй
     */
    public static int isBigger(String s1, String s2){
        int res = (s1.compareTo(s2) > 0)? 1 : 0;
        return res;
    }

    /***
     * Сравнение первой и второй строки
     * @param s1 - первая строка
     * @param s2 - вторая строка
     * @return true если первая строка лексикографически больше или равна второй, false если лексикографически меньше второй
     */
    public static int isBiggerOrEqual(String s1, String s2){
        int res = (s1.compareTo(s2) >= 0)? 1 : 0;
        return res;
    }

    /***
     * Сравнение первой и второй строки
     * @param s1 - первая строка
     * @param s2 - вторая строка
     * @return true если первая строка лексикографически меньше второй, false если равна или лексикографически больше второй
     */
    public static int isLower(String s1, String s2){
        int res = (s1.compareTo(s2) < 0)? 1 : 0;
        return res;
    }

    /***
     * Сравнение первой и второй строки
     * @param s1 - первая строка
     * @param s2 - вторая строка
     * @return true если первая строка лексикографически меньше или равна второй, false если лексикографически больше второй
     */
    public static int isLowerOrEqual(String s1, String s2){
        int res = (s1.compareTo(s2) <= 0)? 1 : 0;
        return res;
    }

    /***
     * Сравнение первой и второй строки
     * @param s1 - первая строка
     * @param s2 - вторая строка
     * @return true если первая строка лексикографически равна со второй, false если лексикографически не равна второй
     */
    public static int isEqual(String s1, String s2){
        int res = (s1.compareTo(s2) == 0)? 1 : 0;
        return res;
    }

    /***
     * Сравнение первой и второй строки
     * @param s1 - первая строка
     * @param s2 - вторая строка
     * @return false если первая строка лексикографически равна со второй, true если лексикографически не равна второй
     */
    public static int isNotEqual(String s1, String s2){
        int res = (s1.compareTo(s2) != 0)? 1 : 0;
        return res;
    }

    /***
     * Склейка первой и второй строки
     * @param s1 - первая строка
     * @param s2 - вторая строка
     * @return объединенные в одну строки
     */
    public static String push_str(String s1, String s2) {
        StringBuilder stringBuilder = new StringBuilder(s1);
        stringBuilder.append(s2);
        return stringBuilder.toString();
    }

    /***
     * Склейка строки с символом
     * @param s - первая строка
     * @param c- вторая строка
     * @return объединенная с символом строка
     */
    public static String push_сhar(String s, char c) {
        StringBuilder stringBuilder = new StringBuilder(s);
        stringBuilder.append(c);
        return stringBuilder.toString();
    }

}

