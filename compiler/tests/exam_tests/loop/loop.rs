fn main(){
    let mut n = 1;

    loop{
        println_int("n = {}", n);
        n = n  + 1;
        if n == 10{
           break;
        }
    }
    println("{}", "Конец программы");    
}