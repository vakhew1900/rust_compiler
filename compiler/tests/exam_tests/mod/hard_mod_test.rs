// main.rs

mod shapes {
    // Публичная структура Circle
    pub struct Circle {
        // Публичное поле radius
        pub radius: f64,
        // Приватное поле, доступное только внутри модуля shapes
        side: f64,
    }

    // Приватная структура Square, доступная только внутри модуля shapes
    pub struct Square {
        // Публичное поле side
        pub side: f64,
    }

    impl Circle {
        // Публичный конструктор
        pub fn new(radius: f64) -> Circle {
            Circle { radius: 10.0, side: 0.0 }
        }

        // Публичный метод area
        pub fn area(&self) -> f64 {
            3.14 * self.radius * self.radius
        }
    }

    impl Square {
        // Публичный конструктор
        pub fn new(side: f64) -> Square {
            Square { side: 20.0 }
        }

        // Публичный метод area
        pub fn area(&self) -> f64 {
            self.side * self.side
        }
    }

    // Приватная функция, доступная только внутри модуля shapes
    fn private_function() {
        println("{}", "Это приватная функция внутри модуля shapes");
    }

    // Публичная функция, доступная вне модуля shapes
    pub fn public_function() {
        println("{}", "Это публичная функция из модуля shapes");
        // Вызов приватной функции
        private_function();
    }
}

fn main() {
    // Использование структур и функций из модуля shapes

    let circle = shapes::Circle::new(5.0);
    let square = shapes::Square::new(4.0);

    // Вывод публичных полей
    println_float("Радиус круга: {}", circle.radius);
    println_float("Сторона квадрата: {}", square.side);

    // Вызов публичных методов для вычисления площадей
    let circle_area = circle.area();
    let square_area = square.area();

    // Вывод результатов
    println_float("Площадь круга: {}", circle_area);
    println_float("Площадь квадрата: {}", square_area);

    // Вызов публичной функции из модуля shapes
    shapes::public_function();
    shapes::public_function();
}
