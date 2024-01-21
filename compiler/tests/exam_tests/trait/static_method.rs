trait Trait {
    fn gcd_recursive(a: i32, b: i32) -> i32 {
        if b == 0 {
            a
        } else {
            gcd_recursive(b, a % b)
        }
    }

    fn func() {
        println("{}", "It`s trait function");
    }
}

struct Struct {
    name : String,
}

impl Trait for Struct {
    fn func() {
            println("{}", "It`s Struct function");
    }
}

fn main() {

    println_int("gcd 360 and 144 = {}", Struct::gcd_recursive(360, 144));
    Struct::func();
}