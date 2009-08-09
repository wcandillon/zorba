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
#ifndef ZORBA_FLOATIMPL_H
#define ZORBA_FLOATIMPL_H

#include <zorba/config.h>
#include "common/common.h"
#include <math.h>
#include "zorbatypes/zorbatypes_decl.h"
#include "zorbatypes/xqpstring.h"

#include "zorbaserialization/serialization_engine.h"

#include "zorbautils/hashmap_str_obj.h"

namespace zorba {

class FloatCommons 
{
 public:
  static const xqpString& get_INF_POS_STR();
  static const xqpString& get_INF_NEG_STR();
  static const xqpString& get_NOT_A_NUM_STR();

  static Double
  parseFloat(const Float&);
   
  static Float 
  parseDouble(const Double&);
};


// exported for testing only
template <typename FloatType>
class ZORBA_DLL_PUBLIC FloatImpl : public ::zorba::serialization::SerializeBaseClass
{
  friend class Integer;
  friend class Decimal;
  friend class FloatCommons;
  template <typename Type>
    friend class FloatImplTraits;
  friend class NumConversions;

private:
  FloatType             theFloating;
  unsigned short        precision;

    FloatImpl(FloatType aFloating) 
    :
    theFloating(aFloating)
  {
    precision = max_precision();
  }


public:
  SERIALIZABLE_TEMPLATE_CLASS(FloatImpl)
  SERIALIZABLE_CLASS_CONSTRUCTOR(FloatImpl)
  void serialize(::zorba::serialization::Archiver &ar)
  {
    ar & theFloating;
    ar & precision;
  }
#ifdef ZORBA_NUMERIC_OPTIMIZATION
public:
  static  HashCharPtrObjPtrLimited<FloatImpl>  parsed_floats;
#endif
public:
  FloatImpl() : theFloating(0) { precision = max_precision();}

  FloatImpl(const FloatImpl& aFloatImpl)
    :
    ::zorba::serialization::SerializeBaseClass(),
    theFloating(aFloatImpl.theFloating),
    precision(aFloatImpl.precision)
  {
  }
  virtual ~FloatImpl() {}

public:
  /**
   * @return float or double that represents 0
   */
  static FloatImpl<FloatType>&
  zero();

  /**
   * @return float or double that represents -0
   */
  static FloatImpl<FloatType>&
  zero_neg();

  /**
   * @return float or double that represents +1
   */
  static FloatImpl<FloatType>&
  one();

  /**
   * @return float or double that represents -1
   */
  static FloatImpl<FloatType>&
  one_neg();

  /**
   * @return float or double that represents NaN
   */
  static FloatImpl<FloatType>&
  nan();

  /**
   * @return float or double that represents +INF
   */
  static FloatImpl<FloatType>&
  inf_pos();

  /**
   * @return float or double that represents -INF
   */
  static FloatImpl<FloatType>&
  inf_neg();

  /**
   * @return mapm number
   */
  FloatType
  getNumber() const { return theFloating; }

  /**
   * Checks if the passed number in string format is NaN, inf, 
   * -inf, negative or non-negative number.
   * @param aNumber Number in string format
   * @param parsed number
   * @return false if aNumber is not parsable to inf or nan 
   */
  static bool 
  parseInfNaNString(const char* aNumber, FloatImpl& aFloatImpl);

  /**
   * Parses string to float value
   */
  static bool
  parseString(const char* aCharStar, FloatImpl& aFloatImpl);

  /**
   * Parses float type (double of float) to float value
   */
  static FloatImpl<FloatType>
  parseFloatType(FloatType aFloatImpl);

  /**
   * Parses int to float value
   */
  static FloatImpl<FloatType>
  parseInt(int32_t);

  /**
   * Parses long to float value
   */
  static FloatImpl<FloatType>
  parseLong(long);

  static FloatImpl<FloatType>
  parseDecimal(const Decimal&);

  static FloatImpl<FloatType>
  parseInteger(const Integer&);

  static int max_precision();

  FloatImpl<FloatType>& operator=(const FloatImpl& aFloatImpl) 
  {
    theFloating = aFloatImpl.theFloating;
    precision = aFloatImpl.precision;
    return *this;
  }

  FloatImpl<FloatType> operator+(const FloatImpl& aFloatImpl) const;

