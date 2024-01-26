fn main() {
    let mut numbers = [4, 3, 2, 3, 3, 10, 2];

    // Вызываем функцию сортировки
    bubble_sort(&mut numbers);

    // Выводим отсортированный массив
    for j in 0..7 {
        print_int("{}, ", numbers[j]);
    }
}

// Функция для сортировки пузырьком
fn bubble_sort(arr: &mut [i32; 7]) {
    let len = 7;

    for i in 0..len {
        for j in 0..len - i - 1 {
            if arr[j] > arr[j + 1] {
                let tmp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}
