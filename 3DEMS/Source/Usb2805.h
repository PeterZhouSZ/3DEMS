#ifndef _USB2805_DEVICE_
#define _USB2805_DEVICE_

#include<windows.h>
//***********************************************************
// ����AD�ɼ��Ĳ����ṹ
typedef struct _USB2805_PARA_AD
{
	LONG CheckStsMode;		// ���״̬ģʽ
	LONG ADMode;            // ADģʽѡ��(�����ɼ�/����ɼ�)
	LONG FirstChannel;      // ��ͨ��,ȡֵ��ΧΪ[0, 63]
	LONG LastChannel;		// ĩͨ��,ȡֵ��ΧΪ[0, 63]
	LONG Frequency;         // �ɼ�Ƶ��,��λΪHz,ȡֵ��ΧΪ[31, 250000]
	LONG GroupInterval;     // �������ʱ�������(��λ��΢��),ȡֵ��ΧΪ[1, 32767]
	LONG LoopsOfGroup;		// �������ʱ��ÿ��ѭ��������ȡֵ��ΧΪ[1, 255]
	LONG Gains;				// ���������
	LONG TriggerMode;       // ����ģʽѡ��(����������󴥷�)
	LONG TriggerSource;		// ����Դѡ��(ART��DTR)
	LONG TriggerType;		// ��������ѡ��(���ش���/���崥��)
	LONG TriggerDir;		// ��������ѡ��(����/���򴥷�)
	LONG TrigLevelVolt;     // ������ƽ(0mV -- +10000mV)
	LONG TrigWindow;		// ����������(1-255)����λ:0.5΢��
	LONG ClockSource;		// ʱ��Դѡ��(��/��ʱ��Դ)
	LONG bClockOutput;      // �Ƿ�������ADת��ʱ�������=TRUE:���������CN1�ϵ�CLKOUT��=FALSE:��ֹ�����CN1�ϵ�CLKOUT
} USB2805_PARA_AD, *PUSB2805_PARA_AD;

// ADӲ������USB2805_PARA_AD�е�CheckStsMode���״̬��ģʽ��ʹ�õ�ѡ��
const long USB2805_CHKSTSMODE_HALF			= 0x00; // ��ѯFIFO������־(�����Ƶ�ʲɼ�ʱʹ��)
const long USB2805_CHKSTSMODE_NPT			= 0x01; // ��ѯFIFO�ǿձ�־(�����ʵʱ�ɼ�ʱʹ��)

// ADӲ������USB2805_PARA_AD�е�ADMode����ģʽ��ʹ�õ�ѡ��
const long USB2805_ADMODE_SEQUENCE			= 0x00; // ��������
const long USB2805_ADMODE_GROUP				= 0x01; // �������

//***********************************************************
// AD����USB2805_PARA_AD�е�Gainsʹ�õ�Ӳ������ѡ��
const long USB2805_GAINS_1MULT				= 0x00; // 1������(ʹ��AD8251�Ŵ���)
const long USB2805_GAINS_2MULT				= 0x01; // 2������(ʹ��AD8251�Ŵ���)
const long USB2805_GAINS_4MULT				= 0x02; // 4������(ʹ��AD8251�Ŵ���)
const long USB2805_GAINS_8MULT				= 0x03; // 8������(ʹ��AD8251�Ŵ���)

//***********************************************************
// ADӲ������USB2805_PARA_AD�е�TriggerMode��Ա������ʹ��AD����ģʽѡ��
const long USB2805_TRIGMODE_SOFT			= 0x00; // �������(�����ڴ���)
const long USB2805_TRIGMODE_POST			= 0x01; // Ӳ���󴥷�(�����ⴥ��)

//***********************************************************
// ADӲ������USB2805_PARA_AD�е�TriggerSource��Ա������ʹ��AD����Դѡ��
const long USB2805_TRIGSOURCE_ATR			= 0x00; // ATR����
const long USB2805_TRIGSOURCE_DTR			= 0x01; // DTR����

