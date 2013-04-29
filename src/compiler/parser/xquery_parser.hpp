/* A Bison parser, made by GNU Bison 2.7.  */

/* Skeleton interface for Bison LALR(1) parsers in C++
   
      Copyright (C) 2002-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/**
 ** \file /Users/pjl/src/flwor/zorba/repo/bug-1090089/zorba/build/src/compiler/parser/xquery_parser.hpp
 ** Define the zorba::parser class.
 */

/* C++ LALR(1) parser skeleton written by Akim Demaille.  */

#ifndef YY_ZORBA_USERS_PJL_SRC_FLWOR_ZORBA_REPO_BUG_1090089_ZORBA_BUILD_SRC_COMPILER_PARSER_XQUERY_PARSER_HPP_INCLUDED
# define YY_ZORBA_USERS_PJL_SRC_FLWOR_ZORBA_REPO_BUG_1090089_ZORBA_BUILD_SRC_COMPILER_PARSER_XQUERY_PARSER_HPP_INCLUDED

/* "%code requires" blocks.  */
/* Line 33 of lalr1.cc  */
#line 5 "/Users/pjl/src/flwor/zorba/repo/bug-1090089/zorba/build/src/compiler/parser/xquery_parser.y"


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

#include <list>
#include <string>
#include <vector>

#include "compiler/parsetree/parsenodes.h"
#include "compiler/parser/zorba_parser_error.h"
#include "zorbatypes/zstring.h"

#ifdef __GNUC__
    // disable a warning in location.hh which comes with bison
    // position.hh:141: warning: suggest parentheses around && within ||
#   pragma GCC diagnostic ignored "-Wparentheses"
#endif

#include "location.hh"

#ifdef __GNUC__
#  pragma GCC diagnostic warning "-Wparentheses"
#endif

typedef std::list<zorba::zstring> string_list_t;
typedef std::pair<zorba::zstring,zorba::zstring> string_pair_t;




/* Line 33 of lalr1.cc  */
#line 92 "/Users/pjl/src/flwor/zorba/repo/bug-1090089/zorba/build/src/compiler/parser/xquery_parser.hpp"


#include <string>
#include <iostream>
#include "stack.hh"
#include "location.hh"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif


namespace zorba {
/* Line 33 of lalr1.cc  */
#line 108 "/Users/pjl/src/flwor/zorba/repo/bug-1090089/zorba/build/src/compiler/parser/xquery_parser.hpp"

  /// A Bison parser.
  class xquery_parser
  {
  public:
    /// Symbol semantic values.
#ifndef YYSTYPE
    union semantic_type
    {
/* Line 33 of lalr1.cc  */
#line 138 "/Users/pjl/src/flwor/zorba/repo/bug-1090089/zorba/build/src/compiler/parser/xquery_parser.y"

