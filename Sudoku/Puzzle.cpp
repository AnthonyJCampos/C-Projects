/** @file Puzzle.cpp
 @author Anthony Campos
 @date 11/15/2021
 This is implementation file a & game known as a 
	Sudoku Puzzle made up of nested Sqaure class 
	that holds an integer value and bool value*/

#include "Puzzle.h"

/** overloaded ostream method
 diplays the Puzzle object to ostream stream
 @param ostream out [out] and Puzzle object [puzzle]
 @pre Must be a Puzzle object
 @post Ostream object in the following format:
	4 2 3|7 5 1|9 6 8
	7 5 9|6 8 3|1 2 4
	1 6 8|2 4 9|3 5 7
	------+-----+------
	9 4 5|3 6 2|8 7 1
	8 7 2|9 1 5|4 3 6
	3 1 6|4 7 8|2 9 5
	------+-----+------
	5 3 7|1 9 4|6 8 2
	6 9 1|8 2 7|5 4 3
	2 8 4|5 3 6|7 1 9
@return ostream object that represents an Puzzle */
std::ostream& operator<<(std::ostream& out, const Puzzle& puzzle) {

	// loop through each row
	for (int row = 0; row < puzzle.defaultRowSize_; ++row) {
		
		// if row equals 3 or 6 diplay section break
		if (row == 3 || row == 6) {
			out << "------+-----+------\n";
		} // end if

		for (int col = 0; col < puzzle.defaultColSize_; ++col) {


			// if col does not equals 3 or 6 don't display section break
			if (col != 3 && col != 6) {
				
				// if get does not equal -1 then display square value
				
				if (puzzle.get(row, col) != -1) {
					out << " " << puzzle.get(row, col);
				}
				else { // else display empty space
					out << "  ";
				} // end if

			}
			else {
				
				// if get does not equal -1 then display square value with section break
				if (puzzle.get(row, col) != -1) {
					out << "|" << puzzle.get(row, col);
				}
				else { // else display empty space with section break
					out << "| ";
				} // end if

			} // end if


		} // end for
		
		// if not last row new line
		if (row != puzzle.defaultRowSize_ - 1) {
			out << "\n";
		} // end if

	} // end for

	return out; // return out
} // end of ostream friend method

/** overloaded istream method
inserts first 81 integer values into Puzzle object using istream
@param istream in [input] and Puzzle object [puzzle]
@pre istream in is open for reading
@post collects first 81 integers values from istream, attempts to insert
values into puzzle object by calling fill. If fill() discovers
invalid puzzle provided, fill returns false, runtime error is thrown and the puzzle is reset. If valid
puzzle provided fill() inserts the 81 values into the puzzle object.
@return istream [input] */
std::istream& operator>>(std::istream& input, Puzzle& puzzle) {

	// get input line,
	std::string inputDigits;
	std::getline(input, inputDigits);
	// use the first 81 ASCII characters
	const int maxInput = 81;
	//store usable inputs
	int outputDigits[maxInput]{ 0 };
	int digitCount = 0; // track usable digits.

	// loop through the input
	for (decltype(inputDigits.size()) i = 0; i < inputDigits.size() && digitCount < maxInput; ++i) {

		//if the char at a given index is between 0 to 9
		//then it is usable
		if (inputDigits[i] >= '0' && inputDigits[i] <= '9') {

			outputDigits[digitCount] = static_cast<int>(inputDigits[i]) - 48;
			++digitCount;

		} // end if

	} // end if

	// call fill method
	if(!puzzle.fill(outputDigits)) {

		throw std::runtime_error("None Valid Puzzle Provided, Puzzle Fill Did Not Complete");

	}// end if

	return input; // return input

} // end of overloaded operator>>


/** Puzzle Class   */

/** Puzzle Constructor*/
Puzzle::Puzzle() 
:size_(81) {
} // end of Constructor



/** gets current value at given row [x] and col [y]
@param row index [x], and col index [y]
@return the integer value at the given indices*/
int Puzzle::get(int x, int y) const {
	//return value at specific x/row or y/col
	return puzzleStructure_[x][y].getValue();

} // end of get

/** sets value at given row [x] and col [y] to new integer value [newValue]
@param row index [x], and col index [y], and new value [newValue]
@post if successful, [newValue] added at provided indices, check by
calling contains() method
@return true if [newValue] added to indices, false otherwise*/
bool Puzzle::set(int x, int y, int newValue) {
	// hold if value was set successfully
	bool valueSet = false;

	if (!contains(x, y, newValue)) {

		puzzleStructure_[x][y].setValue(newValue);
		valueSet = true;

	} // end if

	return valueSet; // return valueSet
} // end of set

