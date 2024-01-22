fn main() {

	// Массив массивов
	let matrix: [[f32; 3]; 3] = [
		[1.0, 2.0, 3.0],
		[4.0, 5.0, 6.0],
		[7.0, 8.0, 9.0],
	];

	for i in  0..3 {
		for j in 0..3 {
			print_float("{} ", matrix[i][j]);
		}
		println("{}", "");
	}

}