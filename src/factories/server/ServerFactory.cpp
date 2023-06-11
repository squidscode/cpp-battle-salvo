#include "ServerFactory.hpp"
#include <exception>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace Factory;

ServerFactory::ServerFactory(const char* username, Controller::GameType game_type, const char* host, int port, PlayerFactory *pf){
    int status, valread, client_fd;
    struct sockaddr_in serv_addr;
    char buffer[1024] = { 0 };
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr, "\n Socket creation error \n");
        exit(1);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if(inet_pton(AF_INET, host, &serv_addr.sin_addr) <= 0) {
        fprintf(stderr, "\n Invalid address / Address not supported \n");
        exit(1);
    }

    if ((status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
        fprintf(stderr, "\nConnection Failed \n");
        exit(1);
    }
    this->client_fd = client_fd;
    this->player = pf->CreatePlayer();
    this->controller = new Controller::ProxyController(username, game_type, client_fd, this->player);
}

ServerFactory::~ServerFactory() {
    delete this->player;
    delete this->controller;
    close(this->client_fd);
}

View::View *ServerFactory::CreateView(){
    throw std::runtime_error("Illegal call to create view (view does not exist).");
}

Controller::Controller *ServerFactory::CreateController(){
    return this->controller;
}

Model::BattleSalvoGame *ServerFactory::CreateBattleSalvoGame(){
    throw std::runtime_error("Model not created for a ServerFactory.");
}
