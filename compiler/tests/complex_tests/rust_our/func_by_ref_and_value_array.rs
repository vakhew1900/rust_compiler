// Функция, принимающая массив по значению
fn by_value(arr: [i32; 3]) {
    print_arr(&arr);

    // Изменение значения элементов массива
    let modified_arr = [arr[0] + 10, arr[1] + 10, arr[2] + 10];

    print_arr(&modified_arr);
    // arr будет уничтожен по завершении функции, так как передан по значению
}

// Функция, принимающая массив по ссылке и изменяющая его
fn by_reference(arr: &mut [i32; 3]) {
    print_arr(&arr);

    // Изменение значения элементов массива
    arr[0] = arr[0] + 5;
    arr[1] = arr[1] + 5;
    arr[2] = arr[2] + 5;

    print_arr(&arr);
    // arr остается владельцем после завершения функции, так как передан по ссылке
}

fn main() {
    // Создание массива
    let mut my_array = [1, 2, 3];

    // Вызов функции by_value с передачей массива по значению
    by_value(my_array);

    // После вызова функции by_value, my_array больше не доступен,
    // так как он был перемещен внутрь функции

    // Создание нового массива
    let mut my_array_ref = [4, 5, 6];

    // Вызов функции by_reference с передачей массива по ссылке
    by_reference(&mut my_array_ref);

    // my_array_ref остается доступным после вызова функции by_reference
    print_arr(&my_array_ref);
}

fn print_arr(arr: &[i32; 3]){
    for i in &arr{
        print_int("{} ", i);
    }
    println("{}", "");
}