struct MyStruct {
    data: i32,
}

fn by_value(mut obj: MyStruct) {
    println_int("Function by_value: data before = {}", obj.data);
    obj.data = 999;
    println_int("Function by_value: data modified = {}", obj.data);
}

fn by_reference(obj: &mut MyStruct) {
    println_int("Function by_reference: data before = {}", obj.data);
    obj.data = 888;
    println_int("Function by_reference: data modified = {}", obj.data);
}

mod geometry {

    pub struct Circle {

        pub radius: f64,

        side: f64,
    }


    pub mod triangle {

        pub struct Triangle {

            pub base: f64,

            pub height: f64,
        }

        impl Triangle {

            pub fn new(base: f64, height: f64) -> Triangle {
                Triangle { base: base, height: height}
            }


            pub fn area(&self) -> f64 {
                0.5 * self.base * self.height
            }
        }


        fn private_function() {
            println("{}", "Это приватная функция внутри модуля triangle");
        }


        pub fn public_function() {
            println("{}", "Это публичная функция из модуля triangle");

            private_function();
        }
    }


    mod inner_module {

        pub struct InnerStruct {
            pub field: i32,
        }


        pub fn inner_function() {
            println("{}", "Это внутренняя функция из модуля inner_module");
        }
    }


    pub fn use_inner_module() {

        let inner_instance = inner_module::InnerStruct { field: 42 };


        println_int("Поле InnerStruct: {}", inner_instance.field);
        inner_module::inner_function();
    }

    impl Circle {

        pub fn new(radius: f64) -> Circle {
            Circle { radius: radius, side: 0.0 }
        }


        pub fn area(&self) -> f64 {
            3.14 * self.radius * self.radius
        }
    }


    fn private_function() {
        println("{}", "Это приватная функция внутри модуля geometry");
    }


    pub fn public_function() {
        println("{}", "Это публичная функция из модуля geometry");

        private_function();
    }
}


