use std::collections::{HashMap, HashSet};

// Implement problem 21 (find the sum of all amicable numbers below 10000)
fn main() {
  let mut num_to_sum = HashMap::new();

  // Build up all the sums
  for i in 1..10000 {
    let mut sum = 0;
    let stop = i/2 + 1;
    for j in 1..stop {
      if i % j == 0 {
        sum += j;
      }
    }
    num_to_sum.insert(i, sum);
  }

  // Figure out which numbers are amicable
  let mut amicables = HashSet::new();
  for (num, sum) in &num_to_sum {
    if num != sum && get_sum_or_zero(&num_to_sum, &sum) == *num {
      amicables.insert(num);
      amicables.insert(sum);
    }
  }

  // sum the amicable numbers
  let mut sum = 0;
  for amicable in amicables {
    sum += amicable;
  }

  println!("{}", sum);
}

fn get_sum_or_zero(num_to_sum: &HashMap<i32, i32>, sum: &i32) -> i32 {
  if let Some(&value) = num_to_sum.get(sum) {
    return value;
  }
  return 0;
}
