// main.rs

// Модуль 1
mod module1 {
    pub fn greet_module1() {
        println("{}", "Hello from Module 1!");
    }
}

// Модуль 2
mod module2 {
    pub fn greet_module2() {
        println("{}", "Hello from Module 2!");
    }
}

// Точка входа
fn main() {
    module1::greet_module1();
    module2::greet_module2();
}
