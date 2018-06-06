#ifndef REGRESSION_LOGISTIC_MODEL_H
#define REGRESSION_LOGISTIC_MODEL_H

#include "model.h"

namespace Regression {

class LogisticModel : public Model {
public:
  using Model::Model;
  double evaluate(double * modelCoefficients, double x) const override;
  double partialDerivate(double * modelCoefficients, int derivateCoefficientIndex, double x) const override;
  double numberOfCoefficients() const override { return 3; }
};

}


#endif
