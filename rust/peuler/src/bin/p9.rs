fn main() {
  let x = find_answer();
  println!("{}", x);
}

// a < b < c
// a^2 + b^2 = c^2
// find a*b*c when a+b+c == 1000
fn find_answer() -> u32 {
  for a in 0..998 {
    for b in a+1..999 {
      for c in b+1..1000 {
        if a+b+c == 1000 && a*a + b*b == c*c {
          return a*b*c;
        }
      }
    }
  }
  0
}
