#include "Server.hpp"
#include "Client.hpp"
#include "Utilities.hpp"
#include "Replies.hpp"

Channel::Channel(const std::string& channelName) : channel_name(channelName) {}

Channel::~Channel() {}