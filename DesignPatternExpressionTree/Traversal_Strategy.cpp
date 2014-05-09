//Name: Xianshi Xie
//Email: xianshi.xie@vanderbilt.edu

#if !defined (_Traversal_Strategy_CPP)
#define _Traversal_Strategy_CPP

#include "Traversal_Strategy.h"
#include "Traversal_Strategy_Impl.h"
#include "Options.h"
#include "Tree_Factory.h"

// Ctor
Traversal_Strategy::Traversal_Strategy (Traversal_Strategy_Impl *strategy)
  // You fill in here.
  :strategy_impl_(strategy)
{
}

/// Copy ctor - needed for reference counting.
Traversal_Strategy::Traversal_Strategy (const Traversal_Strategy &ts)
  // You fill in here.
  :strategy_impl_(ts.strategy_impl_)
{
}

/// Assignment operator - needed for reference counting.
void
Traversal_Strategy::operator= (const Traversal_Strategy &ts)
{
  // You fill in here.
  if (this == &ts) return;
    strategy_impl_ = ts.strategy_impl_;
}

/// Dtor
Traversal_Strategy::~Traversal_Strategy ()
{
  // refcounter will do the right thing here
}

/// Traverse method delegated to the implementation.
void
Traversal_Strategy::traverse (const TREE &root)
{
  // You fill in here.
  strategy_impl_->traverse(root);

}

#endif /* _Traversal_Strategy_CPP */
