#pragma once
#include "Server.hpp"
#include "Client.hpp"
#include "Utilities.hpp"
#include "Replies.hpp"


class Client;

class Channel {
    public:
        std::vector<Client> channel_client;

};