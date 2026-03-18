#ifndef LEVEL_CONFIG_LOADER_H
#define LEVEL_CONFIG_LOADER_H

#include <string>
#include "configs/models/LevelConfig.h"

/**
 * @brief Loads level configuration from JSON files.
 * @details Produces LevelConfig structures used by the model generator.
 */
namespace cardgame {

class LevelConfigLoader
{
public:
    /**
     * @brief Load level config from a JSON file.
     * @param filePath File path relative to search paths.
     * @param outConfig Output configuration.
     * @return true when parsing succeeds.
     */
    static bool loadFromFile(const std::string& filePath, LevelConfig& outConfig);
};

} // namespace cardgame

#endif // LEVEL_CONFIG_LOADER_H
