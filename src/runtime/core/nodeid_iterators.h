#ifndef XQP_NODEID_ITERATORS_H
#define XQP_NODEID_ITERATORS_H


#include "util/rchandle.h"
#include "util/logging/logging.hh"
#include "compiler/expression/expr_consts.h"
#include "runtime/base/iterator.h"
#include "runtime/base/unarybase.h"

namespace xqp 
{

/*******************************************************************************

********************************************************************************/
class NodeDistinctIterator : public UnaryBaseIterator<NodeDistinctIterator>
{
protected:
  class NodeDistinctState : public PlanIterator::PlanIteratorState
  {
  public:
    Iterator_t  theStoreIterator;
  };

public:
  NodeDistinctIterator(
        const yy::location& loc,
        PlanIter_t input)
    :
    UnaryBaseIterator<NodeDistinctIterator>(loc, input)
  {
  }

  ~NodeDistinctIterator() { }

  Item_t nextImpl(PlanState& planState);
  void resetImpl(PlanState& planState);
  void releaseResourcesImpl(PlanState& planState);

  virtual uint32_t getStateSize() const { return sizeof(NodeDistinctState); }

  virtual void setOffset(PlanState& planState, uint32_t& offset);

  virtual void accept(PlanIterVisitor&) const;
};

#if 0
/*******************************************************************************

********************************************************************************/
class NodeSortIterator : public UnaryBaseIterator<NodeSortIterator>
{
 protected:

 public:
  NodeSortIterator(
        const yy::location& loc,
        PlanIter_t input)
    :
    UnaryBaseIterator<NodeSortIterator>(loc, input)
  {
  }

  ~NodeSortIterator() { }

  Item_t nextImpl(PlanState& planState);
  void resetImpl(PlanState& planState);
  void releaseResourcesImpl(PlanState& planState);

  int32_t getStateSize() { return sizeof(NodeSortState); }

  void setOffset(PlanState& planState, int32_t& offset);

  virtual void accept(PlanIterVisitor&) const;
};
#endif

}

#endif
