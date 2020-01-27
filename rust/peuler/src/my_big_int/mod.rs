// Just enough BigInt for problems 13 and 16
#[derive(Clone)]
pub struct BigInt {
  rep: Vec<u8>, // ascii "string" form of the int, stored with least significant digit first
}

impl BigInt {
  // Make a new BigInt from a string. Converts the string into rep form (ascii string in reverse, in byte form)
  pub fn new(rep: &str) -> BigInt {
    BigInt{ rep: String::from(rep).into_bytes().into_iter().rev().collect() }
  }

  pub fn string(&self) -> String {
    String::from_utf8(self.rep.clone().into_iter().rev().collect()).unwrap()
  }
}

// Implement += for BigInt
impl std::ops::AddAssign<&BigInt> for BigInt {
  fn add_assign(&mut self, other: &BigInt) {
    let max_size = if self.rep.len() > other.rep.len() { self.rep.len() } else { other.rep.len() };
    let mut carry = 0 as u8;
    let mut result = Vec::with_capacity(max_size);
    for i in 0..max_size {
      let self_char  = if i < self.rep.len() { self.rep[i] - ('0' as u8) } else { 0 };
      let other_char = if i < other.rep.len() { other.rep[i] - ('0' as u8) } else { 0 };
      let mut result_char = self_char + other_char + carry;
      carry = if result_char >= 10 { 1 } else { 0 };
      if carry > 0 {
        result_char -= 10;
      }
      result.push(result_char + ('0' as u8));
    }
    if carry > 0 {
      result.push('1' as u8);
    }
    self.rep = result;
  }
}

// Implement the println! compatibility
impl std::fmt::Display for BigInt {
  fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
    // Convert from rep back to string
    write!(f, "{}", String::from_utf8(self.rep.clone().into_iter().rev().collect()).unwrap())
  }
}
