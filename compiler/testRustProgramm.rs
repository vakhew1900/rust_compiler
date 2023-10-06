fn main() {
    // Дополнительные ключевые слова
    let array = [1, 2, 3];
    let vector = vec![4, 5, 6]; // Создание вектора (динамический массив)

    // Integer
    let x = -1;
    let x1 = - 1;
    let x2 = -  1;
    let x3 = -  3;
    let y = 10;
    let z = 10i32;
    let w = 50_10_10;
    let v = 40__10__10;

    // Строковые константы
    let string1: &str = "Привет, мир!"; // Строка в двойных кавычках
    let string2: &str = r"Это строка с 'ро' внутри"; // Raw string
    // Raw строковый литерал в тройных кавычках
    let raw_triple_quoted = r###"Это ##"raw"## строка с тройными кавычками"###;
    let raw_triple_quoted = r"Это \0 \n \t \xFF строка с тройными кавычками";
    let string3: String = String::from("Это строка String"); // Строка типа String
    let string4: String = "Это тоже строка String".to_string(); // Использование to_string()

    // Конкатенация строк
    let concat_string = format!("{} {}", string1, string2);

    // Множественные строки (String Literals)
    let multiline_string = "Это множественная
    строка,
    состоящая из нескольких строк.";

    // Unicode и символы
    let unicode_Q = '\u{0051}';

    // Escaping
    let escaped_string = "Это строка\n с символами: \\n (новая строка)\0, \\t (табуляция) \\0 (терминальный ноль)";

    // Байтовые строки (byte strings)
    let byte_string: &[u8] = b"Hello, World!";
    println!("{:?}", byte_string);

    // Целые числа
    let integer1: i32 = 42;
    let integer2: i64 = 123456789012345;
    let integer3: u64 = 987654321098765;


    // Символы
    let char1: char = 'A';
    let char2: char = 'Б';
    let escaped_char = '\n';
    let unicode_char = '\u{276__4__________}';

    // Арифметические операции
    let sum = integer1 + integer2;
    let difference = integer2 - integer1;
    let product = integer1 * 5;
    let quotient = integer3 / 2;

    // Операции сравнения
    let is_equal = integer1 == integer2;
    let is_not_equal = integer1 != integer2;
    let greater_than = integer2 > integer1;
    let less_than_or_equal = integer1 <= 42;

    // Присваивание
    let mut mutable_variable = 10;
    mutable_variable += 5;
    mutable_variable -= 3;
    mutable_variable *= 2;
    mutable_variable /= 4;

    // Создание одномерного массива (вектора)
    let numbers = vec![1, 2, 3, 4, 5];

    // Доступ к элементам массива
    let first_element = numbers[0]; // Обращение к первому элементу

    // Итерация по элементам массива
    for number in &numbers {
        println!("Элемент массива: {}", number);
    }

    // Изменение элемента массива
    let mut mutable_numbers = vec![10, 20, 30];
    mutable_numbers[1] = 25; // Изменение второго элемента

    // Вывод измененных значений
    println!("Измененный массив: {:?}", mutable_numbers);

    // Добавление элементов в вектор
    mutable_numbers.push(40);

    // Удаление элемента из вектора
    let removed_element = mutable_numbers.pop(); // Удаление последнего элемента

    // 3
    // Целочисленные литералы
    let decimal_integer = 4_2;          // Десятичное целое число (42, _ не несет смысловой нагрузки)
    let hexadecimal_integer = 0x2A;    // Шестнадцатеричное целое число
    let binary_integer = 0b101010;     // Двоичное целое число
    let octal_integer = 0o52;          // Восьмеричное целое число
    let byte_integer: i8 = b'X';       // Байтовое целое число

    // Символьные литералы
    // Escape-последовательности
    let newline = '\n';         // Новая строка
    let tab = '\t';             // Табуляция
    let backslash = '\\';       // Обратный слеш
    let single_quote = '\'';    // Одинарная кавычка
    let double_quote = '\"';    // Двойная кавычка
    let hex_escape = '\x41';    // \xHH - ASCII символы в шестнадцатеричной форме \x7F - предел)
    let unicode_symb = '\u{100__6___}';  //\u{XXXX} - Unicode символы \u{10FFFF} - предел

    // Строковые литералы аналогично
    let quote_escape = "Это строка с символами \" внутри";
    let ascii_escape = "ASCII символы: \x48\x65\x6C\x6C\x6F"; // Hello
    let unicode_escape = "Символы Unicode: \u{0042} \u{0043} \u{0041}";

    // Управляющие структуры
    // if
    let x = 5;
    if x > 0 {
        println!("x положительное");
    } else if x < 0 {
        println!("x отрицательное");
    } else {
        println!("x равно нулю");
    }

    // Сопоставление (match)
    let number = 3;
    match number {
        1 => println!("Один"),
        3 => println!("Три"),
        _ => println!("Другое число"),
    }

    // Сопоставление if let
    let some_value = Some(5);
    if let Some(x) = some_value {
        println!("Значение x: {}", x);
    } else {
        println!("Нет значения");
    }

    //Циклы
    // 1. Бесконечный цикл (loop)
    let mut count = 0;
    loop {
        println!("Бесконечный цикл: {}", count);
        count += 1;
        if count >= 3 {
            break;
        }
    }

    // 2. Цикл с предусловием (while)
    let mut while_count = 0;
    while while_count < 3 {
        println!("Цикл с предусловием: {}", while_count);
        while_count += 1;
    }

    // 3. Цикл с постусловием (do-while)
    let mut do_while_count = 0;
    loop {
        println!("Цикл с постусловием: {}", do_while_count);
        do_while_count += 1;
        if do_while_count >= 3 {
            break;
        }
    }

    // 4. Цикл for-in с диапазоном
    for i in 0..3 {
        println!("Цикл for-in с диапазоном: {}", i);
    }

    // 5. Цикл for-in с коллекцией
    let numbers = vec![1, 2, 3];
    for num in &numbers {
        println!("Цикл for-in с коллекцией: {}", num);
    }

    // 6. Итераторы (map, filter)
    let data = vec![1, 2, 3, 4, 5];
    let result: Vec<_> = data.iter().map(|&x| x * 2).filter(|&x| x > 5).collect();
    println!("Итераторы: {:?}", result);



    // Функции
    // Функция без параметров и возвращаемого значения
    fn simple_function() {
        println!("Привет, мир!");
    }

    // Функция с параметрами
    fn add(x: i32, y: i32) -> i32 {
        x + y
    }

    // Функция с возвращаемым значением, но без параметров
    fn generate_random_number() -> i32 {
        // Генерация случайного числа
        42
    }

    // Функция с параметрами и возвращаемым значением
    fn multiply(x: i32, y: i32) -> i32 {
        x * y
    }

    // Функция с областью видимости (scope)
    fn outer_fn() {
        // Функция внутри outer_fn()
        fn inner_function() {
            println!("Внутренняя функция");
        }

        inner_function(); // Вызов внутренней функции
    }

    // Функция с использованием замыкания (closure)
    fn use_closure() {
        let add_one = |x| x + 1;
        let result = add_one(5);
        println!("Результат замыкания: {}", result); // Вывод: Результат замыкания: 6
    }

    // Функция как аргумент другой функции (функции высшего порядка)
    fn apply_function(func: fn(i32) -> i32, x: i32) -> i32 {
        func(x)
    }

    fn double(x: i32) -> i32 {
        x * 2
        let x = 0o_;
    }
    fn use_higher_order_function() {
        let result = apply_function(double, 5);
        println!("Результат функции высшего порядка: {}", result); // Вывод: Результат функции высшего порядка: 10
    }

    // Обобщенные (generic) функции
    fn generic_function<T>(x: T) {
        println!("Значение: {:?}", x);
    }

    //Ввод
    io::stdin().read_line(&mut input).expect("Не удалось прочитать строку");

    // struct, trait, impl
    // Определяем трейт Animal
    trait Animal {
        // Абстрактный метод, который должен быть реализован всеми типами, реализующими трейт Animal
        fn speak(&self);
    }

    // Структура Dog, которая реализует трейт Animal
    struct Dog {
        name: String,
    }

    // Реализация трейта Animal для структуры Dog
    impl Animal for Dog {
        fn speak(&self) {
            println!("Собака {} говорит: Гав-гав!", self.name);
        }
    }

    // Структура Cat, которая реализует трейт Animal
    struct Cat {
        name: String,
    }

    // Реализация трейта Animal для структуры Cat
    impl Animal for Cat {
        fn speak(&self) {
            println!("Кот {} говорит: Мяу-мяу!", self.name);
        }
    }
    let dog = Dog { name: "Барсик".to_string() };
    let cat = Cat { name: "Тузик".to_string() };
    dog.speak();
    cat.speak();
    // Массивы
    // Массив массивов
    let matrix: [[i32; 3]; 3] = [
        [1, 2, 3],
        [4, 5, 6],
        [7, 8, 9],
    ];

    // Вектор векторов
    let matrix: Vec<Vec<i32>> = vec![
        vec![1, 2, 3],
        vec![4, 5, 6],
        vec![7, 8, 9],
    ];
    // Логические операции
    // Комбинирование
    let a = true;
    let b = false;
    let c = true;

    let result1 = a && b || c;
    let result2 = !(a && b) || c;

    // Операции над строками
    // Конкатенация строк с использованием оператора +
    let hello = "Hello, ";
    let world = "world!";
    let greeting = hello.to_string() + world;
    println!("{}", greeting); // Результат: "Hello, world!"

    // Форматирование строк с макросом format!
    let name = "Alice";
    let age = 30;
    let formatted = format!("Имя: {}, Возраст: {}", name, age);
    println!("{}", formatted); // Результат: "Имя: Alice, Возраст: 30"

    // Индексирование и срезы строк
    let text = "Rust Programming";
    let first_char = &text[0..1];
    let last_word = &text[5..];
    println!("Первый символ: {}", first_char); // Результат: "R"
    println!("Последнее слово: {}", last_word); // Результат: "Programming"

    // Применение методов на строку
    let text = "This is a test.";
    let contains_test = text.contains("test");
    println!("Содержит 'test': {}", contains_test); // Результат: true

    // Области видимости
    mod my_module {
        pub(crate) struct MyStruct {
            pub my_field: i32,
        }

        impl MyStruct {

            pub fn my_method(&self) {
                println!("Публичный метод");
            }
        }
    }

    let instance = my_module::MyStruct { my_field: 42 };

    // Объявление перечислимого типа данных
    enum Color {
        Red,
        Green,
        Blue,
    }
    // Создание переменных с типом данных Color
    let favorite_color = Color::Blue;

    // Ссылки в Rust
    // Создание переменных
    let x = 42;
    let y = 24;

    // Ссылки и заимствование
    let reference_x = &x; // Неизменяемая ссылка на x
    println!("Значение x: {}", x);
    println!("Значение, на которое ссылается reference_x: {}", *reference_x);

    // reference_x = &y; // Ошибка! Нельзя изменить ссылку на другую переменную

    // Мутабельные ссылки
    let mut mutable_x = x; // Создаем копию x
    println!("Изначальное значение mutable_x: {}", mutable_x);

    let reference_mutable_x = &mut mutable_x; // Мутабельная ссылка на mutable_x
    reference_mutable_x += 10; // Меняем значение через ссылку

    println!("Новое значение mutable_x: {}", mutable_x);

    // Срезы
    let arr = [1, 2, 3, 4, 5];
    let slice = &arr[1..4]; // Срез массива arr с индексами 1, 2, 3

    println!("Срез: {:?}", slice);

    // Владение и переход владения
    let string1 = String::from("Привет");
    let string2 = string1; // Переход владения
    // println!("string1: {}", string1); // Ошибка! string1 больше не доступна

    println!("string2: {}", string2);

    // Клонирование
    let string3 = string2.clone();
    println!("string2: {}", string2); // string2 по-прежнему доступна

    println!("string3: {}", string3);

    // Примеры ссылок на структуры
    #[derive(Debug)]
    struct Point {
        x: i32,
        y: i32,
    }

    let point = Point { x: 5, y: 10 };
    let reference_point = &point;

    println!("point: {:?}", point);
    println!("reference_point: {:?}", reference_point);


    /* Многострочный коммент Все, что находится между символами /* и */
    pub fn my_method(&self) {
                println!("Публичный метод");
            }
     */

   let x: char = '';
}

