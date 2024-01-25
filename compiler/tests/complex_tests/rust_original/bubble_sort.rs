fn main() {
    let mut numbers = [4, 3, 2, 3, 3, 10, 2];

    // Вызываем функцию сортировки
    bubble_sort(&mut numbers);

    // Выводим отсортированный массив
    println!("Sorted numbers: {:?}", numbers);
}

// Функция для сортировки пузырьком
fn bubble_sort(arr: &mut [i32; 7]) {
    let len = arr.len();

    for i in 0..len {
        for j in 0..len - i - 1 {
            // Сравниваем соседние элементы и меняем их местами, если необходимо
            if arr[j] > arr[j + 1] {
                let tmp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}
