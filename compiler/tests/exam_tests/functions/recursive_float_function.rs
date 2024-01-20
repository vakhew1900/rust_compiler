fn recursive_function(value: f32) -> f32 {
    if value > 500.0 {
        return 1.0;
    }

    if value <= 1.0 {
        value
    } else {
        println_float("Отнимаем от {}", value);
        recursive_function(value - 1.0)
    }
}

fn main() {
    println("{}","Введите число float для рекурсивной функции:");

    let mut value = read_float();
    let result = recursive_function(value);

    println_float("Результат рекурсивной функции: {}", result);
}
