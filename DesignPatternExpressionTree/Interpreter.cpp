//Name: Xianshi Xie
//Email: xianshi.xie@vanderbilt.edu
#ifndef _INTERPRETER_CPP_
#define _INTERPRETER_CPP_

#include <iostream>
#include <list>
#include <map>

#include "Interpreter.h"
#include "Typedefs.h"
#include "Node.h"

// You fill in the appropriate header files corresponding to the
// Node-related header files you created for the Composite pattern. 

/**
* @class Symbol
* @brief Abstract base class of all parse tree nodes.
*/
class Symbol
{
public:
  /// constructor
  Symbol (Symbol *left, Symbol *right, int precedence_ = 0);

  /// destructor
  virtual ~Symbol (void);

  /// abstract method for returning precedence level (higher
  /// value means higher precedence
  virtual int precedence (void)
  {
    return precedence_;
  }

  virtual int add_precedence (int accumulated_precedence) = 0;

  /// abstract method for building a TREE Node

  virtual NODE *build (void) = 0;

  /// left and right pointers

  Symbol *left_;
  Symbol *right_;
  int precedence_;
};

/**
* @class Operator
* @brief Abstract base class for all parse tree node operators
* @see   Add, Subtract, Multiply, Divide
*/
class Operator : public Symbol
{
public:
  /// constructor
  Operator (Symbol *left, Symbol *right, int precedence_ = 1);

  /// destructor
  ~Operator (void);
};

/**
* @class Unary_Operator
* @brief Abstract base class for all parse tree node operators
* @see   Add, Subtract, Multiply, Divide
*/
class Unary_Operator : public Symbol
{
public:
  /// constructor
  Unary_Operator (Symbol *right, int precedence_ = 1);

  /// destructor
  ~Unary_Operator (void);
};

/**
* @class Number
* @brief Leaf node of parse tree
*/

class Number : public Symbol
{
public:
  /// constructors
  Number (std::string input);
  Number (int input);

  /// destructor
  virtual ~Number (void);

  /// returns the precedence level
  //virtual int precedence (void);
  virtual int add_precedence (int accumulated_precedence);

  /// builds an equivalent TREE node
  virtual NODE *build (void);
private:
  /// contains the value of the leaf node
  int item_;
};

/**
* @class Subtract
* @brief Subtraction node of the parse tree
*/

class Subtract : public Operator
{
public:
  /// constructor
  Subtract (void);

  /// destructor
  virtual ~Subtract (void);

  /// returns the precedence level
  //virtual int precedence (void);
  virtual int add_precedence (int accumulated_precedence);

  /// builds an equivalent TREE node
  virtual NODE *build (void);
};

/**
* @class Add
* @brief Addition node of the parse tree
*/

class Add : public Operator
{
public:
  /// constructor
  Add (void);

  /// destructor
  virtual ~Add (void);

  /// returns the precedence level
  //virtual int precedence (void);
  virtual int add_precedence (int accumulated_precedence);

  /// builds an equivalent TREE node
  virtual NODE *build (void);
};

/**
* @class Negate
* @brief Negate node of the parse tree
*/

class Negate : public Unary_Operator
{
public:
  /// constructor
  Negate (void);

  /// destructor
  virtual ~Negate (void);

  /// returns the precedence level
  //virtual int precedence (void);
  virtual int add_precedence (int accumulated_precedence);

  /// builds an equivalent TREE node
  virtual NODE *build (void);
};

/**
* @class Multiply
* @brief Multiplication node of the parse tree
*/

class Multiply : public Operator
{
public:
  /// constructor
  Multiply (void);

  /// destructor
  virtual ~Multiply (void);

  /// returns the precedence level
  //virtual int precedence (void);
  virtual int add_precedence (int accumulated_precedence);

  /// builds an equivalent TREE node
  virtual NODE *build (void);
};

/**
* @class Divide
* @brief Division node of the parse tree
*/

class Divide : public Operator
{
public:
  /// constructor
  Divide (void);

  /// destructor
  virtual ~Divide (void);

  /// returns the precedence level
  //virtual int precedence (void);
  virtual int add_precedence (int accumulated_precedence);

  /// builds an equivalent TREE node
  virtual NODE *build (void);
};

// constructor
Interpreter_Context::Interpreter_Context (void)
{
}

// destructor
Interpreter_Context::~Interpreter_Context (void)
{
}

// return the value of a variable
int
Interpreter_Context::get (std::string variable)
{
  return map_[variable];
}

// set the value of a variable
void
Interpreter_Context::set (std::string variable, int value)
{
  map_[variable] = value;
}

