fn main() {
  let mut sum: u64 = 0;
  for i in 1..2000000 {
    if is_prime(i) {
      sum += i as u64
    }
  }

  println!("{}", sum);
}

fn is_prime(n: i32) -> bool {
  for i in 2..=n/2 {
    if n % i == 0 {
      return false;
    }
  }
  true
}
