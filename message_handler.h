#ifndef MESSAGE_HANDLER_H_
#define MESSAGE_HANDLER_H_

#include <string>
#include <map>

class MessageHandler {

 private:
    std::string language;
    std::map<std::string, std::map<std::string, std::string>> messages;

 public:
    explicit MessageHandler(const std::string& lang);
    std::string getMessage(const std::string& key);
};

#endif // MESSAGE_HANDLER_H_
