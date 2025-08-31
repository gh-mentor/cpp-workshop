#ifndef FACTORY_ASSEMBLY_LINE_H
#define FACTORY_ASSEMBLY_LINE_H

#include <unordered_map>

/**
 * Represents a factory assembly line with multiple stations.
 */
class FactoryAssemblyLine {
public:
  FactoryAssemblyLine(int numStations);

  void addStation(int stationId, int processingTime);
  void removeStation(int stationId);
  void startAssembly(int stationId);
  void stopAssembly(int stationId);

  int getProcessingTime(int stationId) const;
  int getTotalProcessingTime() const;
  int getNumStations() const;
  int getNumActiveStations() const;
  int getNumInactiveStations() const;
  bool isStationActive(int stationId) const;

private:
  struct Station {
    int processingTime;
    bool isActive;
  };

  int m_numStations;
  int m_numActiveStations;
  std::unordered_map<int, Station> m_stations;
};

#endif // FACTORY_ASSEMBLY_LINE_H