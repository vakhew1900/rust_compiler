fn main(){
    let mut n = 0;
    while n < 10
    {
		if n > 8 {
			break;
		}
        println_int("n = {}", n);
        n = n + 1;
    }
    println("{}", "Конец программы");    
}