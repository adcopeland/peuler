// Reusing logic from p13.
fn main() {
	// start at 2^0, loop 1000 times
  let mut current = peuler::my_big_int::BigInt::new("1");
  for _i in 0..1000 {
		// Add the number to itself to double it. This takes 2^n => 2^(n+1)
    current += &current.clone();
  }

  let mut sum = 0;
  current.string().as_bytes().iter().for_each(|c| {
    match (*c as char).to_digit(10) {
      Some(d) => sum += d,
      None => println!("WARNING: somehow a bad digit is in number!"),
    }
  });

  println!("{}", sum);
}
