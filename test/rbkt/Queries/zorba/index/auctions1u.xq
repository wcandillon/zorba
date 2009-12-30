import module namespace xqddf = "http://www.zorba-xquery.com/modules/xqddf";

import module namespace auctions = "http://www.w3.org/TestModules/auctions" at
                                       "auctions_module1.xqlib";

declare variable $emp-id := $auctions:PersonId;
declare variable $emp-city := $auctions:PersonCity;

block
{
  auctions:create-db();

  for $x in auctions:probe-point-id($emp-id, "person1")
  return <person id = "{$x/@id}">{$x/name}</person>;
}
,
block
{
  insert node
    <person id="person50"><name>Some Name</name><city>Amsterdam</city></person>
  as first into
    xqddf:collection($auctions:auctions)/site/people
  ,
  xqddf:refresh-index($emp-id);
  (: don't refresh the emp-city index manually because it's done automatically :)
}
,
"

"
,
for $x in auctions:probe-point-id($emp-id, "person50")
return <person id = "{$x/@id}">{$x/name}</person>
,
"

"
,
for $x in auctions:probe-point-city($emp-city, "Amsterdam")
return <person id = "{$x/@id}">{$x/name}</person>
,
block
{
  xqddf:insert-nodes($auctions:auctions, doc("auctions2.xml"));
}
,
"

"
,
for $x in auctions:probe-range-city($emp-city, "T")
return <person id = "{$x/@id}">{$x/name}</person>


