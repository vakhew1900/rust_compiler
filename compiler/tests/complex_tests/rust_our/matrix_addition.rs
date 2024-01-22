fn add_matrices(matrix1: &[[i32; 3]; 3], matrix2: &[[i32; 3]; 3]) -> [[i32; 3]; 3] {
    let mut result = [[0; 3]; 3];

    for i in 0..3 {
        for j in 0..3 {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }

    result
}

fn matrix_print(matrix1: &[[i32; 3]; 3]){
    for i in  0..3 {
        for j in 0..3 {
            print_int("{} ", matrix1[i][j]);
        }
        println("{}", "");
    }
}

fn main() {
    // Пример двух матриц 3x3
    let matrix_a = [
        [1, 2, 3],
        [4, 5, 6],
        [7, 8, 9],
    ];

    let matrix_b = [
        [9, 8, 7],
        [6, 5, 4],
        [3, 2, 1],
    ];

    // Вызываем функцию сложения матриц
    let result_matrix = add_matrices(&matrix_a, &matrix_b);

    // Выводим результат
    println("{}", "Матрица A:");
    matrix_print(&matrix_a);

    println("{}", "Матрица B:");
    matrix_print(&matrix_b);

    println("{}", "Результат сложения:");
    matrix_print(&result_matrix);
}
