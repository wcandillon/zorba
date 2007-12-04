/**
 * Copyright FLWOR Foundation
 *
 * Author: David Graf (david.graf@28msec.com)
 */

#include <string>
#include <fstream>
#include <vector>

#include "runtime/sequences/SequencesImpl.h"
#include "store/naive/simple_loader.h"
#include "store/api/collection.h"
#include "store/naive/store_defs.h"
#include "errors/Error.h"
#include "runtime/visitors/planitervisitor.h"

using namespace std;
namespace xqp {
  

/*______________________________________________________________________
|  
| 15.1 General Functions and Operators on Sequences
|_______________________________________________________________________*/

//15.1.1 fn:boolean



//15.1.2 op:concatenate 
//---------------------

FnConcatIterator::FnConcatIterator(
	yy::location loc,
	vector<PlanIter_t>& aChildren)
:
	NaryBaseIterator<FnConcatIterator>(loc, aChildren)
{}

FnConcatIterator::~FnConcatIterator(){}

Item_t 
FnConcatIterator::nextImpl(PlanState& planState) {
	Item_t item;
	
	FnConcatIteratorState* state;
	STACK_INIT(FnConcatIteratorState, state, planState);
	
  for (; state->getCurIter() < theChildren.size(); state->incCurIter()) {;
		item = this->consumeNext(theChildren[state->getCurIter()], planState);
		while (item != NULL) {
			STACK_PUSH (item, state);
			item = this->consumeNext(theChildren[state->getCurIter()], planState);
		}
	}
	
	STACK_END();
}

void 
FnConcatIterator::resetImpl(PlanState& planState) {
	FnConcatIteratorState* state;
	GET_STATE(FnConcatIteratorState, state, planState);
	state->reset();
	
	std::vector<PlanIter_t>::iterator iter = theChildren.begin();
	for(; iter != theChildren.end(); ++iter) {
		this->resetChild(*iter, planState);
	}
}

void
FnConcatIterator::FnConcatIteratorState::init() {
	PlanIterator::PlanIteratorState::init();
	theCurIter = 0;
}

void
FnConcatIterator::FnConcatIteratorState::reset() {
	PlanIterator::PlanIteratorState::reset();
	theCurIter = 0;
}

void
FnConcatIterator::FnConcatIteratorState::incCurIter() {
	theCurIter++;
}


//15.1.3 fn:index-of
// FIXME this iterator has three arguments (i.e. the collaction as #3)
FnIndexOfIterator::FnIndexOfIterator(yy::location loc,
                                    PlanIter_t& arg1,
                                    PlanIter_t& arg2,
                                    std::string collation)
 : BinaryBaseIterator<FnIndexOfIterator> ( loc, arg1, arg2 )
{ }

FnIndexOfIterator::~FnIndexOfIterator(){}

Item_t 
FnIndexOfIterator::nextImpl(PlanState& planState) {
  Item_t lSequence;
  Item_t lSearch;

  FnIndexOfIteratorState* state;
  STACK_INIT(FnIndexOfIteratorState, state, planState);
  
  state->theSearchItem = consumeNext(theChild1, planState);
  if ( state->theSearchItem == NULL ) 
  {
    ZORBA_ERROR_ALERT(
         error_messages::FORG0006_INVALID_ARGUMENT_TYPE,
         error_messages::RUNTIME_ERROR,
         NULL, false,
         "An empty sequence is not allowed as search item of fn:index-of");    
  }

  while ( (lSequence = consumeNext(theChild0, planState)) != NULL )
  {
    ++state->theCurrentPos; // index-of starts with one
    
    if (lSequence->equals(state->theSearchItem))
      STACK_PUSH(zorba::getItemFactory()->createInteger(state->theCurrentPos), state);
  }

  STACK_END();
}


uint32_t
FnIndexOfIterator::getStateSizeOfSubtree() const 
{
 return theChild0->getStateSizeOfSubtree() 
        + theChild1->getStateSizeOfSubtree() + getStateSize();
}

void 
FnIndexOfIterator::releaseResourcesImpl(PlanState& planState)
{
  BinaryBaseIterator<FnIndexOfIterator>::releaseResourcesImpl(planState);
  
  FnIndexOfIteratorState* state;
  GET_STATE(FnIndexOfIteratorState, state, planState);
  
  // do we need a releaseResouces function in the state or is it always the same as reset?
  state->reset(); 
}

void 
FnIndexOfIterator::resetImpl(PlanState& planState)
{
  BinaryBaseIterator<FnIndexOfIterator>::resetImpl(planState);

  FnIndexOfIteratorState* state;
  GET_STATE(FnIndexOfIteratorState, state, planState);
  state->reset();
}


void
FnIndexOfIterator::FnIndexOfIteratorState::init() 
{
 PlanIterator::PlanIteratorState::init();
 theCurrentPos = 0;
 theSearchItem = NULL;
}

void
FnIndexOfIterator::FnIndexOfIteratorState::reset() {
 PlanIterator::PlanIteratorState::reset();
 theCurrentPos = 0;
 theSearchItem = NULL;
}


//15.1.4 fn:empty
/*
 * If the value of $arg is the empty sequence, the function returns true; 
 * otherwise, the function returns false.
 */
FnEmptyIterator::FnEmptyIterator(yy::location loc,
	                             PlanIter_t& arg)
	: UnaryBaseIterator<FnEmptyIterator> ( loc, arg )
{ }

FnEmptyIterator::~FnEmptyIterator(){}

Item_t 
FnEmptyIterator::nextImpl(PlanState& planState) {
	Item_t item;

  PlanIterator::PlanIteratorState* state;
  STACK_INIT(PlanIterator::PlanIteratorState, state, planState);

	item = consumeNext(theChild, planState);
	if (item == NULL) 
	{
		STACK_PUSH (zorba::getItemFactory()->createBoolean ( true ), state);
	}
	else
	{
    STACK_PUSH (zorba::getItemFactory()->createBoolean ( false ), state);	  
	}

	STACK_END();
}

//15.1.5 fn:exists
/*
 * If the value of $arg is not the empty sequence, the function returns true; 
 * otherwise, the function returns false.
 */
FnExistsIterator::FnExistsIterator(yy::location loc,
	                                 PlanIter_t& arg)
	: UnaryBaseIterator<FnExistsIterator> ( loc, arg )
{ }

FnExistsIterator::~FnExistsIterator(){}

Item_t 
FnExistsIterator::nextImpl(PlanState& planState) {
	Item_t item;
	
  PlanIterator::PlanIteratorState* state;
  STACK_INIT(PlanIterator::PlanIteratorState, state, planState);
	
	item = consumeNext(theChild, planState);
	if (item != NULL) 
	{
		STACK_PUSH (zorba::getItemFactory()->createBoolean ( true ), state);
	}
	else
	{
    STACK_PUSH (zorba::getItemFactory()->createBoolean ( false ), state);	  
	}

	STACK_END();
}


//15.1.6 fn:distinct-values

//15.1.7 fn:insert-before

//15.1.8 fn:remove

//15.1.9 fn:reverse

//15.1.10 fn:subsequence

//15.1.11 fn:unordered


/*______________________________________________________________________
|  
| 15.2 Functions That Test the Cardinality of Sequences
|_______________________________________________________________________*/

//15.2.1 fn:zero-or-one

//15.2.2 fn:one-or-more

//15.2.3 fn:exactly-one


/*______________________________________________________________________
|
| 15.3 Equals, Union, Intersection and Except
|_______________________________________________________________________*/

//15.3.1 fn:deep-equal

//15.3.2 op:union

//15.3.3 op:intersect

//15.3.4 op:except


/*______________________________________________________________________
|
| 15.4 Aggregate Functions
|_______________________________________________________________________*/

//15.4.1 fn:count

//15.4.2 fn:avg

//15.4.3 fn:max

//15.4.4 fn:min

//15.4.5 fn:sum


/*______________________________________________________________________
|
| 15.5 Functions and Operators that Generate Sequences
|_______________________________________________________________________*/

//15.5.1 op:to

//15.5.2 fn:id

//15.5.3 fn:idref



/*______________________________________________________________________
|	15.5.4 fn:doc
|
|		fn:doc($uri as xs:string?) as document-node()?
|	
|	Summary: Retrieves a document using an xs:anyURI, which may include a 
|	fragment identifier, supplied as an xs:string. If $uri is not a valid 
|	xs:anyURI, an error is raised [err:FODC0005]. If it is a relative URI 
|	Reference, it is resolved relative to the value of the base URI 
|	property from the static context. The resulting absolute URI Reference 
|	is promoted to an xs:string. If the Available documents discussed in 
|	Section 2.1.2 Dynamic ContextXP provides a mapping from this string to 
|	a document node, the function returns that document node. If the 
|	Available documents maps the string to an empty sequence, then the 
|	function returns an empty sequence. If the Available documents 
|	provides no mapping for the string, an error is raised [err:FODC0005]. 
|	
|	If $uri is the empty sequence, the result is an empty sequence.
|_______________________________________________________________________*/

DocIterator::DocIterator (
    yy::location loc, PlanIter_t& arg)
    :
    UnaryBaseIterator<DocIterator> ( loc, arg )
{
}

DocIterator::~DocIterator() {}

Item_t
DocIterator::nextImpl ( PlanState& planState )
{
  Item_t item, xml;

  DocIteratorState* state;
  STACK_INIT ( DocIteratorState, state, planState );

  item = consumeNext(theChild, planState);

  if (!state->got_doc || item->getStringValue() != state->uri)
  {
    state->uri = item->getStringValue();
    SimpleStore& store = GET_STORE();
    state->collection = store.getCollection(item);
    
    if (state->collection != NULL)
    {
      state->childrenIter = state->collection->getIterator(true);
      state->got_doc = 2;
    }
    else
    {
      // load file
      ifstream ifs;
      ifs.open(((string)state->uri).c_str(), ios::in);
      if (ifs.is_open() == false)
      {
        // File does not exist
        ZORBA_ERROR_ALERT(error_messages::FODC0002_Error_retrieving_resource,
                          error_messages::RUNTIME_ERROR,
                          NULL,
                          false,
                          "The file does not exist");
      }

      XmlLoader& loader = store.getXmlLoader();
      state->doc = loader.loadXml(ifs);
      state->childrenIter = state->doc->getChildren();
      state->got_doc = 1;
    }
  }

  do
  {
    item = state->childrenIter->next();
    if (item != NULL)
      STACK_PUSH(item, state);
  }
  while (item != NULL);
  
  STACK_END();
}

uint32_t
DocIterator::getStateSize() const {
  return sizeof(DocIteratorState);
}

DocIterator::DocIteratorState::DocIteratorState()
  :
  got_doc(0)
{
}

void
DocIterator::DocIteratorState::init()
{
  PlanIterator::PlanIteratorState::init();
  if (got_doc == 1)
    childrenIter = doc->getChildren();
  else if (got_doc == 2)
    childrenIter = collection->getIterator(true);
}

void
DocIterator::DocIteratorState::reset()
{
  PlanIterator::PlanIteratorState::reset();
  got_doc = 0;
}

//15.5.5 fn:doc-available

//15.5.6 fn:collection


} /* namespace xqp */

