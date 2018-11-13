#ifndef SBMEECGACQUISITIONOBJ_H
#define SBMEECGACQUISITIONOBJ_H

#include <QObject>
#include "SBMEMacroDefinition.h"
#include "SBMEUserDef.h"
#include "Usb2805.h"
//#include <QFile>
//#include <QDataStream>

class SBMEECGAcquisitionObj : public QObject
{ 
    Q_OBJECT

public: 
    SBMEECGAcquisitionObj();

    void ECGAcquisitionStop();

private:
    int  m_nDeviceLgcID;      //�豸�߼���
    int  m_nReturn;           //��������ֵ
    int  m_nReadSizeWords;    // ÿ�ζ�ȡAD���ݸ���
    long m_lRetWords;         // ʵ�ʶ�ȡ�����ݸ���

	int m_nReadIndex;

    HANDLE          m_hDevice;     //�豸������
    volatile bool   m_bAcqStopped;
    USB2805_PARA_AD m_ADPara;      // ��ʼ��AD�Ĳ����ṹ
	
	//QFile AcqObjFile;
	//QDataStream AcqObjIn;

signals: 
    void m_signalAcqObjCreateDeviceErr();
    void m_signalAcqObjInitializeDeviceErr();
    void m_signalAcqObjReadDeviceErr();
	void m_signalAcqObjDataFlowErr();                                                                                                                                                                                                    
	//void AcqObjOpenFileErr();

private slots:
    void m_slotECGAcquisitionStart();
	//void m_slotECGAcquisitionStop();
};

#endif // SBMEECGACQUISITIONOBJ_H
