fn main(){
    for num in 1..6
    {
		if num == 3 {
			continue;
		}
        println_int("num = {}", num);
    }
    println("{}","Конец программы");    
}