fn main() {
  let mut max_seq_len = 0 as u32;
  let mut max_seq_len_num = 0 as u32;
  for i in 1..1000000 as u32 {
    let l = seq_len(i);
    if l > max_seq_len {
      max_seq_len = l;
      max_seq_len_num = i;
    }
  }
  println!("{}", max_seq_len_num);
}

fn seq_len(mut n: u32) -> u32 {
  let mut seq_len = 0;
  while n != 1u32 {
    seq_len += 1;
    n = next(n);
  }
  seq_len
}

fn next(n: u32) -> u32 {
  if n%2 == 1 {
    3*n+1
  }
  else {
    n/2
  }
}
