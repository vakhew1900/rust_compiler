fn main(){

    let tom = Person{ name: String::from("Tom"), age: 36 };
    tom.print();    // Person Tom; age: 36
}

struct Person { name: String, age: u8}

trait Printer{
    fn print(&self);
}

impl Printer for Person{

    fn print(&self){
        RTL::print("Person {};", self.name);
        println_int("age: {}", self.age);
    }


}
///exam_tests/trait/simple.rs
///exam_tests/trait/trait_after_main.rs