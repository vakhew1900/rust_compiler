fn add_matrices(matrix1: &[[i32; 3]; 3], matrix2: &[[i32; 3]; 3]) -> [[i32; 3]; 3] {
    let mut result = [[0; 3]; 3];

    for i in 0..3 {
        for j in 0..3 {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }

    result
}

fn main() {
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

    let result_matrix = add_matrices(&matrix_a, &matrix_b);

    println!("Матрица A:");
    for row in &matrix_a {
        println!("{:?}", row);
    }

    println!("Матрица B:");
    for row in &matrix_b {
        println!("{:?}", row);
    }

    println!("Результат сложения:");
    for row in &result_matrix {
        println!("{:?}", row);
    }
}
