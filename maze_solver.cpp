/*------------------------------------------------------------- 
   Maze Solver, (9/05/2002)

   The BFS function was mainly written by Ralf Gandy,
   with some modifications by me.
   The remainder of the program was developed by Won You
  
   Description:
   The program will take in a series a points, and use
   breadth-first search to discover a path
   The maze is represented as character matrix, where
   an 'X' is a wall, and every other character is considered
   an open space.
  
   File Format:
   The maze files should be in plain text and have the first
   two characters specify the dimensions of the maze.

   Note: 
   The only valid moves are north, south, east, and west.
   This limitation can easily be adjusted in all of the 
   algorithms, if desired.
 
   Also, the coordinates are zero-based, with (0,0) specifying
   the upper-left corner.
-------------------------------------------------------------*/

#include <iostream>
#include "maze.h"

using namespace std;

int main()
{
  char fname[20];
  char output_name[20];
  char choice;
  char answer;
  char do_answer='y';
  int start_x, start_y,
      dest_x, dest_y;
  Maze maze;

  cout << "\n------------------------------" << endl;
  cout << "  Welcome to the Maze Solver " << endl;
  cout << "\n------------------------------" << endl;

  cout << "Enter the name of the maze file: ";
  cin >> fname;
  maze.readMaze(fname);

  maze.printMaze();   /* Show the contents of the maze */

  do{
    cout << "\n----------------------------------------" << endl;
    cout << "Enter the coordinate for the start node: ";
    cin >> start_x >> start_y;
    cout << "Enter the coordinate for the goal node: ";
    cin >> dest_x >> dest_y;
    cout << "\n-----------------------------------------" << endl;


    //set the coordinates 
    maze.setCoords(start_x, start_y, dest_x, dest_y);

    cout << "\nDo you want a (b)readth-first or (d)epth-first search: ";
    cin >> choice;

    if (choice =='b'){
      maze.BFS(); 
      maze.printpath();
    }
    else{
      int dist = maze.DFS(start_x, start_y);
      if (dist){
	cout << "\nSuccess!" << endl;
        maze.printpath();
        cout << "\nThe distance of the solution: " << dist << endl;
      }
      else cout << "No path exits!" << endl;
    }// end if/else     


    cout << "Do you want to save the results? ";
    cin >> answer;
    if (answer == 'y'){
      cout << "Where do you want to save it? ";
      cin >> output_name;    
      maze.writeMaze(output_name);
    }

    cout << "Do you want to do another search? ";
    cin >> do_answer;
    
    //This is inefficient but who cares
    if (do_answer=='y') maze.readMaze(fname); /*reinitialize the maze*/
    maze.reset();

  } while(do_answer=='y');

  return 0;
}
