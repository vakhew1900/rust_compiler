use std::io;

fn main() {
    let mut name = String::new();

    println("Введите ваше имя: ");
    io::stdin().read_line(&mut name).expect("Не удалось прочитать строку");

    let name = name.trim();

    println("Привет! {}", name);
}
