use std::collections::BTreeSet;
use std::fs::File;
use std::io::{self,BufRead};
use std::error::Error;

fn main() {
  match read_names() {
    Err(err) => {
      panic!("{}", err);
    },
    Ok(names) => {
      let mut total_score = 0;
      for (i, name) in names.iter().enumerate() {
        let mut word_score = 0;
        for c in name.chars() {
          // Only works if names are all capital letters (they are). Add 1 since A is 1, not 0.
          word_score += c as i32 - 'A' as i32 + 1;
        }
        total_score += word_score * (i as i32 + 1);
      }
      println!("{}", total_score);
    },
  }
}

fn read_names() -> Result<BTreeSet<String>, Box<Error>> {
  let mut result = BTreeSet::new();
  let file = File::open("../data/p022_names.txt")?;
  let reader = io::BufReader::new(file);
  let mut split_iter = reader.split(b',');
  while let Some(name_result) = split_iter.next() {
    let name = name_result?;
    let name_bytes = name.as_slice();
    // strip first and last characters (the quotes)
    let no_quotes = &name_bytes[1..name_bytes.len()-1];
    result.insert(std::str::from_utf8(no_quotes)?.to_owned());
  }

  Ok(result)
}
