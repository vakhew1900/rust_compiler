fn main() {
    let quote_escape = "Это строка с символами \" внутри ___";
    let ascii_escape = "ASCII символы: \x48\x65\x6C\x6C\x6F"; // Hello
    let unicode_escape = "Символы Unicode: \u{00__42_} __ \u{0043} \u{0041}";
    println("{}", quote_escape);
    println("{}", ascii_escape);
    println("{}", unicode_escape);

    let multiline_string = "Это множественная
    строка,
    состоящая из нескольких строк."; //- ошибка вывода
    println("{}", multiline_string);
}