// print all variables and their values
void
Interpreter_Context::print (void)
{
  for (std::map<std::string, int>::iterator i = map_.begin ();
    i != map_.end (); 
    ++i)
    std::cout << i->first << "=" << i->second << "\n";
}

// clear all variables and their values
void
Interpreter_Context::reset (void)
{
  map_.clear ();
}

// constructor
Symbol::Symbol (Symbol *left, Symbol *right, int precedence)
: left_ (left), right_ (right), precedence_ (precedence)
{
}

// destructor
Symbol::~Symbol (void)
{
  delete left_;
  delete right_;
}

// constructor
Operator::Operator (Symbol *left, Symbol *right, int precedence)
: Symbol (left, right, precedence)
{
}

// destructor
Operator::~Operator (void)
{
}

// constructor
Unary_Operator::Unary_Operator (Symbol *right, int precedence)
: Symbol (0, right, precedence)
{
}

// destructor
Unary_Operator::~Unary_Operator (void)
{
}

// constructor
Number::Number (std::string input)
: Symbol (0, 0, 4)
{
  item_ = atoi (input.c_str ());
}

// constructor
Number::Number (int input)
: Symbol (0, 0, 4), 
item_ (input)
{
}

// destructor
Number::~Number (void)
{
}

// returns the precedence level
int 
Number::add_precedence (int precedence)
{
  return this->precedence_ = 4 + precedence;
}

// builds an equivalent TREE node
NODE *
Number::build (void)
{
  return new LEAF_NODE(item_);// You fill in here.
}

// constructor
Negate::Negate (void)
: Unary_Operator (0, 3)
{
}

// destructor
Negate::~Negate (void)
{
}

// returns the precedence level
int 
Negate::add_precedence (int precedence)
{
  return this->precedence_ = 3 + precedence;
}

// builds an equivalent TREE node
NODE *
Negate::build ()
{
  // You fill in here.
  NODE * right = right_->build();
  return new COMPOSITE_NEGATE_NODE(right);
}

// constructor
Add::Add (void)
: Operator (0, 0, 1)
{
}

// destructor
Add::~Add (void)
{
}

// returns the precedence level
int 
Add::add_precedence (int precedence)
{
  return this->precedence_ = 1 + precedence;
}

// builds an equivalent TREE node
NODE *
Add::build (void)
{
  // You fill in here.
  NODE * left = left_->build();
  NODE * right = right_->build();
  return new COMPOSITE_ADD_NODE(left,right); 
}

// constructor
Subtract::Subtract (void)
: Operator (0, 0, 1)
{
}

// destructor
Subtract::~Subtract (void)
{
}

// returns the precedence level
int 
Subtract::add_precedence (int precedence)
{
  return this->precedence_ = 1 + precedence;
}

// builds an equivalent TREE node
NODE *
Subtract::build (void)
{
  NODE * left = left_->build();
  NODE * right = right_->build();
  return new COMPOSITE_SUBTRACT_NODE(left,right); // You fill in here.
}

// constructor
Multiply::Multiply (void)
: Operator (0, 0, 2)
{
}

// destructor
Multiply::~Multiply (void)
{
}

// returns the precedence level
int 
Multiply::add_precedence (int precedence)
{
  return this->precedence_ = 2 + precedence;
}

// builds an equivalent TREE node
NODE *
Multiply::build (void)
{
  NODE * left = left_->build();
  NODE * right = right_->build();
  return new COMPOSITE_MULTIPLY_NODE(left,right); // You fill in here.
}

// constructor
Divide::Divide (void)
: Operator (0, 0, 2)
{
}

// destructor
Divide::~Divide (void)
{
}

// returns the precedence level
int 
Divide::add_precedence (int precedence)
{
  return this->precedence_ = 2 + precedence;
}

// builds an equivalent TREE node
NODE *
Divide::build (void)
{
  NODE * left = left_->build();
  NODE * right = right_->build();
  return new COMPOSITE_DIVIDE_NODE(left,right); // You fill in here.
}

// constructor
Interpreter::Interpreter (void)
{
}

// destructor
Interpreter::~Interpreter (void)
{
}

// method for checking if a character is a valid operator
bool
Interpreter::is_operator (char input)
{
  return input == '+' 
    || input == '-' 
    || input == '*' 
    || input == '/';
}

// method for checking if a character is a number
bool
Interpreter::is_number (char input)
{
  return input >= '0' && input <= '9';
}

// method for checking if a character is a candidate
// for a part of a variable name
bool
Interpreter::is_alphanumeric (char input)
{
  return (input >= 'a' && input <= 'z') 
    || (input >= 'A' && input <= 'Z') 
    || (input == '_') 
    || (input >= '0' && input <= '9');
}

