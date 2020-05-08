#ifndef GNOTE_HPP
#define GNOTE_HPP

class GNote {
public:
	GNote(); //TO DO
	virtual void setOff(int time_off);
	virtual ~GNote();

private:
	int _note;
	int _velocity;
	int _time_on;
	int _time_off;

};

#endif