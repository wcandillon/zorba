#ifndef ZORBA_EXPR_TOOLS_H
#define ZORBA_EXPR_TOOLS_H

#include "common/shared_types.h"
#include "compiler/semantic_annotations/annotations.h"
#include "compiler/semantic_annotations/annotation_keys.h"
#include "functions/signature.h"
#include "store/api/item_factory.h"
#include "store/api/store.h"
#include "system/globalenv.h"

#include <set>

#define LOOKUP_FN( pfx, local, arity ) static_cast<function *> (GENV.getRootStaticContext ().lookup_fn (pfx, local, arity))
#define LOOKUP_OP1( local ) static_cast<function *> (GENV.getRootStaticContext ().lookup_builtin_fn (":" local, 1))
#define LOOKUP_OP2( local ) static_cast<function *> (GENV.getRootStaticContext ().lookup_builtin_fn (":" local, 2))
#define LOOKUP_OP3( local ) static_cast<function *> (GENV.getRootStaticContext ().lookup_builtin_fn (":" local, 3))
#define LOOKUP_OPN( local ) static_cast<function *> (GENV.getRootStaticContext ().lookup_builtin_fn (":" local, VARIADIC_SIG_SIZE))

#define ITEM_FACTORY (GENV.getStore().getItemFactory())

namespace zorba {

typedef rchandle<var_expr> varref_t;

class VarSetAnnVal : public AnnotationValue {
public:
  std::set<var_expr *> varset;
  void add (var_expr *v) { varset.insert (varset.begin (), v); }
};
  
  const std::set<var_expr *> &get_varset_annotation (const expr *e, Annotation::key_t k);


int count_variable_uses(expr *root, var_expr *var, int limit);

}

#endif /* ZORBA_EXPR_TOOLS_H */
/* vim:set ts=2 sw=2: */
/*
 * Local variables:
 * mode: c++
 * End:
 */
