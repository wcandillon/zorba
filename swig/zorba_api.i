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

%module zorba_api
%module(directors="1") zorba_api

%include "std_string.i"
%include "cstring.i"
%include "std_pair.i"
%include "exception.i"
%include "carrays.i"
%apply (char *STRING, size_t LENGTH) { (const char aStream[], size_t aLen) }
%rename(opEquals) operator=;

%include "std_vector.i"

%exception {
  try {
    $action
  }
  catch (zorba::XQueryException& e) {
    std::stringstream lStream;
    lStream << e;
    SWIG_exception(SWIG_RuntimeError, lStream.str().c_str());
  }
  catch (zorba::ZorbaException& e) {
    std::stringstream lStream;
    lStream << e;
    SWIG_exception(SWIG_RuntimeError, lStream.str().c_str());
  }
}

namespace std {
  %template(StringPairVector) std::vector< pair<std::string, std::string> >;
  %template(StringPair) std::pair<std::string, std::string>;
  %template(StringVector) std::vector< std::string >;
}




%{  // Implementations



#include "Config.h"
#include <string>
#include <sstream>
#include <zorba/zorba.h>
#include <zorba/store_manager.h>
#include <zorba/zorba_exception.h>
#include <zorba/diagnostic_handler.h>
#include <zorba/options.h>
#include <zorba/singleton_item_sequence.h>
#include <zorba/serializer.h>
#include <zorba/static_collection_manager.h>

  class CompilerHints;
  class DiagnosticHandler;
  class Store;
  class Zorba;
  class Iterator;

  class DynamicException;
  class DocumentManager;
  class XQueryException;
  class SerializationException;
  class StaticException;
  class SystemException;
  class TypeException;
  class UserException;
  class ZorbaException;
  class XmlDataManager;
  class StaticCollectionManager;
  class Store;
  class InMemoryStore;

  #include "ZorbaIOStream.h"
  #include "ZorbaStreamBuffer.h"
  #include "SerializationOptions.h"
  #include "SequenceType.h"
  #include "Item.h"
  #include "Iterator.h"
  #include "DynamicContext.h"
  #include "StaticContext.h"
  #include "XQuery.h"
  #include "ItemFactory.h"
  #include "Zorba.h"
  #include "ItemSequence.h"
  #include "Collection.h"
  #include "CollectionManager.h"
  #include "StaticCollectionManager.h"
  #include "DocumentManager.h"
  #include "XmlDataManager.h"
  #include "DiagnosticHandler.h"
  #include "Store.h"

%}


namespace std {
%template(ItemVector) std::vector<Item>;
%template(ItemPair) std::pair<Item, Item>;
}

/* %include "various.i" required for mapping to Java byte[]*/


%include "ZorbaIOStream.i"
%include "ZorbaStreamBuffer.i"
%include "SerializationOptions.i"
%include "SequenceType.i"
%include "Item.i"
%include "Iterator.i"
%include "DynamicContext.i"
%include "CompilerHints.i"
%include "StaticContext.i"
%include "XQuery.i"
%include "Store.i"
%include "Exceptions.i"
%include "DiagnosticHandler.i"
%include "Zorba.i"
%include "ItemFactory.i"
%include "ItemSequence.i"
%include "Collection.i"
%include "CollectionManager.i"
%include "StaticCollectionManager.i"
%include "DocumentManager.i"
%include "XmlDataManager.i"

