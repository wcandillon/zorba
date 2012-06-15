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

#ifndef ZORBA_STORE_JSON_ITEMS_H
#define ZORBA_STORE_JSON_ITEMS_H

#include <vector>
#include <set>

#include <zorba/config.h>
#include "atomic_items.h"
#include "simple_collection.h"
#include "store/api/item_handle.h"
#include "store/api/iterator.h"


namespace zorba
{

namespace store
{
class CopyMode;
}

namespace simplestore
{

namespace json
{

/******************************************************************************

*******************************************************************************/

class JSONNull : public AtomicItem
{
protected:
  SYNC_CODE(mutable RCLock  theRCLock;)

public:
  JSONNull() : AtomicItem() { }

  virtual ~JSONNull() {}

  SYNC_CODE(RCLock* getRCLock() const { return &theRCLock; })

  zstring getStringValue() const { return "null"; }

  void
  getTypedValue(store::Item_t& val, store::Iterator_t& iter) const;

  store::SchemaTypeCode getTypeCode() const { return store::JDM_NULL; }

  store::Item* getType() const; 

  bool 
  equals(
      const store::Item* other,
      long timezone = 0,
      const XQPCollator* collation = 0) const;

  uint32_t 
  hash(long timezone = 0, const XQPCollator* aCollation = 0) const;

  bool
  getEBV() const { return false; }
};


/******************************************************************************

*******************************************************************************/

class JSONItem : public store::Item
{
protected:
  SYNC_CODE(mutable RCLock  theRCLock;)
public:
  SYNC_CODE(RCLock* getRCLock() const { return &theRCLock; })

  JSONItem() : store::Item(JSONIQ) {}

  virtual ~JSONItem() {}

  bool 
  equals(
      const store::Item* other,
      long timezone = 0,
      const XQPCollator* aCollation = 0) const
  {
    return this == other;
  }
};


/******************************************************************************

*******************************************************************************/

class JSONObject : public JSONItem
{
public:
  virtual ~JSONObject() {}

  store::StoreConsts::JSONItemKind getJSONItemKind() const 
  {
    return store::StoreConsts::jsonObject;
  }

  bool isJSONObject() const { return true; }

  virtual bool add(const JSONObjectPair_t& aPair, bool accumulate) = 0;

  virtual JSONObjectPair_t remove(const store::Item_t& aName) = 0;

  virtual xs_integer getSize() const = 0;

  bool getBooleanValue() const { return true; }

  virtual Item* getType() const;

  virtual SimpleCollection* getCollection() const = 0;

  virtual void setCollection(SimpleCollection* collection, xs_integer pos) = 0;

#if 0
  uint32_t hash(long timezone = 0, const XQPCollator* aCollation = 0) const;

  virtual store::Item* copy(store::Item* parent, const store::CopyMode&) const;
#endif
};


/******************************************************************************

*******************************************************************************/

class SimpleJSONObject : public JSONObject
{
protected:
  struct JSONObjectPairComparator
  {
    bool operator() (const store::Item* lhs, const store::Item* rhs) const;
  };

  typedef std::map<store::Item*, size_t, JSONObjectPairComparator> PairMap;
  typedef PairMap::const_iterator PairMapConstIter;
  typedef PairMap::iterator PairMapIter;

  typedef std::vector<JSONObjectPair*>  Pairs;
  typedef Pairs::const_iterator         PairsConstIter;
  typedef Pairs::iterator               PairsIter;

  PairMap thePairMap;
  Pairs   thePairs;

  SimpleCollection* theCollection;

  class PairIterator : public store::Iterator
  {
    protected:
      SimpleJSONObject_t theObject;
      PairsConstIter     theIter;

    public:
      PairIterator(const SimpleJSONObject_t& aObject) : theObject(aObject) {}

      virtual ~PairIterator();

      virtual void open();

      virtual bool next(store::Item_t&);

      virtual void reset();

      virtual void close();
  };

public:
  SimpleJSONObject() : theCollection(0) {}

  virtual ~SimpleJSONObject();

  bool add(const JSONObjectPair_t& aPair, bool accumulate);

  JSONObjectPair_t remove(const store::Item_t& aName);

  xs_integer getSize() const { return xs_integer(thePairs.size()); }

  store::Iterator_t getPairs() const;

  store::Item* getPair(const store::Item_t& name) const;

  store::Item* copy(store::Item* parent, const store::CopyMode& copymode) const;

  zstring getStringValue() const;

  void getStringValue2(zstring& val) const;

  void appendStringValue(zstring& buf) const;

  void getTypedValue(store::Item_t& val, store::Iterator_t& iter) const;

  virtual SimpleCollection* getCollection() const { return theCollection; }

  void setCollection(SimpleCollection* collection, xs_integer pos);
};


/******************************************************************************

*******************************************************************************/

class JSONArray : public JSONItem
{
public:
  JSONArray() : JSONItem() {}

  virtual ~JSONArray() {}

  bool isJSONArray() const { return true; }

  store::StoreConsts::JSONItemKind
  getJSONItemKind() const { return store::StoreConsts::jsonArray; }

  virtual store::Item*
  getType() const;

  virtual void
  push_back(const store::Item_t& aValue) = 0;

  virtual void
  push_back(const std::vector<store::Item_t>& members) = 0;

  virtual void
  push_front(const std::vector<store::Item_t>& members) = 0;

