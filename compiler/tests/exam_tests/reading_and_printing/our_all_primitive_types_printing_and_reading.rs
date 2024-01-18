fn main() {
    let ch = 'x';
    println_char("char is {}", ch);

    let integ = 1000000000;
    println_int("int is {}", integ);
    println_int("int is {}", 100);

    let f = 1.2;
    println_float("float is {}", f);
    println_float("float is {}", 1e10);

    let bool_val = true;
    let b1 = !bool_val;
    println_bool("boolean is {}", bool_val);
    println_bool("boolean is {}", b1);

    let ri = read_int();
    println_int("\nentered int: {}", ri);

    println_float("\nentered float: {}", read_float());

    println("\nentered string: {}", read());
    println_char("\nentered char: {}", read_char());
}