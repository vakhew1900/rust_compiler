fn main() {
    // Пример 1: Возвращение значения из блока if в присваивание переменной
    let b1 = 5;
    let x1 = if b1 > 0 { "Positive" } else { "Non-positive" };
    println("Пример 1: {}", x1);

    // Пример 2: Возвращение значения из блока if в функцию
    let b2 = 5;
    let x2 = calculate_x(b2);
    println("Пример 2: {}", x2);

    // Пример 3: Возвращение значения из блока if в теле цикла
    for i in 1..5 {
        let result = if i % 2 == 0 { "Even" } else { "Odd" };
        print_int("Пример 3 (итерация {})", i);
        println(" {}", result);
    }

    // Пример 4: Возвращение значения из блока if во внешний блок
    let y = {
        let z = 10;
        if z > 5 {
            z * 2
        } else {
            z * 3
        }
    };
    println_int("Пример 4: {}", y);

    // Пример 5: Возвращение значения из блока if в присваивание переменной (блок как выражение)
    let b5 = 5;
    let z = if b5 > 0 { b5 * 2 } else { b5 * 3 };
    println_int("Пример 5: {}", z);

    // Пример 6: Возвращение значения из блока if внутри функции
    let input = read_int();
    let result_function = process_input(input);
    println("Пример 6: Результат обработки введенного значения: {}", result_function);
}

// Функция для демонстрации возвращения значения из блока if внутри функции
fn process_input(value: i32) -> String {
    if value > 0 {
        "Positive"
    } else {
        "Non-positive"
    }
}

// Функция для демонстрации возвращения значения из блока if внутри функции
fn calculate_x(b: i32) -> String {
    if b > 0 {
        "Positive"
    } else {
        "Non-positive"
    }
}
