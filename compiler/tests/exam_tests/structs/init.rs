struct House {
    width: f64,
    length: f64,
   height: f64,
}


impl House {
    fn standard_value(&mut self) {
        self.width = 10.0;
        self.length = 15.0;
        self.height = 8.0;
    }

    fn init() -> House {
        House {
                width: 12.0,
                length: 16.0,
                height: 1.0
        }
    }
}



fn main() {
    let my_house = House::init();
    println_float("width = {}", my_house.width);
    println_float("height = {}", my_house.height);
    println_float("length = {}", my_house.length);

    my_house.standard_value();

    println_float("width = {}", my_house.width);
    println_float("height = {}", my_house.height);
    println_float("length = {}", my_house.length);
}


// /exam_tests/structs/init.rs