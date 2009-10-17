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
#include <vector>

#include "system/globalenv.h"

#include "types/typeops.h"

#include "functions/function_impl.h"
#include "functions/Accessors.h"
#include "functions/single_seq_func.h"

#include "runtime/accessors/AccessorsImpl.h"
#include "runtime/accessors/accessors.h"
#include "runtime/core/var_iterators.h"

using namespace std;

namespace zorba 
{


/*******************************************************************************
  
********************************************************************************/
class fn_data_func : public single_seq_function
{
public:
  fn_data_func(const signature& sig) : single_seq_function (sig) {}    

  xqtref_t return_type(const std::vector<xqtref_t> &arg_types) const;

  DEFAULT_UNARY_CODEGEN(FnDataIterator);
};


xqtref_t fn_data_func::return_type (const std::vector<xqtref_t> &arg_types) const 
{
  RootTypeManager& RTM = GENV_TYPESYSTEM;

  if (TypeOps::is_subtype(*arg_types[0], *RTM.ANY_ATOMIC_TYPE_STAR))
    return arg_types[0];  // includes () case

  TypeConstants::quantifier_t q = TypeOps::quantifier (*arg_types [0]);

  if (TypeOps::is_subtype(*arg_types[0], *RTM.ANY_NODE_TYPE_STAR)) 
  {
    const XQType& type = *arg_types[0];
    if (type.type_kind() == XQType::NODE_TYPE_KIND) 
    {
      const NodeXQType& nType = static_cast<const NodeXQType&>(type);

      store::StoreConsts::NodeKind nodeKind = nType.get_node_kind();

      if (nodeKind == store::StoreConsts::piNode ||
          nodeKind == store::StoreConsts::commentNode)
      {
        return RTM.create_builtin_atomic_type(TypeConstants::XS_STRING, q);
      }

      if (nodeKind == store::StoreConsts::documentNode ||
          nodeKind == store::StoreConsts::textNode)
      {
        return RTM.create_builtin_atomic_type(TypeConstants::XS_UNTYPED_ATOMIC, q);
      }

      xqtref_t cType = nType.get_content_type();
      if (cType != NULL) 
      {
        if (TypeOps::is_equal(*cType, *RTM.UNTYPED_TYPE))
          return RTM.create_builtin_atomic_type(TypeConstants::XS_UNTYPED_ATOMIC, q);
        else if (TypeOps::is_subtype(*cType, *RTM.ANY_ATOMIC_TYPE_STAR))
          return RTM.create_type(*cType, q);
      }
    }
  }

  return RTM.create_builtin_atomic_type(TypeConstants::XS_ANY_ATOMIC, q);
}


/*******************************************************************************
  
********************************************************************************/
class fn_root_func : public function
{
public:
  fn_root_func(const signature& s) : function (s) {}

  DEFAULT_NARY_CODEGEN(RootIterator);
};


/*******************************************************************************
  
********************************************************************************/
class fn_nodename_func : public function
{
public:
  fn_nodename_func(const signature& s) : function (s) {}

  DEFAULT_NARY_CODEGEN(NodeNameIterator);
};


/*******************************************************************************
  2.2 fn:nilled
********************************************************************************/
class fn_nilled_func : public function
{
public:
  fn_nilled_func(const signature& s) : function (s) {}

  DEFAULT_NARY_CODEGEN(NilledIterator);
};


/*******************************************************************************
  2.5 fn:base-uri
********************************************************************************/
class fn_base_uri_func : public function
{
public:
  fn_base_uri_func(const signature& s) : function (s) {}

  DEFAULT_NARY_CODEGEN(BaseUriIterator);
};


/*******************************************************************************
  2.6 fn:document-uri
********************************************************************************/
class fn_document_uri_func : public function
{
public:
  fn_document_uri_func(const signature& s) : function (s) {}

  DEFAULT_NARY_CODEGEN(DocumentUriIterator);
};


/*******************************************************************************
  
********************************************************************************/
class fn_name_func : public function
{
public:
  fn_name_func(const signature& s) : function (s) {}

  CODEGEN_DECL();
};


PlanIter_t fn_name_func::codegen(
    CompilerCB* /*cb*/,
    static_context* sctx,
    const QueryLoc& loc,
    std::vector<PlanIter_t>& argv,
    AnnotationHolder& ann) const
{
  PlanIter_t nnIter = new NodeNameIterator(sctx, loc, argv);
  std::vector<PlanIter_t> lVec;
  lVec.push_back(nnIter);
  return new StringIterator(sctx, loc, lVec, true);
}


/*******************************************************************************
  
********************************************************************************/
class fn_string_func : public function
{
public:
  fn_string_func(const signature& s) : function (s) {}

  PlanIter_t codegen(
        CompilerCB* /*cb*/,
        static_context* sctx,
        const QueryLoc& loc,
        std::vector<PlanIter_t>& argv,
        AnnotationHolder& ann) const
  {
    return new StringIterator(sctx, loc, argv, true);
  }
};


/*******************************************************************************
  
********************************************************************************/
void populateContext_Accesors(static_context* sctx)
{
DECL(sctx, fn_data_func,
     (createQName (XQUERY_FN_NS, "fn", "data"),
      GENV_TYPESYSTEM.ITEM_TYPE_STAR, GENV_TYPESYSTEM.ANY_ATOMIC_TYPE_STAR));

DECL(sctx, fn_root_func,
     (createQName(XQUERY_FN_NS, "fn", "root"),
      GENV_TYPESYSTEM.ANY_NODE_TYPE_QUESTION, GENV_TYPESYSTEM.ANY_NODE_TYPE_QUESTION));

DECL(sctx, fn_nodename_func,
     (createQName(XQUERY_FN_NS, "fn", "node-name"),
      GENV_TYPESYSTEM.ANY_NODE_TYPE_QUESTION, GENV_TYPESYSTEM.QNAME_TYPE_QUESTION));

DECL(sctx, fn_nilled_func,
     (createQName(XQUERY_FN_NS, "fn", "nilled"),
      GENV_TYPESYSTEM.ANY_NODE_TYPE_QUESTION, GENV_TYPESYSTEM.BOOLEAN_TYPE_QUESTION));

DECL(sctx, fn_base_uri_func,
     (createQName(XQUERY_FN_NS, "fn", "base-uri"),
      GENV_TYPESYSTEM.ANY_NODE_TYPE_QUESTION, GENV_TYPESYSTEM.ANY_URI_TYPE_QUESTION));

DECL(sctx, fn_document_uri_func,
     (createQName(XQUERY_FN_NS, "fn", "document-uri"),
      GENV_TYPESYSTEM.ANY_NODE_TYPE_QUESTION, GENV_TYPESYSTEM.ANY_URI_TYPE_QUESTION));

DECL(sctx, fn_name_func,
     (createQName(XQUERY_FN_NS, "fn", "name"),
      GENV_TYPESYSTEM.ANY_NODE_TYPE_QUESTION, GENV_TYPESYSTEM.STRING_TYPE_ONE));

DECL(sctx, fn_string_func,
     (createQName(XQUERY_FN_NS, "fn", "string"),
      GENV_TYPESYSTEM.ITEM_TYPE_QUESTION, GENV_TYPESYSTEM.STRING_TYPE_ONE));
}


} /* namespace zorba */
