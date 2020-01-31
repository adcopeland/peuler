#include <iostream>
#include <vector>

// The triangle data
static const int NUM_TRIANGLE_ROWS = 15;
static const int TRIANGLE[] = {
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
};

// Calculate the flattened index based on row and position
constexpr int flattenedIndex(int rowNum, int rowPos) {
  int sum = 0;
  for (int i = 0; i < rowNum; ++i) {
    sum += i+1;
  }
  return sum+rowPos;
}

// Calculate the triangle size based on the number of rows
constexpr int calculateTriangleSize(int numRows) {
  return flattenedIndex(numRows, 0);
}

// Holds memoized results and a reference to the data
class Solver {
  public:
    explicit Solver(const int* triangle, int numRows);
    int MaxSum(int rowNum, int rowPos);
  private:
    std::vector<int> m_memoizedResults;
    const int* const m_triangle;
    const int        m_numRows;
};

// Calculate the answer to the problem
int main() {
  constexpr int NUM_TRIANGLE_ELEMENTS = sizeof(TRIANGLE) / sizeof(decltype(TRIANGLE[0]));
  static_assert(NUM_TRIANGLE_ELEMENTS == calculateTriangleSize(NUM_TRIANGLE_ROWS),
    "Data in TRIANGLE does not line up with NUM_TRIANGLE_ROWS");

  Solver solver(TRIANGLE, NUM_TRIANGLE_ROWS);
  std::cout << solver.MaxSum(0,0) << "\n";
}

// Construct a solver
Solver::Solver(const int* triangleData, int numRows)
  : m_memoizedResults(calculateTriangleSize(numRows), 0)
  , m_triangle(triangleData)
  , m_numRows(numRows)
{
}

// Determine the max sum for the provided (row, pos) "index"
int Solver::MaxSum(int rowNum, int rowPos) {
  const int thisRowIndex = flattenedIndex(rowNum, rowPos);

	// If this position already has a max sum, return it.
  int result = m_memoizedResults[thisRowIndex];
  if (result != 0) {
    return result;
  }

	// If there's no next row down, then the new max is just this value.
	// store and return the result.
  const int currentVal = m_triangle[thisRowIndex];
  const int nextRowNum = rowNum+1;
  if (nextRowNum >= m_numRows) {
    result = currentVal;
    m_memoizedResults[thisRowIndex] = result;
    return result;
  }

	// Otherwise, new max would be the larger of the MaxSum for the next row at the current
	// rowPos or the current rowPos + 1.
	// The next row always has 1 more item than this one, so no need to verify rowPos+1 exists.
  const int equalPosVal   = MaxSum(nextRowNum, rowPos);
  const int plusOnePosVal = MaxSum(nextRowNum, rowPos+1);

  // store and return after adding in the current value
  result = std::max(equalPosVal, plusOnePosVal) + currentVal;
  m_memoizedResults[thisRowIndex] = result;
  return result;
}
