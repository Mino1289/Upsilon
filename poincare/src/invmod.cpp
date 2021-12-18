#include <poincare/invmod.h>
#include <poincare/arithmetic.h>
#include <poincare/layout_helper.h>
#include <poincare/serialization_helper.h>

namespace Poincare {

constexpr Expression::FunctionHelper InverseModulaire::s_functionHelper;

Layout InverseModulaireNode::createLayout(Preferences::PrintFloatMode floatDisplayMode, int numberOfSignificantDigits) const {
  return LayoutHelper::Prefix(InverseModulaire(this), floatDisplayMode, numberOfSignificantDigits, InverseModulaire::s_functionHelper.name());
}

int InverseModulaireNode::serialize(char * buffer, int bufferSize, Preferences::PrintFloatMode floatDisplayMode, int numberOfSignificantDigits) const {
  return SerializationHelper::Prefix(this, buffer, bufferSize, floatDisplayMode, numberOfSignificantDigits, InverseModulaire::s_functionHelper.name());
}

Expression InverseModulaireNode::shallowReduce(ReductionContext reductionContext) {
  return InverseModulaire(this).shallowReduce(reductionContext);
}

Expression InverseModulaireNode::shallowBeautify(ReductionContext * reductionContext) {
  return InverseModulaire(this).shallowBeautify(reductionContext->context());
}

template<typename T>
Evaluation<T> InverseModulaireNode::templatedApproximate(ApproximationContext approximationContext) const {
  return Arithmetic::IMOD<T>(*this, approximationContext);
}

Expression InverseModulaire::shallowBeautify(Context * context) {
  sortChildrenInPlace([](const ExpressionNode * e1, const ExpressionNode * e2, bool canBeInterrupted) { return ExpressionNode::SimplificationOrder(e1, e2, false, canBeInterrupted); }, context, true, true);
  return *this;
}

Expression InverseModulaire::shallowReduce(ExpressionNode::ReductionContext reductionContext) {
  Expression result = Arithmetic::IMOD(*this);

  replaceWithInPlace(result);
  return result;
}

template Evaluation<float> InverseModulaireNode::templatedApproximate<float>(ApproximationContext approximationContext) const;
template Evaluation<double> InverseModulaireNode::templatedApproximate<double>(ApproximationContext approximationContext) const;

}
