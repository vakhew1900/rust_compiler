fn main(){
    let integer1: i32 = 42;
    let integer2: i32 = 500;
    let integer3: i32 = 100;

    let sum = integer1 + integer2;
    let difference = integer2 - integer1;
    let product = integer1 * 5;
    let quotient = (-integer3) / 2;

    let x = -    integer1; //унарный минус
    let x1 = -        9;

    println_int("{}", sum);
    println_int("{}", difference);
    println_int("{}", product);
    println_int("{}", quotient);
    println_int("{}", x);
    println_int("{}", x1);
}