#include<stdio.h>
#include<math.h>
#include<time.h>

//We see max and min voltage given out by accelerometer manually, by rotation it different directions.
#define MaxValue 450//(Suppose)The voltage corresponding to 1g
#define MinValue 250//(Suppose)The voltage corresponding to -1g

#define pi 3.1415926
#define time 0.01

//The calibrating function for voltage to acceleration conversion
double calibrate(double value, double upperl, double lowerl, double callow, double multiplier)
	{
		double cal_value;
		cal_value= callow+((value-lowerl)/(upperl-lowerl))*multiplier;
		return cal_value;		
	}

//Input Function
//Kept at scanf as of now. Can be changed as required.
double accinput()
	{
		double vol_value;
		scanf("%lf",&vol_value);
		if(vol_value<MinValue||vol_value>MaxValue)
			{
				printf("Invalid Input\nRetry\n");
				vol_value=accinput();
			}
		return vol_value;
	}
double gyroinput()
	{
		double angvel;
		scanf("%lf",&angvel);;
		return angvel;
	}
double maginput()
	{
		double mag;
		scanf("%lf",&mag);
		return mag;
	}
//Wait For Function
//Takes number of seconds as input and makes program wait till then
void delay(double dly)
	{
		const clock_t start = clock();
		clock_t current;
		do
			{
				current = clock();
			}
		while((double)(current-start)/CLOCKS_PER_SEC < dly);
	}
int main()
	{	
		for(;;)
			{
				//Initializations
				double xacc,yacc,zacc;
				double pitch,roll,yaw,accpitch,accroll,gyropitch=0,gyroroll=0,gyroyaw=0,magx,magy,magz,magyaw;
		
				//Finding out actual accelerations from voltages
				xacc=calibrate(accinput(),MaxValue,MinValue,-1,2);
				yacc=calibrate(accinput(),MaxValue,MinValue,-1,2);
				zacc=calibrate(accinput(),MaxValue,MinValue,-1,2);
				
				//Finding roll and pitch with trigonometric functions
				accroll= (atan2(yacc,zacc))*180/pi;
				accpitch= (atan2(-xacc,sqrt(yacc*yacc+zacc*zacc)))*180/pi;
				
				//Finding roll, pitch and yaw from Gyro
				gyroroll= gyroroll + gyroinput()*time;
				gyropitch= gyropitch + gyroinput()*time;
				gyroyaw= gyroyaw + gyroinput()*time;
				
				//Applying complementary filter
				roll=0.98*gyroroll + 0.02*accroll;
				pitch=0.98*gyropitch + 0.02*accpitch;
				
				//Integrating magnetometer
				magx=maginput();
				magy=maginput();
				magyaw=atan2(magy*cos(roll)-magz*sin(roll), magx*cos(pitch)+magy*sin(roll)*sin(pitch)+magz*cos(roll)*sin(pitch));
				yaw=0.98*gyroyaw + 0.02*magyaw;
				
				//Final Print
				printf("Acceleration along axes is-\n");
				printf("x axis: %1.3lfg, y axis: %1.3lfg, z axis: %1.3lfg\n",xacc,yacc,zacc);
				printf("Pitch is %3.3lf degrees, Roll is %3.3lf and Yaw is %3.3lf  degrees\n",pitch,roll,yaw);
				delay(time);
			}
	}
