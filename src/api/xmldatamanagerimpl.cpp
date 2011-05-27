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
#include "api/xmldatamanagerimpl.h"

#include <fstream>

#include <zorba/zorba_string.h>
#include <zorba/item.h>
#include <zorba/diagnostic_handler.h>

#include "api/zorbaimpl.h"
#include "api/unmarshaller.h"
#include "api/collectionimpl.h"
#include "diagnostics/xquery_diagnostics.h"

#include "store/api/collection.h"
#include "store/api/item.h"
#include "system/globalenv.h"
#include "store/api/store.h"
#include "store/api/item_factory.h"

#include "context/static_context.h"
#include "context/internal_uri_resolvers.h"

#include "runtime/util/flowctl_exception.h"

namespace zorba {


#define ZORBA_DM_TRY                                                        \
  DiagnosticHandler* errorHandler = (aDiagnosticHandler != 0 ?              \
                                aDiagnosticHandler : theDiagnosticHandler); \
  try

#define ZORBA_DM_CATCH                                  \
  catch (ZorbaException const& e)                       \
  {                                                     \
    ZorbaImpl::notifyError(errorHandler, e);            \
  }                                                     \
  catch (std::exception const& e)                       \
  {                                                     \
    ZorbaImpl::notifyError(errorHandler, e.what());     \
  }                                                     \
  catch (...)                                           \
  {                                                     \
    ZorbaImpl::notifyError(errorHandler);               \
  }


XmlDataManagerImpl::XmlDataManagerImpl()
{
  theDiagnosticHandler = new DiagnosticHandler();
  theUserDiagnosticHandler = false;

  ZORBA_TRY
  {
    theStore = & GENV.getStore();
  }
  ZORBA_CATCH
}


XmlDataManagerImpl::~XmlDataManagerImpl()
{
  if (!theUserDiagnosticHandler)
    delete theDiagnosticHandler;
}


void XmlDataManagerImpl::registerDiagnosticHandler(DiagnosticHandler* aDiagnosticHandler)
{
  SYNC_CODE(AutoLatch lock(theLatch, Latch::WRITE);)

  if (!theUserDiagnosticHandler)
    delete theDiagnosticHandler;

  theDiagnosticHandler = aDiagnosticHandler;
  theUserDiagnosticHandler = true;
}


Item XmlDataManagerImpl::parseDocument(std::istream& aStream)
{
  SYNC_CODE(AutoLatch lock(theLatch, Latch::READ);)
  DiagnosticHandler* aDiagnosticHandler = 0;
  ZORBA_DM_TRY
  {
    store::LoadProperties loadProperties;
    loadProperties.setStoreDocument(false);
    return &*theStore->loadDocument("", "", aStream, loadProperties);
  }
  ZORBA_DM_CATCH
  return Item();
}


Item XmlDataManagerImpl::loadDocument(
    const String& aLocalFileUri,
    bool aReplaceDoc)
{
  XmlDataManager::LoadProperties loadProperties;
  return loadDocument(aLocalFileUri, loadProperties, aReplaceDoc);
}


Item XmlDataManagerImpl::loadDocument(
    const String& aUri,
    std::istream& aStream,
    bool aReplaceDoc)
{
  XmlDataManager::LoadProperties loadProperties;
  return loadDocument(aUri, aStream, loadProperties, aReplaceDoc);
}


Item XmlDataManagerImpl::loadDocument(
    const String& aLocalFileUri,
    const XmlDataManager::LoadProperties& aLoadProperties,
    bool aReplaceDoc)
{
  DiagnosticHandler* aDiagnosticHandler = NULL;

  SYNC_CODE(AutoLatch lock(theLatch, Latch::READ);)

  ZORBA_DM_TRY
  {
    const zstring& fileUri = Unmarshaller::getInternalString(aLocalFileUri);

    std::ifstream fileStream(fileUri.c_str());

    return loadDocument(aLocalFileUri, fileStream, aLoadProperties, aReplaceDoc);
  }
  ZORBA_DM_CATCH
  return Item();
}


Item XmlDataManagerImpl::loadDocument(
    const String& uri,
    std::istream& stream,
    const XmlDataManager::LoadProperties& aLoadProperties,
    bool aReplaceDoc)
{
  DiagnosticHandler* aDiagnosticHandler = NULL;

  SYNC_CODE(AutoLatch lock(theLatch, Latch::READ);)

  ZORBA_DM_TRY
  {
    if ( ! stream.good() )
			throw ZORBA_EXCEPTION( zerr::ZOSE0003_STREAM_READ_FAILURE );

    const zstring& docUri = Unmarshaller::getInternalString(uri);

    if (aReplaceDoc)
      theStore->deleteDocument(docUri);

    store::LoadProperties loadProps;
    loadProps.setEnableDtd( aLoadProperties.getEnableDtd() );

    return &*theStore->loadDocument(docUri, docUri, stream, loadProps);
  }
  ZORBA_DM_CATCH
  return Item();
}


Item XmlDataManagerImpl::loadDocumentFromUri(
    const String& aUri,
    bool aReplaceDoc)
{
  SYNC_CODE(AutoLatch lock(theLatch, Latch::READ);)

  DiagnosticHandler* aDiagnosticHandler = NULL;

  ZORBA_DM_TRY
  {
    InternalDocumentURIResolver* uri_resolver;
    uri_resolver = GENV_ROOT_STATIC_CONTEXT.get_document_uri_resolver();

    zstring docUri = Unmarshaller::getInternalString(aUri);

    zorba::store::ItemFactory* item_factory = GENV_ITEMFACTORY;
    store::Item_t uriItem;

    item_factory->createAnyURI(uriItem, docUri);

    store::Item_t docItem;
    docItem = uri_resolver->resolve(uriItem,
                                    &GENV_ROOT_STATIC_CONTEXT,
                                    true,
                                    aReplaceDoc);

    if(docItem.isNull())
      return Item();

    return Item(docItem);
  }
  ZORBA_DM_CATCH
  return Item();
}


Item XmlDataManagerImpl::getDocument(const String& uri)
{
  return getDocument(uri, theDiagnosticHandler);
}


Item XmlDataManagerImpl::getDocument(const String& uri, DiagnosticHandler* aDiagnosticHandler)
{
  SYNC_CODE(AutoLatch lock(theLatch, Latch::READ);)

  ZORBA_DM_TRY
  {
    const zstring& docUri = Unmarshaller::getInternalString(uri);
    return &*theStore->getDocument(docUri);
  }
  ZORBA_DM_CATCH
  return Item();
}


bool XmlDataManagerImpl::deleteDocument(const String& uri)
{
  return deleteDocument(uri, theDiagnosticHandler);
}


bool XmlDataManagerImpl::deleteDocument(const String& uri, DiagnosticHandler* aDiagnosticHandler)
{
  SYNC_CODE(AutoLatch lock(theLatch, Latch::READ);)

  ZORBA_DM_TRY
  {
    const zstring& docUri = Unmarshaller::getInternalString(uri);
    theStore->deleteDocument(docUri);
    return true;
  }
  ZORBA_DM_CATCH
  return false;
}


void XmlDataManagerImpl::deleteAllDocuments()
{
  DiagnosticHandler* aDiagnosticHandler = NULL;

  SYNC_CODE(AutoLatch lock(theLatch, Latch::READ);)

  ZORBA_DM_TRY
  {
    theStore->deleteAllDocuments();
  }
  ZORBA_DM_CATCH
}


Collection_t XmlDataManagerImpl::createCollection(const String& uri)
{
  return createCollection(uri, theDiagnosticHandler);
}


Collection_t XmlDataManagerImpl::createCollection(
    const String& uri,
    DiagnosticHandler* aDiagnosticHandler)
{
  SYNC_CODE(AutoLatch lock(theLatch, Latch::READ);)

  ZORBA_DM_TRY
  {
    const zstring& colUri = Unmarshaller::getInternalString(uri);
    return Collection_t(new CollectionImpl(theStore->createUriCollection(colUri),
                                           aDiagnosticHandler));
  }
  ZORBA_DM_CATCH
  return Collection_t();
}


Collection_t XmlDataManagerImpl::getCollection(const String& uri)
{
  return getCollection(uri, theDiagnosticHandler);
}


Collection_t XmlDataManagerImpl::getCollection(
    const String& uri,
    DiagnosticHandler* aDiagnosticHandler)
{
  SYNC_CODE(AutoLatch lock(theLatch, Latch::READ);)

  ZORBA_DM_TRY
  {
    const zstring& colUri = Unmarshaller::getInternalString(uri);
    store::Collection_t lColl = theStore->getUriCollection(colUri);
    if (lColl)
      return Collection_t(new CollectionImpl(lColl, aDiagnosticHandler));
    else
      return NULL;
  }
  ZORBA_DM_CATCH
  return NULL;
}


bool XmlDataManagerImpl::deleteCollection(const String& uri)
{
  return deleteCollection(uri, theDiagnosticHandler);
}


bool XmlDataManagerImpl::deleteCollection(
    const String& uri,
    DiagnosticHandler* aDiagnosticHandler)
{
  SYNC_CODE(AutoLatch lock(theLatch, Latch::READ);)

  ZORBA_DM_TRY
  {
    const zstring& colUri = Unmarshaller::getInternalString(uri);
    theStore->deleteUriCollection(colUri);
    return true;
  }
  ZORBA_DM_CATCH
  return false;
}

} // namespace zorba
/* vim:set et sw=2 ts=2: */