    zorba::parsenode *node;
    zorba::exprnode *expr;
    zorba::FunctionSig *fnsig;
    zorba::VarNameAndType *varnametype;
    off_t sval;
    const char *strval;
    xs_integer *ival;
    xs_double *dval;
    xs_decimal *decval;
    ZorbaParserError *err;
    string_list_t *strlist;
    string_pair_t *strpair;
    std::vector<string_pair_t> *vstrpair;
    CatchExpr::NameTestList *name_test_list;
    FTStopWordOption::incl_excl_list_t *incl_excl_list;
    FTSelection::pos_filter_list_t *pos_filter_list;
    FTThesaurusOption::thesaurus_id_list_t *thesaurus_id_list;
    ft_anyall_mode::type ft_anyall_value;


/* Line 33 of lalr1.cc  */
#line 142 "/Users/pjl/src/flwor/zorba/repo/bug-1090089/zorba/build/src/compiler/parser/xquery_parser.hpp"
    };
#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;
    /// Tokens.
    struct token
    {
      /* Tokens.  */
   enum yytokentype {
     _EOF = 0,
     UNRECOGNIZED = 258,
     APOS_ATTR_CONTENT = 260,
     CHAR_LITERAL = 261,
     CHAR_LITERAL_AND_CDATA_END = 262,
     CHAR_LITERAL_AND_PI_END = 263,
     CHAR_REF_LITERAL = 264,
     ELEMENT_CONTENT = 265,
     ELEM_WILDCARD = 266,
     ELEM_EQNAME_WILDCARD = 267,
     ENTITY_REF = 268,
     EXPR_COMMENT_LITERAL = 269,
     PI_NCNAME_LBRACE = 270,
     NCNAME_SVAL = 271,
     PRAGMA_LITERAL_AND_END_PRAGMA = 272,
     QNAME_SVAL_AND_END_PRAGMA = 273,
     EQNAME_SVAL_AND_END_PRAGMA = 274,
     PREFIX_WILDCARD = 275,
     COMP_ELEMENT_QNAME_LBRACE = 276,
     COMP_ATTRIBUTE_QNAME_LBRACE = 277,
     COMP_PI_NCNAME_LBRACE = 278,
     COMP_NS_NCNAME_LBRACE = 279,
     QNAME_SVAL = 280,
     EQNAME_SVAL = 281,
     ANNOTATION_QNAME_SVAL = 282,
     ANNOTATION_EQNAME_SVAL = 283,
     QUOTE_ATTR_CONTENT = 284,
     STRING_LITERAL = 285,
     XML_COMMENT_LITERAL = 286,
     DECLARE = 289,
     MODULE = 290,
     BLANK = 291,
     ALLOWING = 292,
     BASE_URI = 293,
     BOUNDARY_SPACE = 294,
     COMMENT = 295,
     CONSTRUCTION = 296,
     COPY_NAMESPACES = 297,
     COUNT = 298,
     DOCUMENT = 299,
     DOCUMENT_NODE = 300,
     ELEMENT = 301,
     FOR = 302,
     FUNCTION = 303,
     IF = 304,
     IMPORT = 305,
     INSTANCE = 306,
     LET = 307,
     MOST = 308,
     NS_NODE = 309,
     NEXT = 310,
     NO = 311,
     ONLY = 312,
     OPTION = 313,
     ORDERING = 314,
     PREVIOUS = 315,
     PROCESSING_INSTRUCTION = 316,
     SCHEMA = 317,
     SCHEMA_ATTRIBUTE = 318,
     SCHEMA_ELEMENT = 319,
     SEQUENTIAL = 320,
     SET = 321,
     SIMPLE = 322,
     SLIDING = 323,
     SOME = 324,
     SPACE = 325,
     STABLE = 326,
     TEXT = 327,
     TUMBLING = 328,
     SWITCH = 329,
     TYPESWITCH = 330,
     UPDATING = 331,
     VALIDATE = 332,
     TYPE = 333,
     WHEN = 334,
     WORD = 335,
     DECIMAL_FORMAT = 336,
     DECIMAL_SEPARATOR = 337,
     GROUPING_SEPARATOR = 338,
     INFINITY_VALUE = 339,
     MINUS_SIGN = 340,
     NaN = 341,
     PERCENT = 342,
     PER_MILLE = 343,
     ZERO_DIGIT = 344,
     DIGIT = 345,
     PATTERN_SEPARATOR = 346,
     ANCESTOR = 347,
     ANCESTOR_OR_SELF = 348,
     AND = 349,
     APOS = 350,
     AS = 351,
     ASCENDING = 352,
     AT = 353,
     ATTRIBUTE = 354,
     AT_SIGN = 355,
     CONCAT = 356,
     CASE = 357,
     CASTABLE = 358,
     CAST = 359,
     CDATA_BEGIN = 360,
     CDATA_END = 361,
     CHILD = 362,
     COLLATION = 363,
     COMMA = 364,
     COMMENT_BEGIN = 365,
     COMMENT_END = 366,
     DECIMAL_LITERAL = 367,
     CONTEXT = 368,
     VARIABLE = 369,
     DEFAULT = 370,
     DESCENDANT = 371,
     DESCENDANT_OR_SELF = 372,
     DESCENDING = 373,
     DIV = 374,
     DOLLAR = 375,
     DOT = 376,
     DOT_DOT = 377,
     COLON = 378,
     DOUBLE_COLON = 379,
     DOUBLE_LBRACE = 380,
     DOUBLE_LITERAL = 381,
     DOUBLE_RBRACE = 382,
     ELSE = 383,
     _EMPTY = 384,
     GREATEST = 385,
     LEAST = 386,
     EMPTY_TAG_END = 387,
     ENCODING = 388,
     EQUALS = 389,
     ESCAPE_APOS = 390,
     ESCAPE_QUOTE = 391,
     EVERY = 392,
     EXCEPT = 393,
     EXTERNAL = 394,
     FOLLOWING = 395,
     FOLLOWING_SIBLING = 396,
     FOLLOWS = 397,
     GE = 398,
     GETS = 399,
     GT = 400,
     HOOK = 401,
     HASH = 402,
     IDIV = 403,
     _IN = 404,
     INHERIT = 405,
     INTEGER_LITERAL = 406,
     INTERSECT = 407,
     IS = 408,
     ITEM = 409,
     LBRACE = 410,
     LBRACK = 411,
     LE = 412,
     LPAR = 413,
     LT_OR_START_TAG = 414,
     MINUS = 415,
     MOD = 416,
     NAMESPACE = 417,
     _NAN = 418,
     NE = 419,
     NODECOMP = 420,
     NO_INHERIT = 421,
     NO_PRESERVE = 422,
     OR = 423,
     ORDER = 424,
     ORDERED = 425,
     BY = 426,
     GROUP = 427,
     PARENT = 428,
     PERCENTAGE = 429,
     PI_BEGIN = 430,
     PI_END = 431,
     PLUS = 432,
     PRAGMA_BEGIN = 433,
     PRAGMA_END = 434,
     PRECEDES = 435,
     PRECEDING = 436,
     PRECEDING_SIBLING = 437,
     PRESERVE = 438,
     QUOTE = 439,
     RBRACE = 440,
     RBRACK = 441,
     RETURN = 442,
     RPAR = 443,
     SATISFIES = 444,
     SELF = 445,
     SEMI = 446,
     SLASH = 447,
     SLASH_SLASH = 448,
     BANG = 449,
     STAR = 450,
     START_TAG_END = 451,
     STRIP = 452,
     TAG_END = 453,
     THEN = 454,
     TO = 455,
     TREAT = 456,
     UNION = 457,
     UNORDERED = 458,
     VAL_EQ = 459,
     VAL_GE = 460,
     VAL_GT = 461,
     VAL_LE = 462,
     VAL_LT = 463,
     VAL_NE = 464,
     VALUECOMP = 465,
     VBAR = 466,
     EMPTY_SEQUENCE = 467,
     WHERE = 468,
     XML_COMMENT_BEGIN = 469,
     XML_COMMENT_END = 470,
     XQUERY = 471,
     VERSION = 472,
     START = 473,
     AFTER = 474,
     BEFORE = 475,
     REVALIDATION = 476,
     _STRICT = 477,
     LAX = 478,
     SKIP = 479,
     _DELETE = 480,
     NODE = 481,
     INSERT = 482,
     NODES = 483,
     RENAME = 484,
     REPLACE = 485,
     VALUE = 486,
     OF = 487,
     FIRST = 488,
     INTO = 489,
     LAST = 490,
     MODIFY = 491,
     COPY = 492,
     WITH = 493,
     BREAK = 494,
     CONTINUE = 495,
     EXIT = 496,
     LOOP = 497,
     RETURNING = 498,
     WHILE = 499,
     TRY = 500,
     CATCH = 501,
     USING = 502,
     ALL = 503,
     ANY = 504,
     CONTAINS = 505,
     CONTENT = 506,
     DIACRITICS = 507,
     DIFFERENT = 508,
     DISTANCE = 509,
     END = 510,
     ENTIRE = 511,
     EXACTLY = 512,
     FROM = 513,
     FTAND = 514,
     FTNOT = 515,
     NOT = 516,
     FT_OPTION = 517,
     FTOR = 518,
     INSENSITIVE = 519,
     LANGUAGE = 520,
     LEVELS = 521,
     LOWERCASE = 522,
     OCCURS = 523,
     PARAGRAPH = 524,
     PARAGRAPHS = 525,
     PHRASE = 526,
     RELATIONSHIP = 527,
     SAME = 528,
     SCORE = 529,
     SENSITIVE = 530,
     SENTENCE = 531,
     SENTENCES = 532,
     STEMMING = 533,
     STOP = 534,
     THESAURUS = 535,
     TIMES = 536,
     UPPERCASE = 537,
     WEIGHT = 538,
     WILDCARDS = 539,
     WINDOW = 540,
     WITHOUT = 541,
     WORDS = 542,
     COLLECTION = 543,
     CONSTOPT = 544,
     APPEND_ONLY = 545,
     QUEUE = 546,
     MUTABLE = 547,
     READ_ONLY = 548,
     UNIQUE = 549,
     NON = 550,
     INDEX = 551,
     MANUALLY = 552,
     AUTOMATICALLY = 553,
     MAINTAINED = 554,
     ON = 555,
     RANGE = 556,
     EQUALITY = 557,
     GENERAL = 558,
     INTEGRITY = 559,
     CONSTRAINT = 560,
     CHECK = 561,
     KEY = 562,
     FOREACH = 563,
     FOREIGN = 564,
     KEYS = 565,
     L_SIMPLE_OBJ_UNION = 566,
     R_SIMPLE_OBJ_UNION = 567,
     L_ACCUMULATOR_OBJ_UNION = 568,
     R_ACCUMULATOR_OBJ_UNION = 569,
     JSON = 570,
     APPEND = 571,
     POSITION = 572,
     OBJECT = 573,
     ARRAY = 574,
     JSON_ITEM = 575,
     STRUCTURED_ITEM = 576,
     BYTE_ORDER_MARK_UTF8 = 577,
     SHEBANG = 578,
     RANGE_REDUCE = 579,
     SEQUENCE_TYPE_REDUCE = 580,
     ADDITIVE_REDUCE = 581,
     UNION_REDUCE = 582,
     INTERSECT_EXCEPT_REDUCE = 583,
     QVARINDECLLIST_REDUCE = 584,
     COMMA_DOLLAR = 585,
     UNARY_PREC = 586,
     STEP_REDUCE = 587,
     SIMPLEMAPEXPR_REDUCE = 588,
     MULTIPLICATIVE_REDUCE = 589
   };

    };
    /// Token type.
    typedef token::yytokentype token_type;

