bool gbSenserConnectState = false;

IMU_ST_ANGLES_DATA stAngles;
IMU_ST_SENSOR_DATA stGyroRawData;
IMU_ST_SENSOR_DATA stAccelRawData;
IMU_ST_SENSOR_DATA stMagnRawData;
IMU_ST_Q_DATA stQData;

void imu_init() {
  bool bRet;
  IMU_EN_SENSOR_TYPE enMotionSensorType, enPressureType;

  imuInit(&enMotionSensorType, &enPressureType);
  if(IMU_EN_SENSOR_TYPE_ICM20948 == enMotionSensorType)
  {
    Serial.println("Motion sersor is ICM-20948");
  }
  else
  {
    Serial.println("Motion sersor NULL");
  }
  if(IMU_EN_SENSOR_TYPE_BMP280 == enPressureType)
  {
    Serial.println("Pressure sersor is BMP280");
  }
  else
  {
    Serial.println("Pressure sersor NULL");
  }
  delay(1000);
}


void updateIMUData() {
  imuDataGet( &stAngles, &stGyroRawData, &stAccelRawData, &stMagnRawData, &stQData);

  icm_roll = stAngles.fRoll * PI / 180.0;
  icm_pitch = stAngles.fPitch * PI / 180.0;
  icm_yaw = stAngles.fYaw * PI / 180.0;

  icm_q0 = stQData.Q0;
  icm_q1 = stQData.Q1;
  icm_q2 = stQData.Q2;
  icm_q3 = stQData.Q3;

  ax = stAccelRawData.s16X / 16384.0;
  ay = stAccelRawData.s16Y / 16384.0;
  az = stAccelRawData.s16Z / 16384.0;

  gx = stGyroRawData.s16X / 32.8 * PI / 180.0;
  gy = stGyroRawData.s16Y / 32.8 * PI / 180.0;
  gz = stGyroRawData.s16Z / 32.8 * PI / 180.0;
}


void imuCalibration() {
  
}


void getIMUData() {
	jsonInfoHttp.clear();
	jsonInfoHttp["T"] = FEEDBACK_IMU_DATA;

  jsonInfoHttp["r"] = icm_roll;
  jsonInfoHttp["p"] = icm_pitch;
  jsonInfoHttp["y"] = icm_yaw;

  jsonInfoHttp["q0"] = icm_q0;
  jsonInfoHttp["q1"] = icm_q1;
  jsonInfoHttp["q2"] = icm_q2;
  jsonInfoHttp["q3"] = icm_q3;

	String getInfoJsonString;
	serializeJson(jsonInfoHttp, getInfoJsonString);
	Serial.println(getInfoJsonString);
}


void getIMUOffset() {

}


void setIMUOffset(int16_t inputX, int16_t inputY, int16_t inputZ) {

}