  FloatImpl<FloatType>& operator+=(const FloatImpl& aFloatImpl)
  {
    *this = *this + aFloatImpl;
    return *this;
  }

  FloatImpl<FloatType> operator-(const FloatImpl& aFloatImpl) const;

  FloatImpl<FloatType>& operator-=(const FloatImpl& aFloatImpl)
  {
    *this = *this - aFloatImpl;
    return *this;
  }

  FloatImpl<FloatType> operator*(const FloatImpl& aFloatImpl) const;

  FloatImpl<FloatType>& operator*=(const FloatImpl& aFloatImpl)
  {
    *this = *this * aFloatImpl;
    return *this;
  }

  FloatImpl<FloatType> operator/(const FloatImpl& aFloatImpl) const;

  FloatImpl<FloatType>& operator/=(const FloatImpl& aFloatImpl)
  {
    *this = *this / aFloatImpl;
    return *this;
  }

  FloatImpl<FloatType> operator%(const FloatImpl& aFloatImpl) const;

  FloatImpl<FloatType>& operator%=(const FloatImpl& aFloatImpl)
  {
    *this = *this % aFloatImpl;
    return *this;
  }

  FloatImpl<FloatType> 
  operator-() const;

  FloatImpl<FloatType> 
  floor() const; 

  FloatImpl<FloatType>
  ceil() const; 

  FloatImpl<FloatType>
  round() const;

  FloatImpl<FloatType> 
  round(Integer aPrecision) const;

  FloatImpl<FloatType> 
  roundHalfToEven(Integer aPrecision) const;

  FloatImpl<FloatType> sqrt() const;
  FloatImpl<FloatType> exp() const;
  FloatImpl<FloatType> log() const;
  FloatImpl<FloatType> log10() const;
  FloatImpl<FloatType> sin() const;
  FloatImpl<FloatType> cos() const;
  FloatImpl<FloatType> tan() const;
  FloatImpl<FloatType> asin() const;
  FloatImpl<FloatType> acos() const;
  FloatImpl<FloatType> atan() const;
  FloatImpl<FloatType> sinh() const;
  FloatImpl<FloatType> cosh() const;
  FloatImpl<FloatType> tanh() const;
  FloatImpl<FloatType> asinh() const;
  FloatImpl<FloatType> acosh() const;
  FloatImpl<FloatType> atanh() const;

  bool 
  isNaN() const;

  bool 
  isFinite() const;

  bool 
  isPosInf() const;

  bool
  isNegInf() const;

  bool 
  isNeg() const;

  bool
  isPos() const;

  bool 
  isZero() const;

  bool
  isPosZero() const;

  bool
  isNegZero() const;

  bool 
  operator==(const FloatImpl& aFloatImpl) const;

  bool 
  operator!=(const FloatImpl& aFloatImpl) const;

  bool 
  operator<(const FloatImpl& aFloatImpl) const;

  bool 
  operator<=(const FloatImpl& aFloatImpl) const;

  bool 
  operator>(const FloatImpl& aFloatImpl) const;

  bool 
  operator>=(const FloatImpl& aFloatImpl) const;

  long compare(const FloatImpl& aFloatImpl) const
  {
    return (*this < aFloatImpl ? -1 : (*this == aFloatImpl ? 0 : 1));
  }

  xqpString 
  toIntegerString() const;
  
  xqpString 
  toString(bool no_scientific_mode = false) const;

  uint32_t
  hash() const;

}; // class FloatImpl


std::ostream&
operator<<(std::ostream& os, const Double& aFloatImpl); 
  
  
std::ostream&
operator<<(std::ostream& os, const Float& aFloatImpl);
  
  
Double
operator+(const Double&, const Float&);
  
  
Double
operator+(const Float&, const Double&);
  
  
Double
operator-(const Double&, const Float&);
  
  
Double
operator-(const Float&, const Double&);
  
  
Double
operator*(const Double&, const Float&);
  
  
Double
operator*(const Float&, const Double&);
  
  
Double
operator/(const Double&, const Float&);
  
  
Double
operator/(const Float&, const Double&);
  
  
Double
operator%(const Double&, const Float&);
  
  
Double
operator%(const Float&, const Double&);
  
} /* namespace zorba */

#endif // ZORBA_DOUBLE_H

/*
 * Local variables:
 * mode: c++
 * End:
 */
