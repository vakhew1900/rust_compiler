struct Point {
    x: f32,
    y: f32,
}

fn func(point: Point) {
    println_float("x = {}", point.x);
    println_float("y = {}", point.y);
}

fn main() {
    let point = Point{x : 10.0, y: 10.0};
    func(point);
    println_float("x = {}", point.x);
    println_float("y = {}", point.y);
}