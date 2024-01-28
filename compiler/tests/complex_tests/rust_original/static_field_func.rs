
struct Maths;

impl Maths {
    const PI: f64 = 3.14;

    fn circle_area(radius: f64) -> f64 {
        Maths::PI * radius * radius
    }
}

fn main() {
    let radius = 2.0;

    // Использование статического поля
    println!("Value of Pi: {}", Maths::PI);

    // Использование статической функции
    let area = Maths::circle_area(radius);

    println!("Area of the circle with radius 1: {}", area);
}
