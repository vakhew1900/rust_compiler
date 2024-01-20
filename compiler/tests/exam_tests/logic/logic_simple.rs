fn main(){
    let a = true;
    let b = false;
    let c = true;

    let r3 : bool = b || a;
    let r4 : bool = a && !b;
    println_bool("{}", r3);
    println_bool("{}", r4);
}