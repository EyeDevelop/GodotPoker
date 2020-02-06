//
// Created by eyedevelop on 06/02/2020.
//

#include "server.h"
#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/bind.hpp>

using tcp = boost::asio::ip::tcp;

Server::Server(boost::asio::io_context &io_context) noexcept
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), 6969)) {
    start_accept();
}

int main() {
    try {
        boost::asio::io_context io_context;
        Server server(io_context);
        io_context.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

void Server::start_accept() {
    tcp_connection::pointer new_conn = tcp_connection::create(acceptor_.get_executor().context());
    acceptor_.async_accept(new_conn->socket(), boost::bind(&Server::handle_accept, this, new_conn, boost::asio::placeholders::error));
}

void Server::handle_accept(tcp_connection::pointer new_conn, const boost::system::error_code &error) {
    if (!error) {
        new_conn->start();
    }

    start_accept();
}
