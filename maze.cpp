////////////////   maze.cpp    //////////////////////

#include "maze.h"


//---------------------------------------
//Display the given maze to the screen
//---------------------------------------
void Maze::printMaze(){

  int i, j;

  cout << "\nHere's the maze: " << endl;
  cout << "    ";

  //shows lines to make the output more presentable
  for (j=0; j<=mazex+1; j++)
      cout << "-";  
  cout << endl;

  //Print the maze  
  for (i=0; i<mazey; i++){
    cout << "    |";
    for (j=0; j<mazex; j++){
	cout << maze[i][j];        
    }
    cout << "|" << endl;   
  }

  //shows lines to make the output more presentable
  cout << "    ";
  for (j=0; j<=mazex+1; j++)
      cout << "-";  
  
  cout << "\nDimensions: " << mazey << "x" << mazex << endl;	
}


//---------------------------------------
// Print the path that is found, marks
// the path with "o"s. Takes an
// argument which specifies the solution
// to print
//---------------------------------------
void Maze::printpath(){
  int i,j;
  cout << "\nHere's the solution: " << endl;
  cout << "    ";

  //shows lines to make the output more presentable
  for (i=0; i<=mazex+1; i++)
      cout << "-";  
  cout << endl;
  
  for (i=0; i<mazey; i++){   
      cout << "    |";
      for (int j=0; j<mazex; j++){
	if (i == start_x && j == start_y)
	  cout << 's';
	else if (i == dest_x && j == dest_y)
	  cout << 'd';
	else{
	  if (maze[i][j]== '+') cout << ' '; 
	  else cout << maze[i][j];
        }
      }
      cout << "|" << endl;
  }

  //shows lines to make the output more presentable
  cout << "    ";
  for (i=0; i<=mazex+1; i++)
      cout << "-";  
  cout << endl;
}


//Open the given file and place the maze into memory
void Maze::readMaze(char* filename){

   int i = 0, j;    // Row and column indices.
   int flag = 0;    // Return value is 0 if file is ok.
   char c;
   ifstream inputfile;
   inputfile.open(filename);

   if (!inputfile) {
      cout << "File: " << filename << " not found.\n";
      exit(1);
   }

   inputfile >> mazex >> mazey;         // get the column and row dimensions
   maze = vector<vector<char> >(mazey); // reserve the size for the maze

  for (int i = 0; i < mazey; i++){
    maze[i] = vector<char>(mazex);

    for (int j = 0; j < mazex; j++){
      inputfile.get(c); //use the get method to read in the blank characters

      if (c != '\n'){
         maze[i][j]=c;
      }
      else j--;

    }
  }

   inputfile.close();
}

//save the maze to disk
void Maze::writeMaze(char* filename ){
  ofstream outfile;
  outfile.open(filename, ios::app); //append, don't overwrite

  for (int i=0; i<mazey; i++){
    for (int j=0; j<mazex; j++)
      outfile << maze[i][j];
    outfile << endl;
  }

  outfile.close();
}

// This is a recursive function displays
// the solution path for BFS 
void Maze::printBFS(node u){

  if (u != startnode)
    printBFS(predecessor[u]);
  if (u != endnode && u != startnode)
    maze[u.first][u.second] = 'o';
}


//This function is used by the breadth-first search algorithm
bool Maze::visit (node u, int udist, node upredecessor)
{
  if (u.first < 0 || u.second < 0 || 
      u.first >= mazey || u.second >= mazex || 
      maze[u.first][u.second] == 'X' || 
      dist.find(u) != dist.end()) return false;

  dist[u] = udist;               // update the cost list
  predecessor[u] = upredecessor; // map the node's parent to itself
  myqueue.push(u);               // add a new node onto the queue
  return u == endnode;
}

//////////////////////////////////////////////////////////////
//
//  Breadth-first search engine, 
//  written mainly by Ralf Gandy, for further details read
//  an algorithms book. The important data structure here
//  is the queue (FIFO).  It is also important that the
//  starting point be specified in an open area
//
//////////////////////////////////////////////////////////////
void Maze::BFS(){

  while (true){
      dist = map<node, int>();
      predecessor = map<node, node>();
      myqueue = queue<node>();

      visit(startnode, 1, startnode);
	while (!myqueue.empty())
	  {
	    node u = myqueue.front();
	    myqueue.pop();
	    // Visit the frontier or the neighbors
	    if (visit(node(u.first, u.second + 1), dist[u] + 1, u)){
	      break;
	    }
	    if (visit(node(u.first, u.second - 1), dist[u] + 1, u)){
	      break;
	    }
	    if (visit(node(u.first + 1, u.second), dist[u] + 1, u)){
	      break;
	    }
	    if (visit(node(u.first - 1, u.second), dist[u] + 1, u)){
	      break;
	    }
	  }

      // we've reached our destination
      if (dist.find(endnode) != dist.end())
	{
	  //Subtract by 2 to exclude the endpoints
	  cout << "\nFound a path of length " 
               << dist[endnode]-1 << ":" << endl;	
          printBFS(endnode);  
	
          break;
	}
      else{
	cout << "No solution." << endl;
        break;
      }
      cout << endl;
   
    } //end of while

}

// Determine if the given coordinates x,y are a valid position
// This function is used exclusively by DFS
bool Maze::validMove(const int& x, const int& y){

 if ((maze[x][y]!='+') && (maze[x][y]!='*')
     && ((maze[x][y]==' ') || (x==dest_x && y==dest_y)))
    return true;
 else
    return false;
}    

//////////////////////////////////////////////////////////////
//
// This function is the maze solving engine
// A depth-first search is performed to traverse the maze.
// Normally, a stack is used to implement this algorithm, but
// here I use the memory to act as my stack, rather than
// creating one outright. Note: this is an un-optimal algorithm
//
// This is a recursive function that takes as input the
// current position, and returns the distance of solution path 
// if one exists.
//////////////////////////////////////////////////////////////

int Maze::DFS(int x, int y)
{

  //The following commented out lines were for debugging
  //cout << "Our current coordinates are: " << x << "," <<y<<endl;  
  //cout << "This is the current character: " << maze[x][y]<<endl;
  //cout << count << endl;

  if ((x<=mazey && x>=0) && (y<=mazex && y>=0)){

    //Basic Case: We've reached the solution
    if (x==dest_x && y==dest_y){
      testFlag = true;
    }

    if(!testFlag){

      maze[x][y]='+';  /* mark this node as being visited */

      //Move South
      if ( ((x+1)<=mazey) && (validMove((x+1), y) ) ) 
	DFS( x+1, y );

      //Move East
      if ( ((y+1)<=mazex) && (validMove(x, (y+1)) ) )
	 DFS( x, y+1 );      

      //Move North
      if ( ((x-1)>=0) && (validMove((x-1), y) ) )
	DFS( x-1, y );

      //Move West
      if ( ((y-1)>=0) && (validMove(x, y-1) ) )
	DFS( x, y-1 );

      if (testFlag){
	maze[x][y]='*';     /* mark the solution path */
        distance++;             /* increment the cost of the path */
      }
      else if (testFlag && maze[x][y]=='+'){ 
          maze[x][y]=' ';    /* remove our bread crumb when we're done */
      }     
      
    }
  }

  return distance;
}   
