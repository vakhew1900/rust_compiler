// main.rs

mod geometry {
    pub const PI: f64 = 3.14;

    // Вложенный модуль внутри triangle
    pub mod nested {
        // Функция, использующая super:: для обращения к родительскому модулю
        pub fn print_from_nested() {
            println!("{}", "Вызов ПРИВАТНОЙ функции через супер:");
            super::private_function();
        }
    }

    // Публичная структура Circle
    pub struct Circle {
        // Публичное поле radius
        pub radius: f64,
        // Приватное поле, доступное только внутри модуля Circle
        side: f64,
    }

    // Публичный модуль Triangle внутри модуля geometry
    pub mod triangle {


        // Публичная структура Triangle
        pub struct Triangle {
            // Публичное поле base
            pub base: f64,
            // Публичное поле height
            pub height: f64,
        }

        impl Triangle {
            // Публичный конструктор
            pub fn new(base: f64, height: f64) -> Triangle {
                Triangle { base: base, height: height}
            }

            // Публичный метод area
            pub fn area(&self) -> f64 {
                0.5 * self.base * self.height
            }
        }

        // Приватная функция, доступная только внутри модуля triangle
        fn private_function() {
            println!("{}", "Это приватная функция внутри модуля triangle");
        }

        // Публичная функция, доступная вне модуля triangle
        pub fn public_function() {
            println!("{}", "Это публичная функция из модуля triangle");
            // Вызов приватной функции
            private_function();
        }
    }

    // Непубличный модуль inner_module
    mod inner_module {
        pub const PI: f64 = 6.28;
        // Приватная структура, доступная только внутри модуля inner_module
        pub struct InnerStruct {
            pub field: i32,
        }

        // Публичная функция, доступная только внутри модуля inner_module
        pub fn inner_function() {
            // self::
            println!("Это внутренняя функция inner_module PI is: {}", self::PI);
        }
    }

    // Публичный метод, использующий непубличный модуль
    pub fn use_inner_module() {
        // Создаем экземпляр структуры из inner_module
        let inner_instance = inner_module::InnerStruct { field: 42 };

        // Выводим значение поля и вызываем внутреннюю функцию
        println!("Поле InnerStruct: {}", inner_instance.field);
        inner_module::inner_function();
    }

    impl Circle {
        // Публичный конструктор
        pub fn new(radius: f64) -> Circle {
            Circle { radius: radius, side: 0.0 }
        }

        // Публичный метод area
        pub fn area(&self) -> f64 {
            //обращение к корневому модулю через крейт
            crate::geometry::PI * self.radius * self.radius
        }
    }

    // Приватная функция, доступная только внутри модуля geometry
    fn private_function() {
        println!("{}", "Это приватная функция внутри модуля geometry");
    }

    // Публичная функция, доступная вне модуля geometry
    pub fn public_function() {
        println!("{}", "Это публичная функция из модуля geometry");
        // Вызов приватной функции
        private_function();
    }
}

fn main() {
    // Использование структур и функций из модуля geometry и его подмодуля triangle

    let circle = geometry::Circle::new(5.0);
    let triangle = geometry::triangle::Triangle::new(3.0, 4.0);

    // Вывод публичных полей
    println!("Радиус круга: {}", circle.radius);
    println!("Основание треугольника: {}", triangle.base);
    println!("Высота треугольника: {}", triangle.height);

    // Вызов публичных методов для вычисления площадей
    let circle_area = circle.area();
    let triangle_area = triangle.area();

    // Вывод результатов
    println!("Площадь круга: {}", circle_area);
    println!("Площадь треугольника: {}", triangle_area);

    // Вызов публичной функции из модуля geometry
    geometry::public_function();

    // Вызов публичной функции из подмодуля triangle
    geometry::triangle::public_function();

    // Вызов публичной функции, использующей непубличный модуль
    geometry::use_inner_module();

    geometry::nested::print_from_nested();
}
