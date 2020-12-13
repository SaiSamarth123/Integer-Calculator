//
// main.cpp
//  
// An user interface that serves as an Integer calculator. 
// Each Integer object is dynamically stored into an array. 
// Commands entered by the user are used to call functions 
// from the Integer class
//
// Project 06
// Completed version of Project 06 written by
//   Author: Sai Samarth, U. of Illinois Chicago, Fall 2020
//   Date: 05 December 2020
//

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include "integer.h"

using namespace std;

//
// commandFile
// 
// Function to read the user entered file and carry out the commands
// Called when the user enters the command l
// 
// pre-condition: properly initialized Integer array, filename and size.
// post-condition: return 0 after the commands are done. 
//
int
commandFile (Integer * intArray1, string & filename, int size)
{
  string value;
  int pos, pos1;

  ifstream infile (filename);
  // to check if the file exists
  if (!infile.good ())
    {
      cout << "File does not exist, try again..." << endl;
      return 0;
    }
  cout << "Load: loading '" << filename << "'" << endl;

  // get commands from the file
  string cmd;
  infile >> cmd;
  // while loop runs until the command is x
  while (cmd != "x")
    {

      // checks if the command starts with i
      if (cmd.at (0) == 'i')
	{
	  cmd = cmd.substr (1);	// gets the number(pos) after i
	  pos = stoi (cmd);
	  infile >> cmd;

	  // checks if the pos is 0 or greater than the size
	  if (pos > size || pos == 0)
	    {
	      cout << "Invalid variable, try again..." << endl;
	    }
	  else
	    {
	      if (cmd == "=")
		{		// checks if the cmd is =            
		  infile >> value;
		  if (isdigit (value.at (0)))
		    {
		      // try catch block to catch the error from constructor
		      try
		      {
			intArray1[pos - 1] = Integer (value);
		      }
		      catch (exception & e)
		      {
			cout << "Invalid value" << endl;
		      }

		    }
		  else if (value.at (0) == 'i')
		    {		// to assign one object to another
		      pos1 = stoi (value.substr (1));
		      intArray1[pos - 1] = intArray1[pos1 - 1];
		    }
		}
	      else if (cmd == "+=")
		{		// checks for the add command

		  infile >> value;
		  if (isdigit (value.at (0)))
		    {		// checks if it's a number
		      // try and catch block for the error thrown by constructor
		      try
		      {
			Integer number (value);
			intArray1[pos - 1].add (number);	// add the number
		      }
		      catch (exception & e)
		      {
			cout << "Invalid value" << endl;
		      }

		    }
		  else if (value.at (0) == 'i')
		    {		// else if it's an Integer object
		      pos1 = stoi (value.substr (1));
		      Integer i = intArray1[pos1 - 1];
		      intArray1[pos - 1].add (i);	// add Integer at pos1 to Integer at pos
		    }
		}
	      else if (cmd == "?")
		{		// checks if the command is to print
		  // prints the object at pos - 1
		  cout << intArray1[pos - 1].toStr () << endl;
		}
	      else if (cmd == "<<")
		{		// checks if the command is to shift left
		  infile >> value;
		  // try and catch block for the error in shift_left
		  try
		  {
		    intArray1[pos - 1].shift_left (stoi (value));
		  }
		  catch (exception & e)
		  {
		    cout << e.what () << endl;
		  }
		}
	      else if (cmd == ">>")
		{		// checks if the command is to shift right
		  infile >> value;
		  // try and catch block for the error in shift_right
		  try
		  {
		    intArray1[pos - 1].shift_right (stoi (value));
		  }
		  catch (exception & e)
		  {
		    cout << e.what () << endl;
		  }

		}
	      else
		{		// prints invalid command if it's not one of the commands
		  cout << "Invalid command, try again..." << endl;
		}
	    }

	}
      else if (cmd == "l")
	{			// checks if the command is to load a file
	  string name;
	  infile >> name;
	  // calls the commandFile function which reads commands from a file
	  commandFile (intArray1, name, size);
	}
      else
	{			// prints invalid command if it's not one of the commands
	  cout << "Invalid command, try again..." << endl;
	}
      infile >> cmd;
    }
  cout << "Load: done '" << filename << "'" << endl;
  return 0;
}

