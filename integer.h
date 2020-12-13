/*integer.h*/

//
// An Integer class for adding and shifting integers of unlimited
// digits.  Each integer is stored as a linked-list of individual
// digits.
// 
// Completed version of Project 06 written by
// Author: Sai Samarth, U. of Illinois Chicago, Fall 2020
// Date: 05 September 2020
// Initially by: Prof. Hummel, U. of Illinois Chicago, Fall 2020
// Project 06
//

#pragma once

#include <iostream>

#include <string>

#include <exception>

#include <stdexcept>

#include <cstddef>

using namespace std;

class Integer
{
private:

  //
  // Data members:
  //

  struct Node
  {
    int Value;
    Node *Prev;
    Node *Next;
  };

  Node *Head;
  Node *Tail;

  int Length = 0;

  //
  // Private function members:
  //

//
// init
//
// Initializes the list to empty.
//
// pre-condition: L is uninitialized and has not been used.
// post-condition: L is properly initialized to denote empty.
// parameters: List L

  void init ()
  {
    // initialises Head and Tail to nullptr
    Head = nullptr;
    Tail = nullptr;
  }

//
// free
//
// Frees the memory associated with the nodes in the list, 
// and then sets the list to empty.
//
// pre-condition: a properly initialized list.
// post-condition: L is properly set to denote empty.
// parameters: List L

  void free ()
  {
    Node *cur = Head;
    while (cur != nullptr)
      {
	Node *remove = cur;
	cur = cur->Next;
	delete remove;
      }
    Head = nullptr;
    Tail = nullptr;
  }

//
// ith
//
// Returns the value in the node at the given position.
// Positions are 0-based, which means a position of 0 
// denotes the head of the list, and a position of N-1
// denotes the tail of the list (where N=size(L)).  
//
// Example: if L=[10,20,30] then 
//    ith(L,2) => 30
//
// pre-condition: a properly initialized list.
// post-condition: L is unchanged.
// exception: throws invalid_argument if position invalid.
// parameters: List L and int position of Node

  int ith (int position) const
  {

    // traverses through the list
    Node *curr = Head;
    int count = 0;
    while (curr != nullptr)
      {
	// if the position is found it returns the value of the node
	if (count == position)
	  {
	    return curr->Value;
	  }
	count++;
	curr = curr->Next;
      }

    // if the position is invalid an error is thrown
    throw invalid_argument ("ith: invalid position");
  }


//
// pop_front
//
// Removes the node at the head of the list and returns
// the value from this node.
//
// pre-condition: a properly initialized list.
// post-condition: L with head node removed.
// exception: throws runtime_error if list empty.
// parameters: List L

  int pop_front ()
  {

    // throws runtime error if List is empty


    //removes Head and returns its value
    Node *curr = Head;
    Head = curr->Next;
    if (Head == nullptr)
      {
	Tail = nullptr;
      }
    else
      {
	Head->Prev = nullptr;
      }
    int value = curr->Value;
    curr->Next = nullptr;
    delete curr;
    return value;
  }

//
// push_front
//
// Inserts the given value at the head of the list.
//
// pre-condition: a properly initialized list.
// post-condition: L with value inserted at head.
// parameters: List L and int value to be added

  void push_front (int value)
  {
    Node *N = new Node ();
    N->Value = value;
    N->Next = nullptr;
    N->Prev = nullptr;

    // if Head is null then list is empty
    if (Head == nullptr)
      {
	//Head and Tail point at the new node is list is empty
	Head = N;
	Tail = N;
      }
    else
      {
	Head->Prev = N;
	N->Next = Head;
	Head = N;
      }
  }

//
// push_back
//
// Inserts the given value at the tail of the list.
//
// pre-condition: a properly initialized list.
// post-condition: L with value inserted at tail.
// parameters: List L and int value
// parameters: List L and int value to be added

  void push_back (int value)
  {
    Node *N = new Node ();
    N->Value = value;
    N->Next = nullptr;
    N->Prev = nullptr;

    // if Tail is null then the list is empty
    if (Tail == nullptr)
      {
	// Head and Tail point to the new node if list is empty
	Head = N;
	Tail = N;
      }
    else
      {
	// else add the new node to the end of the list
	Tail->Next = N;
	N->Prev = Tail;
	Tail = N;
      }
  }

//
// replace
//
// Replaces the value of Node given the value and position.
//
// pre-condition: initialized position and value
// post-condition: void and Node with a new value
// parameters: int pos and int value

  void replace (int pos, int value)
  {

    int i = 0;
    Node *curr = Head;
    while (curr != nullptr)
      {
	if (i == pos)
	  {
	    curr->Value = value;
	    break;
	  }
	i++;
	curr = curr->Next;
      }

  }

//
// deepCopy
//
// Makes the copy of the given Integer object
//
// pre-condition: a properly initialized Integer object.
// post-condition: A copy of the parameter object
// parameters: const Integer & object

