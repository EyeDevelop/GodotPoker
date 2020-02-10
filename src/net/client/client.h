//
// Created by eyedevelop on 10/02/2020.
//

#ifndef GODOTPOKER_CLIENT_H
#define GODOTPOKER_CLIENT_H

#include <string>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketStream.h>
#include <Poco/Poco.h>

class Client {
    std::string endpoint;
    Poco::Net::StreamSocket socket;
    Poco::Net::SocketStream stream;

public:
    explicit Client(std::string_view host);

    void send_message(std::string_view msg);

    std::string receive_message();
};

#endif //GODOTPOKER_CLIENT_H
