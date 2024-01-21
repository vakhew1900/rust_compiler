fn main() {
	
	let numbers: [f32; 7] = [1.0, 2.0, 3.0, 5.0, 8.0, 13.0, 21.0];
	
	for i in 1..7 {
		println_float("float number = {}", numbers[i]);
	}
}