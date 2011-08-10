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
#include "stdafx.h"

#include "diagnostics/assert.h"
#include "diagnostics/xquery_diagnostics.h"

#include "runtime/fetch/fetch.h"
#include "system/globalenv.h"
#include "store/api/item_factory.h"

#include "context/static_context.h"
#include "context/uri_resolver.h"


namespace zorba {

/*******************************************************************************
********************************************************************************/
void
FetchContentIterator::destroyStream(std::istream& aStream)
{
  delete &aStream;
}

bool
FetchContentIterator::nextImpl(
    store::Item_t& result,
    PlanState& aPlanState) const
{
  store::Item_t lUri;
  store::Item_t lEntityKind;
  impl::EntityData::Kind lKind;
  zstring lKindStr;
  zstring lErrorMessage;
  std::auto_ptr<impl::Resource> lRes;
  impl::StreamResource* lStreamRes;

  PlanIteratorState* state;
  DEFAULT_STACK_INIT(PlanIteratorState, state, aPlanState);

  consumeNext(lUri, theChildren[0].getp(), aPlanState);
  consumeNext(lEntityKind, theChildren[1].getp(), aPlanState);

  // Figure out the EntityKind (any better way to do this?)
  lKindStr = lEntityKind->getStringValue();
  if ( ! lKindStr.compare("SOME_CONTENT")) {
    lKind = impl::EntityData::SOME_CONTENT;
  }
  else if ( ! lKindStr.compare("SCHEMA")) {
    lKind = impl::EntityData::SCHEMA;
  }
  else if ( ! lKindStr.compare("MODULE")) {
    lKind = impl::EntityData::MODULE;
  }
  else if ( ! lKindStr.compare("THESAURUS")) {
    lKind = impl::EntityData::THESAURUS;
  }
  else if ( ! lKindStr.compare("STOP_WORDS")) {
    lKind = impl::EntityData::STOP_WORDS;
  }
  else {
    throw XQUERY_EXCEPTION(
          zerr::ZXQP0026_INVALID_ENUM_VALUE,
          ERROR_PARAMS(lKindStr, "entityKind"),
          ERROR_LOC(loc));
  }

  try {
    // ask the uri mappers and resolvers to give
    // me a resource of specified kind
    lRes = theSctx->resolve_uri(
      lUri->getStringValue(),
      lKind,
      lErrorMessage);

  } catch (ZorbaException const& e) {
    throw XQUERY_EXCEPTION(
      zerr::ZXQP0025_ITEM_CREATION_FAILED,
      ERROR_PARAMS( e.what() ),
      ERROR_LOC( loc )
    );
  }

  lStreamRes = dynamic_cast<impl::StreamResource*>(lRes.get());
  if ( !lStreamRes ) {
    throw XQUERY_EXCEPTION(
      zerr::ZXQP0025_ITEM_CREATION_FAILED,
      ERROR_PARAMS( "Resource not available." ),
      ERROR_LOC( loc )
    );
  }

  // return the resource in a streamable string. This transfers memory
  // ownership of the istream (via its StreamReleaser) to the StreamableString
  // object, so we then remove the StreamReleaser from the StreamResource.
  GENV_ITEMFACTORY->createStreamableString(
        result,
        *lStreamRes->getStream(),
        lStreamRes->getStreamReleaser()
  );
  lStreamRes->setStreamReleaser(nullptr);

  STACK_PUSH(result != NULL, state);

  STACK_END(state);
}


/*******************************************************************************
********************************************************************************/
bool
FetchContentTypeIterator::nextImpl(
    store::Item_t& result,
    PlanState& aPlanState) const
{
  PlanIteratorState* state;
  DEFAULT_STACK_INIT(PlanIteratorState, state, aPlanState);

  STACK_PUSH(false, state);

  STACK_END(state);
}

} /* namespace zorba */
/* vim:set et sw=2 ts=2: */