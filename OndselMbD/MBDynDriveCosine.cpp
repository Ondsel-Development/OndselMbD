#include "MBDynDriveCosine.h"

using namespace MbD;

std::shared_ptr<MBDynDriveCosine> MbD::MBDynDriveCosine::With()
{
	auto inst = std::make_shared<MBDynDriveCosine>();
	inst->initialize();
	return inst;
}

void MbD::MBDynDriveCosine::readFunction(std::vector<std::string>& args)
{
	assert(readStringNoSpacesOffTop(args) == "cosine");
	std::string initial_time, angular_velocity, amplitude, number_of_cycles, initial_value;
	initial_time = popOffTop(args);
	angular_velocity = popOffTop(args);
	amplitude = popOffTop(args);
	number_of_cycles = popOffTop(args);
	initial_value = popOffTop(args);
	initial_time.erase(remove_if(initial_time.begin(), initial_time.end(), isspace), initial_time.end());
	angular_velocity.erase(remove_if(angular_velocity.begin(), angular_velocity.end(), isspace), angular_velocity.end());
	amplitude.erase(remove_if(amplitude.begin(), amplitude.end(), isspace), amplitude.end());
	number_of_cycles.erase(remove_if(number_of_cycles.begin(), number_of_cycles.end(), isspace), number_of_cycles.end());
	initial_value.erase(remove_if(initial_value.begin(), initial_value.end(), isspace), initial_value.end());
	//f(t) = initial_value + amplitude * (1 ? cos (angular_velocity * (t ? initial_time)))

	double nCycle;
	if (number_of_cycles.find("forever") != std::string::npos) {
		nCycle = 1.0e9;
	}
	else if (number_of_cycles.find("one") != std::string::npos) {
		nCycle = 1.0;
	}
	else if (number_of_cycles.find("half") != std::string::npos) {
		nCycle = 0.5;
	}
	else {
		nCycle = stod(number_of_cycles);
	}
	double x0 = stod(initial_time);
	double y0 = stod(initial_value);
	double omega = stod(angular_velocity);
	double amp = stod(amplitude);
	double x1 = x0 + (2 * OS_M_PI * nCycle / omega);
	double y1 = y0 + amp * (1.0 - std::cos(omega * (x1 - x0)));
	double f1 = y0;
	auto ss = std::stringstream();
	ss << "(" << y0 << " + " << amp << "*(1.0 - cos(" << omega << "*(time - " << x0 << "))))";
	std::string f2 = ss.str();
	double f3 = y1;
	double t1 = x0;
	double t2 = x1;
	ss = std::stringstream();
	ss << "piecewise(time, functions(" << f1 << ", " << f2 << ", " << f3 << "), transitions(" << t1 << ", " << t2 << "))";
	formula = ss.str();
}

void MbD::MBDynDriveCosine::createASMT()
{
	assert(false);
}
