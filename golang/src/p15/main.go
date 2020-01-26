package main

import "fmt"

// Get the number of routes from the top to the bottom of a 20x20 grid.
// Note: At each step we can go right or down. There will be 40 decisions,
//       because we eventually have to go right 20 times and down 20 times.

// This tracks state of a route. It contains the number of downs and number of rights so far.
type State struct {
	NumDown   uint8
	NumRight  uint8
	Direction Direction
}

type Direction bool

const Right Direction = true
const Down Direction = false

// Grid is 20x20. Note: MaxDown/MaxRight is the max valid INDEX to use, starting from 0.
// However, because of how the calculation works the starting row is the outside corner (not counted in the grid)
// so even though a GridMaxDown of 20 and GridMaxRight of 20 results in a 21x21 array, it acts like a 20x20 grid.
const GridMaxDown uint8 = 20
const GridMaxRight uint8 = 20

// Basically a wrapper around memoizedResults so it's not global
type Solver struct {
	memoizedResults [GridMaxDown + 1][GridMaxRight + 1]uint64
}

func main() {
	var solver Solver

	// Since Direction can't be set initially, main actually sums the possibilities of the 2 starting paths (right and down)
	possibilitiesDown := solver.NumRoutesFrom(State{
		NumDown:   1,
		NumRight:  0,
		Direction: Down,
	})
	possibilitiesRight := solver.NumRoutesFrom(State{
		NumDown:   0,
		NumRight:  1,
		Direction: Right,
	})

	// Add the possibiltiies of those two routes together, plus the 2 routes themselves
	fmt.Println(possibilitiesDown + possibilitiesRight + 2)
}

// Determine the number of routes to the bottom corner from the current state,
// via recursion
func (self *Solver) NumRoutesFrom(s State) uint64 {
	// Base case: We've reached the end
	if s.NumDown == GridMaxDown && s.NumRight == GridMaxRight {
		return uint64(0)
	}

	// Make use of memoized results if we're been here before.
	// Cheating a little because we know the array initializes to 0 and every spot has at least one route to the end.
	memoizedResult := self.memoizedResults[s.NumDown][s.NumRight]
	if memoizedResult != 0 {
		return memoizedResult
	}

	// Sum the possibilities of all choices from the current state.
	// In each case, add one to the number of routes to account for the new route generated.
	possibilitiesDown := uint64(0)
	if s.NumDown < GridMaxDown {
		nextState := s
		nextState.NumDown++
		nextState.Direction = Down
		possibilitiesDown = self.NumRoutesFrom(nextState) + self.NewRoute(s, nextState)
	}

	possibilitiesRight := uint64(0)
	if s.NumRight < GridMaxRight {
		nextState := s
		nextState.NumRight++
		nextState.Direction = Right
		possibilitiesRight = self.NumRoutesFrom(nextState) + self.NewRoute(s, nextState)
	}

	// result is the sum of the possibilities.
	// Store it and return it.
	result := possibilitiesDown + possibilitiesRight
	self.memoizedResults[s.NumDown][s.NumRight] = result
	return result
}

// A route is a new route if we turned away from the path we're traveling on AND
// that turn was not a "forced" turn (we hit the end of the board; the "continuing"
// route doesn't exist, it's turning)
func (*Solver) NewRoute(s, next State) uint64 {
	if s.Direction != next.Direction {
		forcedTurnRight := s.NumDown == GridMaxDown && s.Direction == Down
		forcedTurnDown := s.NumRight == GridMaxRight && s.Direction == Right
		forcedTurn := forcedTurnRight || forcedTurnDown
		if !forcedTurn {
			return 1
		}
	}
	return 0
}