  virtual void
  insert_before(const xs_integer& pos, const store::Item_t& member) = 0;

  virtual void
  insert_before(const xs_integer& pos, const std::vector<store::Item_t>& members) = 0;

  virtual void
  insert_after(const xs_integer& pos, const std::vector<store::Item_t>& members) = 0;

  virtual void
  remove(const xs_integer& pos) = 0;

  virtual void
  replace(const xs_integer& pos, const store::Item_t& value) = 0;

  virtual xs_integer
  getSize() const = 0;

  virtual const store::Item*
  operator[](const xs_integer&) const = 0;

  virtual SimpleCollection* getCollection() const = 0;

  virtual void setCollection(SimpleCollection* collection, xs_integer pos) = 0;
};


/******************************************************************************

*******************************************************************************/

class SimpleJSONArray : public JSONArray
{
protected:
  typedef std::vector<store::Item*> Members;
  typedef Members::const_iterator MembersConstIter;
  typedef Members::iterator MembersIter;

  Members            theContent;
  SimpleCollection * theCollection;

  class ValuesIterator : public store::Iterator
  {
    protected:
      SimpleJSONArray_t theArray;
      MembersConstIter    theIterator;

    public:
      ValuesIterator(const SimpleJSONArray_t& aArray)
        :
        theArray(aArray)
      {
      }

      virtual ~ValuesIterator()
      {
      }

      virtual void open() { theIterator = theArray->theContent.begin(); }

      virtual bool next(store::Item_t& res)
      {
        if (theIterator == theArray->theContent.end())
        {
          return false;
        }
        else
        {
          res = *(theIterator++);
          return true;
        }
      }

      virtual void reset() { open(); }

      virtual void close() { theIterator = theArray->theContent.end(); }
  };

  friend class ValuesIterator;

public:
  SimpleJSONArray()
    :
    theCollection(0)
  {
  }

  virtual ~SimpleJSONArray();

  virtual void
  push_back(const store::Item_t& aValue);

  virtual void
  push_back(const std::vector<store::Item_t>& members);

  virtual void
  push_front(const std::vector<store::Item_t>& members);

  virtual void
  insert_before(const xs_integer& pos, const store::Item_t& member);

  virtual void
  insert_before(const xs_integer& pos, const std::vector<store::Item_t>& members);

  virtual void
  insert_after(const xs_integer& pos, const std::vector<store::Item_t>& members);

  virtual void
  remove(const xs_integer& aPos);

  virtual void
  replace(const xs_integer& aPos, const store::Item_t& value);

  virtual xs_integer
  getSize() const { return xs_integer(theContent.size()); }

  virtual const store::Item*
  operator[](const xs_integer&) const;

  virtual store::Iterator_t
  getMembers() const;

  virtual store::Item*
  getMember(const store::Item_t& position) const;

  store::Item* copy(store::Item* parent, const store::CopyMode& copymode) const;

  zstring getStringValue() const;

  void getStringValue2(zstring& val) const;

  void appendStringValue(zstring& buf) const;

  void
  getTypedValue(store::Item_t& val, store::Iterator_t& iter) const;

  virtual SimpleCollection* getCollection() const { return theCollection; }

  void setCollection(SimpleCollection* collection, xs_integer pos);

protected:
  void
  add(uint64_t pos, const std::vector<store::Item_t>& aNewMembers);

  static uint64_t
  cast(const xs_integer& i);
};


/******************************************************************************

*******************************************************************************/
class JSONObjectPair : public JSONItem
{
public:
  virtual ~JSONObjectPair() {}

  bool isJSONPair() const { return true; }

  virtual void
  setName(const store::Item_t& aName) = 0;

  virtual void
  setValue(const store::Item_t& aValue)  = 0;

  virtual store::Item*
  getName() const = 0;

  virtual store::Item*
  getValue() const = 0;

  store::StoreConsts::JSONItemKind
  getJSONItemKind() const { return store::StoreConsts::jsonPair; }

  virtual Item*
  getType() const;
};


/******************************************************************************

*******************************************************************************/
class SimpleJSONObjectPair : public JSONObjectPair
{
protected:
  store::Item_t          theName;
  store::Item_t          theValue;

public:
  SimpleJSONObjectPair() {}

  SimpleJSONObjectPair(const store::Item_t& aName, const store::Item_t& aValue)
    :
    theName(aName),
    theValue(aValue)
  {
  }

  virtual ~SimpleJSONObjectPair() {}

  zstring getStringValue() const { return theValue->getStringValue(); }

  void getStringValue2(zstring& val) const { theValue->getStringValue2(val); }

  void appendStringValue(zstring& buf) const { theValue->appendStringValue(buf); }
  
  void
  setName(const store::Item_t& aName) { theName = aName; }

  void
  setValue(const store::Item_t& aValue) { theValue = aValue; }

  store::Item*
  getName() const { return theName.getp(); }

  store::Item*
  getValue() const { return theValue.getp(); }

  store::Item* copy(store::Item* parent, const store::CopyMode& copymode) const;

  void
  getTypedValue(store::Item_t& val, store::Iterator_t& iter) const;
};

} // namespace json
} // namespace simplestore
} // namespace zorba
#endif /* ZORBA_STORE_JSON_ITEMS_H */

/*
 * Local variables:
 * mode: c++
 * End:
 */
/* vim:set et sw=2 ts=2: */