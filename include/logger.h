#ifndef LOGGER_H
#define LOGGER_H


#include <QTextBrowser>
#include <memory>
#include <queue>
#include "utils.h"

class QTextBrowserAppender {
	using Target = QTextBrowser;
	Target& t_;
public:
	QTextBrowserAppender(Target& t): t_(t) {}

	void append(std::string s) { t_.append(s.c_str()); }
};


template <typename T>
class appender_for {};

template <>
class appender_for<QTextBrowser> {
public:
	using type = QTextBrowserAppender;
};


template <typename Target, typename Appender = typename appender_for<Target>::type>
class Logger {
	std::unique_ptr<Appender> appender_;
	bool enabled_ = false;
	std::queue<std::string> queue_;

	void do_log(std::string msg) { assert(appender_); appender_->append(msg); }
public:	
	Logger() {}

	void enable(Target& t);

	template <typename T, typename A>
	friend Logger<T, A>& operator<<(Logger<T, A>& l, std::string msg);
};

extern Logger<QTextBrowser> event_log;

class multiple_log_enable_error : public std::exception {};

template <typename Target, typename Appender>
void Logger<Target, Appender>::enable(Target& t) {
	if (enabled_) throw multiple_log_enable_error();

	appender_ = make_unique<Appender>(t);
	enabled_ = true;

	while (!queue_.empty()) {
		auto& msg = queue_.front();
		queue_.pop();
		appender_->append(msg);
	}
}

template <typename T, typename A>
Logger<T, A>& operator<<(Logger<T, A>& l, std::string msg) {
	if (l.enabled_) {
		l.do_log(msg);
	} else {
		l.queue_.push(msg);
	}
	return l;
}

#endif /* LOGGER_H */
