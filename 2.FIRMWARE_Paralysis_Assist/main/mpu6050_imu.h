
#ifndef _MPU6050_H
#define _MPU6050_H

#include "Wire.h"

const byte   MPU_addr          =        0x68;

int16_t AcX, AcY, AcZ;
float ax = 0, ay = 0, az = 0;
//int data[STORE_SIZE][5]; //array for saving past data
//byte currentIndex=0; //stores current data array index (0-255)
class MPU6050
{
public:
//const short MPU_addr = 0x68; // I2C address of the MPU-6050
boolean fall = false;     //stores if a fall has occurred
byte fallCounter = 0;

    void beginMPU()
    {
        Wire.begin();
        Wire.beginTransmission(MPU_addr);
        Wire.write(0x6B); // PWR_MGMT_1 register
        Wire.write(0);    // set to zero (wakes up the MPU-6050)
        Wire.endTransmission(true);
//        Serial.begin(9600);
        
        //pinMode(11, OUTPUT);
        //digitalWrite(11, HIGH);
    }

    /* returns true if fall detected , else false for no fall */
    boolean detectFall( boolean *flag)
    {
      fallCounter = 0;
        runMPU(); //get fall detection counter
//        Serial.println(fallCounter);
        if(fallCounter >= 2)
        {
          *flag = 1;
          //Serial.println(fallCounter);
          return true; // fall detected return 1
        }
       *flag = 0;
       return false; // No fall detected 
    }

    void detectFallVal(byte *fallVal)
    {
      runMPU();
      *fallVal = fallCounter;
    }
    
    void runMPU()
    {
        mpu_read();
        //2050, 77, 1947 are values for calibration of accelerometer
        // values may be different for you
        ax = (AcX - 2050) / 16384.00;
        ay = (AcY - 77) / 16384.00;
        az = (AcZ - 1947) / 16384.00;

        //270, 351, 136 for gyroscope
        //gx = (GyX + 270) / 131.07;
        //gy = (GyY - 351) / 131.07;
        //gz = (GyZ + 136) / 131.07;

        /* Inactive block */
#if 0
         // Serial.print(ax); Serial.print("\t");
         // Serial.print(ay); Serial.print("\t");
         // Serial.println(az); //Serial.print("\t");
          //Serial.print(gx); Serial.print("\t");
          //Serial.print(gy); Serial.print("\t");
          //Serial.println(gz);
#endif

        // calculating Amplitute vactor for 3 axis
        float Raw_AM = pow(pow(ax, 2) + pow(ay, 2) + pow(az, 2), 0.5);
        byte AM = Raw_AM * 10; // as values are within 0 to 1, I multiplied
        // it by for using if else conditions
      //fallCounter = AM;
    /* Fall detection for next 200 ms to confirm object is falling */
        if(AM < 1) // setting fall detection threshold to 5
        {
          #if 0
          #endif 
          fallCounter = 3;
        }
    }

    void mpu_read()
    {
        Wire.beginTransmission(MPU_addr);
        Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
        Wire.endTransmission(false);
        //Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers
        Wire.requestFrom(MPU_addr, 6, true); // request a total of 6 registers
        
        AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
        AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
        AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
        //Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
        //GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
        //GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
        //GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
    }
};



#endif
