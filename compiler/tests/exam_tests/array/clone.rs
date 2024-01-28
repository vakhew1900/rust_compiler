/******************************************************************************

                            Online Rust Compiler.
                Code, Compile, Run and Debug Rust program online.
Write your code in this editor and press "Run" button to execute it.

*******************************************************************************/


fn main() {
    let x = [[1, 2, 3], [1, 2, 3]];
    let mut y =  x;

    y[0] = [10,10, 10];

    for array in x  {

        for elem in array {
            print_int("{} ", elem);
        }
        println("{}", "");
    }

    println("-----------------{}", "----");
    for array in y  {

        for elem in array {
            print_int("{}", elem);
        }
        println("{}", "");
    }
}
