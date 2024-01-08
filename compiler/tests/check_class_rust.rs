
struct Car {
    engine : Engine,
    carSize : CarSize,
    isStarted : bool,
}

struct Engine {
    volume : f64,
    creatorName : String
}

struct CarSize {
    width : f64,
    height : f64
}

trait Action {
    fn boostEngine(&mut self, boost : f64);
    fn resizeBodyCar(&mut self, width : f64, height : f64);
    fn simpleTestStaticMethod() {
        println!("{}", "Я просто статический метод для тестирования");
    }
    fn doItLater();
}

impl Action for Car {
    fn doItLater() {
        println!("{}", "Я сделал это позже))))");
    }
    fn boostEngine(&mut self, boost : f64) {
        self.engine.volume = boost;
    }
    fn resizeBodyCar(&mut self, width : f64, height : f64) {
        self.carSize.width = width;
        self.carSize.height = height;
    }
}

impl Car {
    fn start(&mut self) -> bool {
        self.isStarted = true;
        println!("{}", "Start engine!!!");
        return self.isStarted;
    }
    fn drownOut(&mut self) -> bool {
        self.isStarted = false;
        println!("{}", "Drown out engine!!!");
        self.isStarted
    }
}

fn main() {

    Car::simpleTestStaticMethod();
    Car::doItLater();

    let mut car = Car {
        carSize : CarSize { width : 3.5, height : 5.4 },
        engine : Engine { creatorName : "VAZ".to_string(), volume : 1.2 },
        isStarted : false
    };

    println!("{}", car.start());

    car.boostEngine(0.1);
    car.resizeBodyCar(2.0, 4.0);

    println!("{}", car.engine.volume);
    println!("{}", car.carSize.width);
    println!("{}", car.carSize.height);

    println!("{}", car.drownOut());

}