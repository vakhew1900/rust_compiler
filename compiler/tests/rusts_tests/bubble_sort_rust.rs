fn main() {

    let mut arr = [4, 7, 1, 9, 2, 0, 3, 7, 1];

    for i in 0..9 {
        for j in 0..9 {
            if arr[i] < arr[j] {
                let tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            };
        };
    };

    for i in 0..9 {
        println_int("{}  ", arr[i]);
    };
	
	let x = -10;
	let y = - x;
	let f = false;
	let z = x * y + x / y - x % 10 + ('c' as i32) + 10*12-13 + 100 / 10 + 10 % 2;
	let b = ( x != y  && x < y || x > 20) ;
}