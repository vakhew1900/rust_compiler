fn main() {

let matrix =
	[
	  [ 1.0, 2.0, 3.0],
	  [ 4.0, 5.0, 6.0],
	  [ 7.0, 8.0, 9.0]
	];

	for array in matrix {
	    for elem in array {
	        print_float("{} ", elem);
	    }
	    println("{}", "");
	}


}