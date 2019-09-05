#include "ImageStreamer.h"
#include <iostream>
#include <boost/log/trivial.hpp>

ImageStreamer::ImageStreamer()
{
    BOOST_LOG_TRIVIAL(debug) << __PRETTY_FUNCTION__;

    if (!camera_.isOpened())
    {
        camera_.setHeight(imageHeight);
        camera_.setWidth(imageWidth);
        camera_.setFormat(raspicam::RASPICAM_FORMAT_GRAY);
        camera_.setFrameRate(2);

        BOOST_LOG_TRIVIAL(info) << "Opening camera ...";
        if ( !camera_.open() )
        {
            BOOST_LOG_TRIVIAL(error) << "Error opening camera!";
        }
        // wait a while until camera stabilizes
        sleep(3);
    }
}

ImageStreamer::~ImageStreamer()
{
    BOOST_LOG_TRIVIAL(debug) << __PRETTY_FUNCTION__;
}

void ImageStreamer::addClient(const std::string &ipAddress)
{
    BOOST_LOG_TRIVIAL(debug) << __PRETTY_FUNCTION__;

    if (socket_.is_open())
    {
        BOOST_LOG_TRIVIAL(warning) << "Already a client connected";
        return;
    }
    socket_.connect( boost::asio::ip::tcp::endpoint( boost::asio::ip::address::from_string(ipAddress), 8082));
    streamingActive_ = true;
    m_workerThread = std::thread(&ImageStreamer::sendImage, this);
    m_workerThread.detach();
}

void ImageStreamer::stop()
{
    BOOST_LOG_TRIVIAL(debug) << __PRETTY_FUNCTION__;

    streamingActive_ = false;
    socket_.close();
}

void ImageStreamer::sendImage()
{
    BOOST_LOG_TRIVIAL(debug) << __PRETTY_FUNCTION__;

    boost::system::error_code we;

    while (streamingActive_)
    {
        camera_.grab();
        camera_.retrieve(imageBuffer_.data());

        boost::asio::write( socket_, boost::asio::buffer(imageBuffer_.data(),imageBuffer_.size()), we);

        if (we)
        {
            BOOST_LOG_TRIVIAL(error) << "ImageStreamer write error: " << we.message();
            stop();
        }
    }
}
