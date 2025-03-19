//
// Created by kotik on 19/03/2025.
//
#include <pybind11/pybind11.h>
#ifndef PYTHON_BINDINGS_H
#include "unitree_lidar_sdk.h"
#include <memory>
#include <sstream> // __str__
#include <string>

#include <functional>

#ifndef BINDER_PYBIND11_TYPE_CASTER
        #define BINDER_PYBIND11_TYPE_CASTER
        PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>, false)
        PYBIND11_DECLARE_HOLDER_TYPE(T, T*, false)
        PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

PYBIND11_MODULE(lidar, M) {
        // unitree_lidar_sdk::get_system_timestamp() file:include/unitree_lidar_sdk.h line:42
        M.def("get_system_timestamp", (double (*)()) &unitree_lidar_sdk::get_system_timestamp, "Get the system timestamp in seconds.\n\nC++: unitree_lidar_sdk::get_system_timestamp() --> double");

        // unitree_lidar_sdk::MessageType file:include/unitree_lidar_sdk.h line:92
        pybind11::enum_<unitree_lidar_sdk::MessageType>(M, "MessageType", pybind11::arithmetic(), "Returned message type after one parse")
                .value("NONE", unitree_lidar_sdk::NONE)
                .value("IMU", unitree_lidar_sdk::IMU)
                .value("POINTCLOUD", unitree_lidar_sdk::POINTCLOUD)
                .value("RANGE", unitree_lidar_sdk::RANGE)
                .value("AUXILIARY", unitree_lidar_sdk::AUXILIARY)
                .value("VERSION", unitree_lidar_sdk::VERSION)
                .value("TIMESYNC", unitree_lidar_sdk::TIMESYNC)
                .export_values();

        ;

        // unitree_lidar_sdk::LidarWorkingMode file:include/unitree_lidar_sdk.h line:105
        pybind11::enum_<unitree_lidar_sdk::LidarWorkingMode>(M, "LidarWorkingMode", pybind11::arithmetic(), "Lidar Woking Mode")
                .value("NORMAL", unitree_lidar_sdk::NORMAL)
                .value("STANDBY", unitree_lidar_sdk::STANDBY)
                .export_values();

        ;

        // unitree_lidar_sdk::LEDDisplayMode file:include/unitree_lidar_sdk.h line:114
        pybind11::enum_<unitree_lidar_sdk::LEDDisplayMode>(M, "LEDDisplayMode", pybind11::arithmetic(), "LED display mode")
                .value("FORWARD_SLOW", unitree_lidar_sdk::FORWARD_SLOW)
                .value("FORWARD_FAST", unitree_lidar_sdk::FORWARD_FAST)
                .value("REVERSE_SLOW", unitree_lidar_sdk::REVERSE_SLOW)
                .value("REVERSE_FAST", unitree_lidar_sdk::REVERSE_FAST)
                .value("TRIPLE_FLIP", unitree_lidar_sdk::TRIPLE_FLIP)
                .value("TRIPLE_BREATHING", unitree_lidar_sdk::TRIPLE_BREATHING)
                .value("SIXSTAGE_BREATHING", unitree_lidar_sdk::SIXSTAGE_BREATHING)
                .export_values();

        ;
        {
                pybind11::class_<unitree_lidar_sdk::PointUnitree>(M, "PointUnitree")
                .def(pybind11::init<>()) // Default constructor
                .def_readwrite("x", &unitree_lidar_sdk::PointUnitree::x)
                .def_readwrite("y", &unitree_lidar_sdk::PointUnitree::y)
                .def_readwrite("z", &unitree_lidar_sdk::PointUnitree::z)
                .def_readwrite("intensity", &unitree_lidar_sdk::PointUnitree::intensity)
                .def_readwrite("time", &unitree_lidar_sdk::PointUnitree::time)
                .def_readwrite("ring", &unitree_lidar_sdk::PointUnitree::ring);
        };

        {
                pybind11::class_<unitree_lidar_sdk::PointCloudUnitree>(M, "PointCloudUnitree")
                .def(pybind11::init<>()) // Default constructor
                .def_readwrite("stamp", &unitree_lidar_sdk::PointCloudUnitree::stamp)
                .def_readwrite("id", &unitree_lidar_sdk::PointCloudUnitree::id)
                .def_readwrite("ringNum", &unitree_lidar_sdk::PointCloudUnitree::ringNum)
                .def_readwrite("points", &unitree_lidar_sdk::PointCloudUnitree::points);
        };

        { // unitree_lidar_sdk::UnitreeLidarReader file:include/unitree_lidar_sdk.h line:128
                pybind11::class_<unitree_lidar_sdk::UnitreeLidarReader, std::shared_ptr<unitree_lidar_sdk::UnitreeLidarReader>> cl(M, "UnitreeLidarReader", "Unitree Lidar Reader");
                cl.def("initialize", [](unitree_lidar_sdk::UnitreeLidarReader &o) -> int { return o.initialize(); }, "");
                cl.def("initialize", [](unitree_lidar_sdk::UnitreeLidarReader &o, unsigned short const & a0) -> int { return o.initialize(a0); }, "", pybind11::arg("cloud_scan_num"));
                cl.def("initialize", [](unitree_lidar_sdk::UnitreeLidarReader &o, unsigned short const & a0, std::string const & a1) -> int { return o.initialize(a0, a1); }, "", pybind11::arg("cloud_scan_num"), pybind11::arg("port"));
                cl.def("initialize", [](unitree_lidar_sdk::UnitreeLidarReader &o, unsigned short const & a0, std::string const & a1, unsigned int const & a2) -> int { return o.initialize(a0, a1, a2); }, "", pybind11::arg("cloud_scan_num"), pybind11::arg("port"), pybind11::arg("baudrate"));
                cl.def("initialize", [](unitree_lidar_sdk::UnitreeLidarReader &o, unsigned short const & a0, std::string const & a1, unsigned int const & a2, float const & a3) -> int { return o.initialize(a0, a1, a2, a3); }, "", pybind11::arg("cloud_scan_num"), pybind11::arg("port"), pybind11::arg("baudrate"), pybind11::arg("rotate_yaw_bias"));
                cl.def("initialize", [](unitree_lidar_sdk::UnitreeLidarReader &o, unsigned short const & a0, std::string const & a1, unsigned int const & a2, float const & a3, float const & a4) -> int { return o.initialize(a0, a1, a2, a3, a4); }, "", pybind11::arg("cloud_scan_num"), pybind11::arg("port"), pybind11::arg("baudrate"), pybind11::arg("rotate_yaw_bias"), pybind11::arg("range_scale"));
                cl.def("initialize", [](unitree_lidar_sdk::UnitreeLidarReader &o, unsigned short const & a0, std::string const & a1, unsigned int const & a2, float const & a3, float const & a4, float const & a5) -> int { return o.initialize(a0, a1, a2, a3, a4, a5); }, "", pybind11::arg("cloud_scan_num"), pybind11::arg("port"), pybind11::arg("baudrate"), pybind11::arg("rotate_yaw_bias"), pybind11::arg("range_scale"), pybind11::arg("range_bias"));
                cl.def("initialize", [](unitree_lidar_sdk::UnitreeLidarReader &o, unsigned short const & a0, std::string const & a1, unsigned int const & a2, float const & a3, float const & a4, float const & a5, float const & a6) -> int { return o.initialize(a0, a1, a2, a3, a4, a5, a6); }, "", pybind11::arg("cloud_scan_num"), pybind11::arg("port"), pybind11::arg("baudrate"), pybind11::arg("rotate_yaw_bias"), pybind11::arg("range_scale"), pybind11::arg("range_bias"), pybind11::arg("range_max"));
                cl.def("initialize", (int (unitree_lidar_sdk::UnitreeLidarReader::*)(unsigned short, std::string, unsigned int, float, float, float, float, float)) &unitree_lidar_sdk::UnitreeLidarReader::initialize, "Initialize \n \n\n Return 0 if the serial port is opened successfully; \n return -1 if we failed to open the serial port.\n\nC++: unitree_lidar_sdk::UnitreeLidarReader::initialize(unsigned short, std::string, unsigned int, float, float, float, float, float) --> int", pybind11::arg("cloud_scan_num"), pybind11::arg("port"), pybind11::arg("baudrate"), pybind11::arg("rotate_yaw_bias"), pybind11::arg("range_scale"), pybind11::arg("range_bias"), pybind11::arg("range_max"), pybind11::arg("range_min"));
                cl.def("initializeUDP", [](unitree_lidar_sdk::UnitreeLidarReader &o) -> int { return o.initializeUDP(); }, "");
                cl.def("initializeUDP", [](unitree_lidar_sdk::UnitreeLidarReader &o, unsigned short const & a0) -> int { return o.initializeUDP(a0); }, "", pybind11::arg("cloud_scan_num"));
                cl.def("initializeUDP", [](unitree_lidar_sdk::UnitreeLidarReader &o, unsigned short const & a0, unsigned short const & a1) -> int { return o.initializeUDP(a0, a1); }, "", pybind11::arg("cloud_scan_num"), pybind11::arg("lidar_port"));
                cl.def("initializeUDP", [](unitree_lidar_sdk::UnitreeLidarReader &o, unsigned short const & a0, unsigned short const & a1, std::string const & a2) -> int { return o.initializeUDP(a0, a1, a2); }, "", pybind11::arg("cloud_scan_num"), pybind11::arg("lidar_port"), pybind11::arg("lidar_ip"));
                cl.def("initializeUDP", [](unitree_lidar_sdk::UnitreeLidarReader &o, unsigned short const & a0, unsigned short const & a1, std::string const & a2, unsigned short const & a3) -> int { return o.initializeUDP(a0, a1, a2, a3); }, "", pybind11::arg("cloud_scan_num"), pybind11::arg("lidar_port"), pybind11::arg("lidar_ip"), pybind11::arg("local_port"));
                cl.def("initializeUDP", [](unitree_lidar_sdk::UnitreeLidarReader &o, unsigned short const & a0, unsigned short const & a1, std::string const & a2, unsigned short const & a3, std::string const & a4) -> int { return o.initializeUDP(a0, a1, a2, a3, a4); }, "", pybind11::arg("cloud_scan_num"), pybind11::arg("lidar_port"), pybind11::arg("lidar_ip"), pybind11::arg("local_port"), pybind11::arg("local_ip"));
                cl.def("initializeUDP", [](unitree_lidar_sdk::UnitreeLidarReader &o, unsigned short const & a0, unsigned short const & a1, std::string const & a2, unsigned short const & a3, std::string const & a4, float const & a5) -> int { return o.initializeUDP(a0, a1, a2, a3, a4, a5); }, "", pybind11::arg("cloud_scan_num"), pybind11::arg("lidar_port"), pybind11::arg("lidar_ip"), pybind11::arg("local_port"), pybind11::arg("local_ip"), pybind11::arg("rotate_yaw_bias"));
                cl.def("initializeUDP", [](unitree_lidar_sdk::UnitreeLidarReader &o, unsigned short const & a0, unsigned short const & a1, std::string const & a2, unsigned short const & a3, std::string const & a4, float const & a5, float const & a6) -> int { return o.initializeUDP(a0, a1, a2, a3, a4, a5, a6); }, "", pybind11::arg("cloud_scan_num"), pybind11::arg("lidar_port"), pybind11::arg("lidar_ip"), pybind11::arg("local_port"), pybind11::arg("local_ip"), pybind11::arg("rotate_yaw_bias"), pybind11::arg("range_scale"));
                cl.def("initializeUDP", [](unitree_lidar_sdk::UnitreeLidarReader &o, unsigned short const & a0, unsigned short const & a1, std::string const & a2, unsigned short const & a3, std::string const & a4, float const & a5, float const & a6, float const & a7) -> int { return o.initializeUDP(a0, a1, a2, a3, a4, a5, a6, a7); }, "", pybind11::arg("cloud_scan_num"), pybind11::arg("lidar_port"), pybind11::arg("lidar_ip"), pybind11::arg("local_port"), pybind11::arg("local_ip"), pybind11::arg("rotate_yaw_bias"), pybind11::arg("range_scale"), pybind11::arg("range_bias"));
                cl.def("initializeUDP", [](unitree_lidar_sdk::UnitreeLidarReader &o, unsigned short const & a0, unsigned short const & a1, std::string const & a2, unsigned short const & a3, std::string const & a4, float const & a5, float const & a6, float const & a7, float const & a8) -> int { return o.initializeUDP(a0, a1, a2, a3, a4, a5, a6, a7, a8); }, "", pybind11::arg("cloud_scan_num"), pybind11::arg("lidar_port"), pybind11::arg("lidar_ip"), pybind11::arg("local_port"), pybind11::arg("local_ip"), pybind11::arg("rotate_yaw_bias"), pybind11::arg("range_scale"), pybind11::arg("range_bias"), pybind11::arg("range_max"));
                cl.def("initializeUDP", (int (unitree_lidar_sdk::UnitreeLidarReader::*)(unsigned short, unsigned short, std::string, unsigned short, std::string, float, float, float, float, float)) &unitree_lidar_sdk::UnitreeLidarReader::initializeUDP, "Initialize for UDP board\n\nC++: unitree_lidar_sdk::UnitreeLidarReader::initializeUDP(unsigned short, unsigned short, std::string, unsigned short, std::string, float, float, float, float, float) --> int", pybind11::arg("cloud_scan_num"), pybind11::arg("lidar_port"), pybind11::arg("lidar_ip"), pybind11::arg("local_port"), pybind11::arg("local_ip"), pybind11::arg("rotate_yaw_bias"), pybind11::arg("range_scale"), pybind11::arg("range_bias"), pybind11::arg("range_max"), pybind11::arg("range_min"));
                cl.def("closeUDP", (bool (unitree_lidar_sdk::UnitreeLidarReader::*)()) &unitree_lidar_sdk::UnitreeLidarReader::closeUDP, "Close UDP connection\n\nC++: unitree_lidar_sdk::UnitreeLidarReader::closeUDP() --> bool");
                cl.def("getIMU", &unitree_lidar_sdk::UnitreeLidarReader::getIMU);
                cl.def("getCloud", &unitree_lidar_sdk::UnitreeLidarReader::getCloud);
                cl.def("runParse", (enum unitree_lidar_sdk::MessageType (unitree_lidar_sdk::UnitreeLidarReader::*)()) &unitree_lidar_sdk::UnitreeLidarReader::runParse, "Try to parse a message from the serial buffer once.\n \n\n This is the main entrance of this class\n \n\n \n  NONE if no valid message parsed.\n  IMU if a new imu message is parsed.\n  POINTCLOUD if a new cloud is cached.\n\nC++: unitree_lidar_sdk::UnitreeLidarReader::runParse() --> enum unitree_lidar_sdk::MessageType");
                cl.def("reset", (void (unitree_lidar_sdk::UnitreeLidarReader::*)()) &unitree_lidar_sdk::UnitreeLidarReader::reset, "Reset lidar\n\nC++: unitree_lidar_sdk::UnitreeLidarReader::reset() --> void");
                cl.def("getVersionOfFirmware", (std::string (unitree_lidar_sdk::UnitreeLidarReader::*)() const) &unitree_lidar_sdk::UnitreeLidarReader::getVersionOfFirmware, "Get Version of lidar firmware\n\nC++: unitree_lidar_sdk::UnitreeLidarReader::getVersionOfFirmware() const --> std::string");
                cl.def("getVersionOfSDK", (std::string (unitree_lidar_sdk::UnitreeLidarReader::*)() const) &unitree_lidar_sdk::UnitreeLidarReader::getVersionOfSDK, "Get the Version of Lidar SDK \n\nC++: unitree_lidar_sdk::UnitreeLidarReader::getVersionOfSDK() const --> std::string");
                cl.def("getTimeDelay", (unsigned int (unitree_lidar_sdk::UnitreeLidarReader::*)() const) &unitree_lidar_sdk::UnitreeLidarReader::getTimeDelay, "Get time delay of one-way data transmission in us.\n\nC++: unitree_lidar_sdk::UnitreeLidarReader::getTimeDelay() const --> unsigned int");
                cl.def("getDirtyPercentage", (float (unitree_lidar_sdk::UnitreeLidarReader::*)() const) &unitree_lidar_sdk::UnitreeLidarReader::getDirtyPercentage, "Get the removal percentage of points due to the dirt on the protection cover\n \n\n the percentage of removed dirty points\n\nC++: unitree_lidar_sdk::UnitreeLidarReader::getDirtyPercentage() const --> float");
                cl.def("setLidarWorkingMode", (void (unitree_lidar_sdk::UnitreeLidarReader::*)(enum unitree_lidar_sdk::LidarWorkingMode)) &unitree_lidar_sdk::UnitreeLidarReader::setLidarWorkingMode, "Set the Lidar Working Mode\n \n\n \n\nC++: unitree_lidar_sdk::UnitreeLidarReader::setLidarWorkingMode(enum unitree_lidar_sdk::LidarWorkingMode) --> void", pybind11::arg("mode"));
                cl.def("setLEDDisplayMode", (void (unitree_lidar_sdk::UnitreeLidarReader::*)(enum unitree_lidar_sdk::LEDDisplayMode)) &unitree_lidar_sdk::UnitreeLidarReader::setLEDDisplayMode, "Ser LEF display mode with default pattern\n \n\n \n  LED_RING_FUN_FORWARD_SLOW_MODE=2,  Function mode forward at slow.\n  LED_RING_FUN_FORWARD_FAST_MODE=3,  Function mode forward at fast. \n  LED_RING_FUN_REVERSE_SLOW_MODE=4,  Function mode reverse at slow.\n  LED_RING_FUN_REVERSE_FAST_MODE=5,  Function mode reverse at fast. \n  LED_RING_FUN_TRIPLE_FLIP_MODE=6,   Function mode triple flip.\n  LED_RING_FUN_TRIPLE_BREATHING_MODE=7,  Function mode triple breathing.\n  LED_RING_FUN_SIXSTAGE_BREATHING_MODE=8, Function mode six-stage breathing.\n\nC++: unitree_lidar_sdk::UnitreeLidarReader::setLEDDisplayMode(enum unitree_lidar_sdk::LEDDisplayMode) --> void", pybind11::arg("mode"));
                cl.def("printConfig", (void (unitree_lidar_sdk::UnitreeLidarReader::*)()) &unitree_lidar_sdk::UnitreeLidarReader::printConfig, "Print configuration parameters\n\nC++: unitree_lidar_sdk::UnitreeLidarReader::printConfig() --> void");
                cl.def("assign", (class unitree_lidar_sdk::UnitreeLidarReader & (unitree_lidar_sdk::UnitreeLidarReader::*)(const class unitree_lidar_sdk::UnitreeLidarReader &)) &unitree_lidar_sdk::UnitreeLidarReader::operator=, "C++: unitree_lidar_sdk::UnitreeLidarReader::operator=(const class unitree_lidar_sdk::UnitreeLidarReader &) --> class unitree_lidar_sdk::UnitreeLidarReader &", pybind11::return_value_policy::automatic, pybind11::arg(""));
        }
        // unitree_lidar_sdk::createUnitreeLidarReader() file:include/unitree_lidar_sdk.h line:251
        M.def("createUnitreeLidarReader", (class unitree_lidar_sdk::UnitreeLidarReader * (*)()) &unitree_lidar_sdk::createUnitreeLidarReader, "Create a Unitree Lidar Reader object\n \n\n UnitreeLidarReader* \n\nC++: unitree_lidar_sdk::createUnitreeLidarReader() --> class unitree_lidar_sdk::UnitreeLidarReader *", pybind11::return_value_policy::automatic);
}

#define PYTHON_BINDINGS_H

#endif //PYTHON_BINDINGS_H