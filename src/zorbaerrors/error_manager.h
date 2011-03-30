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

#ifndef ZORBA_ERROR_MANAGER_H
#define ZORBA_ERROR_MANAGER_H

#include <memory>
#include <vector>

#include <zorba/config.h>
#include <zorba/zorba_exception.h>

// TODO: this #include is temporary
#include <zorba/error_list.h>

#include "err.h"
#include "xquery_exception.h"

namespace zorba {
namespace error {

/**
 * TODO
 */
class ZORBA_DLL_PUBLIC ErrorManager {
public:
  typedef std::vector<ZorbaException const*> errors_type;

  ErrorManager();
  ~ErrorManager();

  void addError( ZorbaException const *exception ) {
    errors_.push_back( exception );
  }

  void addError( std::auto_ptr<ZorbaException> exception ) {
    addError( exception.release() );
  }

  void addError( ZorbaException const &exception ) {
    addError( exception.clone() );
  }

  bool hasErrors() {
    return !errors_.empty();
  }

  errors_type const& getErrors() const {
    return errors_;
  }

private:
  errors_type errors_;
};

} // namespace error

/**
 * \internal
 * Convenience macro for throwing "not implemented" exception.
 * \hideinitializer
 */
#define ZORBA_NOT_IMPLEMENTED(...) \
  XQUERY_EXCEPTION( XQP0015_SYSTEM_NOT_YET_IMPLEMENTED, __VA_ARGS__ )

/**
 * \internal
 * Convenience macro for throwing "not supported" exception.
 * \hideinitializer
 */
#define ZORBA_NOT_SUPPORTED(...) \
  XQUERY_EXCEPTION( XQP0004_SYSTEM_NOT_SUPPORTED, __VA_ARGS__ )

////////// TEMPORARY TRANSITION MACROS: THESE WILL BE REMOVED /////////////////

#define ZORBA_ERROR(...) \
  throw XQUERY_EXCEPTION( __VA_ARGS__ )

#define ZORBA_ERROR_LOC(LOCALNAME,LOC) \
  ZORBA_ERROR( LOCALNAME, ERROR_LOC(LOC) )

#define ZORBA_ERROR_VAR_LOC(ERROR_VAR,LOC) \
  throw XQUERY_EXCEPTION_VAR( ERROR_VAR, ERROR_LOC(LOC) )

#define ZORBA_ERROR_DESC(LOCALNAME,MSG) \
  throw XQUERY_EXCEPTION( LOCALNAME, ERROR_PARAMS(MSG) )

#define ZORBA_ERROR_DESC_OSS(LOCALNAME,MSG) \
  do { \
    std::ostringstream oss; \
    oss << MSG; \
    ZORBA_ERROR_DESC( LOCALNAME, oss.str() ); \
  } while (0)

#define ZORBA_ERROR_LOC_DESC(LOCALNAME,LOC,MSG) \
  throw XQUERY_EXCEPTION( LOCALNAME, ERROR_PARAMS(MSG), ERROR_LOC(LOC) )

#define ZORBA_ERROR_VAR_LOC_DESC(ERROR_VAR,LOC,MSG) \
  throw XQUERY_EXCEPTION_VAR( ERROR_VAR, ERROR_PARAMS(MSG), ERROR_LOC(LOC) )

#define ZORBA_ERROR_LOC_DESC_OSS(LOCALNAME,LOC,MSG) \
  do { \
    std::ostringstream oss; \
    oss << MSG; \
    ZORBA_ERROR_LOC_DESC( LOCALNAME, LOC, oss.str() ); \
  } while (0)

#define ZORBA_ERROR_VAR_DESC_OSS(ERROR_VAR,MSG) \
  do { \
    std::ostringstream oss; \
    oss << MSG; \
    throw XQUERY_EXCEPTION_VAR( ERROR_VAR, ERROR_PARAMS(oss.str()) ); \
  } while (0)

#define ZORBA_ERROR_VAR_LOC_DESC_OSS(ERROR_VAR,LOC,MSG) \
  do { \
    std::ostringstream oss; \
    oss << MSG; \
    throw XQUERY_EXCEPTION_VAR( ERROR_VAR, ERROR_PARAMS(oss.str()), ERROR_LOC(LOC) ); \
  } while (0)

#define ZORBA_ERROR_PARAM(LOCALNAME,PARAM1,PARAM2) \
  throw XQUERY_EXCEPTION( LOCALNAME, ERROR_PARAMS(PARAM1,PARAM2) )

#define ZORBA_ERROR_VAR_PARAM(ERROR_VAR,PARAM1,PARAM2) \
  throw XQUERY_EXCEPTION_VAR( ERROR_VAR, ERROR_PARAMS(PARAM1,PARAM2) )

#define ZORBA_ERROR_PARAM_OSS(LOCALNAME,PARAM1,PARAM2) \
  do { \
    std::ostringstream oss1, oss2; \
    oss1 << PARAM1; \
    oss2 << PARAM2; \
    throw XQUERY_EXCEPTION( LOCALNAME, ERROR_PARAMS(oss1.str(), oss2.str()) ); \
  } while (0)

#define ZORBA_ERROR_LOC_PARAM(LOCALNAME,LOC,PARAM1,PARAM2) \
  throw XQUERY_EXCEPTION( LOCALNAME, ERROR_PARAMS(PARAM1,PARAM2), ERROR_LOC(LOC) )

#define ZORBA_ERROR_VAR_LOC_PARAM(ERROR_VAR,LOC,PARAM1,PARAM2) \
    throw XQUERY_EXCEPTION_VAR( ERROR_VAR, ERROR_PARAMS(PARAM1,PARAM2), ERROR_LOC(LOC) )

#define ZORBA_ERROR_DESC_CONTINUE(ERR_MGR,LOCALNAME,MSG) \
  (ERR_MGR)->addError( NEW_XQUERY_EXCEPTION( LOCALNAME, ERROR_PARAMS(MSG) ) )

#define ZORBA_ERROR_PARAM_CONTINUE(ERR_MGR,LOCALNAME,PARAM1,PARAM2) \
  (ERR_MGR)->addError( NEW_XQUERY_EXCEPTION( LOCALNAME, ERROR_PARAMS(PARAM1,PARAM2) ) )

#define ZORBA_ERROR_PARAM_CONTINUE_OSS(ERR_MGR,LOCALNAME,PARAM1,PARAM2) \
  do { \
    std::ostringstream oss1; \
    oss1 << PARAM1; \
    (ERR_MGR)->addError( NEW_XQUERY_EXCEPTION( LOCALNAME, ERROR_PARAMS(oss1.str(),PARAM2) ) ); \
  } while (0)

#define ZORBA_ERROR_LOC_PARAM_CONTINUE(ERR_MGR,LOCALNAME,LOC,PARAM1,PARAM2) \
  do { \
    XQueryException *const xe = NEW_XQUERY_EXCEPTION( LOCALNAME, ERROR_PARAMS(PARAM1,PARAM2) ); \
    xe->set_source( (LOC).getFilename().str().c_str(), (LOC).getLineBegin(), (LOC).  getColumnBegin() ); \
    (ERR_MGR)->addError( xe ); \
  } while ( 0 )

} // namespace zorba

#endif /* ZORBA_ERROR_MANAGER_H */
/* vim:set et sw=2 ts=2: */
