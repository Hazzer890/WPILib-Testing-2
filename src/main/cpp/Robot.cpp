// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include <iostream>


void Robot::RobotInit() {
  //Contollers
  driverXbox = new frc::XboxController(0);
  operatorXbox = new frc::XboxController(1);

  //Drive Motors
  flDrive = new TalonSRX(0);
  frDrive = new TalonSRX(1);
  blDrive = new TalonSRX(2);
  brDrive = new TalonSRX(3);
  //Intake Motors
  leftIntake = new TalonSRX(4);
  rightIntake = new TalonSRX(5);
  //Index Motors
  indexOne = new TalonSRX(6);
  indexTwo = new TalonSRX(7);
  //Shooter Motors
  lowerShooter = new TalonSRX(8);
  upperShooter = new VictorSPX(9);

  //Solenoids
  anglePiston = new frc::DoubleSolenoid(frc::PneumaticsModuleType::CTREPCM, 0, 1);
}
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {
  //Drive Code
  double X = driverXbox->GetLeftX();
  double Y = driverXbox->GetLeftY();
  double yaw = driverXbox->GetRightX();

  flDrive->Set(ControlMode::PercentOutput, X + Y + yaw);
  frDrive->Set(ControlMode::PercentOutput, X + Y + yaw);
  blDrive->Set(ControlMode::PercentOutput, X - Y - yaw);
  brDrive->Set(ControlMode::PercentOutput, X - Y - yaw);
  
  //CoDriver Code
  int directionalControl = operatorXbox->GetLeftY();
  bool Intake = operatorXbox->GetAButtonPressed();
  bool Index = operatorXbox->GetBButtonPressed();
  bool Shooter = operatorXbox->GetXButtonPressed();
  bool Angle = operatorXbox->GetYButtonPressed();

  rightIntake->Set(ControlMode::PercentOutput, Intake * directionalControl * 0.7);
  leftIntake->Set(ControlMode::PercentOutput, Intake * directionalControl * -0.7);

  indexOne->Set(ControlMode::PercentOutput, Index * directionalControl * 0.7);
  indexTwo->Set(ControlMode::PercentOutput, Index * directionalControl * -0.7);

  lowerShooter->Set(ControlMode::PercentOutput, Shooter);
  upperShooter->Set(ControlMode::PercentOutput, Shooter);
  if(Angle){
    anglePiston->Set(frc::DoubleSolenoid::kForward);
  } else {
    anglePiston->Set(frc::DoubleSolenoid::kReverse);
  }
  
  
}

void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
