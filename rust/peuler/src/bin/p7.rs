fn main() {
  let mut prime_idx = 0;
  let mut current = 1;

  while prime_idx < 10001 {
    current += 1;
    if peuler::is_prime(current) {
      prime_idx += 1;
    }
  }

  println!("{}", current);
}