/** contains check to see if provided value is legal to insert at provided indices
@param [targetRow] row to be inserted at, [targetCol] col to be inserted at, and
[value] the integer to insert
@return True if [value] is legal to insert at specific indices, false otherwise. */
bool Puzzle::contains(int targetRow, int targetCol, int value) const {
	bool found = false;

	// searches columns for occurrence of value
	for (int row = 0; row < defaultRowSize_; ++row) {	
		if (get(row, targetCol) == value) {
			found = true; // set found to true
			row = defaultRowSize_; // break out of loop
		} // end if

	} // end for

	// searches row for occurrence of value

	for (int col = 0; col < defaultColSize_; ++col) {

		if (get(targetRow, col) == value) {
			found = true; // set found to true
			col = defaultColSize_; // break out of loop
		} // end if

	} // end for

	// must search particular 3*3 matrix,
	//starting row position
	int startRowPos = targetRow - targetRow % 3;
	//starting column position
	int startColPos = targetCol - targetCol % 3;

	for (int i = 0; i < 3; i++) {
		
		for (int j = 0; j < 3; j++) {
			
			if (get((i + startRowPos), (j + startColPos)) == value) {
				found = true; // set found to true
			} // end if

		} // end for

	} // end for

	return found; // return found

} // end contains

/** size returns the number of variable entries in the puzzle,
corresponding to the original size of the puzzle.
@return The integer number of variable entries in the puzzle*/
int Puzzle::size() const {
	
	return size_;

} // end size

/** numEmpty returns amount of open spaces in the puzzle object
@return integer number that represents the number of current open spaces*/
int Puzzle::numEmpty() const {
	// holds open space count
	int openSpaceCount = 0;

	for (int row = 0; row < defaultRowSize_; ++row) {
		
		for (int col = 0; col < defaultColSize_; ++col) {
			
			if (get(row, col) < 0) {
				++openSpaceCount;
			} // end if

		} // end for

	} // end for

	return openSpaceCount; // return open space count
} // end numEmpty

/** solve, solves the provided puzzle stating at the provided indices
recursively using backtracking.
@param [row] and [col] starting indices
@post if successful, the provided sudoku puzzle has been solved,
calls set(), numEmpty(), moveToEmptySquare(), getFixed(), setValue
@return true if puzzle successfully solved, otherwise false */
bool Puzzle::solve(int row, int col) {
	
	// base case
	if (numEmpty() == 0) {
		
		return true; // return true/success

	} // end if

	//Move to next square without a value
	moveToHardestSquare(row, col);

	for (int i = 1; i < 10; ++i) {
		
		//check if legal move
		//if legel value is set
		if (set(row, col, i)) {

			if (solve(row, col)) {
				return true; // return true/success
			} // end if

		} // end if

		// remove incorrect value;
		// don't remove fixed values
		if (!puzzleStructure_[row][col].getFixed()) {
			puzzleStructure_[row][col].setValue(0);
		} // end if	

	} // end for

	// no values valid in current square, previous square is invalid
	return false;

} // end solve

/** solve, solves the provided puzzle stating at indices [0,0].
@post if successful, the provided sudoku puzzle has been solved,
calls solve(int row, int col)
@return true if puzzle successfully solved, otherwise false */
bool Puzzle::solve() {

	return solve(0, 0);

} // end solve

/** clear resets all square objects to default values and size_
@post all Sqaure objects in the puzzle contain a value of -1, false
for fixed_, and size_ reset to 81*/
void Puzzle::clear() {
	
	//loop through each row
	for (int row = 0; row < defaultRowSize_; ++row) {
		
		//loop through each column
		for (int col = 0; col < defaultColSize_; ++col) {

			puzzleStructure_[row][col].resetSquare();

		} // end for

	} // end for

	// reset size of Puzzle object
	size_ = 81; 

} // end clear

/** getOptions get the amount of options for the given sqaure
@param [targetRow] and [targetCol], indices of the current sqaure
@return the count of options for the given sqaure*/
int Puzzle::getOptions(int targetRow, int targetCol) const {

	int optionCount = 0;
	// count open columns for target sqaure
	for (int row = 0; row < defaultRowSize_; ++row) {
		
		if (get(row, targetCol) == -1) {
			++optionCount; 
		} // end if	

	} // end for

	// count open row for target sqaure
	for (int col = 0; col < defaultColSize_; ++col) {
		
		if (get(targetRow, col) == -1) {
			++optionCount;
		} // end if

	} // end for

	// must search particular 3*3 matrix,
	//starting row position
	int startRowPos = targetRow - targetRow % 3;
	//starting column position
	int startColPos = targetCol - targetCol % 3;

	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < 3; j++) {
			
			if (get((i + startRowPos), (j + startColPos)) == -1) {
				++optionCount;
			} // end if

		} // end for

	} // end for

	return optionCount; // return optionCount

} // end getOptions

