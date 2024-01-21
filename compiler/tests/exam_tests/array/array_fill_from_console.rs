fn main() {
	println("{}", "Введите размер массива:");

	let mut size = read_int();

	let mut array: [i32; 100] = [0; 100];

	println("{}", "Введите элементы массива (каждый элемент с новой строки):");

	for i in 0..size {
		let mut element : i32 = read_int();
		array[i] = element;
	}

	println("{}", "Введенный массив:");

	for i in 0..size {
		print_int("{} ", array[i]);
	}
}
