fn main() {
  let mut sum = 0;
  let mut abundant_numbers = Vec::new();
  for i in 1..28124 {
    if is_abundant(i) {
      abundant_numbers.push(i);
    }
    if !is_sum_of_two_abundants(i, abundant_numbers.as_slice()) {
      sum += i;
    }
  }

  println!("{}", sum);
}

fn is_abundant(n: i32) -> bool {
  let mut sum = 1;
  let mut stop = n-1;
  let mut i = 2;
  while i < stop {
    if n % i == 0 {
      sum += i;
      stop = n/i;
      if stop != i {
        sum += stop;
      }
    }

    i += 1;
  }

  return sum > n;
}

fn is_sum_of_two_abundants(n: i32, abundant_numbers: &[i32]) -> bool {
  for (i, abundant) in abundant_numbers.iter().enumerate() {
    let smallest_sum = abundant + abundant;
    if smallest_sum > n {
      break;
    }
    for j in i..abundant_numbers.len() {
      let sum = abundant + abundant_numbers[j];
      if sum == n {
        return true;
      }
      if sum > n {
        break;
      }
    }
  }

  return false;
}
