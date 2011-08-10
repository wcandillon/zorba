/*
 * Copyright 2006-2009 The FLWOR Foundation.
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
#ifndef ZORBA_BASE64_API_H
#define ZORBA_BASE64_API_H

#include <string>

#include <zorba/config.h>
#include <zorba/zorba_string.h>

namespace zorba { namespace encoding {

  class ZORBA_DLL_PUBLIC Base64
  {
    public:

      static String
      encode(const String& aString);

      static String
      encode(std::istream& aStream);

      static String
      decode(const String& aString);
      
      static String
      decode(std::istream& aStream);  

  };

} /* end namespace encoding */

} /* end namespace zorba */

#endif
/* vim:set et sw=2 ts=2: */