#include "Server.h"

//importing libraries
#include <iostream>
#include <boost/enable_shared_from_this.hpp>
#include <boost/optional.hpp>
#include <boost/utility/in_place_factory.hpp>

#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>

#include <thread>
#include <chrono>

using namespace boost::asio;
using ip::tcp;


static void init_log()
{
    static const std::string COMMON_FMT("[%TimeStamp%][%Severity%]:  %Message%");

    boost::log::register_simple_formatter_factory< boost::log::trivial::severity_level, char >("Severity");

    // Output message to console
    boost::log::add_console_log(
        std::cout,
        boost::log::keywords::format = COMMON_FMT,
        boost::log::keywords::auto_flush = true
    );

    // Output message to file, rotates when file reached 1mb or at midnight every day. Each log file
    // is capped at 1mb and total is 20mb
    boost::log::add_file_log (
        boost::log::keywords::file_name = "raspicam-daemon_%3N.log",
        boost::log::keywords::rotation_size = 1 * 1024 * 1024,
        boost::log::keywords::max_size = 20 * 1024 * 1024,
        boost::log::keywords::format = COMMON_FMT,
        boost::log::keywords::auto_flush = true
    );

    boost::log::add_common_attributes();

    // Only output message with INFO or higher severity in Release
#ifndef _DEBUG
    boost::log::core::get()->set_filter(
        boost::log::trivial::severity >= boost::log::trivial::info
    );
#endif

}

int main()
{
    init_log();

    boost::asio::io_service ioService;
    Server ctrlServer(&ioService, 8083);

    try
    {
        ioService.run();
    }
    catch(std::exception& e)
    {
        BOOST_LOG_TRIVIAL(fatal) << "exception in ioService.run(): " << e.what();
    }

    return 0;
}
