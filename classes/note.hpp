#ifndef NOTE_HPP
#define NOTE_HPP

class ParticleCluster;

class Note {
public:
	Note(int note, int velocity, double time_on, double time_off=-1);

	virtual void 				setOff(double time_off);
	virtual void 				setChild(ParticleCluster* child);

	virtual int 				getNote() 			const;
	virtual int 				getVelocity() 		const;
	virtual double 				getTimeOn() 		const;
	virtual double 				getTimeOff() 		const;
	virtual ParticleCluster* 	getChildCluster() 	const;

	virtual ~Note();

private:
	int 				_note;
	int 				_velocity;
	double 				_time_on;
	double 				_time_off;
	ParticleCluster* 	_childCluster;

};

#endif