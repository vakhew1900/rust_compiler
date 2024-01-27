use std::io;

trait Shape {
    // У любой формы можно посчитать площадь.
    fn area(&self) -> f64;

    fn fun(&self) {
        println!("It's a fun function");
    }
}

trait HasAngles: Shape {
    // У любой фигуры с углами можно посчитать количество углов.
    fn angles_count(&self) -> i32;
}

struct Rectangle {
    x: f64,
    y: f64,
}

// Прямоугольник является формой.
impl Shape for Rectangle {
    fn area(&self) -> f64 {
        self.x * self.y
    }
}

// Прямоугольник является фигурой с углами.
impl HasAngles for Rectangle {
    fn angles_count(&self) -> i32 {
        4
    }
}

struct Circle {
    r: f64,
}

// Круг является формой
impl Shape for Circle {
    fn area(&self) -> f64 {
        self.r * self.r * 3.14
    }
}

fn main() {
    let mut array: [&dyn Shape; 2] = [&Circle{r:10.1}, &Rectangle{x: 10.0, y:10.0} ];

    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Не удалось прочитать строку");
    let x: i32 = input.trim().parse().expect("Ошибка при преобразовании в целое число");

    if x == 1 {
        array[1] = &Circle{r:10.0};
    }

    for elem in array {
        println!("Shape area = {}", elem.area());
    }
}
