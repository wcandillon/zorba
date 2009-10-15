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
#include "api/unmarshaller.h"

#include <zorba/item.h>
#include <zorba/zorbastring.h>
#include "api/staticcontextimpl.h"
#include "api/dynamiccontextimpl.h"
#include "api/resultiteratorimpl.h"
#include "api/collectionimpl.h"
#include "store/api/collection.h"
#include "runtime/api/plan_wrapper.h"


namespace zorba {

  store::Item*
  Unmarshaller::getInternalItem(const Item& aItem)
  {
    return aItem.m_item;
  }

  xqpStringStore*
  Unmarshaller::getInternalString(const String& aString)
  {
    return aString.m_string;
  }

  static_context*
  Unmarshaller::getInternalStaticContext(const StaticContext_t& aCtx)
  {
    return static_cast<StaticContextImpl*>(aCtx.get())->theCtx;
  }

  dynamic_context*
  Unmarshaller::getInternalDynamicContext(const DynamicContext* aCtx)
  {
    return static_cast<const DynamicContextImpl*>(aCtx)->theCtx; 
  }

  PlanWrapper_t
  Unmarshaller::getInternalPlan(const ResultIterator* aResultIter)
  {
    return static_cast<const ResultIteratorImpl*>(aResultIter)->thePlan;
  }

  store::Collection_t
  Unmarshaller::getInternalCollection(const Collection_t& aCollection)
  {
    return static_cast<CollectionImpl*>(aCollection.get())->theCollection; 
  }

} /* namespace zorba */
