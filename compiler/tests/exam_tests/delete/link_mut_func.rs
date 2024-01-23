struct Point {
    x: f32,
    y: f32,
}

fn func(point: &mut Point) {
    point.x = point.x + 10 as f32;
    point.y = point.y + 10 as f32;
    println_float("x = {}", point.x);
    println_float("y = {}", point.y);
}

fn main() {
    let mut point = Point{x : 10.0, y: 10.0};
    func(&mut point);
    println_float("x = {}", point.x);
    println_float("y = {}", point.y);
}