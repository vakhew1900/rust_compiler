mod ID {
	pub trait Summary {
		fn summarize(&self, x:i32) -> String;
		fn tmp(&self) {
			self.summarize(32);
			let man = Man { age : 33 };
			//println("sdfkgdsfhjgfds");
		}
		const x: i32 = 11 / 2 % 3 + 12*3 - 16;
		const x1: i32 = -11;
		const z: bool = 11 == 12 || 12 > 11 && 10.0 != 11.1 && 'a' < 'c';
		const str : String = "fffffffff";	
		const ch: char = 'c';
		const float : f64 = 1e12;
		const float2 : f64 = 1.1345;
		const big_int : i32 = 1111111;
	}

	pub struct Tweet {
		pub username: String,
		pub content: String,
		pub reply: bool,
		pub retweet: bool,
	}

	impl Summary for Tweet {
		const ch: char = 'c';
		fn summarize(&self, x:i32) -> String {
			if(true) {3} else {4};
			let var = 600000;
			//self.reply = false;
			//format("{}: {}", self.username, self.content)
			
			if( 10 < var) { 
				return "true";
			}
			
			if ( 10 == var) {
				return "false";
			}
			
			"dffasdsfd"
		}
		
	}
	
	struct Man {
		age : i32
	}
	
	pub fn myFunc() {
		let x = 10;
		let y = 11;
		x + y * 11 + 12;
	}
	
	
	impl Tweet {
		pub fn myFunc(x : i32, object: & impl Summary,  y:f64, z: char, b: bool, array:[[[i32; 4]; 3];12]) {
			1 + 1;
		}
		
		pub fn selfFunc(&mut self){
			1 + 2;
			self.reply = false;
		}
	}
}


enum Enum {
    Foo = 3 + 4 + 7,
    Bar = (10 * 4 - 12 / 3 - 11%10) % 255,
    Baz = 10,
	Br,
	Bazon,
	
}


fn main() { 

	let tweet: ID::Tweet = ID::Tweet {username: "user", content: "content", reply: false, retweet: false};
	tweet.summarize(11);
	let x = tweet.username;
	let mut array: [i32; 4] = [2, 3, 4, 5];
	array[0] = 10;
	println("{}", "func_func_func");
	println_int("{}", 4);
	println_int("{}", array[0]);
	tweet.tmp();
	let y: f64 = ID::Tweet::float2;
	ID::myFunc();
	//crate::myFunc();
	//if true { 3 }
	crate::ID::myFunc();
	
	for x in array {
		let y = x + 10;
	}
	
	let mut matrix :[[i32; 2]; 2] =
	[
	  [1, 2],
	  [3, 4]
	];
	
	matrix[0][1] = 32;
	
}

/*
 1 ВСЕ СТРУКТУРЫ МОДУЛИ ФУНКЦИИ (свободные и находящиесся в трейте)
 2. Нахожу реализации всех функций  и чтобы наследовалось
 3. Расставляю типы для констант, полей и параметров функции
 4. Расставление типов для expression (внутри функций) - pub package  
*/