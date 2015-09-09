#ifndef RAYLEIGHRAND_H
#define RAYLEIGHRAND_H

#include "ContinuousRand.h"
#include "ExponentialRand.h"

/**
 * @brief The RayleighRand class
 */
class RANDLIBSHARED_EXPORT RayleighRand : public ContinuousRand
{
    double sigma;
    double sigmaSqInv_2; // 2 * sigma^2

public:
    explicit RayleighRand(double scale = 1);
    virtual std::string name() override;

    void setScale(double scale);
    inline double getScale() const { return sigma; }

    double f(double x) const override;
    double F(double x) const override;
    double variate() const override;

    double E() const override;
    double Var() const override;

    inline double Median() const;
    inline double Mode() const;
    static constexpr double Skewness();
    static constexpr double ExcessKurtosis();

    bool fitToData(const QVector<double> &sample);
};
#endif // RAYLEIGHRAND_H
