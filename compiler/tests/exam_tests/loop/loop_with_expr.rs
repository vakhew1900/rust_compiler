fn main(){
    let mut num = 1;
    let result = loop
    {
        if num == 4 { break num * 2;}
        num = num + 1;
    };
    println_int("result = {}", result);    // result = 8   
}