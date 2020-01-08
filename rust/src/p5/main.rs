fn main() {
  let mut n = 20;
  loop {
    if divisible_by_all(n) {
      break;
    }
    n += 1;
  }

  println!("{}", n);
}

fn divisible_by_all(n: u32) -> bool {
  for i in 2..21 {
    if n % i != 0 {
      return false;
    }
  }
  true
}
