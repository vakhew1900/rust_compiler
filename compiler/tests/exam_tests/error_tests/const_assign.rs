fn main(){
    const L = 9; // ошибка что нет типа
    const MAX_VAL: i32 = 100;

    MAX_VAL = 90;

    printl_int("{}", MAX_VAL);
}