fn main() {
  let mut prime_idx = 0;
  let mut current = 1;

  while prime_idx < 10001 {
    current += 1;
    if is_prime(current) {
      prime_idx += 1;
    }
  }

  println!("{}", current);
}

fn is_prime(n: i32) -> bool {
  for i in 2..=n/2 {
    if n % i == 0 {
      return false;
    }
  }
  true
}
