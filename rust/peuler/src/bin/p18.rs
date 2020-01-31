fn main() {
  let mut solver = Solver::new(TRIANGLE, NUM_TRIANGLE_ROWS);
  print!("{}\n", solver.max_sum(0,0));
}

// Holds memoized results and a reference to the data
struct Solver<'a> {
  memoized_results: Vec<u32>,
  triangle: &'a[u32],
  num_rows: u32,
}

impl<'a> Solver<'a> {
  // Construct a solver
  fn new(data: &'a[u32], num_rows: u32) -> Solver {
    Solver{
      memoized_results: vec![0; calculate_triangle_size(num_rows)],
      triangle: data,
      num_rows: num_rows,
    }
  }

  // Determine the max sum for the provided (row, pos) "index"
  fn max_sum(&mut self, row_num: u32, row_pos: u32) -> u32 {
    let this_row_index = flattened_index(row_num, row_pos);

	  // If this position already has a max sum, return it.
    let mut result = self.memoized_results[this_row_index as usize];
    if result != 0 {
      return result;
    }

	  // If there's no next row down, then the new max is just this value.
	  // store and return the result.
    let current_val = self.triangle[this_row_index as usize];
    let next_row_num = row_num+1;
    if next_row_num >= self.num_rows {
      result = current_val;
      self.memoized_results[this_row_index as usize] = result;
      return result;
    }

	  // Otherwise, new max would be the larger of the MaxSum for the next row at the current
	  // rowPos or the current rowPos + 1.
	  // The next row always has 1 more item than this one, so no need to verify rowPos+1 exists.
    let equal_pos_val    = self.max_sum(next_row_num, row_pos);
    let plus_one_pos_val = self.max_sum(next_row_num, row_pos+1);

    // store and return after adding in the current value
    let max = if equal_pos_val > plus_one_pos_val { equal_pos_val } else { plus_one_pos_val };
    result = max + current_val;
    self.memoized_results[this_row_index as usize] = result;
    return result;
  }
}

// Calculate the triangle size based on the number of rows
fn flattened_index(row_num: u32, row_pos: u32) -> usize {
  let mut sum = 0u32;
  for i in 0..row_num {
    sum += i+1;
  }
  (sum + row_pos) as usize
}

// Calculate the flattened index based on row and position
fn calculate_triangle_size(num_rows: u32) -> usize {
  flattened_index(num_rows, 0) as usize
}

const NUM_TRIANGLE_ROWS: u32 = 15;
const TRIANGLE: &[u32] = &[
	75,
	95, 64,
	17, 47, 82,
	18, 35, 87, 10,
	20, 4, 82, 47, 65,
	19, 1, 23, 75, 3, 34,
	88, 2, 77, 73, 7, 63, 67,
	99, 65, 4, 28, 6, 16, 70, 92,
	41, 41, 26, 56, 83, 40, 80, 70, 33,
	41, 48, 72, 33, 47, 32, 37, 16, 94, 29,
	53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14,
	70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57,
	91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48,
	63, 66, 4, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31,
	4, 62, 98, 27, 23, 9, 70, 98, 73, 93, 38, 53, 60, 4, 23,
];
