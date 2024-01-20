fn main(){
    let integer1: i32 = 42;
    let integer2: i32 = 500;
    let integer3: i32 = 100;
    let is_equal = integer1 == integer2;
    let is_not_equal = integer1 != integer2;
    let greater_than = integer2 > integer1;
    let lt = integer2 < integer1;
    let gte = integer1 >= 42;
    let less_than_or_equal = integer1 <= 42;

    println_bool("{}", is_equal);
    println_bool("{}", is_not_equal);
    println_bool("{}", greater_than);
    println_bool("{}", lt);
    println_bool("{}", gte);
    println_bool("{}", less_than_or_equal);
}