  void deepCopy (const Integer & other)
  {
    Node *curr = other.Tail;

    while (curr != nullptr)
      {
	push_front (curr->Value);
	curr = curr->Prev;
	Length++;
      }
  }

public:
  //
  // default constructor
  //
  // Constructs an integer object and initializes to the value 0.
  // This function is called automatically when an integer is 
  // constructed; do not call this function directly.
  //
  // pre-condition: an invalid integer object.
  // post-condition: a properly initialized integer set to 0.
  // exception: none.
  //
  Integer ()
  {
    Node *n = new Node ();
    n->Value = 0;
    n->Prev = nullptr;
    n->Next = nullptr;
    Head = n;
    Tail = n;
  }
  //
  // constructor:
  //
  // Constructs this integer based on the digits from the given 
  // integer string; throws an exception if s is not an integer
  // strnig.  This function is called automatically when an integer
  // is constructed; do not call this function directly.
  //
  // Example:
  //   if s = "1234" => integer is 1234
  //   if s = "oops" => integer is 0 and throws an exception
  //
  // pre-condition: an invalid integer object.
  // post-condition: a properly initialized integer object that has
  //   the same integer value as implied by the string.
  // exception: throws invalid_argument if the string is empty or 
  //   non-numeric, with integer initialized to 0.
  //
  Integer (string s)
  {
    Head = nullptr;
    Tail = nullptr;
    int i = 0;
    int num = 0;
    Length = s.length ();

    if (s.empty ())
      {

	throw invalid_argument ("Integer: invalid string");
      }

    while (i < Length)
      {
	if (!isdigit (s[i]))	// checks if the digit is a number or if the list is not empty
	  {
	    // makes the integer 0

	    push_front (0);
	    // throw error
	    throw invalid_argument ("Integer(string s): invalid string");
	    break;
	  }
	else
	  {
	    //adds to the list from the front

	    num = s[i] - '0';
	    push_front (num);
	    i++;
	  }
      }

  }

  //
  // copy constructor
  //
  // Constructs this integer via a deep-copy of the other integer.  
  // This function is called automatically when an integer is 
  // constructed; do not call this function directly.
  //
  // pre-condition: an invalid integer object.
  // post-condition: a properly initialized integer object that has
  //   the same integer value as the other integer.
  // exception: none.
  //
  Integer (const Integer & other)
  {
    Head = nullptr;
    Tail = nullptr;

    Node *curr = other.Tail;


    while (curr != nullptr)
      {
	push_front (curr->Value);
	curr = curr->Prev;
      }

  }

  //
  // destructor
  //
  // Frees the resources associated with this integer.  This function
  // is called automatically when an integer is being destroyed; 
  // do not call this function directly.
  //
  // pre-condition: properly initialized integer objects.
  // post-condition: an invalid integer object.
  // exception: none.
  //
  ~Integer ()
  {
    free ();
  }

  //
  // operator=
  //
  // Performs a proper C++ assignment of the other integer into
  // this integer.  This implies the existing integer is freed,
  // and then a deep-copy of the other integer is made.  This
  // function is called automatically as part of an assignment
  // operation involving integer objects; do not call this function
  // directly.
  //
  // pre-condition: properly initialized integer objects.
  // post-condition: this integer is a deep-copy of the other integer.
  // exception: none.
  //
  Integer & operator = (const Integer & other)
  {
    if (this == &other)		// special case: check for i = i;
      return *this;		// do nothing and just return THIS object back

    free ();
    deepCopy (other);
    return *this;		// done, return THIS object back
  }

  //
  // toRawStr
  //
  // Converts this integer to a string, with no leading zeros.
  // The string is returned.
  //
  // Example:
  //   if i = 123456 => returns "123456"
  //   if i = 0 => return "0"
  //
  // pre-condition: a properly initialized integer object.
  // post-condition: integer string is returned with no leading zeros.
  // exception: none.
  //
  string toRawStr ()
  {

    string output = "";

    Node *curr = Tail;
    int num = 0;

    while (curr != nullptr)
      {
	num = curr->Value;

	output += to_string (num);
	curr = curr->Prev;

      }

    output.erase (0, output.find_first_not_of ("0"));
    if (output == "")
      {
	output += "0";
      }

    return output;
  }

  //
  // toStr()
  //
  // Converts this integer to a string with USA-style commas
  // inserted at every thousandth location, with no leading 
  // zeros.  The string is returned.
  //
  // Example:
  //   if i = 123456 => returns "123,456"
  //   if i = 789 => returns "789"
  //   if i = 0 => return "0"
  //
  // pre-condition: a properly initialized integer object.
  // post-condition: USA-style integer string is returned, with
  //   no leading zeros.
  // exception: none.
  //
  string toStr ()
  {
    string output = "";
    Node *curr = Tail;
    int num = 0;
    int count = 0;
    while (curr != nullptr)
      {
	num = curr->Value;

	output += to_string (num);
	curr = curr->Prev;

      }

    output.erase (0, output.find_first_not_of ("0"));
    if (output == "")
      {
	output += "0";
      }
    curr = Tail;
    int size = output.length ();
    if (output != "0")
      {
	for (int i = size; i > 0; i--)
	  {
	    if (count == 3 && size > 3 && curr != nullptr)
	      {
		output.insert (i, ",");
		count = 0;
		curr = curr->Prev;
	      }

	    count++;
	  }
      }
    return output;
  }

