fn main() {
    // Объявление переменных
    let mut x: f32 = 5.0;
    let y: f32 = 2.5;

    // Объявление константы
    const PI: f32 = 3.14159;

    // Арифметические операции
    let sum = x + y;
    let difference = x - y;
    let product = x * y;
    let quotient = x / y;
    let remainder = x % y;

    // Вывод результатов арифметических операций
    println!("Сумма: {}", sum);
    println!("Разность: {}", difference);
    println!("Произведение: {}", product);
    println!("Частное: {}", quotient);
    println!("Остаток: {}", remainder);

    // Операции сравнения
    let is_equal = x == y;
    let is_not_equal = x != y;
    let is_greater = x > y;
    let is_less = x < y;
    let is_greater_or_equal = x >= y;
    let is_less_or_equal = x <= y;

    // Вывод результатов операций сравнения
    println!("Равно: {}", is_equal);
    println!("Не равно: {}", is_not_equal);
    println!("Больше: {}", is_greater);
    println!("Меньше: {}", is_less);
    println!("Больше или равно: {}", is_greater_or_equal);
    println!("Меньше или равно: {}", is_less_or_equal);

    // Присваивание нового значения переменной
    x = 7.3;

    // Вывод измененного значения переменной
    println!("Новое значение x: {}", x);

    // Использование константы
    let circumference = 2.0 * PI * x;
    println!("Длина окружности: {}", circumference);
}
