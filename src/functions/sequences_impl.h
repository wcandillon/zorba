/*
 * Copyright 2006-2008 The FLWOR Foundation.
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
#ifndef ZORBA_FUNCTIONS_SEQUENCES_IMPLH_H
#define ZORBA_FUNCTIONS_SEQUENCES_IMPLH_H

#include "common/shared_types.h"
#include "functions/function_impl.h"

namespace zorba {

void
populate_context_sequences_impl(static_context* sctx);

/*******************************************************************************
  15.2.3 fn:exactly-one
********************************************************************************/
class fn_exactly_one_noraise : public function
{
protected:
  bool theRaiseError;

public:
  fn_exactly_one_noraise(const signature& sig)
    :
    function(sig),
    theRaiseError(false)
  {}

  xqtref_t return_type(const std::vector<xqtref_t>& arg_types) const;

  PlanIter_t codegen(CompilerCB* cb,
                     static_context* sctx,
                     const QueryLoc& loc,
                     std::vector<PlanIter_t>& argv,
                     AnnotationHolder& ann) const;
};

class fn_exactly_one : public fn_exactly_one_noraise
{
public:
  fn_exactly_one(const signature& sig) : fn_exactly_one_noraise(sig)
  {
    theRaiseError = true;
  }
};

/*******************************************************************************
  fn:union is implemented as fn:concat wrapped in a sort-distinct-nodes-asc.
********************************************************************************/
class fn_union : public function
{
public:
  fn_union(const signature& sig) : function (sig) {}

  ZORBA_PRODUCES_SORTED;
  ZORBA_PRODUCES_DISTINCT;

  CODEGEN_DECL();
};

/*******************************************************************************
  For intersect and except, it's always more efficient to sort the output
  and use hash-join than to sort the inputs and use mergesort-join. Only if
  the inputs happen to be sorted for a different reason will we use mergesort:
  for $x in path/expr1 for $y in path/expr2 return ($x, $y, ($x intersect $y))

  For now, codegen doesn't know whether the inputs are sorted or not.
  TODO: annotate expressions with USE_HASH / USE_MERGESORT properties
  during optimization.
********************************************************************************/
class fn_intersect : public function
{
public:
  fn_intersect(const signature& sig) : function (sig) {}

  ZORBA_PRODUCES_SORTED;
  ZORBA_PRODUCES_DISTINCT;

  CODEGEN_DECL();
};

/*******************************************************************************

********************************************************************************/
class fn_except: public function 
{
public:
  fn_except(const signature& sig) : function (sig) {}

  ZORBA_PRODUCES_SORTED;
  ZORBA_PRODUCES_DISTINCT;
  
  CODEGEN_DECL();
};

/*******************************************************************************
  15.1.6 fn:distinct-values
********************************************************************************/
class fn_distinct_values : public single_seq_function
{
public:
  fn_distinct_values(const signature& sig)
    : single_seq_function (sig, FunctionConsts::FN_DISTINCT_VALUES) {}

  ZORBA_PRODUCES_SORTED;
  ZORBA_PRODUCES_DISTINCT;

  CODEGEN_DECL();
};


class fn_max : public function
{
public:
  fn_max(const signature& sig) : function (sig) {}

  ZORBA_PROPAGATES_ONE_I2O(0);

  CODEGEN_DECL();
};

/*******************************************************************************
  15.4.4 fn:min
********************************************************************************/
class fn_min : public function
{
public:
  fn_min(const signature& sig) : function (sig) {}

  ZORBA_PROPAGATES_ONE_I2O(0);

  CODEGEN_DECL();
};

} /* namespace zorba */
#endif