  //
  // add
  //
  // Adds the other integer to this integer, in effect computing
  // this += other.  Nothing is returned, the integer is internally
  // updated.
  //
  // pre-condition: properly initialized integer objects.
  // post-condition: this integer increased by other integer.
  // exception: none.
  //
  void add (const Integer & other)
  {
    Node *curr = other.Head;
    //Node* curr2;
    int i = 0;

    int size = 0;
    while (curr != nullptr)
      {
	size++;
	curr = curr->Next;
      }
    curr = other.Head;
    int sum;
    int carry = 0;
    //int num;

    if (Length == 0)
      {
	deepCopy (other);
      }
    else if (size == 0)
      {
	return;
      }
    else if (Length == size)
      {				// adding when the lists are equal                               
	while (i < size)
	  {
	    sum = (other.ith (i)) + (ith (i)) + carry;	// adds the values of lists 

	    if (sum >= 10)
	      {
		//carryover
		carry = 1;
		sum = sum % 10;
	      }
	    else
	      {
		carry = 0;
	      }
	    replace (i, sum);
	    i++;
	  }
	if (carry == 1)
	  {
	    push_back (carry);
	    Length++;
	  }

      }
    else if (size > Length)
      {
	int i = 0;
	while (i < Length)
	  {

	    sum = (other.ith (i)) + (ith (i)) + carry;

	    if (sum >= 10)
	      {
		// carryover
		carry = 1;
		sum = sum % 10;
	      }
	    else
	      {
		carry = 0;
	      }

	    replace (i, sum);
	    i++;

	  }
	// cout <<i << endl;
	sum = 0;
	while (i < size)
	  {
	    //cout << i << endl;
	    sum = other.ith (i) + carry;
	    if (sum >= 10)
	      {
		sum = sum % 10;
		push_back (sum);
		Length++;
		carry = 1;
	      }
	    else
	      {
		//cout << ith(j) << endl;
		push_back (sum);
		Length++;
		carry = 0;
	      }

	    i++;
	  }

	if (carry == 1)
	  {
	    push_back (carry);
	    Length++;
	  }

      }
    else if (Length > size)

      {				// adding lists when other is shorter
	int j = 0;

	while (j < size)
	  {
	    sum = (other.ith (j)) + (ith (j)) + carry;	// calculates the sum of nodes and carry
	    if (sum >= 10)
	      {
		// carryover
		carry = 1;
		sum = sum % 10;
	      }
	    else
	      {
		carry = 0;
	      }

	    replace (j, sum);
	    j++;

	  }

	sum = 0;
	//cout << Length << endl;
	while (j < Length)
	  {
	    //cout << Length << endl;
	    //cout << j;
	    sum = ith (j) + carry;
	    if (sum >= 10)
	      {
		sum = sum % 10;
		replace (j, sum);
		carry = 1;
	      }
	    else
	      {
		//cout << ith(j) << endl;
		replace (j, sum);
		carry = 0;
	      }
	    if (j == Length)
	      {
		break;
	      }

	    j++;
	  }
	if (carry == 1)
	  {
	    push_back (carry);
	    Length++;
	  }
      }

  }

  //
  // shift_left
  //
  // Shifts the integer digits left by the given amount N,
  // in effect multiplying the integer by 10^N.  If the integer
  // is 0, then the result remains 0.  Nothing is returned, 
  // the integer is internally updated.
  //
  // Example: 
  //   if i = 1234 then shift_left(i, 2) => 123400
  //   if i = 0 then shift_left(i, x) => 0
  //
  // pre-condition: a properly initialized integer object.
  // post-condition: if non-zero to start, the integer has 
  //   N lower-order 0's added.
  // exception: throws invalid_argument if N < 0.
  //
  void shift_left (int N)
  {

    if (N < 0)
      {
	throw invalid_argument ("shift_left: invalid shift amount N");
      }
    else
      {
	int count = 0;
	while (count < N)
	  {
	    push_front (0);
	    count++;
	    Length++;
	  }
      }
  }

  //
  // shift_right
  //
  // Shifts the integer digits right by the given amount N,
  // in effect dividing the integer by 10^N.  If the integer
  // contains <= N digits, then the integer is shifted right
  // until 1 digit remains.  Nothing is returned, the integer
  // is internally updated.
  //
  // Example: 
  //   if i = 1234 then shift_right(i, 2) => 12
  //   if i = 1234 then shift_right(i, 4) => 1
  //   if i = 0 then shift_right(i, x) => 0
  //
  // pre-condition: a properly initialized integer object.
  // post-condition: if non-zero to start, the integer has 
  //   N lower-order digits removed.
  // exception: throws invalid_argument if N < 0.
  //
  void shift_right (int N)
  {
    if (N < 0)			// throw invalid argument when N is less than 0
      {
	throw invalid_argument ("shift_right: invalid shift amount N");
      }
    int count = 0;
    //cout << Length << endl;
    while (count < N)
      {
	if (Length == 1)
	  {
	    //cout << "end" <<endl;
	    break;
	  }

	pop_front ();
	count++;
	Length--;

      }
  }

};