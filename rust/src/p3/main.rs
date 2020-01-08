fn main() {
  let factors = get_factors(600851475143);

  let m = factors.iter().fold(0, |max, x| {
    if x > &max {
      *x
    } else {
      max
    }
  });
  println!("{}", m);
}

fn get_factors(mut n: u64) -> Vec<u64> {
  let mut factors = Vec::new();
  let mut i: u64 = 2;

  while i < n {
    if n % i == 0 {
      factors.push(i);
      n /= i;
      i = 1;
    }

    i+=1;
  }

  if n != 1 {
    factors.push(n);
  }

  factors
}
