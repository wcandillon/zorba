const char* XQUERY_COMPILATION_[] = { "xquery", "compilation" };
const PropertyGroupImpl XQUERY_COMPILATION(2, XQUERY_COMPILATION_);
const PropertyImpl XQUERY_COMPILATION_FILENAME(XQUERY_COMPILATION, "filename", 0, Property::STRING);
const PropertyImpl XQUERY_COMPILATION_PARSE_DURATION(XQUERY_COMPILATION, "parse-duration", 1, Property::INT);
const PropertyImpl XQUERY_COMPILATION_TRANSLATION_DURATION(XQUERY_COMPILATION, "translation-duration", 2, Property::INT);
const PropertyImpl XQUERY_COMPILATION_OPTIMIZATION_DURATION(XQUERY_COMPILATION, "optimization-duration", 3, Property::INT);
const PropertyImpl XQUERY_COMPILATION_CODEGENERATION_DURATION(XQUERY_COMPILATION, "codegeneration-duration", 4, Property::INT);


const PropertyImpl* PROPERTIES[] = {
  &XQUERY_COMPILATION_FILENAME,
  &XQUERY_COMPILATION_PARSE_DURATION,
  &XQUERY_COMPILATION_TRANSLATION_DURATION,
  &XQUERY_COMPILATION_OPTIMIZATION_DURATION,
  &XQUERY_COMPILATION_CODEGENERATION_DURATION
};