fn main() {
    let mut ch : char = 'x';
    let mut integ : i32 = 1000000000;
    let mut f : f32 = 1.2;
    let mut b : bool = false;
    let mut strs : String = "Petya";
    let x = 23___;
    println_int("{}", x);

    let decimal_integer = 4_2;          // Десятичное целое число (42, _ не несет смысловой нагрузки)
    let hexadecimal_integer = 0x2A;    // Шестнадцатеричное целое число
    let binary_integer = 0b101010;     // Двоичное целое число
    let octal_integer = 0o52;          // Восьмеричное целое число

    println_int("{}", decimal_integer);
    println_int("{}", hexadecimal_integer);
    println_int("{}", binary_integer);
    println_int("{}", octal_integer);

    {
        let x = "abc";
        let y = "aaa";

        println_bool("equal res {}", x == y);
        println_bool("not equal res {}", x != y);
        println_bool("greater res {}", x > y);
        println_bool("lesser res {}", x < y);
        println_bool("ge res {}", x >= y);
        println_bool("le res {}", x <= y);
    }

    let my_object = MyStruct { data: 42 };

    by_value(my_object);
    let mut my_object_ref = MyStruct { data: 123 };

    by_reference(&mut my_object_ref);

    println_int("Main function: data = {}", my_object_ref.data);

    let result = gcd_recursive(24, 36);

    let circle = geometry::Circle::new(5.0);
    let triangle = geometry::triangle::Triangle::new(3.0, 4.0);

    println_float("Радиус круга: {}", circle.radius);
    println_float("Основание треугольника: {}", triangle.base);
    println_float("Высота треугольника: {}", triangle.height);

    let circle_area = circle.area();
    let triangle_area = triangle.area();

    println_float("Площадь круга: {}", circle_area);
    println_float("Площадь треугольника: {}", triangle_area);

    geometry::public_function();

    geometry::triangle::public_function();

    geometry::use_inner_module();

    {
        let mut n = 0;
        while n < 10
        {
            if n > 8 {
                break;
            }
            println_int("n = {}", n);
            n = n + 1;
        }
    }

    {
        let mut n = 0;
        while n < 10
        {
            n = n + 1;
            if n == 9 {
                continue;
            }
            println_int("n = {}", n);
        }
    }

    // Полиморфизм
    {
        let array: [Shape; 2] = [Circle{r:10.1}, Rectangle{x: 10.0, y:10.0} ];

        for elem in array {
            println_float("Shape area {} = ", elem.area());
        }
    }

    {
        let x = 10;
        let n = 0;
        let a = (x != 10);
        let k = (x != 10) && (x / n == 1);
        let all = !((x != 10) && (x / n == 1));
        println_bool("{}", a);
        println_bool("{}", k);
        println_bool("{}", all);
        let mut b = !( a && (x / n == 1));
        println_bool("{}", b);
        if (!((x != 10) && (x / n == 1))){
            println("result is {}", "true");
        } else {
            println("result is {}", "false");
        }
    }

    //left operand and
    {
        let x = 10;
        let n = 0;
        let y = (x != 10) && (x / n == 1) ;
        println_bool("{}", y);
    }

    //left operand or
    {
        let x = 10;
        let n = 0;
        let y = (x == 10) || (x / n == 1) ;
        println_bool("{}", y);
    }

    //enum
    {
        // Создание переменных с типом данных Color
        let COLOR1 = Color::Blue;
        Color::getBright(COLOR1);
    }

    // autofill matrix
    {
        let c = 23;
        let mut matrix = [ [c + 12 * 13 % 46; 3] ; 3];

        for array in matrix {
            for x in array {
                print_int("{} ", x);
            }
            println("{}", "");
        }
    }

    //loop
    {
        let mut num = 1;
        let result = loop
        {
            if num == 4 { break num * 2;}
            num = num + 1;
        };
        println_int("result = {}", result);    // result = 8
    }

    //arithmetic
    {
        let integer1 = 42;
        let mut integer2: i32 = 500;
        const integer3: i32 = 100;

        let sum = integer1 + integer2;
        let difference = integer2 - integer1;
        let product = integer1 * 5;
        let quotient = (-integer3) / 2;

        let x = -    integer1; //унарный минус
        let x1 = -        9;

        println_int("{}", sum);
        println_int("{}", difference);
        println_int("{}", product);
        println_int("{}", quotient);
        println_int("{}", x);
        println_int("{}", x1);

        let mix = integer1 - integer2 + integer3;
        println_int("{}", mix);
    }

    //comparing
    {
        let integer1: i32 = 42;
        let integer2: i32 = 500;
        let integer3: i32 = 100;
        let is_equal = integer1 == integer2;
        let is_not_equal = integer1 != integer2;
        let greater_than = integer2 > integer1;
        let lt = integer2 < integer1;
        let gte = integer1 >= 42;
        let less_than_or_equal = integer1 <= 42;

        println_bool("{}", is_equal);
        println_bool("{}", is_not_equal);
        println_bool("{}", greater_than);
        println_bool("{}", lt);
        println_bool("{}", gte);
        println_bool("{}", less_than_or_equal);
    }

    //shield string
    {
        let mut strg: String = r###"Это ##"raw"## строка с тройными кавычками"###;
        println("{}", strg);
        let raw = r"Это \0 \n \t \xFF строка с тройными кавычками";
        println("{}", raw);
        let escaped_string = "Это строка с символами:\n \\n (новая строка),\t \\t (табуляция)\0 \\0 (терминальный ноль)";
        println("{}", escaped_string);
    }

    //char decl
    {
        let char1: char = 'A';
        let char2: char = 'B';
        let escaped_char = '\n';
        let unicode_char = '\u{007__7__________}';

        println_char("{}", char1);
        println_char("{}", char2);
        println_char("{}", escaped_char);println_char("{}", unicode_char);

        let newline = '\n';         // Новая строка
        let tab = '\t';             // Табуляция
        let backslash = '\\';       // Обратный слеш
        let single_quote = '\'';    // Одинарная кавычка
        let double_quote = '\"';    // Двойная кавычка
        let hex_escape = '\x41';    // \xHH - ASCII символы в шестнадцатеричной форме \x7F - предел)
        let unicode_symb = '\u{0077}';  //\u{XXXX} - Unicode символы \u{10FFFF} - предел

        println_char("{}", newline);
        println_char("{}", tab);
        println_char("{}", backslash);
        println_char("{}", single_quote);
        println_char("{}", double_quote);
        println_char("{}", hex_escape);
        println_char("{}", unicode_symb);
    }
}

fn gcd_recursive(a: i32, b: i32) -> i32 {
    if b == 0 {
        a
    } else {
        gcd_recursive(b, a % b)
    }
}

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

// Объявление перечислимого типа данных
enum Color {
    Red = 1,
    Green = 2,
    Blue = 7,
}

impl Color{
    fn getBright(c : Color){
        if (c == Color::Blue) {
            println("{}", "Ярко");
        } else {
            println("{}", "Неярко");
        }
    }
}