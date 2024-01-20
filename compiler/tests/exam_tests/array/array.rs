fn main() {
	
	let numbers: [i32; 7] = [1, 2, 3, 5, 8, 13, 21];
	
	for i in 1..7 {
		println_int("number ={}", numbers[i]);
	}
}