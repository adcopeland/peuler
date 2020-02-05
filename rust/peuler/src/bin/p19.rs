// How many Sundays fell on the first of the month from Jan 1, 1901 to Dec 31, 2000?
// I couldn't find a "date" in the standard rust library and I'm avoiding external crates
//
// so for now, just use the problem description data (probably what I was supposed to do for the other languges too)
// 1 Jan 1900 was a Monday.
// Thirty days has September,
// April, June and November.
// All the rest have thirty-one,
// Saving February alone,
// Which has twenty-eight, rain or shine.
// And on leap years, twenty-nine.
// A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.
fn main() {
  // current starts before start because that's what we know the day for.
  let mut current = MyDate::new(Month::Jan, 1, 1900, Weekday::Monday);
  let start = MyDate::new(Month::Jan, 1, 1901, Weekday::Unknown);
  let end = MyDate::new(Month::Dec, 31, 2000, Weekday::Unknown);

  // Advance current to start...
  while current < start {
    current = next_day(current);
  }

  // Then calculate
  let mut num_sundays = 0;
  while current < end {
    if let (1, Weekday::Sunday) = (current.day, current.weekday) {
      num_sundays += 1;
    }
    current = next_day(current);
  }

  println!("{}", num_sundays);
}

#[derive(PartialOrd, PartialEq, Copy, Clone)]
enum Weekday {
  Unknown, Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday,
}

#[derive(PartialOrd, PartialEq, Copy, Clone)]
enum Month {
  Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sept, Oct, Nov, Dec,
}

#[derive(PartialOrd, PartialEq, Copy, Clone)]
struct MyDate {
  year:    u32,
  month:   Month,
  day:     u8,
  weekday: Weekday,
}

impl MyDate {
  fn new(m: Month, d: u8, y: u32, wd: Weekday) -> MyDate {
    MyDate{
      month: m,
      day: d,
      year: y,
      weekday: wd,
    }
  }
}

// Returns the next day's MyDate
fn next_day(d: MyDate) -> MyDate {
  let max_day = match d.month {
    Month::Sept | Month::Apr | Month::Jun | Month::Nov
      => 30,
    Month::Feb
      => if is_leap_year(d.year) { 29 } else { 28 },
    _
      =>  31
  };

  // just move forward the day
  let mut next_month = d.month;
  let mut next_year = d.year;
  let mut next_day = d.day+1;

  // If we crossed into the next month, update it.
  if d.day > max_day {
    next_day = 1;

    next_month = match d.month {
      Month::Jan  => Month::Feb,
      Month::Feb  => Month::Mar,
      Month::Mar  => Month::Apr,
      Month::Apr  => Month::May,
      Month::May  => Month::Jun,
      Month::Jun  => Month::Jul,
      Month::Jul  => Month::Aug,
      Month::Aug  => Month::Sept,
      Month::Sept => Month::Oct,
      Month::Oct  => Month::Nov,
      Month::Nov  => Month::Dec,
      Month::Dec  => Month::Jan
    };

    // If we crossed into the next year, update that too
    if next_month != d.month && next_month == Month::Jan {
      next_year += 1;
    }
  }

  // weekday always increments
  let next_weekday = match d.weekday {
    Weekday::Sunday    => Weekday::Monday,
    Weekday::Monday    => Weekday::Tuesday,
    Weekday::Tuesday   => Weekday::Wednesday,
    Weekday::Wednesday => Weekday::Thursday,
    Weekday::Thursday  => Weekday::Friday,
    Weekday::Friday    => Weekday::Saturday,
    Weekday::Saturday  => Weekday::Sunday,
    Weekday::Unknown   => Weekday::Sunday
  };

  MyDate{
    month:   next_month,
    day:     next_day,
    year:    next_year,
    weekday: next_weekday,
  }
}

// A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.
fn is_leap_year(year: u32) -> bool {
  let div4   = year % 4   == 0;
  let div100 = year % 100 == 0;
  let div400 = year % 400 == 0;

  return div4 && (!div100 || div400)
}
