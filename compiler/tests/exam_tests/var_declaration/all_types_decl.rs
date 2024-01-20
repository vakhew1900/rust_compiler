fn main() {
    let mut ch : char = 'x';
    let mut integ : i32 = 1000000000;
    let mut f : f32 = 1.2;
    let mut b : bool = false;
    let mut strs : String = "Petya";
    let x = 23___;
    println_int("{}", x);

    let decimal_integer = 4_2;          // Десятичное целое число (42, _ не несет смысловой нагрузки)
    let hexadecimal_integer = 0x2A;    // Шестнадцатеричное целое число
    let binary_integer = 0b101010;     // Двоичное целое число
    let octal_integer = 0o52;          // Восьмеричное целое число

    println_int("{}", decimal_integer);
    println_int("{}", hexadecimal_integer);
    println_int("{}", binary_integer);
    println_int("{}", octal_integer);
}