//
// <cmds>  ::= <cmd> <more>
// <more>  ::= <cmd> <more> 
//            | EMPTY
//
// <cmd>   ::= x
//         ::= l commandfile
//         ::= <expr>
// <expr>  ::= <var> ?
//           | <var>  = <term>
//           | <var> += <term>
//           | <var> << <int>
//           | <var> >> <int>
// <term>  ::= <var>
//           | <int>
//
// <var>   ::= i1 | i2 | i3 | i4 | i5 | ...
// <int>   ::= 0 | 1 | 2 | 3 | 4 | 5 | ...

//
// main: 
//
int
main ()
{
  string memSize, value;
  int pos, pos1;

  // asks the user for the size of the array
  cout << "Memory size? ";
  cin >> memSize;

  // create the array of Integer objects with memSize as the size
  Integer *intArray = new Integer[stoi (memSize)];

  // asks user to enter command
  string cmd;
  cout << "> ";
  cin >> cmd;
  // while loop runs until the command is x
  while (cmd != "x")
    {

      // checks if the command starts with i
      if (cmd.at (0) == 'i')
	{
	  cmd = cmd.substr (1);	// gets the number(pos) after i
	  pos = stoi (cmd);
	  cin >> cmd;
	  if (pos > stoi (memSize) || pos == 0)
	    {			// checks if the pos is 0 or greater than the size
	      cout << "Invalid variable, try again..." << endl;
	    }
	  else
	    {
	      if (cmd == "=")
		{		// checks if the cmd is =               
		  cin >> value;
		  if (isdigit (value.at (0)))
		    {
		      // try catch block to catch the error from constructor
		      try
		      {
			intArray[pos - 1] = Integer (value);
		      }
		      catch (exception & e)
		      {
			cout << "Invalid value" << endl;
		      }
		    }
		  else if (value.at (0) == 'i')
		    {		// to assign one object to another
		      pos1 = stoi (value.substr (1));
		      intArray[pos] = intArray[pos1 - 1];
		    }
		}
	      else if (cmd == "+=")
		{		// checks for the add command

		  cin >> value;

		  if (isdigit (value.at (0)))
		    {		// checks if it's a number
		      // try catch block to catch the error from constructor
		      try
		      {
			Integer number (value);
			intArray[pos - 1].add (number);	// add the number
		      }
		      catch (exception & e)
		      {
			cout << "Invalid value" << endl;
		      }

		    }
		  else if (value.at (0) == 'i')
		    {		// else if it's an Integer object
		      pos1 = stoi (value.substr (1));
		      Integer i = intArray[pos1 - 1];
		      intArray[pos - 1].add (i);	// add Integer at pos1 to Integer at pos
		    }
		}
	      else if (cmd == "?")
		{		// checks if the command is to print
		  // prints the object at pos - 1
		  cout << intArray[pos - 1].toStr () << endl;
		}
	      else if (cmd == "<<")
		{		// checks if the command is to shift left
		  cin >> value;
		  // try and catch block for the error in shift_left
		  try
		  {
		    intArray[pos - 1].shift_left (stoi (value));
		  }
		  catch (exception & e)
		  {
		    cout << e.what () << endl;
		  }
		}
	      else if (cmd == ">>")
		{		// checks if the command is to shift right
		  cin >> value;
		  // try and catch block for the error in shift_right
		  try
		  {
		    intArray[pos - 1].shift_right (stoi (value));
		  }
		  catch (exception & e)
		  {
		    cout << e.what () << endl;
		  }


		}
	      else
		{		// prints invalid command if it's not one of the commands
		  cout << "Invalid command, try again..." << endl;
		}
	    }

	}
      else if (cmd == "l")
	{			// checks if the command is to load a file
	  string name;
	  cin >> name;
	  // calls the commandFile function which reads commands from a file
	  commandFile (intArray, name, stoi (memSize));
	}
      else
	{			// prints invalid command if it's not one of the commands
	  cout << "Invalid command, try again..." << endl;
	}
      cout << "> ";
      cin >> cmd;

    }
  // delete the array
  delete[]intArray;
  return 0;
}