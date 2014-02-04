#pragma once

#include <string>


class GenericEntity {
public:
	GenericEntity(const std::string& propertyPrefix);

	const std::string& propertyPrefix() const;


protected:
	std::string m_propertyPrefix;
};

