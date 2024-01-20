fn main() {

    let mut strg: String = r###"Это ##"raw"## строка с тройными кавычками"###;
    println("{}", strg);
    let raw = r"Это \0 \n \t \xFF строка с тройными кавычками";
       println("{}", raw);
}