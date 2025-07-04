#include "../src/FactoryAssemblyLine.h"
#include "./doctest.h"
#include <stdexcept> 
#include <sstream>
#include <iostream>


TEST_CASE("FactoryAssemblyLine Initialization") {
    SUBCASE("Valid Initialization") {
        FactoryAssemblyLine line(5);
        CHECK(line.getNumStations() == 5);
        CHECK(line.getNumActiveStations() == 0);
        CHECK(line.getNumInactiveStations() == 5);
    }

    SUBCASE("Invalid Initialization") {
        CHECK_THROWS_AS(FactoryAssemblyLine(-1), std::invalid_argument);
    }
}

TEST_CASE("Adding and Removing Stations") {
    FactoryAssemblyLine line(5);

    SUBCASE("Add Station") {
        line.addStation(1, 10);
        CHECK(line.getProcessingTime(1) == 10);
        CHECK(line.getNumInactiveStations() == 4);
    }

    SUBCASE("Remove Station") {
        line.addStation(1, 10);
        line.removeStation(1);
        CHECK_THROWS_AS(line.getProcessingTime(1), std::out_of_range);
        CHECK(line.getNumInactiveStations() == 5);
    }

    SUBCASE("Invalid Station ID") {
        CHECK_THROWS_AS(line.addStation(-1, 10), std::invalid_argument);
        CHECK_THROWS_AS(line.removeStation(10), std::out_of_range);
    }
}

TEST_CASE("Starting and Stopping Assembly") {
    FactoryAssemblyLine line(5);
    line.addStation(1, 10);

    SUBCASE("Start Assembly") {
        line.startAssembly(1);
        CHECK(line.isStationActive(1) == true);
        CHECK(line.getNumActiveStations() == 1);
    }

    SUBCASE("Stop Assembly") {
        line.startAssembly(1);
        line.stopAssembly(1);
        CHECK(line.isStationActive(1) == false);
        CHECK(line.getNumActiveStations() == 0);
    }

    SUBCASE("Invalid Station ID") {
        CHECK_THROWS_AS(line.startAssembly(10), std::out_of_range);
        CHECK_THROWS_AS(line.stopAssembly(10), std::out_of_range);
    }
}

TEST_CASE("Processing Time Calculations") {
    FactoryAssemblyLine line(5);
    line.addStation(1, 10);
    line.addStation(2, 20);

    SUBCASE("Total Processing Time") {
        line.startAssembly(1);
        line.startAssembly(2);
        CHECK(line.getTotalProcessingTime() == 30);
    }

    SUBCASE("Inactive Stations Not Counted") {
        line.startAssembly(1);
        CHECK(line.getTotalProcessingTime() == 10);
    }
}

TEST_CASE("Edge Cases") {
    FactoryAssemblyLine line(5);

    SUBCASE("Duplicate Station Addition") {
        line.addStation(1, 10);
        CHECK_THROWS_AS(line.addStation(1, 15), std::invalid_argument);
    }

    SUBCASE("Removing Non-Existent Station") {
        CHECK_THROWS_AS(line.removeStation(1), std::out_of_range);
    }

    SUBCASE("Starting/Stopping Non-Existent Station") {
        CHECK_THROWS_AS(line.startAssembly(1), std::out_of_range);
        CHECK_THROWS_AS(line.stopAssembly(1), std::out_of_range);
    }
}




