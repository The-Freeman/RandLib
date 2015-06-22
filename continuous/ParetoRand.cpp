#include "ParetoRand.h"

ParetoRand::ParetoRand(double shape, double scale) :
    U(0, 1)
{
    setParameters(shape, scale);
}

void ParetoRand::setParameters(double shape, double scale)
{
    xm = std::max(shape, MIN_POSITIVE);
    alpha = std::max(scale, MIN_POSITIVE);
    alphaInv = 1.0 / alpha;
    pdfCoef = alpha * std::pow(xm, alpha);
}

void ParetoRand::setShape(double shape)
{
    xm = std::max(shape, MIN_POSITIVE);
    pdfCoef = alpha * std::pow(xm, alpha);
}

void ParetoRand::setScale(double scale)
{
    alpha = std::max(scale, MIN_POSITIVE);
    alphaInv = 1.0 / alpha;
    pdfCoef = alpha * std::pow(xm, alpha);
}

double ParetoRand::pdf(double x)
{
    return (x >= xm) ? pdfCoef / std::pow(x, alpha + 1) : 0;
}

double ParetoRand::cdf(double x)
{
    return (x > xm) ? 1 - std::pow(xm / x, alpha) : 0;
}

double ParetoRand::value()
{
    return xm / std::pow(U.value(), alphaInv);
}
