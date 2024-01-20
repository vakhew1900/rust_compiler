fn main(){
    let float1: f32 = 42.8;
    let float2: f32 = 500.0;
    let float3: f32 = -10.1;

    let sum = float1 + float2;
    let difference = float2 - float1;
    let product = float1 * 5.0;
    let quotient = (-float3) / 2.0;

    let x = -float1; //унарный минус
    let x1 = -        9.0;

    println_float("{}", sum);
    println_float("{}", difference);
    println_float("{}", product);
    println_float("{}", quotient);
    println_float("{}", x);
    println_float("{}", x1);
}