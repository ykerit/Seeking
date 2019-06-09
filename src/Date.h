#pragma once
#include <iostream>
using std::cout;
using std::endl;

class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
	{
		if ((year >= 1900) && (month > 0) && (month < 13) && (day > 0) && (day <= getMonthDay(year, month)))
		{
			_year = year;
			_month = month;
			_day = day;
		}
		else
		{
			cout << "日期错误" << endl;
		}
	}

	Date(const Date& d)
	{
		_year = d._day;
		_month = d._month;
		_day = d._day;
	}

	~Date()
	{
		// cout << "i am died!" << endl;
	}

	void display()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}

	bool operator==(const Date& d) const;
	bool operator<(const Date& d) const;
	bool operator>(const Date& d) const;
	bool operator<=(const Date& d) const;
	bool operator>=(const Date& d) const;
	bool operator!=(const Date& d) const;
	Date operator+(int day) const;
	Date operator-(int day) const;
	Date& operator+=(int day);
	Date& operator-=(int day);
	// 日期差
	int operator-(Date& day) const;
	// 前置++--
	Date& operator++();
	Date& operator--();
	// 后置++--
	Date operator++(int);
	Date operator--(int);

private:
	// 获取月份天数
	inline int getMonthDay(int year, int month)
	{
		static int months[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if ((month == 2)
			&& ((year % 4 == 0 && year % 100 != 0)
				|| (year % 400 == 0)))
		{
			return 29;
		}
		return months[month];
	}

private:
	int _year;
	int _month;
	int _day;
};