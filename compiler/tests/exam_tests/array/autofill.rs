fn main(){
     let mut matrix = [ [1;3] ; 3];

     for array in matrix {
         for x in array {
            print_int("{} ", x);
         }
         println("{}", "");
     }

}