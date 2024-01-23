struct MyStruct {
    data: i32,
}

fn by_value(obj: MyStruct) {
    println!("Function by_value: data = {}", obj.data);
    // obj будет уничтожен по завершении функции, так как передан по значению
}

fn by_reference(obj: &MyStruct) {
    println!("Function by_reference: data = {}", obj.data);
    // obj остается владельцем после завершения функции, так как передан по ссылке
}

fn main() {
    // Создание объекта MyStruct
    let my_object = MyStruct { data: 42 };

    // Вызов функции by_value с передачей объекта по значению
    by_value(my_object);

    // Попытка использовать my_object после передачи по значению вызовет ошибку компиляции,
    // так как my_object больше не доступен (был перемещен внутрь функции by_value)

    // Создание нового объекта MyStruct
    let my_object_ref = MyStruct { data: 123 };

    // Вызов функции by_reference с передачей объекта по ссылке
    by_reference(&my_object_ref);

    // my_object_ref все еще доступен после вызова функции by_reference
    println!("Main function: data = {}", my_object_ref.data);
}
