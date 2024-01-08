trait Shape {
    // У любой фрормы можно посчитать площадь.
    fn area(&self) -> f32;
}

trait HasAngles: Shape {
    // У любой фигуры с углами можно посчитать количество углов.
    fn angles_count(&self) -> i32;
}

struct Rectangle {
    x: f32,
    y: f32,
}

// Прямоугольник является формой.
impl Shape for Rectangle {
    fn area(&self) -> f32 {
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
    r: f32,
}

// Круг является формой
impl Shape for Circle {
    fn area(&self) -> f32 {
        self.r.powi(2) * 3.14   }
}


// Принимаем что угодно, реализующее трейт Shape.
fn areas_sum(shape1: impl Shape, shape2: impl Shape) -> f32 {
    shape1.area() + shape2.area()
}

fn foo(rectangle: Rectangle, circle: Circle) {
    // Можем передать две разные фигуры.
    let sum = areas_sum(rectangle, circle);
}


fn main() {

    let array: [&Shape; 2] = [&Circle{r:10.1}, &Rectangle{x: 10.0, y:10.0} ];
    
  //  let govin: Vec<&dyn Shape> = vec![&Circle{r:10.1}, &Rectangle{x: 32.1, y:32.2} ];
    println!("Hello World {}", array[1].area());
}