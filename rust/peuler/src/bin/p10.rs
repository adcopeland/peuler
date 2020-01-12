fn main() {
  let mut sum: u64 = 0;
  for i in 1..2000000 {
    if peuler::is_prime(i) {
      sum += i as u64
    }
  }

  println!("{}", sum);
}
