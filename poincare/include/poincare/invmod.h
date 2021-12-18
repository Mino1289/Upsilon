#ifndef POINCARE_INVMOD_H
#define POINCARE_INVMOD_H

#include <poincare/n_ary_expression.h>

namespace Poincare {

class InverseModulaireNode final : public NAryExpressionNode  {
public:

  // TreeNode
  size_t size() const override { return sizeof(InverseModulaireNode); }
#if POINCARE_TREE_LOG
  void logNodeName(std::ostream & stream) const override {
    stream << "InverseModulaire";
  }
#endif

  // ExpressionNode
  Sign sign(Context * context) const override { return Sign::Positive; }
  Type type() const override { return Type::InverseModulaire; }

private:
  // Layout
  Layout createLayout(Preferences::PrintFloatMode floatDisplayMode, int numberOfSignificantDigits) const override;
  int serialize(char * buffer, int bufferSize, Preferences::PrintFloatMode floatDisplayMode, int numberOfSignificantDigits) const override;
  // Simplification
  Expression shallowReduce(ReductionContext reductionContext) override;
  Expression shallowBeautify(ReductionContext * reductionContext) override;
  LayoutShape leftLayoutShape() const override { return LayoutShape::MoreLetters; };
  LayoutShape rightLayoutShape() const override { return LayoutShape::BoundaryPunctuation; }
  // Evaluation
  Evaluation<float> approximate(SinglePrecision p, ApproximationContext approximationContext) const override { return templatedApproximate<float>(approximationContext); }
  Evaluation<double> approximate(DoublePrecision p, ApproximationContext approximationContext) const override { return templatedApproximate<double>(approximationContext); }
  template<typename T> Evaluation<T> templatedApproximate(ApproximationContext approximationContext) const;
};

class InverseModulaire final : public NAryExpression {
public:
  InverseModulaire(const InverseModulaireNode * n) : NAryExpression(n) {}
  static InverseModulaire Builder(const Tuple & children = {}) { return TreeHandle::NAryBuilder<InverseModulaire, InverseModulaireNode>(convert(children)); }
  // Using a -2 as numberOfChildren to allow 2 or more children when parsing
  static constexpr Expression::FunctionHelper s_functionHelper = Expression::FunctionHelper("invmod", -2, &UntypedBuilderMultipleChildren<InverseModulaire>);

  // Expression
  Expression shallowReduce(ExpressionNode::ReductionContext reductionContext);
  Expression shallowBeautify(Context * context);
};

}

#endif
