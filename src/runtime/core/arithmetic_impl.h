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
#ifndef ZORBA_ARITHMETIC_IMPL_H
#define ZORBA_ARITHMETIC_IMPL_H

#include "common/shared_types.h"
#include "types/typeconstants.h"
#include "runtime/base/binarybase.h" 

namespace zorba {

/**
 * Functions that are used in all Arith Operations
 */
class ArithOperationsCommons 
{
public:
  static void createError(
      RuntimeCB* rcb,
      const TypeManager* tm,
      const char* aOp, 
      const QueryLoc*, 
      TypeConstants::atomic_type_code_t aType0,
      TypeConstants::atomic_type_code_t aType1
  );
};


/******************************************************************************* 
  Class that implements addition between 2 items. The class has a compute()
  method for each combination of valid data types for the 2 input items.
********************************************************************************/
class AddOperation
{
public:
  static ArithmeticConsts::OperationKind getOperationKind() 
  {
    return ArithmeticConsts::ADDITION;
  }

public:
  template<TypeConstants::atomic_type_code_t ATC0, TypeConstants::atomic_type_code_t ATC1>
  static bool compute(
        store::Item_t& result,
        RuntimeCB* rcb,
        const TypeManager* tm,
        const QueryLoc* loc,
        const store::Item*,
        const store::Item*)
  {
    ArithOperationsCommons::createError(rcb, tm, "add", loc, ATC0, ATC1);
    return 0;
  }

  template<TypeConstants::atomic_type_code_t ATC>
  static bool computeSingleType(
        store::Item_t& result,
        RuntimeCB* rcb,
        const TypeManager* tm,
        const QueryLoc* loc,
        const store::Item* i0,
        const store::Item* i1) 
  {
    return AddOperation::compute<ATC,ATC>(result, rcb, tm, loc, i0, i1);
  }
};


/******************************************************************************* 
  Class that implements subtraction between 2 items. The class has a compute()
  method for each combination of valid data types for the 2 input items.
********************************************************************************/
class SubtractOperation
{
public:
  static ArithmeticConsts::OperationKind getOperationKind() 
  {
    return ArithmeticConsts::SUBTRACTION;
  }

public:
  template<TypeConstants::atomic_type_code_t ATC0, TypeConstants::atomic_type_code_t ATC1>
  static bool compute(
        store::Item_t& result,
        RuntimeCB* rcb,
        const TypeManager* tm,
        const QueryLoc* loc,
        const store::Item*,
        const store::Item*)
  {
    ArithOperationsCommons::createError(rcb, tm, "sub", loc, ATC0, ATC1);
    return 0;
  }

  template<TypeConstants::atomic_type_code_t ATC>
  static bool computeSingleType(
        store::Item_t& result,
        RuntimeCB* rcb,
        const TypeManager* tm,
        const QueryLoc* loc,
        const store::Item* i0,
        const store::Item* i1) 
  {
    return SubtractOperation::compute<ATC,ATC>(result, rcb, tm, loc, i0, i1);
  }
};


/******************************************************************************* 
  Class that implements multiplication between 2 items. The class has a compute()
  method for each combination of valid data types for the 2 input items.
********************************************************************************/
class MultiplyOperation
{
public:
  static ArithmeticConsts::OperationKind getOperationKind() 
  {
    return ArithmeticConsts::MULTIPLICATION;
  }

public:
  template<TypeConstants::atomic_type_code_t ATC0, TypeConstants::atomic_type_code_t ATC1>
  static bool compute(
        store::Item_t& result,
        RuntimeCB* rcb,
        const TypeManager* tm,
        const QueryLoc* loc,
        const store::Item*,
        const store::Item*)
  {
    ArithOperationsCommons::createError(rcb, tm, "mul", loc, ATC0, ATC1);
    return 0;
  }

  template<TypeConstants::atomic_type_code_t ATC>
  static bool computeSingleType(
        store::Item_t& result,
        RuntimeCB* rcb,
        const TypeManager* tm,
        const QueryLoc* loc,
        const store::Item* i0,
        const store::Item* i1) 
  {
    return MultiplyOperation::compute<ATC,ATC>(result, rcb, tm, loc, i0, i1);
  }
};


/******************************************************************************* 
  Class that implements division between 2 items. The class has a compute()
  method for each combination of valid data types for the 2 input items.
********************************************************************************/
class DivideOperation
{
public:
  static ArithmeticConsts::OperationKind getOperationKind() 
  {
    return ArithmeticConsts::DIVISION;
  }

public:
  template<TypeConstants::atomic_type_code_t ATC0, TypeConstants::atomic_type_code_t ATC1>
  static bool compute(
        store::Item_t& result,
        RuntimeCB* rcb,
        const TypeManager* tm,
        const QueryLoc* loc,
        const store::Item*,
        const store::Item*)
  {
    ArithOperationsCommons::createError(rcb, tm, "div", loc, ATC0, ATC1);
    return 0;
  }

