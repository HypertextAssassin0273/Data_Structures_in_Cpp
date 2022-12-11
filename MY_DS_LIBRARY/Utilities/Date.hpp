#ifndef DATE_GUARD
#define DATE_GUARD 1

#include <iostream>
#include <fstream>

class Date{
	typedef Date __D;
	
public:
	/* Member Attributes */
	short day, month, year;
    
    /* Default & Parameterized Constructor (a.k.a ctor) */
	Date(short day=0, short month=0, short year=0):
		day(day), month(month), year(year){}
	
	/* Comparators (comparison operators) */
	bool operator==(const __D& other)const{ return day==other.day&&month==other.month&&year==other.year; }
	bool operator!=(const __D& other)const{ return !(*this==other); }
	
	bool operator>(const __D& other)const{ return day>other.day&&month>other.month&&year>other.year; }
	bool operator<=(const __D& other)const{ return !(*this>other); }
	
	bool operator<(const __D& other)const{ return day<other.day&&month<other.month&&year<other.year; }
	bool operator>=(const __D& other)const{ return !(*this<other); }
	
	/* Overloaded 'cout & cin' Methods */
	friend std::ostream& operator<<(std::ostream& out, const __D& self){
		out<<self.day<<'-'<<self.month<<'-'<<self.year;
		return out;
	}
	friend std::istream& operator>>(std::istream& in, __D& self){
		in>>self.day>>self.month>>self.year;
		return in;
	}
	
	/* Overloaded 'fout & fin' Methods */
	friend std::ofstream& operator<<(std::ofstream& out, const __D& self){//'fout' operator
		out<<self.day<<'-'<<self.month<<'-'<<self.year;
		return out;
	}
	friend std::ifstream& operator>>(std::ifstream& in, __D& self){//'fin' operator
		in>>self.day; in.get(); in>>self.month; in.get(); in>>self.year;
		return in;
	}
};

#endif
