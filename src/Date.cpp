#include "Date.h"

bool Date::operator==(const Date& d) const
{
	return this->_year == d._year && this->_month == d._month && this->_day == d._day;
}

bool Date::operator<(const Date& d) const
{
	if (this->_year < d._year)
	{
		return true;
	}
	else if (this->_year == d._year)
	{
		if (this->_month < d._month)
		{
			return true;
		}
		else if (this->_month == d._month)
		{
			if (this->_day < d._day)
			{
				return true;
			}
		}
	}
	return false;
}

bool Date::operator>(const Date& d) const
{
	return !(*this <= d);
}
bool Date::operator<=(const Date & d) const
{
	return *this < d || * this == d;
}

bool Date::operator>=(const Date & d) const
{
	return !(*this < d);
}

bool Date::operator!=(const Date & d) const
{
	return !(*this == d);
}

Date Date::operator+(int day) const
{
	Date ret = *this;
	ret += day;
	return ret;
}

Date Date::operator-(int day) const
{
	Date ret = *this;
	ret -= day;
	return ret;
}

Date& Date::operator+=(int day)
{
	if (day < 0)
	{
		*this -= -day;
	}
	else
	{
		_day += day;
		while (_day > getMonthDay(_year, _month))
		{
			_day -= getMonthDay(_year, _month);
			++_month;
			if (_month == 13)
			{
				++_year;
				_month = 1;
			}
		}
	}
	return *this;
}

Date& Date::operator-=(int day)
{
	if (day < 0)
	{
		*this += -day;
	}
	else
	{
		_day -= day;
		while (_day <= 0)
		{
			--_month;
			if (_month == 0)
			{
				_month = 12;
				--_year;
			}
			_day += getMonthDay(_year, _month);
		}
	}
	return *this;
}

int Date::operator-(Date & date) const
{
	Date ret = *this;
	int day = 0;
	if (ret == date)
	{
		return 0;
	}
	else if (ret < date)
	{
		ret = ret;
	}
	else
	{
		ret = date;
	}

	while (ret != date)
	{
		++ret;
		++day;
	}
	return day;
}
// 前置++--
Date& Date::operator++()
{
	*this += 1;
	return *this;
}
Date& Date::operator--()
{
	*this -= 1;
	return *this;
}
// 后置++--
Date Date::operator++(int)
{
	Date ret = *this;
	*this += 1;
	return ret;
}
Date Date::operator--(int)
{
	Date ret = *this;
	*this -= 1;
	return ret;
}