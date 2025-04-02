#ifndef FACTORY_ASSEMBLY_LINE_H
#define FACTORY_ASSEMBLY_LINE_H

#include <stdexcept>

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
};

#endif // FACTORY_ASSEMBLY_LINE_H