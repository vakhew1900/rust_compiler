struct Person { name: String, age: i32}

trait Printer{
    fn print_elem(&self);
}

impl Printer for Person{

    fn  print_elem(&self){
        print("Person {};", self.name);
        println_int("age: {}", self.age);
    }
}

fn main(){

    let tom = Person{ name: "Tom", age: 36 };
    tom.print_elem();    // Person Tom; age: 36
}