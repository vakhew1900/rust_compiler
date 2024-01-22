// struct, trait, impl
// Определяем трейт Animal
trait Animal {
    // Абстрактный метод, который должен быть реализован всеми типами, реализующими трейт Animal
    fn speak(&self);
}

// Структура Dog, которая реализует трейт Animal
struct Dog {
    name: String,
}

// Реализация трейта Animal для структуры Dog
impl Animal for Dog {
    fn speak(&self) {
        println("Собака {} говорит: Гав-гав!", self.name);
    }
}

// Структура Cat, которая реализует трейт Animal
struct Cat {
    name: String,
}

// Реализация трейта Animal для структуры Cat
impl Animal for Cat {
    fn speak(&self) {
        println("Кот {} говорит: Мяу-мяу!", self.name);
    }
}

fn main(){
    let dog = Dog { name: "Тузик" };
    let cat = Cat { name: "Мурзик" };
    dog.speak();
    cat.speak();
}