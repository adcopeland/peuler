// sum the count of letters in all numbers from 1 to 1000
fn main() {
  let mut sum_letters = 0;
  for i in 1..1000 {
    sum_letters += letters_in(i);
  }

  sum_letters += letters_in_phrase("one thousand");
  println!("{}", sum_letters);
}

// used by lettersIn for numbers lower than 20
const UNIQUES: [&str; 20] = [
	"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten",
	"eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen",
];

// used by lettersIn to determine the tens prefix.
// "zero" and "teens" are placeholders so num/10 resolves to the right index.
const TENS: [&str; 10] = [
	"zero", "teens", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety",
];

// Returns the number of letters in the english version of the number
fn letters_in(mut num: i32) -> i32 {
  if num >= 1000 {
    panic!("letters_in only works below 1000");
  }

  let mut result = String::new();
  if num >= 100 {
    let num_hundreds = num/100;
    result.push_str(UNIQUES[num_hundreds as usize]);
    result.push_str(" hundred ");
    num -= num_hundreds * 100;
    if num > 0 {
      result.push_str("and ");
    }
  }

  if num >= 20 {
    let num_tens = num/10;
    result.push_str(TENS[num_tens as usize]);
    result.push(' ');
    num -= num_tens * 10;
  }

  if num > 0 {
    result.push_str(UNIQUES[num as usize]);
  }

  return letters_in_phrase(result.as_str());
}

// Returns any non-space letters in the provided string
fn letters_in_phrase(phrase: &str) -> i32 {
  let mut result = 0;
  phrase.chars().for_each(|c| {
    if c != ' ' {
      result += 1;
    }
  });
  return result;
}
