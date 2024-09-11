#include "message_handler.h"

MessageHandler::MessageHandler(const std::string& lang) : language(lang) {
    messages = {
        {"EN", {
            {"CRITICAL_TEMPERATURE", "Temperature is critical!"},
            {"WARNING_TEMPERATURE", "Warning: Temperature is in the critical range!"},
            {"CRITICAL_PULSE", "Pulse rate is critical!"},
            {"WARNING_PULSE", "Warning: Pulse rate is in the critical range!"},
            {"CRITICAL_SPO2", "Oxygen saturation is critical!"},
            {"WARNING_SPO2", "Warning: Oxygen saturation is in the critical range!"},
            {"HYPERTHERMIA", "Approaching hyperthermia!"},
            {"HYPOTHERMIA", "Approaching hypothermia!"}
        }},
        {"DE", {
            {"CRITICAL_TEMPERATURE", "Temperatur ist kritisch!"},
            {"WARNING_TEMPERATURE", "Warnung: Temperatur im kritischen Bereich!"},
            {"CRITICAL_PULSE", "Pulsrate ist kritisch!"},
            {"WARNING_PULSE", "Warnung: Pulsrate im kritischen Bereich!"},
            {"CRITICAL_SPO2", "Sauerstoffsättigung ist kritisch!"},
            {"WARNING_SPO2", "Warnung: Sauerstoffsättigung im kritischen Bereich!"},
            {"HYPERTHERMIA", "Annäherung an Hyperthermie!"},
            {"HYPOTHERMIA", "Annäherung an Hypothermie!"}
        }}
    };
}

std::string MessageHandler::getMessage(const std::string& key) {
    return messages[language][key];
}

