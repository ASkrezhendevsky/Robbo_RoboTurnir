/*
пины микроконтроллера отвечающие за направление движения
1 - назад, 0 - вперёд
*/
#define MOTOR_LEFT_DIR		4 
#define MOTOR_RIGHT_DIR		7	

#define FORWARD	  LOW  //для более осмысленного переключения между направлениями движения, Пример: digitalWrite(MOTOR_LEFT_DIR,FORWARD); //установка левого мотора на движение в перёд
#define BACKWARD	  HIGH

/*
пины микроконтроллера отвечающие за питание моторов
*/
#define MOTOR_LEFT_POW		5 //питание моторов
#define MOTOR_RIGHT_POW		6
