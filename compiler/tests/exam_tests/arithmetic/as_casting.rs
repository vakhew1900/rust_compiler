fn main(){
    let mut integer1: i32 = 77;
    let mut float2: f32 = -9.9;
    let mut float1 : f32 = 1.2;
    let mut ch1 : char = 'i';

    println_char("{}", ch1);
    ch1 = integer1 as char;
    println_char("{}", ch1);

    println_float("{}", float1);
    float1 = integer1 as f32;
    println_float("{}", float1);

    println_int("{}", integer1);
    integer1 = float2 as i32;
    println_int("{}", integer1);


}