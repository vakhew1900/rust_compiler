fn recursive_function(character: char, count: i32) -> char {
    if count == 0 {
        character
    } else {
        println_char("{}", character);
        recursive_function(character, count - 1)
    }
}

fn main() {
    println("{}", "Введите символ:");

    let character = read_char();

    println("{}", "Введите количество повторений:");

    let mut count : i32 = read_int();

    let result = recursive_function(character, count);

    println_char(" Последний раз: {}", result);
}
