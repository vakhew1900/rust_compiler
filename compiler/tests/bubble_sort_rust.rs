fn main() {

    let mut arr = [4, 7, 1, 9, 2, 0, 3, 7, 1];

    for i in 0..9 {
        for j in 0..9 {
            if arr[i] < arr[j] {
                let tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            };
        };
    };

    for i in 0..9 {
        print!("{}  ", arr[i]);
    };
}