fn main() {
    let number = 10;

    // Проверяем, является ли число четным или нечетным
    if number % 2 == 0 {
        println("Число {} - четное.", number);
    } else {
        println("Число {} - нечетное.", number);
    }
	
	if(true) {4} else {3};

    println("Числа от 1 до {}: ", number);
    for i in 1..number {
        println("{}", i);
    }
}
