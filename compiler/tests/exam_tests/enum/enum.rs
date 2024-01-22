// Объявление перечислимого типа данных
enum Color {
    Red,
    Green,
    Blue,
}

fn main(){
    // Создание переменных с типом данных Color
    let favorite_color = Color::Blue;

    if (favorite_color == Color::Blue){
        println("{}", "Blue");
    }
}