/** moveToHardestSquare Searches for next open space
with the least amount of choices.
@param [row] and [col] passed by reference, indices to update to new open space
@post updates [row] and [col] to open space with the least
amount of options by calling getOptions*/
void Puzzle::moveToHardestSquare(int& row, int& col) {

	/** Coordinates struct */
	struct Coordinates {
		
		// attributes of Coordinates
		int rowC; // hold row/x coordinate
		int colC; // hold col/y coordinate
		int options; // holds amount of options

		//overloaded comparison methods
		//these are for std::sort
		bool operator==(const Coordinates& rhs) const {
			return options == rhs.options;
		} // end overloaded ==
		bool operator<(const Coordinates& rhs) const {
			return options < rhs.options;
		} // end overloaded <
		bool operator>(const Coordinates& rhs) const {
			return options > rhs.options;
		} // end overloaded >

	}; // end Coordinates

	// vector to hold open spaces in puzzle
	std::vector<Coordinates> options{};
	// loop through each row
	for (int i = 0; i < defaultRowSize_; ++i) {
		// loop through each col
		for (int j = 0; j < defaultColSize_; ++j) {

			// if sqaure at i(row), j(col) eqauls -1
			if (get(i, j) == -1) {
				// blank space found

				//create temp object to hold this space
				Coordinates temp;
				temp.rowC = i;
				temp.colC = j;
				//get the amount of options at the given indices
				temp.options = getOptions(i, j);
				//push back this sqaure for later comparison
				options.push_back(temp);

			} // end if

		} // end for

	} // end for

	// find an return the space with the least amount of options
	// sorts our options from least to greatest
	std::sort(options.begin(), options.end());

	// double check to confirm our vector is not empty
	if (!options.empty()) {
		
		//set the space to use in solve
		row = options[0].rowC;
		col = options[0].colC;
	} // end if

}// end moveToEmptySquare

/** fill
@param inputData[] holding 81 integer values
@post If successful 81 integer values are inserted into Puzzle Squares,
Otherwise, returns false and resets puzzle object data.
@return true if fill is successful, false otherwise*/
bool Puzzle::fill(const int inputData[]) {

	bool success = true;
	int inputIndex = 0; // index variable for inputData

	// loop through each row
	for (int row = 0; row < defaultRowSize_ && success; ++row) {

		// loop through column
		for (int col = 0; col < defaultColSize_ && success; ++col) {
			
			// check if value is a blank space, represented 
			if (inputData[inputIndex] != 0) { 

				if (!contains(row, col, inputData[inputIndex])) {

					puzzleStructure_[row][col].setValue(inputData[inputIndex]);
					puzzleStructure_[row][col].setFixed(true);
					++inputIndex;

				}
				else {

					success = false;
					// call clear method to reset puzzle object. 
					clear(); 

				} // end if

			}
			else { // Blank Space

				puzzleStructure_[row][col].setValue(inputData[inputIndex]);
				++inputIndex;

			} // end if

		} // end for

	} // end for

	// set size_ to current open space count
	size_ = numEmpty();
	return success;

} // end fill

/** Nested Square Class   */

/** Square Constructor*/
Puzzle::Square::Square(int value, bool fixed) 
:value_(value), fixed_(fixed){} // end of Constructor



/** getValue
@return integer value stored in value_*/
int Puzzle::Square::getValue() const {
	
	return ((value_ > 0) ? value_ : (-1));

} // end of getValue()

/** getfixed
@return bool value stored in fixed_*/
bool Puzzle::Square::getFixed() const {
	
	return fixed_; // return fixed_

} // end getFixed

/** setValue
@param [newValue] the integer value to change value_ to*/
void Puzzle::Square::setValue(int newValue) {

	value_ = newValue;

} // end of setValue()

/** setFixed
@param [fixed] the bool value to change fixed_ to*/
void Puzzle::Square::setFixed(bool fixed) {
	
	fixed_ = fixed; 

} // end setFixed

/** resetSqaure
@post resets Square object to default values*/
void Puzzle::Square::resetSquare() {
	
	value_ = -1;
	fixed_ = false;

} // end reset Sqaure
