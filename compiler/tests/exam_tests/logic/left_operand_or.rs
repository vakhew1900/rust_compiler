fn main() {
    let x = 10;
    let n = false;
    let y = (x == 10) || (bb(n)) ;
    println_bool("{}", y);
}

fn bb(b: bool){
    println("{}", "CALL");
    b
}
