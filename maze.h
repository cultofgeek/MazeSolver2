////////////////   maze.h    //////////////////////

#ifndef _MAZE_H
#define _MAZE_H

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <string>
#include <fstream>

using namespace std;

typedef pair<int, int> node;  //the set contains the coordinates

class Maze{

public: 
       // constructor
       Maze(int s_x=0, int s_y=0, int d_x=0, int d_y=0) :
            start_x( s_x ), start_y( s_y ), dest_x( d_x ), dest_y( d_y ) 
      {  
        startnode = node(start_x, start_y);
        endnode = node(dest_x, dest_y);
        distance = 0;
        testFlag = false;    //this is a static variable used by DFS
      };

      vector< vector<char> > maze;            /*this stl matrix will store our maze*/
      bool testFlag;                 /* Test to see if we've reached the solution */

      void printMaze();                                 /* Displays the maze */
      void printpath();                                 /* Prints the solution */
      void readMaze(char* filename);                    /* Reads a maze from a file */
      void writeMaze(char* filename);                   /* Writes the maze to a file */ 
      bool visit(node u, int udist, node upredecessor); /* visits a node for BFS   */
      bool validMove(const int& x, const int& y);    /* Makes sure the coordinate is valid */
      void printBFS(node u);                            /* Marks the solution path */
      void setWidth(int x) { mazex = x; } 
      void setHeight(int y) { mazey = y; } 
      void setCoords(int sx, int sy, int dx, int dy)   /*Set the coordinates*/
      {
            start_x = sx;
            start_y = sy;
	    dest_x  = dx;
            dest_y  = dy;
            startnode.first = start_x; 
            startnode.second = start_y;
            endnode.first = dest_x;
            endnode.second = dest_y;
      }

      void reset()                                   /* Resets the variables used by DFS */
      { 
         testFlag = false; 
         distance = 0;
      }

      void BFS();                                     /* Implements bread-first search */
      int DFS(int x, int y);                         /* Depth-first search algorithm */
        

private: 

	map<node, node> predecessor;
	map<node, int> dist;
	queue<node> myqueue;
	int start_x, start_y,  /* the coordinates for the beginning and end */
	    dest_x, dest_y;
        int mazex, mazey;      /* the width and height of our maze */
        node startnode, endnode;                /* start and goal coordinates */
        int distance;


};


#endif
