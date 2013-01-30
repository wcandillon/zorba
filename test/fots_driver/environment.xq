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

(:~
 : Zorba FOTS driver environment
 : @author Sorin Nasoi
 :)

module namespace env =
  "http://www.zorba-xquery.com/fots-driver/environment";

import module namespace xqxq =
  "http://www.zorba-xquery.com/modules/xqxq";
import module namespace util =
  "http://www.zorba-xquery.com/fots-driver/util" at "util.xq";

declare namespace fots =
  "http://www.w3.org/2010/09/qt-fots-catalog";

declare namespace ann =
  "http://www.zorba-xquery.com/annotations";


declare variable $env:hof as xs:string :=
  string-join(
    ( "declare namespace op = 'http://www.zorba-xquery.com/options/features';",
      "declare namespace f = 'http://www.zorba-xquery.com/features';",
      "declare option op:enable 'f:hof';"),
    "&#xA;");


(:~
 : If there is a dependency on the HOF feature, return the text for enabling
 : the HOF feature within a query.
 :
 : @param $deps the dependencies of the test set and test case
 : @param $test the raw query text.
 : @return the text for enabling the HOF feature
 :)
declare function env:enable-HOF-feature(
  $deps as element(fots:dependency)*,
  $test as xs:string
) as xs:string? 
{
  let $check := 
    some $dep in $deps
    satisfies $dep[@type eq "feature" and contains(@value, "higherOrderFunctions")]
  return
    if ($check) then $env:hof else ()
};


(:~
 :  Create the text for an XQuery version declaration, if needed.
 :
 : @param $deps the dependencies of the test set and test case.
 : @param $test the raw query text.
 : @return the text for the XQuery version declaration, if necessary; otherwise,
 :         the empty sequence.
 :)
declare function env:add-xquery-version-decl(
  $deps as element(fots:dependency)*,
  $test as xs:string
) as xs:string? 
{
  let $deps := $deps[@type eq "spec"]

  let $v30 :=
    some $dep in $deps
    satisfies $dep[contains(@value, "XQ30") or contains(@value, "XP30")]

  return
    if ($v30 and not(contains($test, "xquery version"))) then
    {
      'xquery version "3.0";'
    }
    else
    {
      let $v10 :=
        some $dep in $deps
        satisfies $dep[contains(@value, "XQ10")]
      return
        if ($v10 and not(contains($test, "xquery version ")))
        then 'xquery version "1.0";'
        else ()
    }
};


(:~
 : Retruns the text for the static-base-uri declarations.
 :
 : NOTE: at least one of $end and $envCase is the empty sequence.
 :
 : @param $env the non-local environment of the test-case, if any. It is an
 :        enviroment specified either at the test-set level or at the catalog
 :        level and is referenced by the test-case.
 : @param $envCase the local environment of the test-case, if any.
 : @return the declare base-uri prolog statement.
 :)
declare function env:decl-base-uri(
  $env      as element(fots:environment)?,
  $envCase  as element(fots:environment)?
) as xs:string? 
{
  for $baseURI in ($env/fots:static-base-uri, $envCase/fots:static-base-uri)
  return concat("declare base-uri '", $baseURI/@uri, "';")
};


(:~
 : Return the text for the default-element-namespace declaration, if needed.
 :
 : NOTE: at least one of $end and $envCase is the empty sequence.
 :
 : @param $env the non-local environment of the test-case, if any. It is an
 :        enviroment specified either at the test-set level or at the catalog
 :        level and is referenced by the test-case.
 : @param $envCase the local environment of the test-case, if any.
 : @return the text for thee default element namespace declaration.
 :)
declare function env:decl-def-elem-namespace(
  $env      as element(fots:environment)?,
  $envCase  as element(fots:environment)?
) as xs:string? 
{
  for $ns in ($env/fots:namespace, $envCase/fots:namespace)
  where $ns[@prefix eq ""]
  return concat('declare default element namespace "', $ns/@uri, '";')
};


