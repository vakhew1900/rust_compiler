fn main(){
    let x =  "string start";
    let y = x.push_str(" string end");

    println("{}", x);
    println("{}", y);

    println("{}", x.push_char('1'));
}