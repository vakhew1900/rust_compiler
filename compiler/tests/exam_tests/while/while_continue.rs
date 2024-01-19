fn main(){
    let mut n = 0;
    while n < 10
    {   
	    n = n + 1;
		if n == 9 {
			continue;
		}
        println_int("n = {}", n);
    }
    println("{}", "Конец программы");    
}