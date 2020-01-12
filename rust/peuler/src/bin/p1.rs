// Problem 1: Sum numbers below 1000 that are multiples of 3 or 5
fn main() {
  let mut total = 0;
  for i in 0..1000 {
    if i % 3 == 0 || i % 5 == 0 {
      total += i;
    }
  }
  println!("{}", total);
}
