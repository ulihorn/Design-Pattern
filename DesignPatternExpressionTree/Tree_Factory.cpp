//Name: Xianshi Xie
//Email: xianshi.xie@vanderbilt.edu

#if !defined (_Tree_Factory_CPP)
#define _Tree_Factory_CPP

#include<string>

#include "Tree_Factory.h"
#include "Tree_Factory_Impl.h"
#include "Traversal_Strategy_Impl.h"
#include "Options.h"

// Default constructor.
Tree_Factory::Tree_Factory (void)
  // You fill in here.
    :factory_impl_(new Binary_Tree_Factory_Impl())
{
}

// Copy ctor - needed for reference counting.
Tree_Factory::Tree_Factory (const Tree_Factory &f)
  // You fill in here.
  :factory_impl_(f.factory_impl_)
{
}

/// Assignment operator - needed for reference counting.
void
Tree_Factory::operator= (const Tree_Factory &f)
{
  // You fill in here.
  if (this==&f) return;
    factory_impl_ = f.factory_impl_;
}

// Destructor.
Tree_Factory::~Tree_Factory ()
{
}

// Method to create the binary tree to traverse.
TREE
Tree_Factory::make_tree ()
{
  // You fill in here.
  // factory_impl_ = new Binary_Tree_Factory_Impl();
   return factory_impl_->make_tree();
}

// Pass method call to implementation for strategy creation.
Traversal_Strategy
Tree_Factory::make_traversal_strategy ()
{
  // You fill in here.
  return factory_impl_->make_traversal_strategy(Options::instance()->traversal_strategy());
}

#endif /* _Tree_Factory_CPP */