// inserts a terminal into the parse tree
void
Interpreter::terminal_insert (Symbol *terminal,
                              std::list<Symbol *>& list)
{
  if (!list.empty ())
  {
    // Something exists in the list, so make this number the rightmost child

    Symbol *symbol = list.back ();

    if (symbol)
    {
      // while there is a right child, continue down
      for (; symbol->right_; symbol = symbol->right_)
        continue;

      // symbol right will be this terminal and that's all we have
      // to do.
      symbol->right_ = terminal;
    }
  }
  else
    // a number appeared first
    list.push_back (terminal);
}

// inserts a variable (leaf node / number) into the parse tree
void
Interpreter::variable_insert (Interpreter_Context &context,
                              const std::string &input,
                              std::string::size_type &i,
                              int & accumulated_precedence,
                              std::list<Symbol *>& list,
                              Symbol *& lastValidInput)
{
  // merge all consecutive number chars into a single
  // Number symbol, eg '123' = int (123). Scope of j needs
  // to be outside of the for loop.

  std::string::size_type j = 1;

  for (; i + j <= input.length () && is_alphanumeric (input[i + j]); ++j)
    continue;

  // lookup the variable in the context

  int value = context.get (input.substr (i,j));

  // make a Number out of the integer

  Number *number = new Number (value);
  number->add_precedence (accumulated_precedence);

  lastValidInput = number;

  // update i to the last character that was a number. the ++i will
  // update the i at the end of the loop to the next check.

  i += j - 1;

  precedence_insert (number, list);
}

// inserts a leaf node / number into the parse tree
void
Interpreter::number_insert (const std::string &input,
                            std::string::size_type &i,
                            int & accumulated_precedence,
                            std::list<Symbol *>& list,
                            Symbol *& lastValidInput)
{
  // merge all consecutive number chars into a single Number symbol,
  // eg '123' = int (123). Scope of j needs to be outside of the for
  // loop.

  std::string::size_type j = 1;

  for (; i + j <= input.length () && is_number (input[i + j]); ++j)
    continue;

  Number *number = new Number (input.substr (i,j));
  number->add_precedence (accumulated_precedence);

  lastValidInput = number;

  // update i to the last character that was a number. the ++i will
  // update the i at the end of the loop to the next check.

  i += j - 1;

  precedence_insert (number, list);
}

// inserts an addition or subtraction into the parse tree
void 
Interpreter::associative_insert (Symbol *op,
                                 std::list<Symbol *>& list)
{
  if (!list.empty ())
  {
    // if last element was a number, then make that our left_

    op->left_ = list.back ();

    // now push the add on the list

    list.pop_back ();
    list.push_back (op);
  }
  else
  {
    // we have an associative operation. Assume something like an
    // input of "+5-3" or "-3+5". Add a left number of 0 to make
    // everything kosher.

    op->left_ = new Number (0);
    list.push_back (op);
  }
}

// inserts a multiplication or division into the parse tree
void 
Interpreter::precedence_insert (Symbol *op,
                                std::list<Symbol *>& list)
{
  if (!list.empty ())
  {
    // if last element was a number, then make that our left_

    Symbol *parent = list.back ();
    Symbol *child = parent->right_;

    if (parent->precedence () < op->precedence ())
    {
      if (child)
      {
        // while there is a child of parent, keep going down the right side
        for (; 
          child && child->precedence () < op->precedence ();
          child = child->right_)
          parent = child;
      }

      // op left will be the old child. new parent child will be the op.
      //  To allow infinite negations, we have to check for unary_operator.

      if (dynamic_cast <Unary_Operator *> (op))
        op->right_ = child;
      else if (!op->left_)
        op->left_ = child;

      parent->right_ = op;
    }
    else
    {
      // if child is null, then simply set op->left to parent. if
      // the syntax was correct, this only happens if this
      // operation is the first one of the input string. Parent
      // should be a number.

      op->left_ = parent;
      list.pop_back ();
      list.push_back (op);
    }
  }
  else
  {
    list.push_back (op);
  }
}

