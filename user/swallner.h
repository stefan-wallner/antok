#ifndef ANTOK_USER_stefan_H
#define ANTOK_USER_stefan_H

#include<yaml-cpp/yaml.h>

namespace antok {

	class Function;

	namespace user {

		namespace stefan {

			antok::Function* getUserFunction(const YAML::Node& function,
			                                 std::vector<std::string>& quantityNames,
			                                 int index);
		antok::Function* getCalcLTProjections(const YAML::Node& function, std::vector<std::string>& quantityNames, int index);
		antok::Function* getCalcArmenterosAlpha(const YAML::Node& function, std::vector<std::string>& quantityNames, int index);
		antok::Function* getCalcRICHPID(const YAML::Node& function, std::vector<std::string>& quantityNames, int index);
		antok::Function* getDetermineKaonPionLV(const YAML::Node& function, std::vector<std::string>& quantityNames, int index);

		}

	}

}

#endif
