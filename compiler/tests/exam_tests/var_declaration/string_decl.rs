fn main() {
    // не работают

    // Жесткая ошибка - конец на терминальном нуле
//     let escaped_string = "Это строка с символами:\n \\n (новая строка),\t \\t (табуляция)\0 \\0 (терминальный ноль)";
//     println("{}", escaped_string);
//     println("{}", s);
    //Все что ниже - работает
    let quote_escape = "Это строка с символами \" внутри";
    let ascii_escape = "ASCII символы: \x48\x65\x6C\x6C\x6F"; // Hello
    let unicode_escape = "Символы Unicode: \u{0042} \u{0043} \u{0041}";
    println("{}", quote_escape);
    println("{}", ascii_escape);
    println("{}", unicode_escape);

        let multiline_string = "Это множественная
    строка,
    состоящая из нескольких строк."; //- ошибка вывода
        println("{}", multiline_string);
}