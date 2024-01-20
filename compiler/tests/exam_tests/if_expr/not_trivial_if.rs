fn main() {

    let x = 10;
    let n = 0;
    let a = (x != 10);
    let k = (x != 10) && (x / n == 1);
    let all = !((x != 10) && (x / n == 1));
    println_bool("{}", a);
    println_bool("{}", k);
    println_bool("{}", all);
    let mut b = !( a && (x / n == 1));
    println_bool("{}", b);
    if (!((x != 10) && (x / n == 1))){
        println("result is {}", "true");
    }
}
