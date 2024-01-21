trait Trait {
    const number1: i32 = 100;
    const number2: i32 = 150;
}

struct Struct {
    name : String,
}

trait Trait2 {

}


impl Trait for Struct {
    const number2: i32 = 200;
}

fn main() {

    println_int("number1 = {}", Struct::number1);
    println_int("number2 = {}", Struct::number2);
}