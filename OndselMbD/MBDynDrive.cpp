#include <regex>

#include "MBDynDrive.h"
#include "MBDynDriveElement.h"
#include "MBDynDriveCosine.h"
#include "MBDynDriveMeter.h"
#include "MBDynDriveRamp.h"
#include "MBDynDriveSine.h"
#include "MBDynDriveString.h"

using namespace MbD;

std::shared_ptr<MBDynDrive> MbD::MBDynDrive::newDrive(std::string statement)
{
	if (lineHasTokens(2, statement, "cosine")) {
		return MBDynDriveCosine::With();
	}
	if (lineHasTokens(2, statement, "element")) {
		return MBDynDriveElement::With();
	}
	if (lineHasTokens(2, statement, "meter")) {
		return MBDynDriveMeter::With();
	}
	if (lineHasTokens(2, statement, "ramp")) {
		return MBDynDriveRamp::With();
	}
	if (lineHasTokens(2, statement, "sine")) {
		return MBDynDriveSine::With();
	}
	if (lineHasTokens(2, statement, "string")) {
		return MBDynDriveString::With();
	}
	assert(false);
	return std::shared_ptr<MBDynDrive>();
}

void MbD::MBDynDrive::parseMBDyn(std::string line)
{
	driveString = line;
	arguments = collectArgumentsFor("drive caller", line);
	readLabel(arguments);
	if (arguments[0].find("name") != std::string::npos) {
		arguments.erase(arguments.begin());
		driveName = readStringNoSpacesOffTop(arguments);
		driveName = std::regex_replace(driveName, std::regex("\""), "");
	}
	readFunction(arguments);

	//auto iss = std::istringstream(arguments.at(0));
	//iss >> name;
	//arguments.erase(arguments.begin());
	//assert(readStringOffTop(arguments) == "name");
	//iss = std::istringstream(arguments.at(0));
	//iss >> driveName;
	//driveName = std::regex_replace(driveName, std::regex("\""), "");
	//arguments.erase(arguments.begin());
	//readFunction(arguments);
}

void MbD::MBDynDrive::readFunction(std::vector<std::string>& args)
{
	if (args.empty()) return;
	std::string str = readStringNoSpacesOffTop(args);
	if (str == "ramp") {
		std::string slope, initValue, initTime, finalTime;
		slope = popOffTop(args);
		initTime = popOffTop(args);
		finalTime = popOffTop(args);
		initValue = popOffTop(args);
		slope.erase(remove_if(slope.begin(), slope.end(), isspace), slope.end());
		initTime.erase(remove_if(initTime.begin(), initTime.end(), isspace), initTime.end());
		finalTime.erase(remove_if(finalTime.begin(), finalTime.end(), isspace), finalTime.end());
		initValue.erase(remove_if(initValue.begin(), initValue.end(), isspace), initValue.end());

		//f = slope*(time - t0) + f0
		//rampstep(time, t0, f0, t1, f1)
		//t0 = initTime
		//f0 = initValue
		//t1 = finalTime
		//f1 = initValue + slope * (finalTime - initTime)
		auto ss = std::stringstream();
		ss << "rampstep(time, " << initTime << ", " << initValue << ", " << finalTime << ", "
			<< initValue << " + " << slope << "*(" << finalTime << " - " << initTime << "))";
		formula = ss.str();
	}
	else if (str == "cosine") {
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
	else if (str == "sine") {
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
		//f(t) = initial_value + amplitude � sin (angular_velocity � (t - initial_time))

		double nCycle;
		if (number_of_cycles.find("forever") != std::string::npos) {
			nCycle = 1.0e9;
		}
		else if (number_of_cycles.find("one") != std::string::npos) {
			nCycle = 0.5;	//Different from cosine
		}
		else if (number_of_cycles.find("half") != std::string::npos) {
			nCycle = 0.25;	//Different from cosine
		}
		else {
			nCycle = stod(number_of_cycles);
			if (nCycle < 0.0) {
				nCycle -= 0.75;
			}
			else if (nCycle > 0.0) {
				nCycle -= 0.5;
			}
		}
		double x0 = stod(initial_time);
		double y0 = stod(initial_value);
		double omega = stod(angular_velocity);
		double amp = stod(amplitude);
		double x1 = x0 + (2 * OS_M_PI * nCycle / omega);
		double y1 = y0 + amp * std::sin(omega * (x1 - x0));
		double f1 = y0;
		auto ss = std::stringstream();
		ss << "(" << y0 << " + " << amp << "*sin(" << omega << "*(time - " << x0 << ")))";
		std::string f2 = ss.str();
		double f3 = y1;
		double t1 = x0;
		double t2 = x1;
		ss = std::stringstream();
		ss << "piecewise(time, functions(" << f1 << ", " << f2 << ", " << f3 << "), transitions(" << t1 << ", " << t2 << "))";
		formula = ss.str();
	}
	else if (str == "meter") {
		auto initial_time = readDoubleOffTop(args);
		assert(initial_time == 0.0);
		auto final_time = readStringNoSpacesOffTop(args);
		assert(final_time == "forever");
		auto steps = readStringNoSpacesOffTop(args);
		assert(steps == "steps");
		auto steps_between_spikes = readStringNoSpacesOffTop(args);
		formula = steps_between_spikes;
		}
	else if (str == "element") {
		readDriveElement(args);
	}
	else {
		assert(false);
	}
}

void MbD::MBDynDrive::readDriveElement(std::vector<std::string>& args)
{
	std::string elementLabel, elementType, str, component, direct, output, yesno;
	elementLabel = readStringNoSpacesOffTop(args);
	elementType = readStringNoSpacesOffTop(args);
	str = readStringNoSpacesOffTop(args);
	component = readStringNoSpacesOffTop(args);
	direct = readStringNoSpacesOffTop(args);
	output = readStringNoSpacesOffTop(args);
	yesno = readStringNoSpacesOffTop(args);
}

void MbD::MBDynDrive::createASMT()
{
	assert(false);
}
