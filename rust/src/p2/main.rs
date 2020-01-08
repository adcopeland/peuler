fn main() {
  let fib = new_fibonacci_sequence();

  // fib is an iterator. Use take_while to terminate the loop at 4 million
  // and fold to perform the sum
  let sum = fib
    .take_while(|x| x <= &4000000)
    .filter(|x| x % 2 == 0)
    .fold(0, |sum, i| sum+i);

  println!("{}", sum)
}

struct FibonacciSequence {
  prev: u64,
  curr: u64,
}

fn new_fibonacci_sequence() -> FibonacciSequence {
  FibonacciSequence{ prev: 1, curr: 1 }
}

impl Iterator for FibonacciSequence {
  type Item = u64;

  fn next(&mut self) -> Option<u64> {
    let old_curr = self.curr;
    self.curr = self.prev + self.curr;
    self.prev = old_curr;
    Some(self.curr)
  }
}
