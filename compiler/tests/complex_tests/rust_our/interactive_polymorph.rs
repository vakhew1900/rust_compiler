trait Shape {
    // У любой фрормы можно посчитать площадь.
    fn area(&self) -> f64 {
        println("{}",  "из Shape");
    }

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
        println("{}",  "из Rectangle");
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

        println("{}",  "из Circle");
        self.r * self.r * 3.14   }
}

fn main() {

	 let mut array: [Shape; 2] = [Circle{r:10.1}, Rectangle{x: 10.0, y:10.0} ];

      println("{} ", "Введите 1, если хотите чтобы второй элемент был кругом");
      let x = read_int();

      if x == 1 {
        array[1] = Circle{r:10.0};
      }

      for elem in array {
       println_float("Shape area = {}", elem.area());
      }

}