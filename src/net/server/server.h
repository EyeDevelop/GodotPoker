//
// Created by eyedevelop on 06/02/2020.
//

#ifndef GODOTPOKER_SERVER_H
#define GODOTPOKER_SERVER_H

#include <boost/asio.hpp>

class Server {
    boost::asio::ip::tcp::acceptor acceptor_;

    void start_accept();

    void handle_accept(tcp_connection::pointer new_conn, const boost::system::error_code &error);

public:
    explicit Server(boost::asio::io_context &io_context) noexcept;
};


#endif //GODOTPOKER_SERVER_H
