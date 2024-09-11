#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <string>
#include <map>

class MessageHandler {
private:
    std::string language;
    std::map<std::string, std::map<std::string, std::string>> messages;

public:
    MessageHandler(const std::string& lang);
    std::string getMessage(const std::string& key);
};

#endif
