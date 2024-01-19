fn main(){
    let mut n = 1;

    loop{
		n = n  + 1;
		if n == 5 {
			continue;
		}
        println_int("n = {}", n);
        if n == 10{
           break;
        }
    }
    println("{}", "Конец программы");    
}