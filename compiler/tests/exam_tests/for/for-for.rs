fn main(){
    for i in 1..6
    {
		if i == 2 {
			continue;
		}
		for j in 1..5 {
			if j == 3 {
				continue;
			}
			
			println_int("i ={}", i);
			println_int("j ={}", j );
		}
    }
    println("{}","Конец программы");    
}