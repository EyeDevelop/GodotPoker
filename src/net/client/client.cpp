//
// Created by eyedevelop on 10/02/2020.
//

#include "client.h"

Client::Client(std::string_view host)
    : endpoint{ host },
        socket{ Poco::Net::StreamSocket{ { endpoint, 6969 } } },
        stream{ Poco::Net::SocketStream{ socket } } {}

void Client::send_message(std::string_view msg) {
    this->stream << msg;
    this->stream.flush();
}

std::string Client::receive_message() {
    std::string ret;
    this->stream >> ret;

    return ret;
}
