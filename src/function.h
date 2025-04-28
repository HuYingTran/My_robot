void motor_setup();
void moveForward();
void moveBackward();
void moveLeft();
void moveRight();
void motor_stop();
void motor_set_peed(uint8_t s1, uint8_t s2, uint8_t s3, uint4_t s4);
void moveForward_calib();

void mpu6050_init();
void task_read_mpu6050();