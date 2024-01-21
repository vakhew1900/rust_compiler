fn main() {
	
	let x =
	[
	  [ 2, 2, 2],
	  [ 1, 0, 1],
	  [ 2, 2, 2]
	];
	
	let y =
	[
	  [ 10, 12, 10],
	  [ 12, 10, 12],
	  [ 10, 12, 10]
	]; 
	
	let mut z =
	[
	  [ 0, 0, 0],
	  [ 0, 0, 0],
	  [ 0, 0, 0]
	]; 
	
	for i in  0..3 {
		for j in 0..3 {
			z[i][j] = x[i][j] + y[i][j];
			print_int("{} ", z[i][j]);
		}
		println("{}", "");
	}
	
}

// /exam_tests/array/matrix.rs


/*

let x =
	[
	  [ 2, 2, 2],
	  [ 1, 0, 1],
	  [ 2, 2, 2]
	];
	
	let y =
	[
	  [ 10, 12, 10],
	  [ 12, 10, 12],
	  [ 10, 12, 10]
	]; 
	
	let mut z =
	[
	  [ 0, 0, 0],
	  [ 0, 0, 0],
	  [ 0, 0, 0]
	]; 
	
	for i in  0..3 {
		for j in 0..3 {
			z[i][j] = x[i][j] + y[i][j];
			print_int("{} ", z[i][j]);
		}
		println("{}", "");
	}




	let mut x =
	[
	  [ 1, 2, 0],
	  [ 1, 0, 1],
	  [ 2, 2, 0]
	];
	
	x[0][0] = 2;
*/