    /// Build a parser object.
    xquery_parser (xquery_driver& driver_yyarg);
    virtual ~xquery_parser ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

  private:
    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Generate an error message.
    /// \param state   the state where the error occurred.
    /// \param tok     the lookahead token.
    virtual std::string yysyntax_error_ (int yystate, int tok);

#if YYDEBUG
    /// \brief Report a symbol value on the debug stream.
    /// \param yytype       The token type.
    /// \param yyvaluep     Its semantic value.
    /// \param yylocationp  Its location.
    virtual void yy_symbol_value_print_ (int yytype,
					 const semantic_type* yyvaluep,
					 const location_type* yylocationp);
    /// \brief Report a symbol on the debug stream.
    /// \param yytype       The token type.
    /// \param yyvaluep     Its semantic value.
    /// \param yylocationp  Its location.
    virtual void yy_symbol_print_ (int yytype,
				   const semantic_type* yyvaluep,
				   const location_type* yylocationp);
#endif


    /// State numbers.
    typedef int state_type;
    /// State stack type.
    typedef stack<state_type>    state_stack_type;
    /// Semantic value stack type.
    typedef stack<semantic_type> semantic_stack_type;
    /// location stack type.
    typedef stack<location_type> location_stack_type;

    /// The state stack.
    state_stack_type yystate_stack_;
    /// The semantic value stack.
    semantic_stack_type yysemantic_stack_;
    /// The location stack.
    location_stack_type yylocation_stack_;

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    /// Internal symbol numbers.
    typedef unsigned short int token_number_type;
    /* Tables.  */
    /// For a state, the index in \a yytable_ of its portion.
    static const short int yypact_[];
    static const short int yypact_ninf_;

