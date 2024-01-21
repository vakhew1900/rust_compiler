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

struct Circle {
    r: f64,
}

// Круг является формой
impl Shape for Circle {
    fn area(&self) -> f64 {
        self.r * self.r * 3.14   }
}

// Принимаем что угодно, реализующее трейт Shape.
fn areas_sum(shape1: impl Shape, shape2: impl Shape) -> f64 {
    shape1.area() + shape2.area()
}


fn main() {

	 let circle = Circle{r:10 as f64};
	 let rectangle = Rectangle{x: 10.0, y:10.0};

     println_float("areas_sum = {}", areas_sum(circle, rectangle))
}