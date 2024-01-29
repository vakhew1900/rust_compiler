fn main(){
    let integer1: i32 = 50;
    {
        let integer1: i32 = 42;
        {
            println_int("{}", integer1);
            let integer1: i32 = -100;
            println_int("{}", integer1);
        }

        println_int("{}", integer1);
    }

    println_int("{}", integer1);
}