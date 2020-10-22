//Source for MazeSolver

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "MazeCell.h"
#include "Stack.h"

using namespace std;

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
#define DONE 4
#define SUCCESS 10
#define FAILURE 20

//method headers*******************************************************

//depthFirst header
void depthFirst(MazeCell start, MazeCell end);

//global variables*****************************************************

//# rows and cols in the maze
int rows, cols;
//pointer to the grid (2-d array of ints)
int** grid;
//pointer to the maze cells (2-d array of MazeCell objects)
MazeCell** cells;

int main() {

    //create the Maze from the file
    ifstream fin("maze.in");
    if(!fin){
        cout << "File not found\n";
        exit(2);
    }

    //read in the rows and cols
    fin >> rows >> cols;

    //create the maze rows
    grid = new int* [rows];

    //add each column
    for (int i = 0; i < rows; i++)
        grid[i] = new int[cols];

    //read in the data from the file to populate
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fin >> grid[i][j];
        }
    }

    //look at it
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 3)
                cout << "S" << " ";
            else if (grid[i][j] == 4)
                cout << "E" << " ";
            else
                cout << grid[i][j] << " ";
        }
        cout << endl;
    }

    //make a 2-d array of cells
    cells = new MazeCell * [rows];
    for (int i = 0; i < rows; i++) {
        cells[i] = new MazeCell[cols];
    }

    //all MazeCell in the cells grid has a default init
    //only update those cells that are not walls

    MazeCell start, end;

    //iterate over the grid
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] != 0) {
                cells[i][j].setCoordinates(i, j);
                //look for the start and end cells
                if (grid[i][j] == 3)
                    start = cells[i][j];
                if (grid[i][j] == 4)
                    end = cells[i][j];

            }

        }
    }

    //testing
    cout <<"start: "<< start << " end: " << end << endl;

    //solve it!
    depthFirst(start, end);


    return 0;
}


//this function should find a path through the maze
//if found, output the path from start to end
//if not path exists, output a message stating so

void depthFirst(MazeCell start, MazeCell end) {
    int row = start.getRow();                                           // Gets the initial row and column
    int col = start.getCol();

    Stack<MazeCell> crackAddict;                                        // creates a stack called crack addict and sets the initial position
    crackAddict.insert(cells[row][col]);

    while (grid[row][col] != 4) {                                       // while we haven't reached the end
        grid[row][col] = 0;
        /*
         * If statements check which directions the head can move
         * Adds or subtracts from row and col as needed to move
         * Else if the head can't move pop top and move back one
         */
        if (((col - 1) >= 0) && grid[row][col - 1] != 0) {              // west
            col--;
            crackAddict.insert(cells[row][col]);
        } else if (((col + 1) <= 5) && grid[row][col + 1] != 0) {       // east
            col++;
            crackAddict.insert(cells[row][col]);
        } else if (((row + 1) <= 3) && grid[row + 1][col] != 0) {       // south
            row++;
            crackAddict.insert(cells[row][col]);
        } else if (((row - 1) >= 0) && grid[row - 1][col] != 0) {       // north
            row--;
            crackAddict.insert(cells[row][col]);
        } else {
            if(!crackAddict.empty()) {
                crackAddict.pop();
                MazeCell temp = crackAddict.top();
                col = temp.getCol();
                row = temp.getRow();
            }
        }
    }

    if (!crackAddict.empty()) {                                         // if the maze path is not empty output solution
        cout << "Maze Path: ";
        while (!crackAddict.empty()) {
            cout << crackAddict.top() << " ";
            crackAddict.pop();
        }
    } else { cout << "No Exit" << endl; }                               // else no solution
}


