// Определение первого трейта
trait Shape {
    fn area(&self) -> f64;
}

// Определение второго трейта, наследующего от Shape
trait ColoredShape: Shape {
    fn color(&self) -> String;
}

// Структура, реализующая первый трейт
struct Circle {
    radius: f64,
}

// Реализация трейта для структуры Circle
impl Shape for Circle {
    fn area(&self) -> f64 {
        3.14 * self.radius * self.radius
    }
}

// Структура, реализующая оба трейта
struct ColoredCircle {
    radius: f64,
    color: String,
}

// Реализация трейта для структуры ColoredCircle
impl Shape for ColoredCircle {
    fn area(&self) -> f64 {
        3.14 * self.radius * self.radius
    }
}

// Реализация трейта для структуры ColoredCircle
impl ColoredShape for ColoredCircle {
    fn color(&self) -> String {
        self.color
    }
}

// Главная функция
fn main() {
    // Создание объектов и вызов методов
    let circle = Circle { radius: 2.0 };
    println_float("Circle Area: {}", circle.area());

    let colored_circle = ColoredCircle {
        radius: 3.0,
        color: "Red"
    };
    println_float("Colored Circle Area: {}", colored_circle.area());
    println("Colored Circle Color: {}", colored_circle.color());
}
