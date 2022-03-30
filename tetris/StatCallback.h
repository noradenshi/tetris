#pragma once
#include <functional>
#include <iostream>

typedef enum {
	Score,
	Lines,
	Level,
	Debug,
} stat_name_t;

typedef std::function<void(int)> callback_t;

class StatValue {
	const int m_default = 0;
	int m_value = 0;
	callback_t m_callback = NULL;
public:
	StatValue() = default;
	StatValue(int t_value) : m_default(t_value), m_value(t_value) {}
	void setCallback(callback_t& t_func) {
		m_callback = t_func;
		m_callback(m_value);
	}
	void reset() {
		m_value = m_default;
		if (m_callback != NULL)
			m_callback(m_value);
	}
	void operator = (int rhs) {
		m_value = rhs;
		if (m_callback != NULL) 
			m_callback(m_value);
	}
	void operator += (int rhs) {
		m_value += rhs;
		if (m_callback != NULL) 
			m_callback(m_value);
	}
	operator int() {
		return m_value;
	}
};