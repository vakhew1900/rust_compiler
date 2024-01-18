fn main() {
    let number=9;

    if number < 10 {
        println("Число меньше 10.");
    } else {
        if (10..20).contains(&number) {
            println("Число находится в диапазоне от 10 до 20 включительно.");
        } else {
            println("Число больше 20.");
        }
    }
}