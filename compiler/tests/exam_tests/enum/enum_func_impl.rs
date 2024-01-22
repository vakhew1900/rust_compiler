// Объявление перечислимого типа данных
enum Color {
    Red = 1,
    Green = 2,
    Blue = 7,
}

impl Color{
    fn getBright(c : Color){
        if (c == Color::Blue) {
            println("{}", "Ярко");
        } else {
            println("{}", "Неярко");
        }
    }
}

fn main(){
    // Создание переменных с типом данных Color
    let COLOR1 = Color::Blue;
    Color::getBright(COLOR1);
}