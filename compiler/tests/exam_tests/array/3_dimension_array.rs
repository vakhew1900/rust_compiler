fn main() {
    // Создаем трехмерный массив размером 2x3x4
    let mut three_dimensional_array = [[[0; 4]; 3]; 2];

    // Присваиваем значения элементам массива
    for i in 0..2 {
        for j in 0..3 {
            for k in 0..4 {
                three_dimensional_array[i][j][k] = i * 100 + j * 10 + k;
            }
        }
    }

    // Выводим значения трехмерного массива
    for i in 0..2 {
        for j in 0..3 {
            for k in 0..4 {
                print_int("{} ", three_dimensional_array[i][j][k]);
            }
            println("{}", "");
        }
        println("{}", "");
    }
}
