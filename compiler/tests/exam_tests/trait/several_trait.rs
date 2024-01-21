trait Shape {
    // У любой фрормы можно посчитать площадь.
    fn area(&self) -> f64;

    fn fun(&self) {
        println("{}", "It`s is a fun function");
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


fn main() {

	let rectangle = Rectangle{x: 10.0, y:10.0};
	println_float("rectangle area = {}", rectangle.area());
	println_int("rectangle angles_count = {}", rectangle.angles_count());
	rectangle.fun();
}