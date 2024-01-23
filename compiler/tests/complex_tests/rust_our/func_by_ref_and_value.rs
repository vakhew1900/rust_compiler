struct MyStruct {
    data: i32,
}

fn by_value(mut obj: MyStruct) {
    println_int("Function by_value: data before = {}", obj.data);
    obj.data = 999;
    println_int("Function by_value: data modified = {}", obj.data);
    // obj будет уничтожен по завершении функции, так как передан по значению
}

fn by_reference(obj: &mut MyStruct) {
    println_int("Function by_reference: data before = {}", obj.data);
    obj.data = 888;
    println_int("Function by_reference: data modified = {}", obj.data);
    // obj остается владельцем после завершения функции, так как передан по ссылке
}

fn main() {
    // Создание объекта MyStruct
    let my_object = MyStruct { data: 42 };

    // Вызов функции by_value с передачей объекта по значению
    by_value(my_object);

    // Попытка использовать my_object после передачи по значению вызовет ошибку компиляции,
    // так как my_object больше не доступен (был перемещен внутрь функции by_value)
    //println_int("Main function: data = {}", my_object.data);

    // Создание нового объекта MyStruct
    let mut my_object_ref = MyStruct { data: 123 };

    // Вызов функции by_reference с передачей объекта по ссылке
    by_reference(&mut my_object_ref);

    // my_object_ref все еще доступен после вызова функции by_reference
    println_int("Main function: data = {}", my_object_ref.data);

    // ВАЖНО - в оригинальном расте и у нас, если передать объект в функцию
    // по немутабельному значению, его нельзя изменять, но он исчезает (переходит во владение
    // функции)
}
