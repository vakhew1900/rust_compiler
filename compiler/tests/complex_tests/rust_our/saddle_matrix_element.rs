fn main() {
    let matrix = [
        [1, 2, 3],
        [4, 5, 6],
        [7, 8, 9],
    ];

    let mut saddle_point = -1;

    for i in 0..3 {
        for j in 0..3 {
            let current_element = matrix[i][j];
            let mut is_row_min = true;
            let mut is_col_max = true;

            for col in 0..3 {
                if matrix[i][col] < current_element {
                    is_row_min = false;
                    break;
                }
            }

            for row in 0..3 {
                if matrix[row][j] > current_element {
                    is_col_max = false;
                    break;
                }
            }

            if is_row_min && is_col_max {
                saddle_point = current_element;
                break;
            }
        }
    }

    if saddle_point != -1 {
        println_int("Saddle point found: {}", saddle_point);
    } else {
        println("{}", "No saddle point found in the matrix");
    }
}
