//Name: Xianshi Xie
//Email: xianshi.xie@vanderbilt.edu

#if !defined (_Options_CPP)
#define _Options_CPP

#include <iostream>
#include <string>

#include "Options.h"
#include "getopt.h"
#include "LQueue.h"
#include "Tree.h"
#include "Typedefs.h"

// Initialize the singleton.
Options *Options::options_impl_ = 0;

Options*
Options::instance ()
{
  // You fill in here.
  if (options_impl_ == 0) options_impl_ = new Options();

  return Options::options_impl_;
}

// Ctor
Options::Options ()
  : traversal_strategy_ ("Postorder"),
    queue_type_ ("AQueue")
{
}

//Dtor
Options::~Options ()
{
  // release the freelist if we used an LQueue
  if (queue_type_ == "LQueue")
    {
      LQueue_Node<TREE>::free_list_release ();
    }
}

// Return queue type.
std::string
Options::queue_type ()
{
  return queue_type_;
}

// Return traversal strategy.
std::string
Options::traversal_strategy ()
{
  return traversal_strategy_;
}

// Parse the command line arguments.
bool
Options::parse_args (int argc, char *argv[])
{
  // You may need to use the getopt() function in the assignment4 directory.
  for (int c;
       (c = parsing::getopt (argc, argv, "t:q:h?")) != EOF;
       )
    switch (c)
      {
      // Parse the traversal strategy option
      case 't':
        switch (parsing::optarg[0])
          {
          // Level order traversal
          case 'L' :
            this->traversal_strategy_ = "Level";
            break;
          // Preorder traversal
          case 'p' :
            this->traversal_strategy_ = "Preorder";
            break;
          // Postorder traversal
          case 'P' :
            this->traversal_strategy_ = "Postorder";
            break;
          // Inorder traversal (default)
          default:
            this->traversal_strategy_ = "Inorder";
            break;
          }
        break;
      // Parse the queue type option
      case 'q':
        this->queue_type_ = parsing::optarg[0] == 'L'
          ? "LQueue"
          : "AQueue";
        break;
      case 'h':
      case '?':
        print_usage ();
        return false;
        break;
      default:
        std::cerr << "Queue type " << char (c) << " unknown" << std::endl; 
      }

  return true;
};

// Parse the command line arguments.
void
Options::print_usage (void)
{
  std::cout << "Usage: Adapter_test [-t L|p|P|I] [-q A|L]" << std::endl;
  std::cout << "    where -t specifies the tree traversal strategy:" 
    << std::endl;
  std::cout << "       L = Level Order (default)" << std::endl;
  std::cout << "       p = preorder" << std::endl;
  std::cout << "       P = Postorder" << std::endl;
  std::cout << "       I = Inorder" << std::endl << std::endl;
  std::cout << "    where -q specifies the queue type:" << std::endl;
  std::cout << "       L = LQueue (default)" << std::endl;
  std::cout << "       A = AQueue" << std::endl;
}

#endif /* _OptionsXS_CPP */
