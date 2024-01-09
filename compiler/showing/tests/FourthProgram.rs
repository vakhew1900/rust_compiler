trait NumberOperation {
    fn is_even(&self) -> bool;
}

impl NumberOperation for i32 {
    fn is_even(&self) -> bool {
        self % 2 == 0
    }
}

fn main() {
    let number = 10;

    let mut current = 1;
    while ( current <= number) {
        if ( current.is_even()) {
            println("Число {} - четное.", current);
        } else {
            println("Число {} - нечетное.", current);
        };
        current = current + 1;
    };

    let mut counter = 1;
    loop {
        if ( counter > number ) {
            break;
        };
        println("Counter: {}", counter);
        counter = current + 1;
    };
}
