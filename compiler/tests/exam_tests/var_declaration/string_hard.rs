fn main() {

    let escaped_string = "Это строка с символами:\n \\n (новая строка),\t \\t (табуляция)\0 \\0 (терминальный ноль)";
    println("{}", escaped_string);
}