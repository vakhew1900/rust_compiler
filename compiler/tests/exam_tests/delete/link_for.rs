fn main() {

    let numbers: [i32; 7] = [1, 2, 3, 5, 8, 16, 25];

    for number in &numbers {
        println_int("number ={}", number);
    }

    println_int("{}", numbers[0]);
}