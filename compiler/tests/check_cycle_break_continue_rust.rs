fn main() {
    for i in 0..100 {
        let mut count = 0;
        println("{}", loop {
            while count < 10 {
                if count < 5 {
                    count = count + 1;
                    println_int("{}", count);
                    continue;
                } else {
                    println("{}","Хватит!");
                    break ;
                };
            };
            break "Остановись!";
        });
        if i == 0 {
            continue;
        } else {
            println("{}","Пока не поздно!");
            break;
        };
    };
}