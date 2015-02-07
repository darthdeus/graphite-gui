#include <QTextBrowser>

#ifndef LOGGER_HPP
#define LOGGER_HPP

extern QTextBrowser* global_logger_logView_;

void log_event(const char* message);

#endif // LOGGER_HPP