/* ML_COMMENT START
*/

fn func_between_comment()
{
}

/* ML_COMMENT FINISH
*/


// Comment

/* ML_COMMENT1 */  static let between_comment = 10; /* ML_COMMENT2 */

//integer in 8 system
static let x = 0o70;
static let y = 0o70_i32;
static let z = 0o_70_i32;

//integer in 2 system
static let x = 0b1111_1111_1001_0000;
static let y = 0b1111_1111_1001_0000i32;
static let z = 0b________1;

//integer in 16 system
static let x = 0xff;
static let y = 0xffi32;
static let z = 0x_1fi32;

// Double
static let x = 1234.0f64;
static let y = 125.0;
static let z = 1.5E+5;
static let x = 1.6E-5;
static let y = 1.3444e+10;
static let z = 123.;
static let x = 111.1E+99;
static let y = 12E+99_f64;
static tmp1 = '\u{002F}';
static tmp1 = '\u{132F}';
static xy = 'xy';
let x = 1.;
let x = .123;
let x = .123E+99f64;
let x = .123E+99;

// if (x == 222) {let z = 64 ;}
let 121212incorrextVar = 1;
0invalidSuffix;
123AFB43;
0b010a;
0xAB_CD_EF_GH;
0b1111_f32; 

$asdasfmlkfa

/* Not Closed Comment

