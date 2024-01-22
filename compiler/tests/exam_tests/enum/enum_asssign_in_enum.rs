// Объявление перечислимого типа данных
enum Color {
    Red = 1,
    Green = 2,
    Blue = 7,
}

fn main(){
    // Создание переменных с типом данных Color
    let favorite_color = Color::Blue;

    if (favorite_color == 7){
        println("{}", "Blue");
    }
}