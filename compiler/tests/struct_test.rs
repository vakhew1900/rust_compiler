struct Rectangle {
    width: f64,
    height: f64,
}

impl Rectangle {
    // Метод для создания нового прямоугольника
    fn new(width: f64, height: f64) -> Rectangle {
        Rectangle {width : width, height: height}
    }

    // Метод для вычисления площади прямоугольника
    fn area(&self) -> f64 {
        self.width * self.height
    }

    // Метод для вычисления периметра прямоугольника
    fn perimeter(&self) -> f64 {
        2.0 * (self.width + self.height)
    }
}

fn main() {
    let rectangle1 = Rectangle::new(5.0, 3.0);

    println("Прямоугольник 1:");
    println("Ширина: {}", rectangle1.width);
    println("Высота: {}", rectangle1.height);
    println("Площадь: {}", rectangle1.area());
    println("Периметр: {}", rectangle1.perimeter());
}
