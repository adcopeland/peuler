// Get the number of routes from the top to the bottom of a 20x20 grid.
// Note: At each step we can go right or down. There will be 40 decisions,
//       because we eventually have to go right 20 times and down 20 times.

#[derive(Copy,Clone)]
enum Direction {
  Right,
  Down,
}

// This tracks state of a route. It contains the number of downs and number of rights so far.
#[derive(Copy,Clone)]
struct State {
  num_down:  u8,
  num_right: u8,
  dir:       Direction,
}

// Grid is 20x20. Note: MaxDown/MaxRight is the max valid INDEX to use, starting from 0.
// However, because of how the calculation works the starting row is the outside corner (not counted in the grid)
// so even though a GridMaxDown of 20 and GridMaxRight of 20 results in a 21x21 array, it acts like a 20x20 grid.
const GRID_MAX_DOWN:  u8 = 20;
const GRID_MAX_RIGHT: u8 = 20;

const GRID_MAX_DOWN_USIZE:  usize = GRID_MAX_DOWN  as usize;
const GRID_MAX_RIGHT_USIZE: usize = GRID_MAX_RIGHT as usize;

fn main() {
  let mut solver = Solver::new();

	// Since Direction can't be set initially, main actually sums the possibilities of the 2 starting paths (right and down)
  let possibilities_down = solver.num_routes_from(State{
    num_down:  1,
    num_right: 0,
    dir:       Direction::Down,
  });

  let possibilities_right = solver.num_routes_from(State{
    num_down:  0,
    num_right: 1,
    dir:       Direction::Right,
  });

  // Add the possibilities of those two routes together, plus the 2 routes themselves
  println!("{}", possibilities_down + possibilities_right + 2);
}

// Admittedly the other versions (C++ and golang) should've looked like this to avoid
// a global mutable array, but I only did it for the rust version since it actually complains.
// With this tiny problem/scope, I wasn't concerned.
struct Solver {
  memoized_results: [[u64; GRID_MAX_DOWN_USIZE+1]; GRID_MAX_RIGHT_USIZE+1],
}

impl Solver {
  fn new() -> Solver {
    Solver{
      memoized_results: [[0u64; GRID_MAX_DOWN_USIZE+1];GRID_MAX_RIGHT_USIZE+1],
    }
  }

  // Determine the number of routes to the bottom corner from the current state, via recursion
  fn num_routes_from(&mut self, s: State) -> u64 {
    // Base case: We've reached the end
    if s.num_down == GRID_MAX_DOWN && s.num_right == GRID_MAX_RIGHT {
      return 0u64;
    }
  
  	// Make use of memoized results if we're been here before.
  	// Cheating a little because we know the array initializes to 0 and every spot has at least one route to the end.
    let memoized_result = self.memoized_results[s.num_down as usize][s.num_right as usize];
    if memoized_result != 0u64 {
      return memoized_result;
    }
  
  	// Sum the possibilities of all choices from the current state.
  	// In each case, add one to the number of routes to account for the new route generated.
    let mut possibilities_down = 0u64;
    if s.num_down < GRID_MAX_DOWN {
      let mut next_state = s;
      next_state.num_down += 1;
      next_state.dir = Direction::Down;
      possibilities_down = self.num_routes_from(next_state) + self.new_route(s, next_state);
    }
  
    let mut possibilities_right = 0u64;
    if s.num_right < GRID_MAX_RIGHT {
      let mut next_state = s;
      next_state.num_right += 1;
      next_state.dir = Direction::Right;
      possibilities_right = self.num_routes_from(next_state) + self.new_route(s, next_state);
    }
  
    let result = possibilities_down + possibilities_right;
    self.memoized_results[s.num_down as usize][s.num_right as usize] = result;
    return result;
  }
  
  // A route is a new route if we turned away from the path we're traveling on AND
  // that turn was not a "forced" turn (we hit the end of the board; the "continuing"
  // route doesn't exist, it's turning)
  // returns 1 for new routes, 0 for "continuing" routes
  fn new_route(&self, s: State, next: State) -> u64 {
    match(s.dir, next.dir) {
      // check for down-to-right forced turn
      (Direction::Down, Direction::Right) => {
        let forced_turn = s.num_down == GRID_MAX_DOWN;
        if forced_turn { 0u64 } else { 1u64 }
      }
      // check for right-to-down forced turn
      (Direction::Right, Direction::Down) => {
        let forced_turn = s.num_right == GRID_MAX_RIGHT;
        if forced_turn { 0u64 } else { 1u64 }
      }
      // otherwise, just continuing in the same direction
      _ => 0u64
    }
  }

}
