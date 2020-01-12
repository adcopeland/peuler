fn main() {
  let mut triangle_num = 1;
  let mut i = 2;
  while num_factors(triangle_num) <= 500 {
    triangle_num += i;
    i += 1;
  }
  println!("{}", triangle_num);
}

fn num_factors(n: i32) -> i32 {
  let sqrt_n = (n as f64).sqrt() as i32;
  let mut result = 0;
  for i in 1..sqrt_n {
    if n%i == 0 {
      result += if n/i == i { 1 } else { 2 };
    }
  }
  result
}