(:~
 : Retruns the text for the necessary namespace declarations.
 :
 : NOTE: at least one of $end and $envCase is the empty sequence.
 :
 : @param $env the non-local environment of the test-case, if any. It is an
 :        enviroment specified either at the test-set level or at the catalog
 :        level and is referenced by the test-case.
 : @param $envCase the local environment of the test-case, if any.
 : @param $test the raw query text
 : @return the text for the namespace declarations.
 :)
declare %ann:nondeterministic function env:decl-namespaces(
  $env     as element(fots:environment)?,
  $envCase as element(fots:environment)?,
  $test    as xs:string
) as xs:string? 
{
  string-join
  (
    for $ns in ($env/fots:namespace, $envCase/fots:namespace)
    where not($ns[@prefix eq ""]) and 
          not(env:is-schema-prefix-bound($ns/@prefix, $test))
    return concat('declare namespace ', $ns/@prefix, ' = "', $ns/@uri, '";')
  ,
  "&#xA;"
  )
};


(:~
 : Return true if the prefix will be bound to a schema in the Query
 : It's a bug in the FOTS if this function returns true: TODO report to W3C
 :)
declare %private %ann:nondeterministic function env:is-schema-prefix-bound(
  $prefix as xs:string,
  $test   as xs:string
) as xs:boolean 
{
  contains($test, concat("import schema namespace ", $prefix))
};


(:~
 : Add the decimal format declarations.
 :
 : @param $decimal-formats decimal formats.
 : @return the decimal formats declarations.
 :)
declare function env:decl-decimal-formats(
  $decimal-formats as element(fots:decimal-format)*
) as xs:string* 
{
  if (empty($decimal-formats))
  then
    ()
  else
    for $tmp in $decimal-formats
    let $default := if ($tmp/@name) then () else "default"
    let $name := if ($tmp/@name) then data($tmp/@name) else ()
    return
      string-join
      (
      (
        "declare", 
        $default,
        "decimal-format",
        $name,
        env:set-properties($tmp),
        ";"
      ),
      ' '
      )
};


declare %private function env:set-properties(
  $decimal-format as element(fots:decimal-format)
) as xs:string* 
{
  for $att in $decimal-format/attribute::*
  let $name := node-name($att)
  let $value := data($att)
  return
    if (exists(index-of(("decimal-separator", "grouping-separator", "infinity",
                         "minus-sign", "NaN", "percent", "per-mille",
                         "zero-digit", "digit", "pattern-separator"),
                         xs:string($name))))
    then concat($name, '="' , $value, '"')
    else ()
};


(:~
 : Create the text for all of the variable declarations that must be added to
 : the text of a query. The required declarations are specified by the <param>
 : and <source> subelements of the applicable <environment>.
 :
 : NOTE: at least one of $end and $envCase is the empty sequence.
 :
 : @param $env the non-local environment of the test-case, if any. It is an
 :        enviroment specified either at the test-set level or at the catalog
 :        level and is referenced by the test-case.
 : @param $envCase the local environment of the test-case, if any.
 : @param $envBaseURI the relative URI for the environment.
 : @param $testSetBaseURI the URI of the test set.
 : @return the text for the variable declarations.
 :)
declare %ann:nondeterministic function env:add-var-decl(
  $env            as element(fots:environment)?,
  $envCase        as element(fots:environment)?,
  $envBaseURI     as xs:anyURI,
  $testSetBaseURI as xs:anyURI
) as xs:string? 
{
  if ($env)
  then env:add-var-decls($env, $envBaseURI)
  else env:add-var-decls($envCase, $testSetBaseURI)
};



declare %private function env:add-var-decls(
  $env         as element(fots:environment)?,
  $envBaseURI  as xs:anyURI
) as xs:string? 
{
  string-join
  (
  (
    for $param in $env/fots:param
    where empty($param[@declared eq "true"])
    return
    {
      let $type := $param/@as
      let $select := $param/@select
      return
      {
        if ($select) then
        {
          let $file := $env/fots:source[@uri = translate($select, "'", "")]/@file

          let $varValue := if (starts-with($select, "'") and
                               ends-with($select, "'") and
                               exists($file))
                           then
                             concat('"', resolve-uri($file, $envBaseURI), '"')
                           else
                             $select
          return
            concat("declare variable $",
                   $param/@name,
                   if ($type) then concat(" as ", $type) else (),
                   " := ",
                   $varValue,
                   ";")
        }
        else
        {
          concat("declare variable $",
                 $param/@name,
                 if ($type) then concat(" as ", $type) else (),
                 " external;")
        }
      }
    }
    ,
    for $source in $env/fots:source
    let $role := $source/@role
    where starts-with($role,"$")
    return concat("declare variable ", $role, " external;")
  )
  ,
  " "
  )
};


