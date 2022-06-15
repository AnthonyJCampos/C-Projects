/** @file Puzzle.H
 @author Anthony Campos
 @date 11/15/2021
 This header class file implements a data structure & game 
	known as a Sudoku Puzzle made up of nested Sqaure class 
	that holds an integer value and bool value*/

#pragma once

#include <string>
#include <iostream>

// test stuff
#include <queue>
#include <vector>
#include <algorithm>

class Puzzle{

	/** Puzzel friend methods*/


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
	friend std::ostream& operator<<(std::ostream & out, const Puzzle & puzzle);

	/** overloaded istream method
	inserts first 81 integer values into Puzzle object using istream
	@param istream in [input] and Puzzle object [puzzle]
	@pre istream in is open for reading
	@post collects first 81 integers values from istream, attempts to insert 
	values into puzzle object by calling fill. If fill() discovers 
	invalid puzzle provided, fill returns false, runtime error is thrown and the puzzle is reset. If valid 
	puzzle provided fill() inserts the 81 values into the puzzle object.
	@return istream [input] */
	friend std::istream& operator>>(std::istream& input, Puzzle& puzzle);

public:

	/** Puzzle Constructor */
	Puzzle();

	/** Puzzle Methods*/

	/** Puzzle Accessors */

	/** gets current value at given row [x] and col [y]
	@param row index [x], and col index [y] 
	@return the integer value at the given indices*/
	int get(int x, int y) const;


	/** Puzzle Mutators */

	/** sets value at given row [x] and col [y] to new integer value [newValue]
	@param row index [x], and col index [y], and new value [newValue]
	@post if successful, [newValue] added at provided indices, check by
	calling contains() method
	@return true if [newValue] added to indices, false otherwise*/
	bool set(int x, int y, int newValue);

	/** contains check to see if provided value is legal to insert at provided indices
	@param [targetRow] row to be inserted at, [targetCol] col to be inserted at, and
	[value] the integer to insert
	@return True if [value] is legal to insert at specific indices, false otherwise. */
	bool contains(int targetRow, int targetCol, int value) const;

	/** size returns the number of variable entries in the puzzle,
	corresponding to the original size of the puzzle.
	@return The integer number of variable entries in the puzzle*/
	int size() const;

	/** numEmpty returns amount of open spaces in the puzzle object
	@return integer number that represents the number of current open spaces*/
	int numEmpty() const;

	/** solve, solves the provided puzzle stating at the provided indices
	recursively using backtracking. 
	@param [row] and [col] starting indices
	@post if successful, the provided sudoku puzzle has been solved,
	calls set(), numEmpty(), moveToEmptySquare(), getFixed(), setValue
	@return true if puzzle successfully solved, otherwise false */
	bool solve(int row, int col);

	/** solve, solves the provided puzzle stating at indices [0,0].
	@post if successful, the provided sudoku puzzle has been solved,
	calls solve(int row, int col)
	@return true if puzzle successfully solved, otherwise false */
	bool solve();


	/** clear resets all square objects to default values and size_
	@post all Sqaure objects in the puzzle contain a value of -1, false 
	for fixed_, and size_ reset to 81*/
	void clear();


private:

	/** Puzzle attributes*/

	/** Square Class */

	class Square {

	public:

		/** Square Constructor*/
		Square(int value = - 1, bool fixed = false);

		/** Square Methods*/

		/** Square Accessors */

		/** getValue 
		@return integer value stored in value_*/
		int getValue() const;

		/** getfixed 
		@return bool value stored in fixed_*/
		bool getFixed() const;

		/** Square Mutators */

		/** setValue 
		@param [newValue] the integer value to change value_ to*/
		void setValue(int newValue);

		/** setFixed 
		@param [fixed] the bool value to change fixed_ to*/
		void setFixed(bool fixed);

		/** resetSqaure 
		@post resets Square object to default values*/
		void resetSquare();


	private:

		/** Square Attributes*/

		// holds the squares numerical value. default is -1
		int value_;
		// A flag indicating if the value is fixed 
		// is (one of the values given at the start of the puzzle)
		// or variable (the values written in as parts of a possible solution)
		bool fixed_;

	}; // end of Square

	// holds the count of variable entries in the puzzle
	int size_;
	// Fixed row of puzzle grid. 
	static const int defaultRowSize_ = 9;
	// Fixed column size of puzzle.
	static const int defaultColSize_ = 9;

	// Puzzle data structure
	Square puzzleStructure_ [defaultRowSize_][defaultColSize_];

	/** Private Methods*/

	/** fill 
	@param inputData[] holding 81 integer values
	@post If successful 81 integer values are inserted into Puzzle Squares, 
	Otherwise, returns false and resets puzzle object data.
	@return true if fill is successful, false otherwise*/
	bool fill(const int inputData[]);


	/** getOptions get the amount of options for the given sqaure
	@param [targetRow] and [targetCol], indices of the current sqaure
	@return the count of options for the given sqaure*/
	int getOptions(int targetRow, int targetCol) const;

	/** moveToHardestSquare Searches for next open space
	with the least amount of choices.
	@param [row] and [col] passed by reference, indices to update to new open space
	@post updates [row] and [col] to open space with the least 
	amount of options by calling getOptions*/
	void moveToHardestSquare(int& row, int& col);

}; // end of Puzzle

