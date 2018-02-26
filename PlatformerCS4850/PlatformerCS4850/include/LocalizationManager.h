#ifndef LOCALIZATIONMANAGER_H
#define LOCALIZATIONMANAGER_H

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include "ConfigParser.h"

/** A manager for localizign strings */
class LocalizationManager {
public:
	/** Gets the singleton instance of the LocalizationManager */
	static LocalizationManager& instance() {
		if (inst_ == NULL) {
			inst_ = new LocalizationManager();
		}
		return *inst_;
	}
	
	/** Loads localization from a settings file */
	void loadLocalization() {
		// open file
		std::ifstream input;
		std::string locale = ConfigParser::instance().getSetting("locale", "en");
		std::string fileName = "./locales/" + locale + "-locale.txt";
		input.open(fileName);
		if (!input) {
			std::cerr << "Error: couldn't open locale " << locale << std::endl;
			exit(1);
		}

		// read in lines until end of file
		std::string line;
		while (std::getline(input, line)) {
			int delim = line.find("=");
			std::string key = line.substr(0, delim);
			std::string value = line.substr(delim + 1, line.length());
			translations.insert(std::pair<std::string, std::string>(key, value));
		}

		input.close();
	}

	/** Localize a string, returning the new value is applicable. Otherwise returns the old value */
	std::string localize(/** The string to localize */std::string str) {
		if (translations.count(str) > 0) {
			return translations[str];
		}
		return str;
	}

	/** Reset the Localization Manager */
	static void reset() {
		delete inst_;
		inst_ = NULL;
	}

private:
	/** Private constructor */
	LocalizationManager() {}
	/** Private Destructor */
	~LocalizationManager() {}

	/** The instance of the Localization Manager */
	static LocalizationManager* inst_;
	/** The localization mapping */
	std::map<std::string, std::string> translations;
};


#endif
