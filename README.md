# Real-Time-Operating-Software Fianl Project


## Requirements
### - 속도, RPM, Battery 잔여량 LCD에 띄우기
### - Battery 잔여량 20% 미만일 경우, 경고문구 띄우기 (Event API 사용)
### - Battery 잔여량 1% 미만일 경우, OS 강제종료 (Event API 사용)
### - RPM 계산은 속도 계산 이후 실행 
### - Left Button 누를 경우, 경고문구 띄우기 (Interrupt API 사용)
### - Up, Down Button 누를 경우, 속도 증가 or 감소
### - 속도, RPM, Battery 잔여량 변수 접근 시 Lock 사용



## Configuration

### - Task_Speed_Read : 가변저항으로부터 값을 받아온 후 Speed 계산
    - RESOURCE = Speed
    - Speed = analogRead(A3)*200.0/1024.0;
  
### - Task_RPM_Cal : Task_Speed_Read 로부터 Speed 값을 받아와 speedToRPM()을 사용하여 rpm 계산
    - RESOURCE = RPM
	- RPM = speedToRPM(speed);
  
### - Task_Battery_Read : Counter 변수 c 와 Speed 를 이용하여 Battery 계산
    - RESOURCE = Battery
    - Battery = Battery - (c * 0.1 + Speed * 0.1);
  
### - Task_LCD_Print : 위의 Task 에서 계산한 Speed, RPM, Battery 변수를 LCD에 print
    - RESOURCE = Speed
    - RESOURCE = RPM
    - RESOURCE = Battery
  
### - Task_Battery_Warn : Battery 값에 따른 Event 발생
    - EVENT = EVENT_BATTERY_WARN


