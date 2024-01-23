fn main() {

    let mut numbers: [i32; 7] = [1, 2, 3, 5, 8, 16, 25];

    for number in &mut numbers {
        number = number + 1;
        println_int("number ={}", number);
    }

    println_int("{}", numbers[0]);
}