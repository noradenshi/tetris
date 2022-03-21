#pragma once
#include <functional>
#include <iostream>

class Stat {
	int m_value = 0;
	std::function<void(int)> m_callback = NULL;

public:
	Stat() = default;
	Stat(int t_value) : m_value(t_value) {}
	void setCallback(std::function<void(int)> &t_func) {
		m_callback = t_func;
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