void
Interpreter::mainLoop (Interpreter_Context & context,
                       const std::string &input,
                       std::string::size_type &i,
                       Symbol *& lastValidInput,
                       bool & handled,
                       int & accumulated_precedence,
                       std::list<Symbol *>& list)
{
  handled = false;
  if (is_number (input[i]))
  {
    handled = true;
    // leaf node
    number_insert (input, i, accumulated_precedence, 
      list, lastValidInput);
  }
  else if (is_alphanumeric (input[i]))
  {
    handled = true;
    // variable leaf node
    variable_insert (context, input, i, accumulated_precedence,
      list, lastValidInput);
  }
  else if (input[i] == '+')
  {
    handled = true;
    // addition operation
    Add *op = new Add ();
    op->add_precedence (accumulated_precedence);

    lastValidInput = 0;

    // insert the op according to left-to-right relationships
    precedence_insert (op, list);
  }
  else if (input[i] == '-')
  {
    handled = true;

    Symbol * op = 0;
    // subtraction operation
    Number *number = 0;

    if (!lastValidInput)
    {
      // Negate
      op = new Negate ();
      op->add_precedence (accumulated_precedence);
    }
    else
    {
      // Subtract
      op = new Subtract ();
      op->add_precedence (accumulated_precedence);
    }

    lastValidInput = 0;

    // insert the op according to left-to-right relationships
    precedence_insert (op, list);

  }
  else if (input[i] == '*')
  {
    handled = true;
    // multiplication operation
    Multiply *op = new Multiply ();
    op->add_precedence (accumulated_precedence);

    lastValidInput = 0;

    // insert the op according to precedence relationships
    precedence_insert (op, list);
    //associative_insert (op);
  }
  else if (input[i] == '/')
  {
    handled = true;
    // division operation
    Divide *op = new Divide ();
    op->add_precedence (accumulated_precedence);

    lastValidInput = 0;

    // insert the op according to precedence relationships
    precedence_insert (op, list);
  }
  else if (input[i] == '(')
  {
    handled = true;
    handleParenthesis (context, input, i, lastValidInput, 
      handled, accumulated_precedence, list);
  }
  else if (input[i] == ' ' || input[i] == '\n')
  {
    handled = true;
    // skip whitespace
  }
}

void 
Interpreter::handleParenthesis (Interpreter_Context & context,
                                const std::string &input,
                                std::string::size_type &i,
                                Symbol *& lastValidInput,
                                bool & handled,
                                int & accumulated_precedence,
                                std::list<Symbol *>& master_list)
{
  /* handle parenthesis is a lot like handling a new interpret.
  the difference is that we have to worry about how the calling
  function has its list setup */

  //std::cerr << "Handling an opening parenthesis.\n";

  accumulated_precedence += 5;

  std::list<Symbol *> list;

  handled = false;
  for (++i; i < input.length (); ++i)
  {
    mainLoop (context, input, i, lastValidInput, 
      handled, accumulated_precedence, list);

    if (input[i] == ')')
    {
      //std::cerr << "Handling a closing parenthesis.\n";

      handled = true;
      ++i;
      accumulated_precedence -= 5;
      break;
    }
  }

  if (master_list.size () > 0 && list.size () > 0)
  {
    Symbol * lastSymbol = master_list.back ();
    Operator * op = dynamic_cast <Operator *> (lastSymbol);
    Unary_Operator * unary = dynamic_cast <Unary_Operator *>
      (lastSymbol);


    // is it a node with 2 children?
    if (op)
    {
      precedence_insert (list.back (), master_list);
    }
    else if (unary)
      // is it a unary node (like negate)
    {
      precedence_insert (list.back (), master_list);
    }
    else
    {
      // is it a terminal node (Number)
      // error
    }
  }
  else if (list.size () > 0)
    master_list = list;

  list.clear ();
}

// converts a string and context into a parse tree, and builds an
// expression tree out of the parse tree
TREE 
Interpreter::interpret (Interpreter_Context &context, 
                        const std::string &input)
{
  std::list<Symbol *> list;
  //list.clear ();
  Symbol * lastValidInput = 0;
  bool handled = false;
  int accumulated_precedence = 0;

  for (std::string::size_type i = 0;
    i < input.length (); ++i)
  {
    mainLoop (context, input, i, lastValidInput, 
      handled, accumulated_precedence, list);

    // store last valid input symbol. this is useful to the '-' operator
    // and will help us determine if '-' is a subtraction or a negation
    //if (input[i] != ' ' && input[i] != '\n')
    // lastValidInput = input[i];
  }

  // if the list has an element in it, then return the back of the list.
  if (!list.empty ())
  {
    // Invoke a recursive TREE build starting with the root
    // symbol. This is an example of the builder pattern. See pg 97
    // in GoF book.

    TREE tree = TREE (list.back ()->build ());
    delete list.back ();
    return tree;
  }

  // If we reach this, we didn't have any symbols.
  return TREE ();
}

#endif // _INTERPRETER_CPP_
