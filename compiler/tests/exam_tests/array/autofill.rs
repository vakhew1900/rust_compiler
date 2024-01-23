fn main(){
    let c = read_int();
    let mut matrix = [ [c + 12 * 13 % 46; 3] ; 3];

    for array in matrix {
        for x in array {
            print_int("{} ", x);
        }
        println("{}", "");
    }

}