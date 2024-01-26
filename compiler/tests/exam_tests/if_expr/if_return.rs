fn main() {
    let number = 0;

    let result = check_number(number);

    println("Result: {}", result);
}

fn check_number(number: i32) -> String {
    if number < 0 {
        return "Negative";
    } else if number == 0 {
        return "Zero";
    } else {
        return "Positive";
    }
    return "bebebe";
}
