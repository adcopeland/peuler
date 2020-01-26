// Get the number of routes from the top to the bottom of a 20x20 grid.
// Note: At each step we can go right or down. There will be 40 decisions,
//       because we eventually have to go right 20 times and down 20 times.

#include <iostream>
#include <cstdint>

enum Direction : uint8_t {
  Right,
  Down
};

// This tracks state of a route. It contains the number of downs and number of rights so far.
struct State {
  uint8_t   NumDown;
  uint8_t   NumRight;
  Direction Dir;
};

// Grid is 20x20. Note: MaxDown/MaxRight is the max valid INDEX to use, starting from 0.
// However, because of how the calculation works the starting row is the outside corner (not counted in the grid)
// so even though a GridMaxDown of 20 and GridMaxRight of 20 results in a 21x21 array, it acts like a 20x20 grid.
static constexpr uint8_t GridMaxDown  = 20u;
static constexpr uint8_t GridMaxRight = 20u;

// Wrapper to hold the memoized results
class Solver {
  public:
    Solver();
    uint64_t NumRoutesFrom(State s);
    uint64_t NewRoute(State current, State next);

  private:
    uint64_t MemoizedResults[GridMaxDown+1][GridMaxRight+1];
};

int main() {
  Solver solver;

	// Since Direction can't be set initially, main actually sums the possibilities of the 2 starting paths (right and down)
  const auto possibilitiesDown  = solver.NumRoutesFrom(State{1, 0, Down});
  const auto possibilitiesRight = solver.NumRoutesFrom(State{0, 1, Right});

	// Add the possibiltiies of those two routes together, plus the 2 routes themselves
  std::cout << (possibilitiesDown + possibilitiesRight + 2) << "\n";
}

// Initialize by zero-ing out the results
inline Solver::Solver()
{
  for (uint8_t i = 0u; i < GridMaxDown+1; ++i) {
    for (uint8_t j = 0u; j < GridMaxRight+1; ++j) {
      MemoizedResults[i][j] = 0u;
    }
  }
}

// Determine the number of routes to the bottom corner from the current state, via recursion
inline uint64_t Solver::NumRoutesFrom(State s) {
  // Base case: We've reached the end
  if (s.NumDown == GridMaxDown && s.NumRight == GridMaxRight) {
    return 0u;
  }

	// Make use of memoized results if we're been here before.
	// Cheating a little because we know the array initializes to 0 and every spot has at least one route to the end.
  const uint64_t memoizedResult = MemoizedResults[s.NumDown][s.NumRight];
  if (memoizedResult != 0u) {
    return memoizedResult;
  }

	// Sum the possibilities of all choices from the current state.
	// In each case, add one to the number of routes to account for the new route generated.
	uint64_t possibilitiesDown = 0u;
	if (s.NumDown < GridMaxDown) {
		State nextState = s;
		++nextState.NumDown;
		nextState.Dir = Down;
		possibilitiesDown = NumRoutesFrom(nextState) + NewRoute(s, nextState);
	}

	uint64_t possibilitiesRight = 0u;
	if (s.NumRight < GridMaxRight) {
		State nextState = s;
		++nextState.NumRight;
		nextState.Dir = Right;
		possibilitiesRight = NumRoutesFrom(nextState) + NewRoute(s, nextState);
	}

	// result is the sum of the possibilities.
	// Store it and return it.
	const uint64_t result = possibilitiesDown + possibilitiesRight;
	MemoizedResults[s.NumDown][s.NumRight] = result;
	return result;
}

// A route is a new route if we turned away from the path we're traveling on AND
// that turn was not a "forced" turn (we hit the end of the board; the "continuing"
// route doesn't exist, it's turning)
inline uint64_t Solver::NewRoute(State s, State next) {
  if (s.Dir != next.Dir) {
    const bool forcedTurnRight = s.NumDown  == GridMaxDown  && s.Dir == Down;
    const bool forcedTurnDown  = s.NumRight == GridMaxRight && s.Dir == Right;
    const bool forcedTurn = forcedTurnRight || forcedTurnDown;
    if (!forcedTurn) {
      return 1;
    }
  }
  return 0;
}
