pub mod my_big_int;

pub fn is_prime(n: i32) -> bool {
  let mut i = 2;
  while i < n/i {
    if n % i == 0 {
      return false;
    }
    i += 1;
  }
  true
}
