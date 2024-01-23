// Функция, принимающая массив по значению
fn by_value(arr: [i32; 3]) {
    println!("Function by_value: original array = {:?}", arr);

    // Изменение значения элементов массива
    let modified_arr = [arr[0] + 10, arr[1] + 10, arr[2] + 10];

    println!("Function by_value: modified array = {:?}", modified_arr);
    // arr будет уничтожен по завершении функции, так как передан по значению
}

// Функция, принимающая массив по ссылке и изменяющая его
fn by_reference(arr: &mut [i32; 3]) {
    println!("Function by_reference: original array = {:?}", arr);

    // Изменение значения элементов массива
    arr[0] += 5;
    arr[1] += 5;
    arr[2] += 5;

    println!("Function by_reference: modified array = {:?}", arr);
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
    println!("Main function: modified array = {:?}", my_array_ref);
}
