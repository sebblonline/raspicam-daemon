#ifndef IMAGESTREAMER_H
#define IMAGESTREAMER_H

#include <raspicam/raspicam.h>
#include <boost/asio.hpp>
#include <array>
#include <thread>


class ImageStreamer
{
public:
    explicit ImageStreamer();
    ~ImageStreamer();

    void addClient(const std::string& ipAddress);

    void stop();

private:
    void sendImage();

    boost::asio::io_service io_service_;
    boost::asio::ip::tcp::socket socket_ = boost::asio::ip::tcp::socket(io_service_);

    raspicam::RaspiCam camera_;

    std::thread m_workerThread;
    bool streamingActive_ = false;

    static constexpr size_t imageHeight = 480;
    static constexpr size_t imageWidth = 640;
    static constexpr size_t colorDepth = 1;

    std::array<unsigned char, imageHeight*imageWidth*colorDepth> imageBuffer_;
};

#endif // IMAGESTREAMER_H
