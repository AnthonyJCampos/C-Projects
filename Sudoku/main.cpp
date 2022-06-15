/** @file main.cpp
 @author Anthony Campos
 @date 11/15/2021
 This is the driver cpp file to run the Sudoku
 Puzzle game.*/

#include <iostream>
#include <chrono>
#include "Puzzle.h"


int main() {

	// introduction to the program
	std::cout << "\n=============== Let's solve some Sudoku Puzzle ===============" << std::endl;
	// get the amount of puzzles the user would like to solve.
	std::cout << "How many Sudoku Puzzle's would you like to solve? Please enter an integer value: ";
	// store user input
	int userInput;
	std::cin >> userInput;
	// Restore input stream to working state
	std::cin.clear();
	// Get rid of any garbage that user might have entered
	std::cin.ignore(100, '\n');

	std::cout << "\nThank you, time to solve " << userInput << " Sudoku Puzzle(s)." << std::endl;

	//loop number of times requested by user
	for (int i = 0; i < userInput; ++i) {

		// Puzzle object
		Puzzle puzzleObj;

		try {
			// get puzle from user
			std::cout << "\nPlease provide a Sudoku Puzzle:";
			std::cin >> puzzleObj;

			// display provided puzzle
			std::cout << "\n\n" << puzzleObj << std::endl;
			std::cout << "\nSize: " << puzzleObj.size() << ", Open Blank Spaces: " << puzzleObj.numEmpty() << std::endl;
			std::cout << "Solving..." << std::endl;

			// begin solving timer
			auto start = std::chrono::high_resolution_clock::now();

			if (puzzleObj.solve()) {

				//  calculate time it took to solve puzzle
				auto stop = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);

				// display puzzle object and time taken
				std::cout << "\n\n" << puzzleObj << std::endl;
				std::cout << "\nSize: " << puzzleObj.size() << ", Open Blank Spaces: " << puzzleObj.numEmpty() << std::endl;
				std::cout << "Time Taken: " << duration.count() << " seconds" << std::endl;

				//clear puzzle object for next loop iteration
				puzzleObj.clear();

			}
			else { // the puzzle was not solveable
				auto stop = std::chrono::high_resolution_clock::now();
				std::cout << "The provided puzzle could not be solved by the system!" << std::endl;
			} // end if

		}
		catch (std::runtime_error err) {
			// diplay error message
			std::cerr << err.what() << std::endl;

		} // end try

	} // end for

	std::cout << "\nThank you for playing. Have a wonderful day!" << std::endl;
	
} // end main