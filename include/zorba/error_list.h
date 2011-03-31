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

#ifndef ZORBA_ERROR_LIST_API_H
#define ZORBA_ERROR_LIST_API_H

#include <zorba/config.h>
#include <zorba/error.h>

#define XQUERY_DEC_ERROR(ERR) extern ZORBA_DLL_PUBLIC XQueryError ERR

namespace zorba {
namespace err {

////////// XQuery Errors //////////////////////////////////////////////////////

/**
 * It is a static error if analysis of an expression relies on some component
 * of the static context that has not been assigned a value.
 */
XQUERY_DEC_ERROR( XPST0001 );

/**
 * It is a dynamic error if evaluation of an expression relies on some part of
 * the dynamic context that has not been assigned a value.
 */
XQUERY_DEC_ERROR( XPDY0002 );

/**
 * It is a static error if an expression is not a valid instance of the
 * grammar.
 */
XQUERY_DEC_ERROR( XPST0003 );

/**
 * It is a type error if, during the static analysis phase, an expression is
 * found to have a static type that is not appropriate for the context in which
 * the expression occurs, or during the dynamic evaluation phase, the dynamic
 * type of a value does not match a required type as specified by the matching
 * rules in 2.5.4 SequenceType Matching.
 */
XQUERY_DEC_ERROR( XPTY0004 );

/**
 * During the analysis phase, it is a static error if the static type assigned
 * to an expression other than the expression \c () or \c data(()) is
 * <code>empty-sequence()</code>.
 */
XQUERY_DEC_ERROR( XPST0005 );

/**
 * It is a static error if an expression refers to an element name, attribute
 * name, schema type name, namespace prefix, or variable name that is not
 * defined in the static context, except for an ElementName in an ElementTest
 * or an AttributeName in an AttributeTest.
 */
XQUERY_DEC_ERROR( XPST0008 );

/**
 * An implementation that does not support the Schema Import Feature must raise
 * a static error if a Prolog contains a schema import.
 */
XQUERY_DEC_ERROR( XQST0009 );

/**
 * An implementation must raise a static error if it encounters a reference to
 * an axis that it does not support.
 */
XQUERY_DEC_ERROR( XPST0010 );

/**
 * It is a static error if the set of definitions contained in all schemas
 * imported by a Prolog do not satisfy the conditions for schema validity
 * specified in Sections 3 and 5 of [XML Schema] Part 1--i.e., each definition
 * must be valid, complete, and unique.
 */
XQUERY_DEC_ERROR( XQST0012 );

/**
 * It is a static error if an implementation recognizes a pragma but determines
 * that its content is invalid.
 */
XQUERY_DEC_ERROR( XQST0013 );

/**
 * An implementation that does not support the Module Feature raises a static
 * error if it encounters a module declaration or a module import.
 */
XQUERY_DEC_ERROR( XQST0016 );

/**
 * It is a static error if the expanded QName and number of arguments in a
 * function call do not match the name and arity of a function signature in the
 * static context.
 */
XQUERY_DEC_ERROR( XPST0017 );

/**
 * It is a type error if the result of the last step in a path expression
 * contains both nodes and non-nodes.
 */
XQUERY_DEC_ERROR( XPTY0018 );

/**
 * It is a type error if the result of a step (other than the last step) in a
 * path expression contains an atomic value.
 */
XQUERY_DEC_ERROR( XPTY0019 );

/**
 * It is a type error if, in an axis step, the context item is not a node.
 */
XQUERY_DEC_ERROR( XPTY0020 );

/**
 * It is a static error if the value of a namespace declaration attribute is
 * not a URILiteral.
 */
XQUERY_DEC_ERROR( XQST0022 );

/**
 * It is a type error if the content sequence in an element constructor
 * contains an attribute node following a node that is not an attribute node.
 */
XQUERY_DEC_ERROR( XQTY0024 );

/**
 * It is a dynamic error if any attribute of a constructed element does not
 * have a name that is distinct from the names of all other attributes of the
 * constructed element.
 */
XQUERY_DEC_ERROR( XQDY0025 );

/**
 * It is a dynamic error if the result of the content expression of a computed
 * processing instruction constructor contains the string "?>".
 */
XQUERY_DEC_ERROR( XQDY0026 );

/**
 * In a validate expression, it is a dynamic error if the root element
 * information item in the PSVI resulting from validation does not have the
 * expected validity property: \c valid if validation mode is \c strict, or
 * either \c valid or \c notKnown if validation mode is \c lax.
 */
XQUERY_DEC_ERROR( XQDY0027 );

/**
 * It is a type error if the argument of a validate expression does not
 * evaluate to exactly one document or element node.
 */
XQUERY_DEC_ERROR( XQTY0030 );

/**
 * It is a static error if the version number specified in a version
 * declaration is not supported by the implementation.
 */
XQUERY_DEC_ERROR( XQST0031 );

/**
 * A static error is raised if a Prolog contains more than one base URI
 * declaration.
 */
XQUERY_DEC_ERROR( XQST0032 );

/**
 * It is a static error if a module contains multiple bindings for the same
 * namespace prefix.
 */
XQUERY_DEC_ERROR( XQST0033 );

/**
 * It is a static error if multiple functions declared or imported by a module
 * have the same number of arguments and their expanded QNames are equal (as
 * defined by the eq operator).
 */
XQUERY_DEC_ERROR( XQST0034 );

/**
 * It is a static error to import two schema components that both define the
 * same name in the same symbol space and in the same scope.
 */
XQUERY_DEC_ERROR( XQST0035 );

/**
 * It is a static error to import a module if the in-scope schema definitions
 * of the importing module do not include all of the following:
 *
 * -# An in-scope schema type for each type-name that appears:
 *    - in the type of a variable that is declared in the imported module and
 *      referenced in the importing module, OR
 *    - in a parameter-type or result-type of a function that is declared in
 *      the imported module and referenced in the importing module.
 * -# An in-scope element declaration for each element-name \c EN such that:
 *    - \c schema-element(EN) appears in the declared type of a variable in the
 *      imported module, and that variable is referenced in the importing
 *      module, OR
 *    - \c schema-element(EN) appears in a parameter-type or result-type of a
 *      function declared in the imported module, and that function is
 *      referenced in the importing module.
 * -# An in-scope attribute declaration for each attribute-name \c AN such that:
 *    - \c schema-attribute(AN) appears in the declared type of a variable in
 *      the imported module, and that variable is referenced in the importing
 *      module, OR
 *    - \c schema-attribute(AN) appears in a parameter-type or result-type of a
 *      function declared in the imported module, and that function is
 *      referenced in the importing module.
 */
XQUERY_DEC_ERROR( XQST0036 );

/**
 * It is a static error if a Prolog contains more than one default collation
 * declaration, or the value specified by a default collation declaration is
 * not present in statically known collations.
 */
XQUERY_DEC_ERROR( XQST0038 );

/**
 * It is a static error for a function declaration to have more than one
 * parameter with the same name.
 */
XQUERY_DEC_ERROR( XQST0039 );

/**
 * It is a static error if the attributes specified by a direct element
 * constructor do not have distinct expanded QNames.
 */
XQUERY_DEC_ERROR( XQST0040 );

/**
 * It is a dynamic error if the value of the name expression in a computed
 * processing instruction constructor cannot be cast to the type \c xs:NCName.
 */
XQUERY_DEC_ERROR( XQDY0041 );

/**
 * It is a static error the node-name of a node constructed by a computed
 * attribute constructor has any of the following properties:
 * - Its namespace prefix is \c xmlns.
 * - It has no namespace prefix and its local name is \c xmlns.
 * - Its namespace URI is <code>http://www.w3.org/2000/xmlns/</code>.
 * - Its namespace prefix is \c xml and its namespace URI is not
 *   <code>http://www.w3.org/XML/1998/namespace</code>.
 * - Its namespace prefix is other than \c xml and its namespace URI is
 *   <code>http://www.w3.org/XML/1998/namespace</code>.
 */
XQUERY_DEC_ERROR( XQDY0044 );

/**
 * It is a static error if the function name in a function declaration is in
 * one of the following namespaces:
 * <code>http://www.w3.org/XML/1998/namespace</code>,
 * <code>http://www.w3.org/2001/XMLSchema</code>,
 * <code>http://www.w3.org/2001/XMLSchema-instance</code>,
 * <code>http://www.w3.org/2005/xpath-functions</code>.
 */
XQUERY_DEC_ERROR( XQST0045 );

/**
 * An implementation MAY raise a static error if the value of a URILiteral is
 * of nonzero length and is not in the lexical space of \c xs:anyURI.
 */
XQUERY_DEC_ERROR( XQST0046 );

/**
 * It is a static error if multiple module imports in the same Prolog specify
 * the same target namespace.
 */
XQUERY_DEC_ERROR( XQST0047 );

/**
 * It is a static error if a function or variable declared in a library module
 * is not in the target namespace of the library module.
 */
XQUERY_DEC_ERROR( XQST0048 );

/**
 * It is a static error if two or more variables declared or imported by a
 * module have equal expanded QNames (as defined by the eq operator.)
 */
XQUERY_DEC_ERROR( XQST0049 );

/**
 * It is a dynamic error if the dynamic type of the operand of a treat
 * expression does not match the sequence type specified by the treat
 * expression. This error might also be raised by a path expression beginning
 * with "<code>/</code>" or "<code>//</code>" if the context node is not in a
 * tree that is rooted at a document node. This is because a leading
 * "<code>/</code>" or "<code>//</code>" in a path expression is an
 * abbreviation for an initial step that includes the clause \c treat as \c
 * document-node().
 */
XQUERY_DEC_ERROR( XPDY0050 );

/**
 * It is a static error if a QName that is used as an AtomicType in a
 * SequenceType is not defined in the in-scope schema types as an atomic type.
 */
XQUERY_DEC_ERROR( XPST0051 );

/**
 * It is a static error if a variable depends on itself.
 */
XQUERY_DEC_ERROR( XQST0054 );

/**
 * It is a static error if a Prolog contains more than one copy-namespaces
 * declaration.
 */
XQUERY_DEC_ERROR( XQST0055 );

/**
 * It is a static error if a schema import binds a namespace prefix but does
 * not specify a target namespace other than a zero-length string.
 */
XQUERY_DEC_ERROR( XQST0057 );

/**
 * It is a static error if multiple schema imports specify the same target
 * namespace.
 */
XQUERY_DEC_ERROR( XQST0058 );

/**
 * It is a static error if an implementation is unable to process a schema or
 * module import by finding a schema or module with the specified target
 * namespace.
 */
XQUERY_DEC_ERROR( XQST0059 );

/**
 * It is a static error if the name of a function in a function declaration is
 * not in a namespace (expanded QName has a null namespace URI).
 */
XQUERY_DEC_ERROR( XQST0060 );

/**
 * It is a dynamic error if the operand of a validate expression is a document
 * node whose children do not consist of exactly one element node and zero or
 * more comment and processing instruction nodes, in any order.
 */
XQUERY_DEC_ERROR( XQDY0061 );

/**
 * It is a dynamic error if the value of the name expression in a computed
 * processing instruction constructor is equal to "XML" (in any combination of
 * upper and lower case).
 */
XQUERY_DEC_ERROR( XQDY0064 );

/**
 * A static error is raised if a Prolog contains more than one ordering mode
 * declaration.
 */
XQUERY_DEC_ERROR( XQST0065 );

/**
 * A static error is raised if a Prolog contains more than one default
 * element/type namespace declaration, or more than one default function
 * namespace declaration.
 */
XQUERY_DEC_ERROR( XQST0066 );

/**
 * A static error is raised if a Prolog contains more than one construction
 * declaration.
 */
XQUERY_DEC_ERROR( XQST0067 );

/**
 * A static error is raised if a Prolog contains more than one boundary-space
 * declaration.
 */
XQUERY_DEC_ERROR( XQST0068 );

/**
 * A static error is raised if a Prolog contains more than one empty order
 * declaration.
 */
XQUERY_DEC_ERROR( XQST0069 );

/**
 * A static error is raised if one of the predefined prefixes \c xml or \c
 * xmlns appears in a namespace declaration, or if any of the following
 * conditions is statically detected in any expression or declaration:
 * - The prefix \c xml is bound to some namespace URI other than
 *   <code>http://www.w3.org/XML/1998/namespace</code>.
 * - A prefix other than \c xml is bound to the namespace URI
 *   <code>http://www.w3.org/XML/1998/namespace</code>.
 * - The prefix \c xmlns is bound to any namespace URI.
 * - A prefix other than \c xmlns is bound to the namespace URI
 *   <code>http://www.w3.org/2000/xmlns/</code>.
 */
XQUERY_DEC_ERROR( XQST0070 );

/**
 * A static error is raised if the namespace declaration attributes of a direct
 * element constructor do not have distinct names.
 */
XQUERY_DEC_ERROR( XQST0071 );

/**
 * It is a dynamic error if the result of the content expression of a computed
 * comment constructor contains two adjacent hyphens or ends with a hyphen.
 */
XQUERY_DEC_ERROR( XQDY0072 );

/**
 * It is a dynamic error if the value of the name expression in a computed
 * element or attribute constructor cannot be converted to an expanded QName
 * (for example, because it contains a namespace prefix not found in statically
 * known namespaces.)
 */
XQUERY_DEC_ERROR( XQDY0074 );

/**
 * An implementation that does not support the Validation Feature must raise a
 * static error if it encounters a \c validate expression.
 */
XQUERY_DEC_ERROR( XQST0075 );

/**
 * It is a static error if a \c collation subclause in an order by clause of a
 * FLWOR expression does not identify a collation that is present in statically
 * known collations.
 */
XQUERY_DEC_ERROR( XQST0076 );

/**
 * It is a static error if an extension expression contains neither a pragma
 * that is recognized by the implementation nor an expression enclosed in curly
 * braces.
 */
XQUERY_DEC_ERROR( XQST0079 );

/**
 * It is a static error if the target type of a \c cast or \c castable
 * expression is \c xs:NOTATION or \c xs:anyAtomicType.
 */
XQUERY_DEC_ERROR( XPST0080 );

/**
 * It is a static error if a QName used in a query contains a namespace prefix
 * that cannot be expanded into a namespace URI by using the statically known
 * namespaces.
 */
XQUERY_DEC_ERROR( XPST0081 );

/**
 * It is a static error if the target type of a \c cast expression or
 * constructor function is \c xs:QName or a type derived from \c xs:QName or \c
 * xs:NOTATION, and the argument of the cast expression or constructor function
 * is not a string literal.
 */
XQUERY_DEC_ERROR( XPST0083 );

/**
 * It is a dynamic error if the element validated by a \c validate statement
 * does not have a top-level element declaration in the in-scope element
 * declarations, if validation mode is \c strict.
 */
XQUERY_DEC_ERROR( XQDY0084 );

/**
 * It is a static error if the namespace URI in a namespace declaration
 * attribute is a zero-length string, and the implementation does not support
 * [XML Names 1.1].
 */
XQUERY_DEC_ERROR( XQST0085 );

/**
 * It is a type error if the typed value of a copied element or attribute node
 * is namespace-sensitive when construction mode is \c preserve and
 * copy-namespaces mode is \c no-preserve.
 */
XQUERY_DEC_ERROR( XQTY0086 );

/**
 * It is a static error if the encoding specified in a Version Declaration does
 * not conform to the definition of \c EncName specified in [XML 1.0]
 */
XQUERY_DEC_ERROR( XQST0087 );

/**
 * It is a static error if the literal that specifies the target namespace in a
 * module import or a module declaration is of zero length.
 */
XQUERY_DEC_ERROR( XQST0088 );

/**
 * It is a static error if a variable bound in a \c for or \c window clause of
 * a FLWOR expression, and its associated positional variable, do not have
 * distinct names (expanded QNames).
 */
XQUERY_DEC_ERROR( XQST0089 );

/**
 * It is a static error if a character reference does not identify a valid
 * character in the version of XML that is in use.
 */
XQUERY_DEC_ERROR( XQST0090 );

/**
 * An implementation MAY raise a dynamic error if an \c xml:id error, as
 * defined in [XML ID], is encountered during construction of an attribute
 * named \c xml:id.
 */
XQUERY_DEC_ERROR( XQDY0091 );

/**
 * An implementation MAY raise a dynamic error if a constructed attribute named
 * \c xml:space has a value other than \c preserve or \c default.
 */
XQUERY_DEC_ERROR( XQDY0092 );

/**
 * It is a static error to import a module M1 if there exists a sequence of
 * modules M1 ... Mi ... M1 such that each module directly depends on the next
 * module in the sequence (informally, if M1 depends on itself through some
 * chain of module dependencies.)
 */
XQUERY_DEC_ERROR( XQST0093 );

/**
 * It is a dynamic error the node-name of a node constructed by a computed
 * element constructor has any of the following properties:
 * - Its namespace prefix is \c xmlns.
 * - Its namespace URI is <code>http://www.w3.org/2000/xmlns/</code>.
 * - Its namespace prefix is \c xml and its namespace URI is not
 *   <code>http://www.w3.org/XML/1998/namespace</code>.
 * - Its namespace prefix is other than \c xml and its namespace URI is
 *   <code>http://www.w3.org/XML/1998/namespace</code>.
 */
XQUERY_DEC_ERROR( XQDY0096 );

/**
 * It is a static error for a decimal-format to specify a value that is not
 * legal for a given property, as described in statically known decimal
 * formats.
 */
XQUERY_DEC_ERROR( XQST0097 );

/**
 * It is a static error if, for any named or unnamed decimal format, the
 * properties representing characters used in a picture string do not each have
 * distinct values. These properties are decimal-separator-sign,
 * grouping-separator, percent-sign, per-mille-sign, zero-digit, digit-sign,
 * and pattern-separator-sign.
 */
XQUERY_DEC_ERROR( XQST0098 );

/**
 * It is a static error if a function's annotations contain more than one
 * annotation named \c private or \c public.  It is a static error if a
 * function's annotations contain more than one annotation named \c
 * deterministic or \c nondeterministic.
 */
XQUERY_DEC_ERROR( XQST0106 );

/**
 * It is a static error for a query prolog to contain two decimal formats with
 * the same name, or to contain two default decimal formats.
 */
XQUERY_DEC_ERROR( XQST0111 );

////////// XQuery Full-Text Errors ////////////////////////////////////////////

#ifndef XQUERY_NO_FULL_TEXT

/**
 * It is a static error if, during the static analysis phase, the query is
 * found to contain a stop word option that refers to a stop word list that is
 * not found in the statically known stop word lists.
 */
XQUERY_DEC_ERROR( FTST0008 );

/**
 * It may be a static error if, during the static analysis phase, the query is
 * found to contain a language identifier in a language option that the
 * implementation does not support. The implementation may choose not to raise
 * this error and instead provide some other implementation-defined behavior.
 */
XQUERY_DEC_ERROR( FTST0009 );

/**
 * It is a dynamic error if a weight value is not within the required range of
 * values; it is also a dynamic error if an implementation that does not
 * support negative weights encounters a negative weight value.
 */
XQUERY_DEC_ERROR( FTDY0016 );

/**
 * It is a dynamic error if an implementation encounters a mild not selection,
 * one of whose operands evaluates to an AllMatches that contains a
 * StringExclude.
 */
XQUERY_DEC_ERROR( FTDY0017 );

/**
 * It is a static error if, during the static analysis phase, the query is
 * found to contain a thesaurus option that refers to a thesaurus that is not
 * found in the statically known thesauri.
 */
XQUERY_DEC_ERROR( FTST0018 );

/**
 * It is a static error if, within a single FTMatchOptions, there is more than
 * one match option of any given match option group.
 */
XQUERY_DEC_ERROR( FTST0019 );

/**
 * It is a dynamic error if, when "wildcards" is in effect, a query string
 * violates wildcard syntax.
 */
XQUERY_DEC_ERROR( FTDY0020 );

#endif /* XQUERY_NO_FULL_TEXT */

////////// XQuery Functions & Operators Errors ////////////////////////////////

/**
 * Unidentified error.
 */
XQUERY_DEC_ERROR( FOER0000 );

/**
 * Division by zero.
 */
XQUERY_DEC_ERROR( FOAR0001 );

/**
 * Numeric operation overflow/underflow.
 */
XQUERY_DEC_ERROR( FOAR0002 );

/**
 * Input value too large for decimal.
 */
XQUERY_DEC_ERROR( FOCA0001 );

/**
 * Invalid lexical value.
 */
XQUERY_DEC_ERROR( FOCA0002 );

/**
 * Input value too large for integer.
 */
XQUERY_DEC_ERROR( FOCA0003 );

/**
 * NaN supplied as float/double value.
 */
XQUERY_DEC_ERROR( FOCA0005 );

/**
 * String to be cast to decimal has too many digits of precision.
 */
XQUERY_DEC_ERROR( FOCA0006 );

/**
 * Code point not valid.
 */
XQUERY_DEC_ERROR( FOCH0001 );

/**
 * Unsupported collation.
 */
XQUERY_DEC_ERROR( FOCH0002 );

/**
 * Unsupported normalization form.
 */
XQUERY_DEC_ERROR( FOCH0003 );

/**
 * Collation does not support collation units.
 */
XQUERY_DEC_ERROR( FOCH0004 );

/**
 * No context document.
 */
XQUERY_DEC_ERROR( FODC0001 );

/**
 * Error retrieving resource.
 */
XQUERY_DEC_ERROR( FODC0002 );

/**
 * Function stability not defined.
 */
XQUERY_DEC_ERROR( FODC0003 );

/**
 * Invalid argument to <code>fn:collection</code>.
 */
XQUERY_DEC_ERROR( FODC0004 );

/**
 * Invalid argument to <code>fn:doc</code> or <code>fn:doc-available</code>.
 */
XQUERY_DEC_ERROR( FODC0005 );

/**
 * Invalid content passed to <code>fn:parse()</code>.
 */
XQUERY_DEC_ERROR( FODC0006 );

/**
 * Base URI passed to <code>fn:parse()</code> is not a valid absolute URI.
 */
XQUERY_DEC_ERROR( FODC0007 );

/**
 * Invalid decimal format name supplied to <code>fn:format-number()</code>.
 */
XQUERY_DEC_ERROR( FODF1280 );

/**
 * Invalid <code>fn:format-number()</code> picture string.
 */
XQUERY_DEC_ERROR( FODF1310 );

/**
 * Overflow/underflow in date/time operation.
 */
XQUERY_DEC_ERROR( FODT0001 );

/**
 * Overflow/underflow in duration operation.
 */
XQUERY_DEC_ERROR( FODT0002 );

/**
 * Invalid timezone value.
 */
XQUERY_DEC_ERROR( FODT0003 );

/**
 * No namespace found for prefix.
 */
XQUERY_DEC_ERROR( FONS0004 );

/**
 * Base-URI not defined in the static context.
 */
XQUERY_DEC_ERROR( FONS0005 );

/**
 * Invalid value for cast/constructor.
 */
XQUERY_DEC_ERROR( FORG0001 );

/**
 * Invalid argument to <code>fn:resolve-uri()</code>.
 */
XQUERY_DEC_ERROR( FORG0002 );

/**
 * <code>fn:zero-or-one</code> called with a sequence containing more than one
 * item.
 */
XQUERY_DEC_ERROR( FORG0003 );

/**
 * <code>fn:one-or-more</code> called with a sequence containing no items.
 */
XQUERY_DEC_ERROR( FORG0004 );

/**
 * <code>fn:exactly-one</code> called with a sequence containing zero or more
 * than one item.
 */
XQUERY_DEC_ERROR( FORG0005 );

/**
 * Invalid argument type.
 */
XQUERY_DEC_ERROR( FORG0006 );

/**
 * The two arguments to fn:dateTime have inconsistent timezones.
 */
XQUERY_DEC_ERROR( FORG0008 );

/**
 * Error in resolving a relative URI against a base URI in
 * <code>fn:resolve-uri</code>.
 */
XQUERY_DEC_ERROR( FORG0009 );

/**
 * Invalid regular expression flags.
 */
XQUERY_DEC_ERROR( FORX0001 );

/**
 * Invalid regular expression.
 */
XQUERY_DEC_ERROR( FORX0002 );

/**
 * Regular expression matches zero-length string.
 */
XQUERY_DEC_ERROR( FORX0003 );

/**
 * Invalid replacement string.
 */
XQUERY_DEC_ERROR( FORX0004 );

/**
 * Argument node does not have a typed value.
 */
XQUERY_DEC_ERROR( FOTY0012 );

/**
 * An argument to <code>fn:data()</code> contains a node that does not have a
 * typed value.
 */
XQUERY_DEC_ERROR( FOTY0013 );

/**
 * The argument to <code>fn:string()</code> is a function item.
 */
XQUERY_DEC_ERROR( FOTY0014 );

/**
 * An argument to <code>fn:deep-equal()</code> contains a function item.
 */
XQUERY_DEC_ERROR( FOTY0015 );

////////// XQuery Update Facility /////////////////////////////////////////////

XQUERY_DEC_ERROR( XUST0001 );
XQUERY_DEC_ERROR( XUST0002 );
XQUERY_DEC_ERROR( XUST0003 );
XQUERY_DEC_ERROR( XUTY0004 );
XQUERY_DEC_ERROR( XUTY0005 );
XQUERY_DEC_ERROR( XUTY0006 );
XQUERY_DEC_ERROR( XUTY0007 );
XQUERY_DEC_ERROR( XUTY0008 );
XQUERY_DEC_ERROR( XUDY0009 );
XQUERY_DEC_ERROR( XUTY0010 );
XQUERY_DEC_ERROR( XUTY0011 );
XQUERY_DEC_ERROR( XUTY0012 );
XQUERY_DEC_ERROR( XUTY0013 );
XQUERY_DEC_ERROR( XUDY0014 );
XQUERY_DEC_ERROR( XUDY0015 );
XQUERY_DEC_ERROR( XUDY0016 );
XQUERY_DEC_ERROR( XUDY0017 );
XQUERY_DEC_ERROR( XUDY0018 );
XQUERY_DEC_ERROR( XUDY0019 );
XQUERY_DEC_ERROR( XUDY0020 );
XQUERY_DEC_ERROR( XUDY0021 );
XQUERY_DEC_ERROR( XUTY0022 );
XQUERY_DEC_ERROR( XUDY0023 );
XQUERY_DEC_ERROR( XUDY0024 );
XQUERY_DEC_ERROR( XUDY0025 );
XQUERY_DEC_ERROR( XUST0026 );
XQUERY_DEC_ERROR( XUDY0027 );
XQUERY_DEC_ERROR( XUST0028 );
XQUERY_DEC_ERROR( XUDY0029 );
XQUERY_DEC_ERROR( XUDY0030 );
XQUERY_DEC_ERROR( XUDY0031 );
XQUERY_DEC_ERROR( FOUP0001 );
XQUERY_DEC_ERROR( FOUP0002 );

////////// Serialization //////////////////////////////////////////////////////

/**
 * It is an error if an item in S6 in sequence normalization is an attribute
 * node or a namespace node.
 */
XQUERY_DEC_ERROR( SENR0001 );

/**
 * It is an error if the serializer is unable to satisfy the rules for either a
 * well-formed XML document entity or a well-formed XML external general parsed
 * entity, or both, except for content modified by the character expansion
 * phase of serialization.
 */
XQUERY_DEC_ERROR( SERE0003 );

/**
 * It is an error to specify the doctype-system parameter, or to specify the
 * standalone parameter with a value other than omit, if the instance of the
 * data model contains text nodes or multiple element nodes as children of the
 * root node.
 */
XQUERY_DEC_ERROR( SEPM0004 );

/**
 * It is an error if the serialized result would contain an NCName Names that
 * contains a character that is not permitted by the version of Namespaces in
 * XML specified by the version parameter.
 */
XQUERY_DEC_ERROR( SERE0005 );

/**
 * It is an error if the serialized result would contain a character that is
 * not permitted by the version of XML specified by the version parameter.
 */
XQUERY_DEC_ERROR( SERE0006 );

/**
 * It is an error if an output encoding other than UTF-8 or UTF-16 is requested
 * and the serializer does not support that encoding.
 */
XQUERY_DEC_ERROR( SESU0007 );

/**
 * It is an error if a character that cannot be represented in the encoding
 * that the serializer is using for output appears in a context where character
 * references are not allowed (for example if the character occurs in the name
 * of an element).
 */
XQUERY_DEC_ERROR( SERE0008 );

/**
 * It is an error if the omit-xml-declaration parameter has the value yes, and
 * the standalone attribute has a value other than omit; or the version
 * parameter has a value other than 1.0 and the doctype-system parameter is
 * specified.
 */
XQUERY_DEC_ERROR( SEPM0009 );

/**
 * It is an error if the output method is xml, the value of the
 * undeclare-prefixes parameter is yes, and the value of the version parameter
 * is 1.0.
 */
XQUERY_DEC_ERROR( SEPM0010 );

/**
 * It is an error if the value of the normalization-form parameter specifies a
 * normalization form that is not supported by the serializer.
 */
XQUERY_DEC_ERROR( SESU0011 );

/**
 * It is an error if the value of the normalization-form parameter is
 * fully-normalized and any relevant construct of the result begins with a
 * combining character.
 */
XQUERY_DEC_ERROR( SERE0012 );

/**
 * It is an error if the serializer does not support the version of XML or HTML
 * specified by the version parameter.
 */
XQUERY_DEC_ERROR( SESU0013 );

/**
 * It is an error to use the HTML output method when characters which are legal
 * in XML but not in HTML, specifically the control characters #x7F-#x9F,
 * appear in the instance of the data model.
 */
XQUERY_DEC_ERROR( SERE0014 );

/**
 * It is an error to use the HTML output method when \c > appears within a
 * processing instruction in the data model instance being serialized.
 */
XQUERY_DEC_ERROR( SERE0015 );

/**
 * It is a an error if a parameter value is invalid for the defined domain.
 */
XQUERY_DEC_ERROR( SEPM0016 );

/**
 * It is a non-recoverable dynamic error if the picture string does not satisfy
 * the format-number function rules.
 */
XQUERY_DEC_ERROR( XTDE1310 );

/**
 * It is a non-recoverable dynamic error if the syntax of the picture is
 * incorrect.
 */
XQUERY_DEC_ERROR( XTDE1340 );

/**
 * It is a non-recoverable dynamic error if a component specifier within the
 * picture refers to components that are not available in the given type of
 * <code>$value</code>.
 */
XQUERY_DEC_ERROR( XTDE1350 );

////////// Zorba Errors ///////////////////////////////////////////////////////

#define ZORBA_DEC_ERROR(ERR)  extern ZORBA_DLL_PUBLIC ZorbaError ERR

ZORBA_DEC_ERROR( XQP0000_NO_ERROR );
ZORBA_DEC_ERROR( XQP0001_DYNAMIC_RUNTIME_ERROR );
ZORBA_DEC_ERROR( XQP0002_DYNAMIC_ITERATOR_OVERRUN );
ZORBA_DEC_ERROR( XQP0003_DYNAMIC_ILLEGAL_NODE_CHILD );
ZORBA_DEC_ERROR( XQP0004_DYNAMIC_TARGET_NAMESPACE_NOT_FOUND );
ZORBA_DEC_ERROR( XQP0005_SYSTEM_NOT_SUPPORTED );
ZORBA_DEC_ERROR( XQP0006_SYSTEM_ASSERT_FAILED );
ZORBA_DEC_ERROR( XQP0007_SYSTEM_HASH_ERROR_KEYLEN_EXCEEDS_MAXKEYLEN );
ZORBA_DEC_ERROR( XQP0008_SYSTEM_VECTOR_OUT_OF_RANGE );
ZORBA_DEC_ERROR( XQP0009_SYSTEM_READ_LOCK_FAILED );
ZORBA_DEC_ERROR( XQP0010_SYSTEM_WRITE_LOCK_FAILED );
ZORBA_DEC_ERROR( XQP0011_SYSTEM_POP_FROM_EMPTY_LIST );
ZORBA_DEC_ERROR( XQP0012_SYSTEM_FILE_ERROR_IN_FUNCTION );
ZORBA_DEC_ERROR( XQP0013_SYSTEM_FXCHARHEAP_IOEXCEPTION );
ZORBA_DEC_ERROR( XQP0014_SYSTEM_MMFILE_IOEXCEPTION );
ZORBA_DEC_ERROR( XQP0015_SYSTEM_NOT_YET_IMPLEMENTED );
ZORBA_DEC_ERROR( XQP0016_RESERVED_MODULE_TARGET_NAMESPACE );
ZORBA_DEC_ERROR( XQP0017_FILE_ACCESS_DISABLED );
ZORBA_DEC_ERROR( XQP0019_INTERNAL_ERROR );
ZORBA_DEC_ERROR( XQP0020_INVALID_URI );
ZORBA_DEC_ERROR( XQP0021_USER_ERROR );
ZORBA_DEC_ERROR( XQP0022_GET_RESULTS_AS_DOM_FAILED );
ZORBA_DEC_ERROR( XQP0023_GET_RESULTS_AS_SAX_FAILED );
ZORBA_DEC_ERROR( XQP0024_XML_DOES_NOT_MATCH_SCHEMA );
ZORBA_DEC_ERROR( XQP0025_COULD_NOT_CREATE_ITEM );
ZORBA_DEC_ERROR( XQP0026_COULD_NOT_CREATE_THREAD );
ZORBA_DEC_ERROR( XQP0026_CANNOT_INIT_STORE );
ZORBA_DEC_ERROR( XQP0027_MS_DOM_ERROR );
ZORBA_DEC_ERROR( XQP0028_FUNCTION_IMPL_NOT_FOUND );
ZORBA_DEC_ERROR( XQP0029_MODULE_IMPORT_NOT_ALLOWED );
ZORBA_DEC_ERROR( XQP0030_DEADLOCK );
ZORBA_DEC_ERROR( XQP0031_MALFORMED_XQUERYX_INPUT );
ZORBA_DEC_ERROR( XQP0032_ERROR_TRANSFORMING_XQUERYX_TO_XQUERY );
ZORBA_DEC_ERROR( XQP0034_ILLEGAL_UTF8_BYTE );
ZORBA_DEC_ERROR( XQP0035_ILLEGAL_UTF16_BYTE );
ZORBA_DEC_ERROR( XQP0036_BREAKITERATOR_CREATION_FAILED );

#ifndef ZORBA_NO_FULL_TEXT
ZORBA_DEC_ERROR( XQP8401_THESAURUS_VERSION_MISMATCH );
ZORBA_DEC_ERROR( XQP8402_THESAURUS_DATA_ERROR );
#endif /* ZORBA_NO_FULL_TEXT */

ZORBA_DEC_ERROR( XQD0000_PREFIX_NOT_DECLARED );
ZORBA_DEC_ERROR( XQD0001_DOCUMENT_NOT_VALID );

////////// Zorba API Errors ///////////////////////////////////////////////////

ZORBA_DEC_ERROR( API0001_XQUERY_STRING_IS_EMPTY );
ZORBA_DEC_ERROR( API0002_XQUERY_COMPILATION_FAILED );
ZORBA_DEC_ERROR( API0003_XQUERY_NOT_COMPILED );
ZORBA_DEC_ERROR( API0004_XQUERY_ALREADY_COMPILED );
ZORBA_DEC_ERROR( API0005_XQUERY_ALREADY_EXECUTING );
ZORBA_DEC_ERROR( API0006_XQUERY_ALREADY_CLOSED );
ZORBA_DEC_ERROR( API0007_CANNOT_SERIALIZE_PUL );
ZORBA_DEC_ERROR( API0008_NOT_AN_UPDATE_XQUERY );
ZORBA_DEC_ERROR( API0009_XQUERY_NOT_COMPILED_IN_DEBUG_MODE );
ZORBA_DEC_ERROR( API0010_THREAD_NOT_INITIALIZED );
ZORBA_DEC_ERROR( API0010_XQUERY_HAS_ITERATOR_ALREADY );
ZORBA_DEC_ERROR( API0011_INVALID_VARIABLE_QNAME );
ZORBA_DEC_ERROR( API0012_INVALID_INDEX );
ZORBA_DEC_ERROR( API0013_INAPPROPRIATE_VARIABLE_VALUE );
ZORBA_DEC_ERROR( API0014_INVALID_ARGUMENT );
ZORBA_DEC_ERROR( API0015_CANNOT_OPEN_FILE );
ZORBA_DEC_ERROR( API0016_CANNOT_CREATE_COLLECTION );
ZORBA_DEC_ERROR( API0017_CANNOT_LOAD_DOCUMENT );
ZORBA_DEC_ERROR( API0018_CANNOT_ACCESS_FILE );
ZORBA_DEC_ERROR( API0019_FUNCTION_ALREADY_REGISTERED );
ZORBA_DEC_ERROR( API0020_DOCUMENT_ALREADY_EXISTS );
ZORBA_DEC_ERROR( API0021_ITEM_TO_LOAD_IS_NOT_NODE );
ZORBA_DEC_ERROR( API0022_NOT_PLAIN_FILE );
ZORBA_DEC_ERROR( API0025_END_OF_SEQUENCE );
ZORBA_DEC_ERROR( API0027_CANNOT_UPDATE_DCTX_WITH_ITERATORS );
ZORBA_DEC_ERROR( API0028_INVALID_NODE_URI );
ZORBA_DEC_ERROR( API0030_NO_NODE_AT_GIVEN_POSITION );
ZORBA_DEC_ERROR( API0033_FILE_OR_FOLDER_DOES_NOT_EXIST );
ZORBA_DEC_ERROR( API0034_FILE_OR_FOLDER_CANNOT_BE_OPENED );
ZORBA_DEC_ERROR( API0035_COLLECTION_CANNOT_BE_SERIALIZED );
ZORBA_DEC_ERROR( API0040_ITERATOR_IS_NOT_OPEN );
ZORBA_DEC_ERROR( API0041_ITERATOR_IS_OPEN_ALREADY );
ZORBA_DEC_ERROR( API0042_ITERATOR_QUERY_IS_CLOSED );
ZORBA_DEC_ERROR( API0050_REST_ERROR_HEADER );
ZORBA_DEC_ERROR( API0051_REST_ERROR_PAYLOAD );
ZORBA_DEC_ERROR( API0060_CONV_JSON_PARSE );
ZORBA_DEC_ERROR( API0061_CONV_JSON_SERIALIZE );
ZORBA_DEC_ERROR( API0062_CONV_JSON_PARAM );
ZORBA_DEC_ERROR( API0063_CONV_JSON_ML_PARSE );
ZORBA_DEC_ERROR( API0064_CONV_JSON_ML_SERIALIZE );
ZORBA_DEC_ERROR( API0065_CONV_JSON_ML_PARAM );
ZORBA_DEC_ERROR( API0066_JSON_SEQUENCE_CANNOT_BE_SERIALIZED );
ZORBA_DEC_ERROR( API0070_INVALID_SERIALIZATION_METHOD_FOR_SAX );

////////// Zorba Class Serialization Errors ///////////////////////////////////

ZORBA_DEC_ERROR( SRL0001_INEXISTENT_INPUT_FIELD );
ZORBA_DEC_ERROR( SRL0002_INCOMPATIBLE_INPUT_FIELD );
ZORBA_DEC_ERROR( SRL0003_UNRECOGNIZED_CLASS_FIELD );
ZORBA_DEC_ERROR( SRL0004_UNRESOLVED_FIELD_REFERENCE );
ZORBA_DEC_ERROR( SRL0005_CLASS_VERSION_IS_TOO_NEW );
ZORBA_DEC_ERROR( SRL0006_CLASS_VERSION_IS_TOO_OLD );
ZORBA_DEC_ERROR( SRL0007_INPUT_ARCHIVE_USED_FOR_OUT_SERIALIZATION );
ZORBA_DEC_ERROR( SRL0008_OUTPUT_ARCHIVE_USED_FOR_IN_SERIALIZATION );
ZORBA_DEC_ERROR( SRL0009_CLASS_NOT_SERIALIZABLE );
ZORBA_DEC_ERROR( SRL0010_ITEM_TYPE_NOT_SERIALIZABLE );
ZORBA_DEC_ERROR( SRL0011_INPUT_ARCHIVE_NOT_ZORBA_ARCHIVE );
ZORBA_DEC_ERROR( SRL0012_INCOMPATIBLE_ARCHIVE_VERSION );
ZORBA_DEC_ERROR( SRL0013_UNABLE_TO_LOAD_QUERY );
ZORBA_DEC_ERROR( SRL0014_INFINITE_CIRCULAR_DEPENDENCIES );
ZORBA_DEC_ERROR( SRL0015_INCOMPATIBLE_BETWEEN_32_AND_64_BITS_OR_LE_AND_BE );

////////// Store Errors ///////////////////////////////////////////////////////

ZORBA_DEC_ERROR( STR0001_INDEX_ALREADY_EXISTS );
ZORBA_DEC_ERROR( STR0002_INDEX_DOES_NOT_EXIST );
ZORBA_DEC_ERROR( STR0003_INDEX_PARTIAL_KEY_INSERT );
ZORBA_DEC_ERROR( STR0004_INDEX_PARTIAL_KEY_REMOVE );
ZORBA_DEC_ERROR( STR0005_INDEX_PARTIAL_KEY_PROBE );
ZORBA_DEC_ERROR( STR0006_INDEX_INVALID_BOX_PROBE );
ZORBA_DEC_ERROR( STR0007_INDEX_UNSUPPORTED_PROBE_CONDITION );
ZORBA_DEC_ERROR( STR0008_COLLECTION_ALREADY_EXISTS );
ZORBA_DEC_ERROR( STR0009_COLLECTION_NOT_FOUND );
ZORBA_DEC_ERROR( STR0010_COLLECTION_NODE_ALREADY_IN_COLLECTION );
ZORBA_DEC_ERROR( STR0011_COLLECTION_NON_ROOT_NODE );
ZORBA_DEC_ERROR( STR0012_COLLECTION_ITEM_MUST_BE_A_NODE );
ZORBA_DEC_ERROR( STR0015_IC_ALREADY_EXISTS );
ZORBA_DEC_ERROR( STR0016_IC_DOES_NOT_EXIST );
ZORBA_DEC_ERROR( STR0020_LOADER_IO_ERROR );
ZORBA_DEC_ERROR( STR0021_LOADER_PARSING_ERROR );
ZORBA_DEC_ERROR( STR0030_NODEID_ERROR );
ZORBA_DEC_ERROR( STR0040_TYPE_ERROR );
ZORBA_DEC_ERROR( STR0041_NAN_COMPARISON );
ZORBA_DEC_ERROR( STR0045_DUPLICATE_NODE_ERROR );
ZORBA_DEC_ERROR( STR0050_FUNCTION_NOT_IMPLEMENTED_FOR_ITEMTYPE );

////////// Data Definition Facility Errors ////////////////////////////////////

ZORBA_DEC_ERROR( XDST0001_COLLECTION_ALREADY_DECLARED );
ZORBA_DEC_ERROR( XDST0002_COLLECTION_ALREADY_IMPORTED );
ZORBA_DEC_ERROR( XDST0003_COLLECTION_DECL_IN_MAIN_MODULE );
ZORBA_DEC_ERROR( XDST0004_COLLECTION_MULTIPLE_PROPERTY_VALUES );
ZORBA_DEC_ERROR( XDST0005_COLLECTION_PROPERTIES_CONFLICT );
ZORBA_DEC_ERROR( XDST0006_COLLECTION_INVALID_PROPERTY_VALUE );
ZORBA_DEC_ERROR( XDST0007_COLLECTION_DECL_IN_FOREIGN_MODULE );
ZORBA_DEC_ERROR( XDST0021_INDEX_ALREADY_DECLARED );
ZORBA_DEC_ERROR( XDST0022_INDEX_ALREADY_IMPORTED );
ZORBA_DEC_ERROR( XDST0023_INDEX_DECL_IN_MAIN_MODULE );
ZORBA_DEC_ERROR( XDST0024_INDEX_MULTIPLE_PROPERTY_VALUES );
ZORBA_DEC_ERROR( XDST0025_INDEX_PROPERTIES_CONFLICT );
ZORBA_DEC_ERROR( XDST0026_INDEX_INVALID_PROPERTY_VALUE );
ZORBA_DEC_ERROR( XDST0027_INDEX_BAD_KEY_TYPE );
ZORBA_DEC_ERROR( XDST0028_INDEX_NOT_DETERMINISTIC );
ZORBA_DEC_ERROR( XDST0029_INDEX_INVALID_DATA_SOURCE );
ZORBA_DEC_ERROR( XDST0030_INDEX_NON_CONST_DATA_SOURCE );
ZORBA_DEC_ERROR( XDST0031_INDEX_HAS_FREE_VARS );
ZORBA_DEC_ERROR( XDST0032_INDEX_REFERENCES_CTX_ITEM );
ZORBA_DEC_ERROR( XDST0033_INDEX_NON_SIMPLE_EXPR );
ZORBA_DEC_ERROR( XDST0034_INDEX_CANNOT_DO_AUTOMATIC_MAINTENANCE );
ZORBA_DEC_ERROR( XDST0035_INDEX_GENERAL_MULTIKEY );
ZORBA_DEC_ERROR( XDST0036_INDEX_DECL_IN_FOREIGN_MODULE );
ZORBA_DEC_ERROR( XDST0041_IC_IS_ALREADY_DECLARED );
ZORBA_DEC_ERROR( XDST0042_MULTI_VALUED_IC_KEY );
ZORBA_DEC_ERROR( XDST0043_NON_ATOMIC_IC_KEY );
ZORBA_DEC_ERROR( XDST0044_IC_DECL_IN_MAIN_MODULE );
ZORBA_DEC_ERROR( XDST0045_IC_HAS_FREE_VARS );
ZORBA_DEC_ERROR( XDST0046_IC_HAS_INVALID_DATA_SOURCE );
ZORBA_DEC_ERROR( XDST0047_IC_NOT_DETERMINISTIC );
ZORBA_DEC_ERROR( XDST0048_IC_DECL_IN_FOREIGN_MODULE );

ZORBA_DEC_ERROR( XDTY0001_COLLECTION_INVALID_NODE_TYPE );
ZORBA_DEC_ERROR( XDTY0010_INDEX_DOMAIN_TYPE_ERROR );
ZORBA_DEC_ERROR( XDTY0011_INDEX_KEY_TYPE_ERROR );
ZORBA_DEC_ERROR( XDTY0012_INDEX_KEY_TYPE_ERROR );

ZORBA_DEC_ERROR( XDDY0001_COLLECTION_NOT_DECLARED );
ZORBA_DEC_ERROR( XDDY0002_COLLECTION_EXISTS_ALREADY );
ZORBA_DEC_ERROR( XDDY0003_COLLECTION_DOES_NOT_EXIST );
ZORBA_DEC_ERROR( XDDY0004_COLLECTION_CONST_UPDATE );
ZORBA_DEC_ERROR( XDDY0005_COLLECTION_APPEND_BAD_INSERT );
ZORBA_DEC_ERROR( XDDY0006_COLLECTION_QUEUE_BAD_INSERT );
ZORBA_DEC_ERROR( XDDY0007_COLLECTION_APPEND_BAD_DELETE );
ZORBA_DEC_ERROR( XDDY0008_COLLECTION_QUEUE_BAD_DELETE );
ZORBA_DEC_ERROR( XDDY0009_COLLECTION_QUEUE_BAD_DELETE );
ZORBA_DEC_ERROR( XDDY0010_COLLECTION_CONST_NODE_UPDATE );
ZORBA_DEC_ERROR( XDDY0011_COLLECTION_NODE_NOT_FOUND );
ZORBA_DEC_ERROR( XDDY0012_COLLECTION_UNORDERED_BAD_INSERT );
ZORBA_DEC_ERROR( XDDY0013_COLLECTION_BAD_DESTROY_INDEXES );
ZORBA_DEC_ERROR( XDDY0014_COLLECTION_BAD_DESTROY_ICS );
ZORBA_DEC_ERROR( XDDY0015_COLLECTION_BAD_DESTROY_NODES );
ZORBA_DEC_ERROR( XDDY0016_COLLECTION_MULTIPLE_CREATES );
ZORBA_DEC_ERROR( XDDY0020_INDEX_DOMAIN_NODE_NOT_IN_COLLECTION );
ZORBA_DEC_ERROR( XDDY0021_INDEX_IS_NOT_DECLARED );
ZORBA_DEC_ERROR( XDDY0022_INDEX_EXISTS_ALREADY );
ZORBA_DEC_ERROR( XDDY0023_INDEX_DOES_NOT_EXIST );
ZORBA_DEC_ERROR( XDDY0024_INDEX_UNIQUE_VIOLATION );
ZORBA_DEC_ERROR( XDDY0025_INDEX_WRONG_NUMBER_OF_PROBE_ARGS );
ZORBA_DEC_ERROR( XDDY0026_INDEX_RANGE_PROBE_NOT_ALLOWED );
ZORBA_DEC_ERROR( XDDY0027_INDEX_MULTIPLE_CREATES );
ZORBA_DEC_ERROR( XDDY0028_INDEX_DOMAIN_HAS_DUPLICATE_NODES );
ZORBA_DEC_ERROR( XDDY0029_INDEX_GENERAL_PROBE_NOT_ALLOWED );
ZORBA_DEC_ERROR( XDDY0031_IC_IS_NOT_DECLARED );
ZORBA_DEC_ERROR( XDDY0032_IC_IS_NOT_ACTIVATED );
ZORBA_DEC_ERROR( XDDY0033_IC_NOT_MET );

///////////////////////////////////////////////////////////////////////////////

#undef XQUERY_DEC_ERROR
#undef ZORBA_DEC_ERROR

} // namespace err
} // namespace zorba
#endif /* ZORBA_ERROR_LIST_API_H */
/* vim:set et sw=2 ts=2: */