// ADӲ������USB2805_PARA_AD�е�TriggerType����������ʹ�õ�ѡ��
const long USB2805_TRIGTYPE_EDGE			= 0x00; // ���ش���
const long USB2805_TRIGTYPE_PULSE			= 0x01; // ���崥��(��ƽ����)

//***********************************************************
// ADӲ������USB2805_PARA_AD�е�TriggerDir����������ʹ�õ�ѡ��
const long USB2805_TRIGDIR_NEGATIVE			= 0x00; // ���򴥷�(�͵�ƽ/�½��ش���)
const long USB2805_TRIGDIR_POSITIVE			= 0x01; // ���򴥷�(�ߵ�ƽ/�����ش���)
const long USB2805_TRIGDIR_POSIT_NEGAT		= 0x02; // �����򴥷�(��/�͵�ƽ������/�½��ش���)

//***********************************************************
// ADӲ������USB2805_PARA_AD�е�ClockSourceʱ��Դ��ʹ�õ�ѡ��
const long USB2805_CLOCKSRC_IN				= 0x00; // �ڲ�ʱ�Ӷ�ʱ����
const long USB2805_CLOCKSRC_OUT				= 0x01; // �ⲿʱ�Ӷ�ʱ����(ʹ��CN1�ϵ�CLKIN�ź�����)

//***********************************************************
// ���������ӿ�
#ifndef _USB2805_DRIVER_
#define DEVAPI __declspec(dllimport)
#else
#define DEVAPI __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
#endif
	//######################## ����ͨ�ú��� #################################
	HANDLE DEVAPI FAR PASCAL USB2805_CreateDevice(int DeviceLgcID = 0); // �����豸����(�ú���ʹ��ϵͳ���߼��豸ID��
	HANDLE DEVAPI FAR PASCAL USB2805_CreateDeviceEx(int DevicePhysID = 0); // �����豸����(ʹ���豸�����), DevicePhysIDָ����������ɰ���DID������ʵ��)
	int DEVAPI FAR PASCAL USB2805_GetDeviceCount(HANDLE hDevice);      // ȡ��USB2805��ϵͳ�е��豸����
	BOOL DEVAPI FAR PASCAL USB2805_GetDeviceCurrentID(HANDLE hDevice, PLONG DeviceLgcID, PLONG DevicePhysID); // ȡ�õ�ǰ�豸������ID�ź��߼�ID��
	BOOL DEVAPI FAR PASCAL USB2805_ResetDevice(HANDLE hDevice);		 // ��λ����USB�豸
	BOOL DEVAPI FAR PASCAL USB2805_ReleaseDevice(HANDLE hDevice);    // �ͷ��豸

	//####################### AD���ݶ�ȡ���� #################################
    BOOL DEVAPI FAR PASCAL USB2805_InitDeviceAD( // ��ʼ���豸,������TRUE��,�豸���̿�ʼ����.
											HANDLE hDevice,     // �豸���
											PUSB2805_PARA_AD pADPara);  // Ӳ������, �����ڴ˺����о���Ӳ��״̬
										
    BOOL DEVAPI FAR PASCAL USB2805_ReadDeviceAD(  // ��ʼ���豸�󣬼����ô˺�����ȡ�豸�ϵ�AD����
											HANDLE hDevice,     // �豸���
											USHORT ADBuffer[],   // �����ڽ������ݵ��û�������
											LONG nReadSizeWords,	// ��ȡAD���ݵĳ���
											PLONG nRetSizeWords);    // ����ʵ�ʶ�ȡ��AD����

	BOOL DEVAPI FAR PASCAL USB2805_ReleaseDeviceAD( HANDLE hDevice); // ֹͣAD�ɼ����ͷ�AD������ռ��Դ

	//################# AD��Ӳ�������������� ########################	
	BOOL DEVAPI FAR PASCAL USB2805_SaveParaAD(HANDLE hDevice, PUSB2805_PARA_AD pADPara);  
	BOOL DEVAPI FAR PASCAL USB2805_LoadParaAD(HANDLE hDevice, PUSB2805_PARA_AD pADPara);
	BOOL DEVAPI FAR PASCAL USB2805_ResetParaAD(HANDLE hDevice, PUSB2805_PARA_AD pADPara); // ��AD���������ָ�������Ĭ��ֵ

	//####################### DA����������� #################################
	// ���ڴ������ͨ�û�����Щ�ӿ���򵥡����ݡ���ɿ������û�����֪���豸
	// �Ͳ㸴�ӵ�Ӳ������Э��ͷ����������Ʊ�̣���������һ������������
	// ��ʵ�ָ��١�������DA�������
	BOOL DEVAPI FAR PASCAL USB2805_WriteDeviceDA(			// дDA����
									HANDLE hDevice,			// �豸������,����CreateDevice��������
									SHORT nDAData,			// �����DAԭʼ����[0, 4095]
									int nDAChannel);		// DA���ͨ��[0-7]

	//####################### ����I/O����������� #################################
	BOOL DEVAPI FAR PASCAL USB2805_GetDeviceDI(					// ȡ�ÿ�����״̬     
									HANDLE hDevice,				// �豸���,��Ӧ��CreateDevice��������								        
									BYTE bDISts[16]);			// ��������״̬(ע��: ���붨��Ϊ16���ֽ�Ԫ�ص�����)

    BOOL DEVAPI FAR PASCAL USB2805_SetDeviceDO(					// ���������״̬
									HANDLE hDevice,				// �豸���,��Ӧ��CreateDevice��������								        
									BYTE bDOSts[16]);			// �������״̬(ע��: ���붨��Ϊ16���ֽ�Ԫ�ص�����)

	BOOL DEVAPI FAR PASCAL USB2805_RetDeviceDO(					// �ض����������״̬
									HANDLE hDevice,				// �豸���,��Ӧ��CreateDevice��������								        
									BYTE bDOSts[16]);			// �������״̬(ע��: ���붨��Ϊ16���ֽ�Ԫ�ص�����)

	//############################ �̲߳������� ################################
	HANDLE DEVAPI FAR PASCAL USB2805_CreateSystemEvent(void); 	// �����ں�ϵͳ�¼�����
	BOOL DEVAPI FAR PASCAL USB2805_ReleaseSystemEvent(HANDLE hEvent); // �ͷ��ں��¼�����

