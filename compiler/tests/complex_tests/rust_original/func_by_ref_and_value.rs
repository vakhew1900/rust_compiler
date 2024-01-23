struct MyStruct {
    data: i32,
}

fn by_value(mut obj: MyStruct) {
    println!("Function by_value: original data = {}", obj.data);

    // Изменение значения поля data
    obj.data = 999;

    println!("Function by_value: modified data = {}", obj.data);
    // obj будет уничтожен по завершении функции, так как передан по значению
}

fn by_reference(obj: &mut MyStruct) {
    println!("Function by_reference: original data = {}", obj.data);

    // Изменение значения поля data
    obj.data = 888;

    println!("Function by_reference: modified data = {}", obj.data);
    // obj остается владельцем после завершения функции, так как передан по ссылке
}

fn main() {
    // Создание объекта MyStruct
    let mut my_object = MyStruct { data: 42 };

    // Вызов функции by_value с передачей объекта по значению
    by_value(my_object);

    // После вызова функции by_value, my_object больше не доступен,
    // так как он был перемещен внутрь функции

    // Создание нового объекта MyStruct
    let mut my_object_ref = MyStruct { data: 123 };

    // Вызов функции by_reference с передачей объекта по ссылке
    by_reference(&mut my_object_ref);

    // my_object_ref остается доступным после вызова функции by_reference
    println!("Main function: modified data = {}", my_object_ref.data);
}
