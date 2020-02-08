fn main() {
  let mut fac_result = peuler::my_big_int::BigInt::new("1");
  let mut current = peuler::my_big_int::BigInt::new("1");

  let end = peuler::my_big_int::BigInt::new("101");
  let increment = peuler::my_big_int::BigInt::new("1");

  while current < end {
    fac_result *= &current;
    current += &increment;
  }

  let mut sum = 0;
  for c in fac_result.string().chars() {
    sum += c as i32 - '0' as i32;
  }

  println!("{}", sum);
}
