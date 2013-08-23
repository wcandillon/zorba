jsoniq version "1.0";

(:
 : Copyright 2006-2011 The FLWOR Foundation.
 :
 : Licensed under the Apache License, Version 2.0 (the "License");
 : you may not use this file except in compliance with the License.
 : You may obtain a copy of the License at
 :
 : http://www.apache.org/licenses/LICENSE-2.0
 :
 : Unless required by applicable law or agreed to in writing, software
 : distributed under the License is distributed on an "AS IS" BASIS,
 : WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 : See the License for the specific language governing permissions and
 : limitations under the License.
 :)

(:===========================================================================:)

(:~
 : This module provides an API for parsing and serializing CSV (comma-separated
 : values) files.
 : See RFC 4180,
 : "Common Format and MIME Type for Comma-Separated Values (CSV) Files."
 : @project Zorba/CSV
 :)

module namespace csv = "http://zorba.io/modules/csv";

declare namespace err = "http://www.w3.org/2005/xqt-errors";
declare namespace zerr = "http://zorba.io/errors";

declare namespace ver = "http://zorba.io/options/versioning";
declare option ver:module-version "1.0";

(:===========================================================================:)

(:~
 : Parses a CSV (comma-separated values) string using the given options.
 : A newline (U+000A), optionally preceeded by a carriage-return (U+000D),
 : terminates lines, aka, "records."
 :
 : Quoted values are always considered strings;
 : unquoted values are attempted to be cast in the following order:
 : integer, decimal, double, or boolean.
 : In addition to the "normal" values of
 : <code>true</code> and <code>false</code> for boolean,
 : <code>T</code> and <code>Y</code> are also considered "true"
 : and <code>F</code> and <code>N</code> are also considered "false."
 : If casting fails, the value is considered a string.
 : Header field names are always considered strings even if unquoted.
 :
 : @param $csv The CSV string to parse.
 : @param $options The options to use:
 :  <dl>
 :    <dt><code>extra-name</code></dt>
 :      <dd>
 :        The field name for extra values, if any;
 :        default: none (error <code>zerr:ZCSV0003</code> is raised).
 :        If this option is given and a line contains one or more extra values
 :        (that is, values that have no corresponding field names),
 :        then the extra values are assigned as the values
 :        for fields having <code>extra-name</code> as their names.
 :        <p/>
 :        If <code>extra-name</code> contains a <code>#</code> (U+0023),
 :        then the <code>#</code> is substituted with the field number
 :        (where field numbers start at 1).
 :        If <code>extra-name</code> does not contains a <code>#</code>,
 :        then the field number is appended.
 :      </dd>
 :    <dt><code>field-names</code></dt>
 :      <dd>
 :        A JSON array of strings denoting field names;
 :        default: none.
 :        If this option is given, then the first CSV line is assumed not to be
 :        a header line; if omitted, then the first CSV line is assumed to be a
 :        header line and the field names are taken from this line.
 :      </dd>
 :    <dt><code>missing-value</code></dt>
 :      <dd>
 :        What should happen when a missing value is detected;
 :        default: <code>"null"</code>.
 :        A "missing" value is one of:
 :        <ul>
 :          <li>Two consecutive <code>separator</code> characters.</li>
 :          <li>A <code>separator</code> character as either the first
 :              or last character on a line.</li>
 :          <li>Fewer values than the number of field names.</li>
 :        </ul>
 :        When a missing value is detected,
 :        the value of this option determines what happens:
 :        <dl>
 :          <dt><code>"error"</code></dt>
 :            <dd>Error <code>zerr:ZCSV0002</code> is raised.</dd>
 :          <dt><code>"omit"</code></dt>
 :            <dd>Both the value and its key are omitted from the result
 :                object.</dd>
 :          <dt><code>"null"</code></dt>
 :            <dd>The value is set to <code>null</code>.</dd>
 :        </dl>
 :      </dd>
 :    <dt><code>quote-char</code></dt>
 :      <dd>
 :        The single ASCII character that may be used to quote values;
 :        default: <code>"</code> (U+0022).
 :      </dd>
 :    <dt><code>quote-escape</code></dt>
 :      <dd>
 :        The single ASCII character used to escape <code>quote-char</code>;
 :        default: same as <code>quote-char</code>.
 :        If <code>quote-escape</code> equals <code>quote-char</code>,
 :        it means that <code>quote-char</code> must be doubled to escape it.
 :        If <code>quote-escape</code> does not equal <code>quote-char</code>,
 :        it means that <code>quote-escape</code> is used to escape
 :        <code>quote-char</code>.
 :        For example, a <code>quote-char</code> of <code>"</code> (U+0022)
 :        and a <code>quote-escape</code> of <code>\</code> (U+005C) means that
 :        quotes will be escaped by <code>\"</code>.
 :      </dd>
 :    <dt><code>separator</code></dt>
 :      <dd>
 :        The single ASCII character used to separate values;
 :        default: <code>,</code> (U+002C).
 :      </dd>
 :  </dl>
 : @return a sequence of zero or more JSON objects where each key is a field
 : name and each value is a parsed value.
 : @error zerr:ZCSV0001 if the <code>quote-char</code>,
 : <code>quote-escape</code>, or <code>separator</code> option is given
 : and it's not a single ASCII character.
 : @error zerr:ZCSV0002 if a missing value is detected and the
 : <code>missing-value</code> option is "<code>error</code>".
 : @error zerr:ZCSV0003 if an extra value is detected and the
 : <code>extra-name</code> option is not set.
 :)
