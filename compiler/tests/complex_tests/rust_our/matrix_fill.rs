
fn main() {
    let mut image: [[i32; 10]; 10] = [
        [0,0,1,0,0,0,0,0,0,0],
        [0,0,1,0,0,0,0,0,0,0],
        [0,0,1,0,0,0,0,0,0,0],
        [0,1,0,0,0,0,0,0,0,0],
        [1,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0]
    ];

    let start_x = 1;
    let start_y = 1;
    let fill_color = 2;

    flood_fill(&mut image, start_x, start_y, fill_color);

    matrix_print(&mut image);
}

fn matrix_print(matrix1: &[[i32; 10]; 10]){
    for i in  0..10 {
        for j in 0..10 {
            print_int("{} ", matrix1[i][j]);
        }
        println("{}", "");
    }
}

fn flood_fill(image: &mut [[i32; 10]; 10], x: i32, y: i32, fill_color: i32) {
    // Проверяем граничные условия и основной цвет текущего пикселя
    if x >= 10 || x < 0 || y >= 10 || y < 0 || image[y][x] == fill_color || image[y][x] == 1 {
        return;
    }

    // Заполняем текущий пиксель новым цветом
    image[y][x] = fill_color;

    // Рекурсивно запускаем заливку для соседних пикселей
    if x + 1 < 10 {
        flood_fill(&mut image, x + 1, y, fill_color); // справа
    }
    if x > 0 {
        flood_fill(&mut image, x - 1, y, fill_color); // слева
    }
    if y + 1 < 10 {
        flood_fill(&mut image, x, y + 1, fill_color); // снизу
    }
    if y > 0 {
        flood_fill(&mut image, x, y - 1, fill_color); // сверху
    }
}
