#include "FactoryAssemblyLine.h"
#include <stdexcept>

/**
 * Constructor for FactoryAssemblyLine.
 * @param numStations The total number of stations in the assembly line.
 * @throws std::invalid_argument if numStations is negative.
 */
FactoryAssemblyLine::FactoryAssemblyLine(int numStations)
  : m_numStations(numStations), m_numActiveStations(0) {
  if (numStations < 0) {
    throw std::invalid_argument("Number of stations cannot be negative");
  }
}

/**
 * Adds a station to the assembly line.
 * @param stationId The ID of the station.
 * @param processingTime The processing time of the station.
 */
void FactoryAssemblyLine::addStation(int stationId, int processingTime) {
  throw std::logic_error("Not implemented");
}

/**
 * Removes a station from the assembly line.
 * @param stationId The ID of the station.
 */
void FactoryAssemblyLine::removeStation(int stationId) {
  throw std::logic_error("Not implemented");
}

/**
 * Starts the assembly process for a station.
 * @param stationId The ID of the station.
 */
void FactoryAssemblyLine::startAssembly(int stationId) {
  throw std::logic_error("Not implemented");
}

/**
 * Stops the assembly process for a station.
 * @param stationId The ID of the station.
 */
void FactoryAssemblyLine::stopAssembly(int stationId) {
  throw std::logic_error("Not implemented");
}

/**
 * Gets the processing time of a station.
 * @param stationId The ID of the station.
 * @return The processing time of the station.
 */
int FactoryAssemblyLine::getProcessingTime(int stationId) const {
  throw std::logic_error("Not implemented");
}

/**
 * Gets the total processing time of all active stations.
 * @return The total processing time.
 */
int FactoryAssemblyLine::getTotalProcessingTime() const {
  throw std::logic_error("Not implemented");
}

/**
 * Gets the total number of stations.
 * @return The total number of stations.
 */
int FactoryAssemblyLine::getNumStations() const {
  throw std::logic_error("Not implemented");
}

/**
 * Gets the number of active stations.
 * @return The number of active stations.
 */
int FactoryAssemblyLine::getNumActiveStations() const {
  throw std::logic_error("Not implemented");
}

/**
 * Gets the number of inactive stations.
 * @return The number of inactive stations.
 */
int FactoryAssemblyLine::getNumInactiveStations() const {
  throw std::logic_error("Not implemented");
}

/**
 * Checks if a station is active.
 * @param stationId The ID of the station.
 * @return True if the station is active, false otherwise.
 */
bool FactoryAssemblyLine::isStationActive(int stationId) const {
  throw std::logic_error("Not implemented");
}