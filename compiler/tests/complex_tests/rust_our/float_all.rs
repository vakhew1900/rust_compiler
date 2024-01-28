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
    println_float("Сумма: {}", sum);
    println_float("Разность: {}", difference);
    println_float("Произведение: {}", product);
    println_float("Частное: {}", quotient);
    println_float("Остаток: {}", remainder);

    // Операции сравнения
    let is_equal = x == y;
    let is_not_equal = x != y;
    let is_greater = x > y;
    let is_less = x < y;
    let is_greater_or_equal = x >= y;
    let is_less_or_equal = x <= y;

    // Вывод результатов операций сравнения
    println_bool("Равно: {}", is_equal);
    println_bool("Не равно: {}", is_not_equal);
    println_bool("Больше: {}", is_greater);
    println_bool("Меньше: {}", is_less);
    println_bool("Больше или равно: {}", is_greater_or_equal);
    println_bool("Меньше или равно: {}", is_less_or_equal);

    // Присваивание нового значения переменной
    x = 7.3;

    // Вывод измененного значения переменной
    println_float("Новое значение x: {}", x);

    // Использование константы
    let circumference = 2.0 * PI * x;
    println_float("Длина окружности: {}", circumference);
}
