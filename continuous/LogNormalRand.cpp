#include "LogNormalRand.h"

LogNormalRand::LogNormalRand(double location, double scale) :
    X(0, 1)
{
    setLocation(location);
    setScale(scale);
}

void LogNormalRand::setLocation(double location)
{
    X.setMean(location);
    expMu = std::exp(X.M());
}

void LogNormalRand::setScale(double scale)
{
    X.setSigma(scale * scale);
    expSigmaSq = std::exp(X.Var());
}

double LogNormalRand::pdf(double x)
{
    return (x > 0) ? X.pdf(std::log(x)) / x : 0;
}

double LogNormalRand::cdf(double x)
{
    return (x > 0) ? X.cdf(std::log(x)) : 0;
}

double LogNormalRand::value()
{
    return std::exp(X.value());
}

double LogNormalRand::ExcessKurtosis()
{
    double expSigma2Sq = expSigmaSq * expSigmaSq;
    double res = expSigma2Sq; /// exp(2s^2)
    res += 2 * expSigmaSq + 3; /// exp(2s^2) + 2exp(s^2) + 3
    res *= expSigma2Sq; /// exp(4s^2) + 2exp(3s^2) + 3exp(2s^2)
    return res - 6;
}
