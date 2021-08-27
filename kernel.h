#ifndef _kernel_h
#define _kernel_h

#include <circle/memory.h>
#include <circle/actled.h>
#include <circle/koptions.h>
#include <circle/devicenameservice.h>
#include <circle/screen.h>
#include <circle/serial.h>
#include <circle/exceptionhandler.h>
#include <circle/interrupt.h>
#include <circle/timer.h>
#include <circle/logger.h>
#include <circle/types.h>
#include <circle/gpioclock.h>
#include <circle/gpiopin.h>
#include <circle/tracer.h>
#include <circle/sched/scheduler.h>
#include <circle/sched/synchronizationevent.h>
#include <circle/types.h>

enum TShutdownMode {
        ShutdownNone,
        ShutdownHalt,
        ShutdownReboot
};

class CKernel {
        public:
                CKernel(void);
                ~CKernel(void);

                boolean Initialize(void);

                TShutdownMode Run(void);

        private:
	        CMemorySystem		m_Memory;
                CActLED                 m_ActLED;
                CKernelOptions          m_Options;
                CDeviceNameService      m_DeviceNameService;
	        CScreenDevice		m_Screen;
                CInterruptSystem        m_Interrupt;
                CTimer                  m_Timer;
                CLogger                 m_Logger;
                CGPIOPin		m_InputPin;
	        CGPIOPin		m_OutputPin;
                CGPIOPin                m_OutputPin_2;
                CGPIOPin                m_OutputPin_3;
                CGPIOPin                m_OutputPin_4;
                CScheduler		m_Scheduler;
                CSynchronizationEvent	m_Event;
};

#endif