fn main() {
  let mut palindromes = Vec::new();

  for i in 100..999 {
    for j in 100..999 {
      let product = i*j;
      if is_palindrome(product) {
        palindromes.push(product)
      }
    }
  }

  let m = palindromes.iter().fold(0, |sum, x| {
    if *x > sum {
      *x
    } else {
      sum
    }
  });

  println!("{}", m)
}

fn is_palindrome(n : u64) -> bool {
  let s = n.to_string();
  let bytes = s.as_bytes();
  for i in 0..bytes.len()/2 {
    if bytes[i] != bytes[s.len()-i-1] {
      return false;
    }
  }
  true
}
