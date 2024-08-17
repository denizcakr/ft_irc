invite has a spesific flag like +i or -i, makes the channel invite only or not, "/INVITE #channel +i" or "/INVITE #channel -i".
also kick doesnt have a spesific flag like +i or sth, its just /KICK #channel username

4.2.7 Invite message
      Command: INVITE
   Parameters: <nickname> <channel>
   The INVITE message is used to invite users to a channel.  The
   parameter <nickname> is the nickname of the person to be invited to
   the target channel <channel>.  There is no requirement that the
   channel the target user is being invited to must exist or be a valid
   channel.  To invite a user to a channel which is invite only (MODE
   +i), the client sending the invite must be recognised as being a
   channel operator on the given channel.
   Numeric Replies:
           ERR_NEEDMOREPARAMS              ERR_NOSUCHNICK
           ERR_NOTONCHANNEL                ERR_USERONCHANNEL
           ERR_CHANOPRIVSNEEDED
           RPL_INVITING                    RPL_AWAY
   Examples:
   :Angel INVITE Wiz #Dust         ; User Angel inviting WiZ to channel #Dust
   INVITE Wiz #Twilight_Zone       ; Command to invite WiZ to #Twilight_zone

 4.2.8 Kick command
      Command: KICK
   Parameters: <channel> <user> [<comment>]
   The KICK command can be  used  to  forcibly  remove  a  user  from  a channel.   It  ’kicks  them  out’  of the channel (forced PART).

RFC 1459              Internet Relay Chat Protocol              May 1993
   Only a channel operator may kick another user out of a  channel.
   Each  server that  receives  a KICK message checks that it is valid
   (ie the sender is actually a  channel  operator)  before  removing
   the  victim  from  the channel.
   Numeric Replies:
           ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
           ERR_BADCHANMASK                 ERR_CHANOPRIVSNEEDED
           ERR_NOTONCHANNEL
   Examples:
 KICK &Melbourne Matthew         ; Kick Matthew from &Melbourne
 KICK #Finnish John :Speaking English ; Kick John from #Finnish using "Speaking English" as the reason (comment).
 :WiZ KICK #Finnish John         ; KICK message from WiZ to remove John from channel #Finnish
 NOTE:
It is possible to extend the KICK command parameters to the following:
 <channel>{,<channel>} <user>{,<user>} [<comment>]