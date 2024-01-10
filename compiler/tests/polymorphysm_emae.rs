trait Shape {
    // У любой фрормы можно посчитать площадь.
    fn area(&self) -> f64;
}


trait HasAngles: Shape {
    // У любой фигуры с углами можно посчитать количество углов.
    fn angles_count(&self) -> i32;
	
	fn area(&self) -> f64 {
        4
    }
}

trait HasAngles2: Shape {
    // У любой фигуры с углами можно посчитать количество углов.
    fn angles_count1(&self) -> i32;
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

fn foo(rectangle: Rectangle, circle: Circle) {
    // Можем передать две разные фигуры.
    let sum = areas_sum(rectangle, circle);
}

impl Circle { 
	fn fun() { 
		"fag";
	}
}


fn main() {
	
	//let array: [Circle; 2] = [Circle{r:10.1}, Circle{r:10.1} ];
    let array: [Shape; 2] = [Circle{r:10.1}, Rectangle{x: 10.0, y:10.0} ];
    
  //  let govin: Vec<&dyn Shape> = vec![&Circle{r:10.1}, &Rectangle{x: 32.1, y:32.2} ];
    println_float("Hello World {}", array[1].area());
	
	let rectangle = Rectangle{x: 10.0, y:10.0};
	rectangle.area();
	rectangle.angles_count();
	//rectangle.fun();
}