(:~
 : Returns the string for setting the context item if needed.
 : @param $env environment.
 : @param $envBaseURI test base URI of the environment.
 : @return the string for setting the context item if needed.
 :)
declare function env:set-context-item(
  $env        as element(fots:environment)?,
  $envBaseURI as xs:anyURI?
) as xs:string?
{
  if (exists($env/fots:source[@role = "."]))
  then string-join((env:declare-context-item($env, $envBaseURI),
                   'xqxq:bind-context-item($queryID, $contextItem);')
                   ,"&#xA;")
  else ()
};


declare %private function env:declare-context-item(
  $env        as element(fots:environment)?,
  $envBaseURI as xs:anyURI?
) as xs:string 
{
  let $ciURI := resolve-uri($env/fots:source[@role = "."]/@file, $envBaseURI)
  return
  if(empty($env/fots:source[@validation = "strict"]))
  then concat('variable $contextItem := doc("', $ciURI, '");')
  else string-join(
    ("&#xA;",
     "variable $contextItemQuery := xqxq:prepare-main-module('",
     env:get-schema-import($env),
     concat('validate { doc("', $ciURI, '")', "}',", " "),
           "resolver:url-resolver#2, ());",
           "variable $contextItem := xqxq:evaluate($contextItemQuery);")
   ,"&#xA;")
};


(:~
 : Returns the strings for variable binding in XQXQ.
 :
 : @param $env the environment of the catalog/test-set (given with 'ref').
 : @param $envBaseURI the relative URI for the environment.
 : @return the strings for variable binding in XQXQ.
 :)
declare function env:set-variables(
  $env        as element(fots:environment)?,
  $envBaseURI as xs:anyURI
) as xs:string? 
{
  if(empty($env))
  then ()
  else
    let $srcNames := for $source in $env/fots:source
                     where starts-with(data($source/@role),"$")
                     return substring-after(data($source/@role),"$"),
        $srcValues := for $srcName in $srcNames
                      return concat('doc("',
                                  resolve-uri($env/fots:source[@role = concat("$",$srcName)]/@file, $envBaseURI),
                                  '")')
  return
  string-join(
    (for $srcName in $srcNames
     let $index := index-of($srcNames, $srcName)
     return
      concat('xqxq:bind-variable( $queryID, xs:QName("', $srcName, '")', ', ',
             $srcValues[$index], ');'),

      for $param in $env/fots:param
      let $select:= $param/@select
      let $file := $env/fots:source[@uri = translate($select, "'", "")]/@file
      let $varValue := if(starts-with($select, "'") and
                          ends-with($select, "'") and
                          exists($file))
                       then  concat('"',
                                   resolve-uri($file, $envBaseURI),
                                   '"')
                       else $select
      let $varName := $param/@name
      where (exists($select) and
(: if there is an attribute 'declared' set to true, this means that the variable
   is declared within the 'test' itself :)
             exists($param[@declared="true"]))
      return
        concat('xqxq:bind-variable( $queryID, xs:QName("',
               $param/@name,
               '")', ', ',
               $varValue, ');'))
    , "&#xA;")
};


declare %private function env:get-schema-import(
  $env  as element(fots:environment)?
) as xs:string 
{
  if (empty($env))
  then ""
  else
    let $namespace := $env/fots:namespace[@uri = data($env/fots:schema/@uri)]
    let $prefix as xs:string := if(exists($namespace))
                                then xs:string(data($namespace/@prefix))
                                else "p"
    return
      if($prefix = "")
      then concat('import schema default element namespace "',
                  $env/fots:schema/@uri,
                  '";&#xA;')
      else concat('import schema namespace ',
                  $prefix,
                  ' = "',
                  $env/fots:schema/@uri,
                  '";&#xA;')
};


