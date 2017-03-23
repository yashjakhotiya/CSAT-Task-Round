#include<stdio.h>
#include<math.h>

//We see max and min voltage given out by accelerometer manually, by rotation it different directions.
#define MaxValue 450//(Suppose)The voltage corresponding to 1g
#define MinValue 250//(Suppose)The voltage corresponding to -1g

#define pi 3.1415926

//The calibrating function for voltage to acceleration conversion
double calibrate(double value, double upperl, double lowerl, double callow, double multiplier)
	{
		double cal_value;
		cal_value= callow+((value-lowerl)/(upperl-lowerl))*multiplier;
		return cal_value;		
	}

//Input Function
//Kept at scanf as of now. Can be changed as required.
double input()
	{
		double vol_value;
		scanf("%lf",&vol_value);
		if(vol_value<MinValue||vol_value>MaxValue)
			{
				printf("Invalid Input\nRetry\n");
				vol_value=input();
			}
		return vol_value;
	}

int main()
	{	
		//Initializations
		double xacc,yacc,zacc;
		double pitch,roll;
		
		//Finding out actual accelerations from voltages
		xacc=calibrate(input(),MaxValue,MinValue,-1,2);
		yacc=calibrate(input(),MaxValue,MinValue,-1,2);
		zacc=calibrate(input(),MaxValue,MinValue,-1,2);
		
		//Finding roll and pitch with trigonometric functions
		roll= (atan2(yacc,zacc))*180/pi;
		pitch= (atan2(-xacc,sqrt(yacc*yacc+zacc*zacc)))*180/pi;
		
		//Final Print
		printf("Acceleration along axes is-\n");
		printf("x axis: %1.3lfg, y axis: %1.3lfg, z axis: %1.3lfg\n",xacc,yacc,zacc);
		printf("Pitch is %3.3lf degrees and Roll is %3.3lf\n",pitch,roll);
		return 0;
	}
