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

#include <algorithm>                    /* for lower_bound */
#include <cassert>

#include "util/less.h"

#include "wn_types.h"

using namespace std;

namespace zorba {
namespace wordnet {

///////////////////////////////////////////////////////////////////////////////

namespace part_of_speech {
  type find( char pos ) {
    switch ( pos ) {
      case adjective:
      case adverb:
      case noun:
      case verb:
        return static_cast<type>( pos );
      default:
        return unknown;
    }
  }
} // namespace part_of_speech

///////////////////////////////////////////////////////////////////////////////

#define DEF_END(CHAR_ARRAY)                             \
  static char const *const *const end =                 \
    CHAR_ARRAY + sizeof( CHAR_ARRAY ) / sizeof( char* );

#define FIND(what) \
  static_cast<type>( find_index( string_of, end, what ) )

/**
 * A less-verbose way to use std::lower_bound.
 */ 
inline int find_index( char const *const *begin, char const *const *end,
                       char const *s ) {
  char const *const *const entry =
    ::lower_bound( begin, end, s, less<char const*>() );
  return entry != end && ::strcmp( s, *entry ) == 0 ? entry - begin : 0;
} 

namespace pointer {

  char const *const string_of[] = {
    "#UNKNOWN",
    "also see",
    "antonym",
    "attribute",
    "cause",
    "derivationally related form",
    "derived from adjective",
    "domain of synset region",
    "domain of synset topic",
    "domain of synset usage",
    "entailment",
    "hypernym",
    "hyponym",
    "instance hypernym",
    "instance hyponym",
    "member holonym",
    "member meronym",
    "member of domain region",
    "member of domain topic",
    "member of domain usage",
    "part holonym",
    "part meronym",
    "participle of verb",
    "pertainym",
    "similar to",
    "substance holonym",
    "substance meronym",
    "verb group"
  };

  type find( char ptr_symbol ) {
    switch ( ptr_symbol ) {
      case 'A' /* !  */: return antonym;
      case 'a' /* =  */: return attribute;
      case 'C' /* >  */: return cause;
      case 'D' /* \  */: return derived_from_adjective;
      case 'E' /* @  */: return hypernym;
      case 'e' /* @i */: return instance_hypernym;
      case 'F' /* +  */: return derivationally_related_form;
      case 'G' /* $  */: return verb_group;
      case 'H' /* #m */: return member_holonym;
      case 'h' /* #p */: return part_holonym;
      case 'i' /* #s */: return substance_holonym;
      case 'L' /* *  */: return entailment;
      case 'M' /* %m */: return member_meronym;
      case 'm' /* %p */: return part_meronym;
      case 'n' /* %s */: return substance_meronym;
      case 'O' /* ~  */: return hyponym;
      case 'o' /* ~i */: return instance_hyponym;
      case 'P' /* \  */: return pertainym;
      case 'R' /* ;r */: return domain_of_synset_region;
      case 'r' /* -r */: return member_of_domain_region;
      case 'S' /* ^  */: return also_see;
      case 'T' /* ;c */: return domain_of_synset_topic;
      case 't' /* -c */: return member_of_domain_topic;
      case 'U' /* ;u */: return domain_of_synset_usage;
      case 'u' /* -u */: return member_of_domain_usage;
      case 'V' /* <  */: return participle_of_verb;
      case '~' /* &  */: return similar_to;
      default          : return unknown;
    }
  }

  type find( char const *relationship ) {
    DEF_END( string_of );
    return FIND( relationship );
  }

  type map_iso_rel( iso2788::rel_type iso_rel ) {
    switch ( iso_rel ) {
      case iso2788::BT : return hypernym;
      case iso2788::BTG: return hypernym;
      case iso2788::BTI: return instance_hypernym;
      case iso2788::BTP: return part_meronym;
      case iso2788::NT : return hyponym;
      case iso2788::NTG: return hyponym;
      case iso2788::NTI: return instance_hyponym;
      case iso2788::NTP: return part_holonym;
      case iso2788::RT : return also_see;
      case iso2788::SN : return unknown;
      case iso2788::TT : return hypernym; // the best we can do
      case iso2788::UF : return unknown;
      case iso2788::USE: return unknown;
      default          : assert( false ); // ensures all cases are handled
    }
  }

} // namespace pointer

///////////////////////////////////////////////////////////////////////////////

} // namespace wordnet
} // namespace zorba

/* vim:set et sw=2 ts=2: */
