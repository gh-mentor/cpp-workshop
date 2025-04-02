#include "../src/FactoryAssemblyLine.h"
#include <gtest/gtest.h>

class FactoryAssemblyLineTest : public ::testing::Test {
protected:
    FactoryAssemblyLine assemblyLine{5}; // Initialize with 5 stations
};

TEST_F(FactoryAssemblyLineTest, StartAssemblyLine) {
    EXPECT_NO_THROW(assemblyLine.start());
}

TEST_F(FactoryAssemblyLineTest, StopAssemblyLine) {
    assemblyLine.start();
    EXPECT_NO_THROW(assemblyLine.stop());
}

TEST_F(FactoryAssemblyLineTest, ProduceChip) {
    assemblyLine.start();
    std::string chipId = assemblyLine.produceChip();
    EXPECT_FALSE(chipId.empty());
}

TEST_F(FactoryAssemblyLineTest, CheckAssemblyLineStatus) {
    EXPECT_FALSE(assemblyLine.isRunning());
    assemblyLine.start();
    EXPECT_TRUE(assemblyLine.isRunning());
}

TEST_F(FactoryAssemblyLineTest, AddAndRemoveStation) {
    EXPECT_NO_THROW(assemblyLine.addStation(6, 10));
    EXPECT_EQ(assemblyLine.getNumStations(), 6);
    EXPECT_NO_THROW(assemblyLine.removeStation(6));
    EXPECT_EQ(assemblyLine.getNumStations(), 5);
}

TEST_F(FactoryAssemblyLineTest, StartAndStopStation) {
    EXPECT_NO_THROW(assemblyLine.startAssembly(1));
    EXPECT_TRUE(assemblyLine.isStationActive(1));
    EXPECT_NO_THROW(assemblyLine.stopAssembly(1));
    EXPECT_FALSE(assemblyLine.isStationActive(1));
}

TEST_F(FactoryAssemblyLineTest, GetProcessingTime) {
    assemblyLine.addStation(6, 15);
    EXPECT_EQ(assemblyLine.getProcessingTime(6), 15);
}

TEST_F(FactoryAssemblyLineTest, GetTotalProcessingTime) {
    assemblyLine.addStation(6, 10);
    assemblyLine.addStation(7, 20);
    EXPECT_EQ(assemblyLine.getTotalProcessingTime(), 30);
}

TEST_F(FactoryAssemblyLineTest, ActiveAndInactiveStations) {
    assemblyLine.startAssembly(1);
    assemblyLine.startAssembly(2);
    EXPECT_EQ(assemblyLine.getNumActiveStations(), 2);
    EXPECT_EQ(assemblyLine.getNumInactiveStations(), 3);
}