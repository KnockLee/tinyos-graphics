#define NEW_PRINTF_SEMANTICS
#include "printf.h"
#include "tgx.h"

configuration TgxAppC {
}
implementation {
	// ************************************************
	// basic wiring
	// ************************************************
	components TgxC as App;
	components MainC, LedsC;
	components RandomMlcgC;
	components new BigQueueC(sensor_msg_t, 20) as SerialMsgQueueC;
	components new TimerMilliC() as SensorTimerC;
	components new TimerMilliC() as BaseStationTimerC;
	components new TimerMilliC() as CheckDogTimerC;

	App.Boot -> MainC;
	App.Leds -> LedsC;
	App.Random -> RandomMlcgC;         // 用来产生节点坐标的随机数发生器
	MainC.SoftwareInit -> RandomMlcgC; // 自动初始化随机数发生器
	App.SerialMsgQueue -> SerialMsgQueueC; // 用来将发往串口的数据排队, 避免冲突
	App.SensorReadTimer -> SensorTimerC;      // 节点维护一个采集时钟
	App.BaseStationTimer -> BaseStationTimerC;
	App.CheckDogTimer -> CheckDogTimerC;

	// ************************************************
	// serial wiring
	// ************************************************
	components SerialActiveMessageC as Serial;
	components new SerialAMSenderC(AM_SENSOR_MSG);
	/*components new SerialAMReceiverC(AM_CONTROL_MSG);*/

	App.SerialSend -> SerialAMSenderC;
	App.SerialPacket -> SerialAMSenderC;
	/*App.SerialReceive -> SerialAMReceiverC;*/
	App.SerialControl -> Serial;


	// ************************************************
	// collection tree protocol
	// ************************************************
	components new CollectionSenderC(AM_SENSOR_MSG);
	components CollectionC;
	components ActiveMessageC as Radio;

	App.CollectionSend -> CollectionSenderC;
	App.CollectionReceive -> CollectionC.Receive[AM_SENSOR_MSG];
	App.RootControl ->CollectionC;
	App.CollectionControl -> CollectionC;
	App.CollectionInfo -> CollectionC;
	App.RadioControl -> Radio;




	// ************************************************
	// dissemination protocol
	// ************************************************
	/*components new DisseminatorC(sensor_msg_t, DESSMINATE_KEY);*/
	/*components DisseminationC;*/

	/*App.DisseminationControl -> DisseminationC;*/
	/*App.DisseminationUpdate -> DisseminatorC;*/
	/*App.DisseminationValue -> DisseminatorC;*/





	// ************************************************
	// sensor wiring
	// ************************************************
	components new SensorMts300C() as Sensor;
	components TgxMicC;
#ifdef USE_LOCAL_MIC
	App.Microphone -> TgxMicC;
#else
	App.Microphone -> Sensor.Microphone;
#endif
	App.MicControl -> TgxMicC;
	App.Temp -> Sensor.Temp;
	App.Light -> Sensor.Light;
	App.AccelX -> Sensor.AccelX;
	App.AccelY -> Sensor.AccelY;
	App.MagX -> Sensor.MagX;
	App.MagY -> Sensor.MagY;



	// ************************************************
	// debug wiring
	// ************************************************
	components PrintfC, SerialStartC;
}