declare function csv:parse( $csv as string, $options as object() )
  as object()* external;

(:~
 : Parses a CSV (comma-separated values) string using the default options.
 : A newline (U+000A), optionally preceeded by a carriage-return (U+000D),
 : terminates lines, aka, "records."
 :
 : Quoted values are always considered strings;
 : unquoted values are attempted to be cast in the following order:
 : integer, decimal, double, or boolean.
 : In addition to the "normal" values of
 : <code>true</code> and <code>false</code> for boolean,
 : <code>T</code> and <code>Y</code> are also considered "true"
 : and <code>F</code> and <code>N</code> are also considered "false."
 : If casting fails, the value is considered a string.
 : Header field names are always considered strings even if unquoted.
 :
 : The default options are:
 :  <dl>
 :    <dt><code>extra-name</code></dt>
 :      <dd>
 :        The field name for extra values, if any;
 :        default: none (error <code>zerr:ZCSV0003</code> is raised).
 :      </dd>
 :    <dt><code>field-names</code></dt>
 :      <dd>
 :        A JSON array of strings denoting field names;
 :        default: none.
 :        The first CSV line is assumed to be a header line
 :        and the field names are taken from this line.
 :      </dd>
 :    <dt><code>missing-value</code></dt>
 :      <dd>
 :        What should happen when a missing value is detected;
 :        default: <code>"null"</code>.
 :        A "missing" value is one of:
 :        <ul>
 :          <li>Two consecutive <code>quote-char</code> characters.</li>
 :          <li>A <code>quote-char</code> character as either the first
 :              or last character on a line.</li>
 :          <li>Fewer values than the number of field names.</li>
 :        </ul>
 :        When a missing value is detected,
 :        the value of this option determines what happens:
 :        <dl>
 :          <dt><code>"error"</code></dt>
 :            <dd>Error <code>zerr:ZCSV0002</code> is raised.</dd>
 :          <dt><code>"omit"</code></dt>
 :            <dd>Both the value and its key are omitted from the result
 :                object.</dd>
 :          <dt><code>"null"</code></dt>
 :            <dd>The value is set to <code>null</code>.</dd>
 :        </dl>
 :      </dd>
 :    <dt><code>quote-char</code></dt>
 :      <dd>
 :        The single ASCII character that may be used to quote values;
 :        default: <code>"</code> (U+0022).
 :      </dd>
 :    <dt><code>quote-escape</code></dt>
 :      <dd>
 :        The single ASCII character used to escape <code>quote-char</code>;
 :        default: same as <code>quote-char</code>.
 :        This means that an escaped quote is doubled as <code>""</code>.
 :      </dd>
 :    <dt><code>separator</code></dt>
 :      <dd>
 :        The single ASCII character used to separate values;
 :        default: <code>,</code> (U+002C).
 :      </dd>
 :  </dl>
 :
 : @param $csv The CSV string to parse.
 : @return a sequence of zero or more JSON objects where each key is a field
 : name and each value is a parsed value.
 : @error zerr:ZCSV0003 if an extra value is detected.
 :)
declare function csv:parse( $csv as string )
  as object()*
{
  csv:parse( $csv, {} )
};

(:~
 : TODO
 :
 : @param $obj TODO
 : @param $options TODO
 : @return TODO
 :)
declare function csv:serialize( $obj as object()*, $options as object() )
  as string* external;

(:~
 : TODO
 :
 : @param $obj TODO
 : @return TODO
 :)
declare function csv:serialize( $obj as object()* )
  as string*
{
  csv:serialize( $obj, {} )
};

(:===========================================================================:)

(: vim:set syntax=xquery et sw=2 ts=2: :)
