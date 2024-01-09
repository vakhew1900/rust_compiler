fn main() {
    let number = 10;

    // Проверяем, является ли число четным или нечетным
    if number % 2 == 0 {
        println("Число {} - четное.", number);
    } else {
        println("Число {} - нечетное.", number);
    }

    println("Числа от 1 до {}: ", number);
    for i in 1..number {
        println("{}", i);
    }
}
