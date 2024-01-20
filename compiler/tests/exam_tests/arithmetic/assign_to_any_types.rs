fn main(){
    let integer1: i32 = 42;
    let c: char = 'k';
    let mut f: f32 = 1.2;

    f = integer1; // mismatched types
    println_float("{}", f);
}