(:~
 : Returns the XQXQ URL resolver declaration.
 : @param $case the test case.
 : @param $env the environment.
 : @param $envBaseURI URI of the environment.
 : @param $testSetBaseURI URI to the test set that defines the test case.
 : @return the XQXQ URL resolver declaration.
 :)
declare function env:resolver(
  $case           as element(fots:test-case),
  $env            as element(fots:environment)?,
  $envBaseURI     as xs:anyURI?,
  $testSetBaseURI as xs:anyURI
) as xs:string?
{
  let $envSchema := $env/fots:schema,
      $tcSchema := $case/fots:environment/fots:schema,
      $schemas := ($envSchema, $tcSchema),
      $modules := $case/fots:module,
      $resources := ($env/fots:resource, $case/fots:environment/fots:schema)
  return
    if (empty($schemas) and empty($modules) and empty($resources))
    then ()
    else string-join(
            ("declare namespace resolver = 'http://www.zorba-xquery.com/modules/xqxq/url-resolver';",
             $env:hof,
            "declare function resolver:url-resolver($namespace as xs:string, $entity as xs:string) {",
            "switch($entity)",
    if (exists($schemas))
    then string-join(("case 'schema'",
                     "  return switch($namespace)",
                    (for $schema in $envSchema
                     return concat("    case '",
                                  data($schema/@uri),
                                   "' return doc('",
                                   resolve-uri($schema/@file, $envBaseURI),
                                   "')"),
                      for $schema in $tcSchema
                      return concat("    case '",
                                   data($schema/@uri),
                                   "' return doc('",
                                   resolve-uri($schema/@file, $testSetBaseURI),
                                   "')")),
                      "    default return ()"),
                      "&#xA;")
    else (),
    if (exists($modules))
    then string-join(("case 'module'",
                      "  return switch($namespace)",
                      for $module in $modules
                      return concat("    case '",
                                   data($module/@uri),
                                   "' return unparsed-text('",
                                   resolve-uri($module/@file, $testSetBaseURI),
                                   "') "),
                    "    default return ()"),
                    "&#xA;")
    else (),
    if (exists($resources)) then
    string-join(("case ''",
                 "  return switch($namespace)",
                  for $resource in $resources
                  return concat("    case '",
                                 data($resource/@uri),
                                 "' return unparsed-text('",
                                 resolve-uri($resource/@file, $envBaseURI),
                                 "'",
                                 if(exists($resource/@encoding))
                                 then concat (",'",
                                              data($resource/@encoding),
                                              "'")
                                 else (),
                                 ") "),
                 "         default return ()")
                ,"&#xA;")
    else ()
    , "default return ()","};"),
    "&#xA;")
};


(:~
 : Checks that a set of dependencies (associated with some test-set or test-case)
 : are met by Zorba's capabilities and implementation-defined features (as 
 : specified in the Zorba manifest).
 :
 : @param $deps the dependencies of the test set or test case
 : @param $zorbaManifest Zorba manifest document.
 : @return a sequence of strings containing one string for each dependency
 :         that was not met, describing the dependency. If all dependencies
 :         are met, the empty sequence is returned.
 :)
declare function env:check-dependencies(
  $deps           as element(fots:dependency)*,
  $zorbaManifest  as node()
) as xs:string* 
{
  if (empty($deps)) then
  { 
    ()
  }
  else
  {
    for $dep in $deps

    let $satisfied := if ($dep/@satisfied)
                      then data($dep/@satisfied)
                      else "true"

    let $zorbaDep := $zorbaManifest//fots:dependency[@type eq $dep/@type and
                                                     @value eq $dep/@value and
                                                     @satisfied eq $satisfied]
    return
      if (empty($zorbaDep))
      then
        concat("Dependency (type=", $dep/@type, ", value=", $dep/@value,
               ", satisfied=", $satisfied, ") was not met. ")
      else ()
  }
};
