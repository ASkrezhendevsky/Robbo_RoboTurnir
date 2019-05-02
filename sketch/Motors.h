/*
пины микроконтроллера отвечающие за направление движения
1 - назад, 0 - вперёд
*/
#define MOTOR_LEFT_DIR		10 
#define MOTOR_RIGHT_DIR		6	

#define FORWARD	    LOW  //для более осмысленного переключения между направлениями движения, Пример: digitalWrite(MOTOR_LEFT_DIR,FORWARD); //установка левого мотора на движение в перёд
#define BACKWARD	  HIGH

/*
пины микроконтроллера отвечающие за питание моторов
*/
#define MOTOR_LEFT_POW		9 //питание моторов
#define MOTOR_RIGHT_POW		5

#define NORMAL_SPEED      150 //скорость

void setMotorDirForward();
void setMotorDirBackward();
void setMotorDir(int lDir,int rDir);
void setMotorPWM(int lPower,int rPower);
void setMotorPWMPID(int Power,int PID);
