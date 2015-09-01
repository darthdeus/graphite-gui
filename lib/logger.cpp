#include <QTextBrowser>
#include <queue>

#include "lib/logger.hpp"

static std::queue<const char*> event_queue_;
QTextBrowser* global_logger_logView_;

void log_event(const char* message) {
    event_queue_.push(message);

    if (global_logger_logView_) {
        while (!event_queue_.empty()) {
            global_logger_logView_->append(event_queue_.front());
            event_queue_.pop();
        }
    }
}

