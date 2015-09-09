#include "WeibullRand.h"

WeibullRand::WeibullRand(double scale, double shape)
{
    setParameters(scale, shape);
}

std::string WeibullRand::name()
{
    return "Weibull(" + toStringWithPrecision(getShape()) + ", " + toStringWithPrecision(getScale()) + ")";
}

void WeibullRand::setParameters(double scale, double shape)
{
    l = std::max(scale, MIN_POSITIVE);
    k = std::max(shape, MIN_POSITIVE);
    lInv = 1.0 / l;
}

double WeibullRand::f(double x) const
{
    if (x <= 0)
        return 0;
    double xAdj = x * lInv;
    double xAdjPow = std::pow(xAdj, k - 1);
    return k * lInv * xAdjPow * std::exp(-xAdj * xAdjPow);
}

double WeibullRand::F(double x) const
{
    if (x <= 0)
        return 0;
    return 1 - std::exp(-std::pow(x * lInv, k));
}

double WeibullRand::variate() const
{
    return l * std::pow(ExponentialRand::standardVariate(), 1.0 / k);
}

double WeibullRand::E() const
{
    return l * std::tgamma(1 + 1.0 / k);
}

double WeibullRand::Var() const
{
    double res = std::tgamma(1 + 1.0 / k);
    res *= res;
    res += std::tgamma(1 + 2.0 / k);
    return l * l * res;
}
