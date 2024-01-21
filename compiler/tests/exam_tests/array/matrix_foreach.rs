fn main() {

let matrix =
	[
	  [ 1, 2, 3],
	  [ 4, 5, 6],
	  [ 7, 8, 9]
	];

	for array in matrix {
	    for elem in array {
	        print_int("{} ", elem);
	    }
	    println("{}", "");
	}


}