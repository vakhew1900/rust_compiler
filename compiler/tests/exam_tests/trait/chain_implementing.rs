
trait Ded {
    fn area(&self) -> f32 {
        3.14 * 100.0
    }
}

trait Batya: Ded {
    fn color(&self) -> String { "КОД КРАСНЫЙ" }
}

trait Son: Batya {
    fn getAngles(&self) -> String;

    fn color(&self) -> String;
}

struct Man {
    iq: f64,
}

impl Son for Man {
    fn getAngles(&self) -> String { "КОД ГЛУПЕЦ" }

    fn color(&self) -> String { "КОД СИНИЙ" }
}

fn main() {
    let mugik = Man { iq: 2.0 };
    println_float("Man iq: {}", mugik.area());
    println("Angles: {}", mugik.getAngles());
    println("Color: {}", mugik.color());
}
