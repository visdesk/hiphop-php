/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010- Facebook, Inc. (http://www.facebook.com)         |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/

#ifndef __EVAL_STATIC_STATEMENT_H__
#define __EVAL_STATIC_STATEMENT_H__

#include <runtime/eval/ast/statement.h>

namespace HPHP {
namespace Eval {
///////////////////////////////////////////////////////////////////////////////

DECLARE_AST_PTR(StaticVariable);
DECLARE_AST_PTR(StaticStatement);
DECLARE_AST_PTR(Expression);
DECLARE_AST_PTR(Name);

class StaticVariable : public Construct {
public:
  StaticVariable(CONSTRUCT_ARGS, const std::string &name, ExpressionPtr val);
  void set(VariableEnvironment &env) const;
  StaticVariable *optimize(VariableEnvironment &env);
  virtual void dump(std::ostream &out) const;
  const NamePtr &name();
  const ExpressionPtr &val() { return m_val; }
private:
  NamePtr m_name;
  ExpressionPtr m_val;
};

class StaticStatement : public Statement {
public:
  StaticStatement(STATEMENT_ARGS, const std::vector<StaticVariablePtr> &vars);
  virtual Statement *optimize(VariableEnvironment &env);
  virtual void eval(VariableEnvironment &env) const;
  virtual void dump(std::ostream &out) const;
  const std::vector<StaticVariablePtr> &vars() const { return m_vars; }
private:
  std::vector<StaticVariablePtr> m_vars;
};

void optimize(VariableEnvironment &env, StaticVariablePtr &var);

///////////////////////////////////////////////////////////////////////////////
}
}

#endif /* __EVAL_STATIC_STATEMENT_H__ */
