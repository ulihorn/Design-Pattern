//Name: Xianshi Xie
//Email: xianshi.xie@vanderbilt.edu
#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>

#include "Tree.h"
#include "Tree_Factory.h"
#include "Options.h"
#include "Print_Visitor.h"
#include "Eval_Visitor.h"
#include "Tree_Iterator.h"
#include "Interpreter.h"


struct acceptor
{
  acceptor (Visitor &v): visitor_ (v) {}

  void operator () (TREE t) { t.accept (visitor_); }

  Visitor &visitor_;
};


int 
main (int argc, char *argv[])
{
  try 
  {
    // Create options class to parse command line options.
    std::auto_ptr<Options> options (Options::instance ());

    // Parse the command-line options. If the user requested help (via "-h"
    // or "-?") then print out the usage and return.
    if (!Options::instance ()->parse_args (argc, argv))
      return 0;

    std::cout << "--Testing options class (singleton)--\n\n";

    // Print out the options used.
    std::cout << "  traversal option: " << options->traversal_strategy ()
      << std::endl;
    std::cout << "  queue option: " << options->queue_type ()
      << std::endl << std::endl;

    // Create a factory.
    Tree_Factory factory;

    // Use the factory to create the tree.
    //TREE root_node = factory.make_tree ();

    Interpreter_Context ic;
    Interpreter Inter;
    std::string input;
    std::cout << "Please input the expression..: " << std::endl;
    std::getline(std::cin,input);

    TREE root_node = Inter.interpret(ic,input);

    std::cout << "Testing the Print_Visitor: " << std::endl;

    Print_Visitor visitor;

    // Use the STL for_each() algorithm.

    std::for_each (
      root_node.begin (Options::instance ()->traversal_strategy ()),
      root_node.end (Options::instance ()->traversal_strategy ()),
      acceptor (visitor));

    // Use an explicit for loop.
    if (Options::instance ()->traversal_strategy ()=="Postorder")
    {
      Post_Order_Eval_Visitor eval;
      for (TREE::iterator 
        iter = root_node.begin (Options::instance ()->traversal_strategy ());
        iter != root_node.end (Options::instance ()->traversal_strategy ());
      iter++)

        //// Below is what I changed: which was (*iter).accept (visitor);
        (*iter).accept (eval);

      std::cout << std::endl;
      std::cout << " The Post_Order evaluation result is: " 
        << eval.eval_result() << std::endl;

    }

    // Evaluate by Pre_Order;
    //First: Reverse the Pre_Order_Iterator; 
    else if (Options::instance ()->traversal_strategy () == "Preorder")
    {
      std::vector<TREE> tstack;
      Pre_Order_Eval_Visitor pre_eval;
      for (TREE::iterator 
        iter = root_node.begin ("Preorder");
        iter != root_node.end ("Preorder");
      ++iter)
        tstack.push_back(*iter);

      for (std::vector<TREE>::reverse_iterator it = tstack.rbegin();
        it != tstack.rend();
        ++it)
        (*it).accept(pre_eval);

      std::cout << std::endl;
      std::cout << "The Pre_Order evaluation result is: " 
        << pre_eval.eval_result() << std::endl;
    }

    else

      std::cout << "Sorry, We just can evaluate by Pre or Post Order!" 
      << std::endl;

    std::cout << std::endl;


  }
  catch (...)
  {
    std::cout << "some exception occurred" << std::endl;
  }

  return 0;
}
