// Области видимости
mod my_module {
    pub struct MyStruct {
        pub my_field: i32,
    }

    impl MyStruct {

        pub fn my_method(&self) {
            println("{}", "Публичный метод");
        }
    }
}

fn main() {
    let instance = my_module::MyStruct { my_field: 42 };
    instance.my_method();
}