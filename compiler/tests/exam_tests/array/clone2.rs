/******************************************************************************

                            Online Rust Compiler.
                Code, Compile, Run and Debug Rust program online.
Write your code in this editor and press "Run" button to execute it.

*******************************************************************************/


fn main() {
    let x = [ 1, 2, 3];
    let mut y =  x;

    y = [4, 5, 6];

    for elem in x  {
        print_int("{}", elem);
    }

    for elem in y  {
        println_int("{}", elem);
    }
}