#ifdef __cplusplus
}
#endif

//#################### �������� #####################

const long USB2805_MAX_AD_CHANNELS = 64;

//***********************************************************
// ����ADģ�������������е�����
const long USB2805_INPUT_N10000_P10000mV	= 0x00; // ��10000mV
const long USB2805_INPUT_N5000_P5000mV		= 0x01; // ��5000mV
const long USB2805_INPUT_N2500_P2500mV		= 0x02; // ��2500mV
const long USB2805_INPUT_0_P10000mV			= 0x03; // 0��10000mV
const long USB2805_INPUT_0_P5000mV			= 0x04; // 0��5000mV

//***********************************************************
// ����DAģ������������е�����
const long USB2805_OUTPUT_0_P5000mV			= 0x00; // 0��5000mV
const long USB2805_OUTPUT_0_P10000mV		= 0x01; // 0��10000mV
const long USB2805_OUTPUT_N5000_P5000mV		= 0x02; // ��5000mV
const long USB2805_OUTPUT_N10000_P10000mV	= 0x03; // ��10000mV

// �Զ������������������
#ifndef _USB2805_DRIVER_
#ifndef _WIN64
#pragma comment(lib, "USB2805_32.lib")
#pragma message("======== Welcome to use our art company's products!")
#pragma message("======== Automatically linking with USB2805_32.dll...")
#pragma message("======== Successfully linked with USB2805_32.dll")
#else
#pragma comment(lib, "USB2805_64.lib")
#pragma message("======== Welcome to use our art company's products!")
#pragma message("======== Automatically linking with USB2805_64.dll...")
#pragma message("======== Successfully linked with USB2805_64.dll")
#endif
#endif

#endif; // _USB2805_DEVICE_