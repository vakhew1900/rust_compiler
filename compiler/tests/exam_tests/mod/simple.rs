
mod Mod {
    // Рекурсивная функция для нахождения наибольшего общего делителя (GCD)
    pub fn gcd_recursive(a: i32, b: i32) -> i32 {
        if b == 0 {
            a
        } else {
            gcd_recursive(b, a % b)
        }
    }
}

fn main() {
    let num1 = 24;
    let num2 = 36;
    let result = Mod::gcd_recursive(num1, num2);

    println_int("Наибольший общий делитель чисел {}", result);
}
