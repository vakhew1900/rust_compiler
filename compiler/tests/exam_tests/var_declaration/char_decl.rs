fn main(){
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
    //юникод работает без ___
    println_char("{}", newline);
    println_char("{}", tab);
    println_char("{}", backslash);
    println_char("{}", single_quote);
    println_char("{}", double_quote);
    println_char("{}", hex_escape);
    println_char("{}", unicode_symb);
}