  template<TypeConstants::atomic_type_code_t ATC>
  static bool computeSingleType(
        store::Item_t& result,
        RuntimeCB* rcb,
        const TypeManager* tm,
        const QueryLoc* loc,
        const store::Item* i0,
        const store::Item* i1) 
  {
    return DivideOperation::compute<ATC,ATC>(result, rcb, tm, loc, i0, i1);
  }
};


/******************************************************************************* 
  Class that implements integer division between 2 items. The class has a compute()
  method for each combination of valid data types for the 2 input items.
********************************************************************************/
class IntegerDivideOperation
{
public:
  static ArithmeticConsts::OperationKind getOperationKind() 
  {
    return ArithmeticConsts::INTEGER_DIVISION;
  }

public:
  template<TypeConstants::atomic_type_code_t ATC0, TypeConstants::atomic_type_code_t ATC1>
  static bool compute(
        store::Item_t& result,
        RuntimeCB* rcb,
        const TypeManager* tm,
        const QueryLoc* loc,
        const store::Item*,
        const store::Item*)
  {
    ArithOperationsCommons::createError(rcb, tm, "int-div", loc, ATC0, ATC1);
    return 0;
  }

  template<TypeConstants::atomic_type_code_t ATC>
  static bool computeSingleType(
        store::Item_t& result,
        RuntimeCB* rcb,
        const TypeManager* tm,
        const QueryLoc* loc,
        const store::Item* i0,
        const store::Item* i1) 
  {
    return IntegerDivideOperation::compute<ATC,ATC>(result, rcb, tm, loc, i0, i1);
  }
};


/******************************************************************************* 
  Class that implements modulo between 2 items. The class has a compute()
  method for each combination of valid data types for the 2 input items.
********************************************************************************/
class ModOperation
{
public:
  static ArithmeticConsts::OperationKind getOperationKind() 
  {
    return ArithmeticConsts::MODULO;
  }

public:
  template<TypeConstants::atomic_type_code_t ATC0, TypeConstants::atomic_type_code_t ATC1>
  static bool compute(
        store::Item_t& result,
        RuntimeCB* rcb,
        const TypeManager* tm,
        const QueryLoc* loc,
        const store::Item*,
        const store::Item*)
  {
    ArithOperationsCommons::createError(rcb, tm, "mod", loc, ATC0, ATC1);
    return 0;
  }

  template<TypeConstants::atomic_type_code_t ATC>
  static bool computeSingleType(
        store::Item_t& result,
        RuntimeCB* rcb,
        const TypeManager* tm,
        const QueryLoc* loc,
        const store::Item* i0,
        const store::Item* i1) 
  {
    return ModOperation::compute<ATC,ATC>(result, rcb, tm, loc, i0, i1);
  }
};



/*******************************************************************************
  Template iterator for arithmetic operations (+, -, *, div, idiv, and mod)
  The class that implements the specific operation is passed as the template
  parameter.

  The iterator can handle operands with any valid combination of data types. 
********************************************************************************/
class GenericArithIteratorState : public PlanIteratorState
{
public:
  const TypeManager * tm;
};


template < class Operation >
class GenericArithIterator : public BinaryBaseIterator<GenericArithIterator<Operation>,
                                                       GenericArithIteratorState>
{
public:
  static bool compute(
        store::Item_t& result,
        RuntimeCB* rcb,
        const TypeManager* tm,
        const QueryLoc& loc,
        store::Item_t& n0,
        store::Item_t& n1);

public:
  GenericArithIterator(short sctx, const QueryLoc&, PlanIter_t&, PlanIter_t&);

  virtual ~GenericArithIterator() {}

  void openImpl(PlanState& planState, uint32_t& offset);

  bool nextImpl(store::Item_t& result, PlanState&) const;
    
  virtual void accept(PlanIterVisitor&) const;

public:
  SERIALIZABLE_TEMPLATE_CLASS(GenericArithIterator)
  SERIALIZABLE_CLASS_CONSTRUCTOR2T(GenericArithIterator, BinaryBaseIterator<GenericArithIterator<Operation>, GenericArithIteratorState>)
  void serialize(::zorba::serialization::Archiver &ar)
  {
    serialize_baseclass(ar, (BinaryBaseIterator<GenericArithIterator<Operation>, GenericArithIteratorState>*)this);
  }
};

}

#endif

/*
 * Local variables:
 * mode: c++
 * End:
 */
