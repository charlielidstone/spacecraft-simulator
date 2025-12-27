#ifndef INTEGRATOR_HPP
#define INTEGRATOR_HPP

class Integrator {
public:
	virtual ~Integrator() = default;
	virtual double integrate(double toIntegrate, double dt) {
		return toIntegrate * dt;
	}
};

#endif