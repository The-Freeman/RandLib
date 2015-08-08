#ifndef GEOMETRICRAND_H
#define GEOMETRICRAND_H

#include "DiscreteRand.h"
#include "../continuous/UniformRand.h"
#include "../continuous/ExponentialRand.h"
#include <functional>

/**
 * @brief The GeometricRand class
 */
class RANDLIBSHARED_EXPORT GeometricRand : public DiscreteRand<int>
{
    double p;

    static constexpr unsigned tableSize = 16;
    // TODO: don't storage both variables (including tableSize)
    double table[tableSize];
    ExponentialRand Exp;

public:
    GeometricRand(double probability);
    void setProbability(double probability);
    inline double getProbability() const { return p; }

    virtual double P(int k) const override;
    virtual double F(double x) const override;
    virtual double variate() override;

private:
    double variateForSmallP();
    double variateForLargeP();

public:
    double E() const override { return 1.0 / p; }
    double Var() const override { return (1 - p) / (p * p); }

    // TODO: add median and entropy
    static double constexpr Mode() { return 1; }
    inline double Skewness() { return (2 - p) / std::sqrt(1 - p); }
    inline double ExcessiveKurtosis() { return 1.0 / (p * (1 - p)) - 6; }
};

#endif // GEOMETRICRAND_H