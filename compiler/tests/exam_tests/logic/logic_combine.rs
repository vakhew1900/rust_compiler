fn main(){
    // Логические операции
    // Комбинирование
    let a = true;
    let b = false;
    let c = true;
    //let result1 = a && true;
    let result1 = a && b || c;
    let result2 = !(a && b) || c;
    println_bool("{}", result1);
    println_bool("{}", result2);
}