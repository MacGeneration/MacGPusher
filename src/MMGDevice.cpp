#include "MMGDevice.hpp"


#pragma mark - Contructors
/**
 * @brief Initialize token and badge number to empty values
 */
MMGDevice::MMGDevice(void)
{
	this->_token = "";
	this->_badge = 0;
}

/**
 * @brief Initialize token and badge number
 * @param token [in] : Device token
 * @param port [in] : Badge number
 */
MMGDevice::MMGDevice(const std::string& token, const unsigned int badge)
{
	this->_token = token;
	this->_badge = badge;
}

#pragma mark - Setters
/**
 * @brief Set device token
 * @param token [in] : Device token
 */
void MMGDevice::SetToken(const std::string& token)
{
	this->_token = token;
}

/**
 * @brief Set device badge number
 * @param badge [in] : Badge number
 */
void MMGDevice::SetBadge(const unsigned int badge)
{
	this->_badge = badge;
}