    /// For a state, default reduction number.
    /// Unless\a  yytable_ specifies something else to do.
    /// Zero means the default is an error.
    static const unsigned short int yydefact_[];

    static const short int yypgoto_[];
    static const short int yydefgoto_[];

    /// What to do in a state.
    /// \a yytable_[yypact_[s]]: what to do in state \a s.
    /// - if positive, shift that token.
    /// - if negative, reduce the rule which number is the opposite.
    /// - if zero, do what YYDEFACT says.
    static const short int yytable_[];
    static const short int yytable_ninf_;

    static const short int yycheck_[];

    /// For a state, its accessing symbol.
    static const unsigned short int yystos_[];

    /// For a rule, its LHS.
    static const unsigned short int yyr1_[];
    /// For a rule, its RHS length.
    static const unsigned char yyr2_[]; 

    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *n);


    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#if YYDEBUG
    /// A type to store symbol numbers and -1.
    typedef short int rhs_number_type;
    /// A `-1'-separated list of the rules' RHS.
    static const rhs_number_type yyrhs_[];
    /// For each rule, the index of the first RHS symbol in \a yyrhs_.
    static const unsigned short int yyprhs_[];
    /// For each rule, its source line number.
    static const unsigned short int yyrline_[];
    /// For each scanner token number, its symbol number.
    static const unsigned short int yytoken_number_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    /* Debugging.  */
    int yydebug_;
    std::ostream* yycdebug_;
#endif

