/* -*- mode: c++; indent-tabs-mode: nil; tab-width: 2 -*-
 *
 *  $Id: Assert.h,v 1.2 2006/10/13 06:53:29 Paul Pedersen Exp $
 *
 *  Copyright 2005-2006 FLWOR Foundation.
 *
 */

// ZORBA_ASSERT (and the deprecated Assert) survive in release mode
// and raise errors via the Zorba error API

#ifndef XQP_ASSERT_H
#define XQP_ASSERT_H

#include <string>

namespace xqp {

void ZorbaAssert(const char *where, const char *fun, const char *what);

#ifdef __GNUC__
#define __ZORBA_ASSERT_aux4( ) __PRETTY_FUNCTION__
#else
#define __ZORBA_ASSERT_aux4( ) "?"
#endif
#define __ZORBA_ASSERT_aux3( line ) #line
#define __ZORBA_ASSERT_aux2( line ) __ZORBA_ASSERT_aux3( line )
#define __ZORBA_ASSERT_aux1( cond, line )       \
  if (! (cond)) \
    ZorbaAssert (__FILE__ ":" __ZORBA_ASSERT_aux2 (line), __ZORBA_ASSERT_aux4(), #cond)
  
#define ZORBA_ASSERT( cond ) __ZORBA_ASSERT_aux1 (cond, __LINE__)

#define ZORBA_NOT_SUPPORTED( what )                                     \
  ZORBA_ERROR_ALERT (AlertCodes::XQP0004_SYSTEM_NOT_SUPPORTED, NULL, false, what)
#define ZORBA_NOT_IMPLEMENTED( what )                                     \
  ZORBA_ERROR_ALERT (AlertCodes::XQP0004_SYSTEM_NOT_SUPPORTED, NULL, false, what)

// Deprecated
#define Assert( cond ) ZORBA_ASSERT (cond)

}	/* namespace xqp */
#endif	/* XQP_ASSERT_H */

