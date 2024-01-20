struct House {
    width: f64,
    length: f64,
   height: f64,
}

/*
impl House {
    fn calculate_area(&self) -> f64 {
        // Площадь стен
        let walls_area = 2.0 * (self.width * self.height + self.length * self.height);
        // Площадь крыши
        let roof_area = 2.0 * self.width * self.length;
        // Общая площадь дома
        let total_area = walls_area + roof_area;

        total_area
    }
}

*/

impl House {
	fn calculate_area() -> f64 {
		10.0
	}
}


fn main() {
    let my_house = House {
        width: 10.0,
        length: 15.0,
        height: 8.0
    };

  //  let area = my_house.calculate_area();
    println_float("Площадь дома: {} квадратных метров", House::calculate_area());
}
