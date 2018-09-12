#include "PID.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

//==================================
//  -- PID Class --
//=================================
	// P -- Proportional
	// I -- Integral
	// D -- Differential

	// Errors:
	//      double p_error;
	//      double i_error;
	//      double d_error;

	// Coefficients:
	//      double Kp;
	//      double Ki;
	//      double Kd;

//----------------------
//      Constructor
//----------------------
	PID::PID() {}

//----------------------
//      Destructor
//----------------------
	PID::~PID() {}

//----------------------
//      Initialize
//----------------------
	void PID::Init( double Kp, double Ki, double Kd,
					double Tp, double Ti, double Td) {

		// Coefficients
			this->Kp = Kp;
			this->Ki = Ki;
			this->Kd = Kd;

			this->Tp = Tp;
			this->Ti = Ti;
			this->Td = Td;

		// Errors
			p_error = 0.0;
			i_error = 0.0;
			d_error = 0.0;

		// Previous CTE
			prev_cte = 0.0;
			sum_cte = 0.0;

		// Steering Angle
			steering_angle = 0.0;

		// Throttle
			throttle = 0.2;
			throttle_max = 0.7;
	}

//----------------------
//      Update Error
//----------------------
	void PID::Update_Error(double cte) {

		p_error = cte;
		i_error += cte;

		if (cte - prev_cte)
			d_error = cte - prev_cte;

		prev_cte = cte;
		sum_cte += cte;
	}

//----------------------
//      Total Error
//----------------------
	double PID::Total_Error() {

		double total_error = (Kp * p_error) + (Ki * i_error) + (Kd * d_error) ;
		cout <<  Kp * p_error <<  " + " << Ki * i_error << " + " << Kd * d_error << setw(5) << endl;
		return total_error;
	}

//----------------------
//      Steering Angle
//----------------------
	void PID::Set_Steering_Angle(){

		// Total Error
			double new_angle = Total_Error();

		// Max steering angle is [-1, 1]
			if (new_angle > 1)
				new_angle = 1;

			if (new_angle < -1)
				new_angle = -1;

		// Set
			steering_angle = new_angle;
	}


//----------------------
//      Throttle
//----------------------
	void PID::Set_Throttle(){

		// Throttle = Tp * (1/x^2)
			throttle = Tp/(pow(p_error, 2));

		// Max Throttle
			throttle = std::min(throttle, throttle_max);
			throttle = std::max(throttle, 0.01);

		// Break if Diverging
			if(abs(d_error) > 0.05 )
			{
				throttle = -1.0;
			}


		//cout << "p i d = " << p_error << " - " << i_error << " - " << d_error << endl;

	}

//----------------------
//      Update
//----------------------
	void PID::Update(double cte) {

		Update_Error(cte);
		Set_Steering_Angle();
		Set_Throttle();

	}








































