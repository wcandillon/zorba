/*
 * Copyright 2006-2012 The FLWOR Foundation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
// ******************************************
// *                                        *
// * THIS IS A GENERATED FILE. DO NOT EDIT! *
// * SEE .xml FILE WITH SAME NAME           *
// *                                        *
// ******************************************

#ifndef ZORBA_RUNTIME_JSOUND_JSOUND_H
#define ZORBA_RUNTIME_JSOUND_JSOUND_H


#include "common/shared_types.h"



#include "runtime/base/narybase.h"


namespace zorba {

/**
 * 
 * Author: 
 */
class JSoundAnnotateIterator : public NaryBaseIterator<JSoundAnnotateIterator, PlanIteratorState>
{ 
public:
  SERIALIZABLE_CLASS(JSoundAnnotateIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(JSoundAnnotateIterator,
    NaryBaseIterator<JSoundAnnotateIterator, PlanIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar);

  JSoundAnnotateIterator(
    static_context* sctx,
    const QueryLoc& loc,
    std::vector<PlanIter_t>& children)
    : 
    NaryBaseIterator<JSoundAnnotateIterator, PlanIteratorState>(sctx, loc, children)
  {}

  virtual ~JSoundAnnotateIterator();

  zstring getNameAsString() const;

  void accept(PlanIterVisitor& v) const;

  bool nextImpl(store::Item_t& result, PlanState& aPlanState) const;
};


/**
 * 
 * Author: 
 */
class JSoundValidateIterator : public NaryBaseIterator<JSoundValidateIterator, PlanIteratorState>
{ 
public:
  SERIALIZABLE_CLASS(JSoundValidateIterator);

  SERIALIZABLE_CLASS_CONSTRUCTOR2T(JSoundValidateIterator,
    NaryBaseIterator<JSoundValidateIterator, PlanIteratorState>);

  void serialize( ::zorba::serialization::Archiver& ar);

  JSoundValidateIterator(
    static_context* sctx,
    const QueryLoc& loc,
    std::vector<PlanIter_t>& children)
    : 
    NaryBaseIterator<JSoundValidateIterator, PlanIteratorState>(sctx, loc, children)
  {}

  virtual ~JSoundValidateIterator();

  zstring getNameAsString() const;

  void accept(PlanIterVisitor& v) const;

  bool nextImpl(store::Item_t& result, PlanState& aPlanState) const;
};


}
#endif
/*
 * Local variables:
 * mode: c++
 * End:
 */ 
