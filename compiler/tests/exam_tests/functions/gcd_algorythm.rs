// Функция для нахождения наибольшего общего делителя (GCD)
fn gcd(mut a: i32, mut b: i32) -> i32 {
    while b != 0 {
        let temp = b;
        b = a % b;
        a = temp;
    }
    a
}

fn main() {
    let num1 = 24;
    let num2 = 36;

    let result = gcd(num1, num2);

    println_int("Наибольший общий делитель чисел: {}", result);

    let mut num3 = read_int();
    let mut num4 = read_int();
    let mut result2 : i32 = gcd(num3, num4);
    println_int("Наибольший общий делитель чисел: {}", result2);
}