    /// Convert a scanner token number \a t to a symbol number.
    token_number_type yytranslate_ (int t);

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg        Why this token is reclaimed.
    ///                     If null, do not display the symbol, just free it.
    /// \param yytype       The symbol type.
    /// \param yyvaluep     Its semantic value.
    /// \param yylocationp  Its location.
    inline void yydestruct_ (const char* yymsg,
			     int yytype,
			     semantic_type* yyvaluep,
			     location_type* yylocationp);

    /// Pop \a n symbols the three stacks.
    inline void yypop_ (unsigned int n = 1);

    /* Constants.  */
    static const int yyeof_;
    /* LAST_ -- Last index in TABLE_.  */
    static const int yylast_;
    static const int yynnts_;
    static const int yyempty_;
    static const int yyfinal_;
    static const int yyterror_;
    static const int yyerrcode_;
    static const int yyntokens_;
    static const unsigned int yyuser_token_number_max_;
    static const token_number_type yyundef_token_;

    /* User arguments.  */
    xquery_driver& driver;
  };

} // zorba
/* Line 33 of lalr1.cc  */
#line 661 "/Users/pjl/src/flwor/zorba/repo/bug-1090089/zorba/build/src/compiler/parser/xquery_parser.hpp"



#endif /* !YY_ZORBA_USERS_PJL_SRC_FLWOR_ZORBA_REPO_BUG_1090089_ZORBA_BUILD_SRC_COMPILER_PARSER_XQUERY_PARSER_HPP_INCLUDED  */
