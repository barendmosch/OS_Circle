#include "kernel.h"
#include "ledblink.h"
#include <assert.h>
#include <circle/string.h>

/* Define the GPIO ports on the RPI  */
#define GPIO_OUTPUT_PIN_SPI_MAIN	18 // GPIO 18 Chip Enable-CE0 SPI1 PWM 
#define GPIO_OUTPUT_PIN_SPI_2		17 // GPIO 17 Chip Enable-CE1 SPI1
#define GPIO_OUTPUT_PIN_SPI_3		8  // GPIO 16 Chip Enable-CE2 SPI1
#define GPIO_OUTPUT_PIN_SPI_4		16 // GPIO 8  Chip Enable-CE0 SPI0

/* Define the different delays in tasks, currently not in use in the main file */
#define FREQUENCY_DELAYS_IN_MS_2        200 // the task delay that the task must wait until continueing the led blink process
#define FREQUENCY_DELAYS_IN_MS_3        300
#define FREQUENCY_DELAYS_IN_MS_4        400

/* The number of tasks, currently not in use */
#define N_TASKS                 3

static const char FromKernel[] = "kernel";

CKernel::CKernel (void) : 
        /* Create the classes */ 
        m_Screen(m_Options.GetWidth (), m_Options.GetHeight ()),
        m_Timer(&m_Interrupt),
	m_Logger(m_Options.GetLogLevel (), &m_Timer),
	m_OutputPin(GPIO_OUTPUT_PIN_SPI_MAIN, GPIOModeOutput),
        m_OutputPin_2(GPIO_OUTPUT_PIN_SPI_2, GPIOModeOutput),
        m_OutputPin_3(GPIO_OUTPUT_PIN_SPI_3, GPIOModeOutput),
        m_OutputPin_4(GPIO_OUTPUT_PIN_SPI_4, GPIOModeOutput) {

        /* Show that the RPI is working */
        m_ActLED.Blink(5);
}

CKernel::~CKernel (void) {
}

/* Initialize the systems */
boolean CKernel::Initialize (void) {
        boolean bOK = TRUE;

	if (bOK) {
		bOK = m_Screen.Initialize ();
	}

        if (bOK) {
                CDevice *pTarget = m_DeviceNameService.GetDevice (m_Options.GetLogDevice(), FALSE);

                if (pTarget == 0) {
			pTarget = &m_Screen;
		}

                bOK = m_Logger.Initialize(pTarget);
        }

        if (bOK) {
                bOK = m_Interrupt.Initialize();
        }

        if (bOK) {
                bOK = m_Timer.Initialize();
        }

        return bOK;
}

TShutdownMode CKernel::Run(void) {
        CString Message;
       	m_Logger.Write(FromKernel, LogNotice, "Compile time: " __DATE__ " " __TIME__);

        /* Start each tasks, arguments:
         - task number
         - address of the outpin instance
         - address of the screen instance (used for logging mainly)
        */
        CLEDBlink led_task_2 = CLEDBlink(1, &m_OutputPin_2, &m_Screen);
        CLEDBlink led_task_3 = CLEDBlink(2, &m_OutputPin_3, &m_Screen);
        CLEDBlink led_task_4 = CLEDBlink(3, &m_OutputPin_4, &m_Screen);

        /* Used for checking certain tasks information, we can print these in the logging to show the values */
        // bool _valid = CScheduler::Get()->IsActive(); // returns 1, meaning a valid scheduler is present
        // bool _val_2 = CScheduler::Get()->IsValidTask(&led_task_2); // All these booleans returns 1, meaning the task created is valid
        // bool _val_3 = CScheduler::Get()->IsValidTask(&led_task_3);
        // bool _val_4 = CScheduler::Get()->IsValidTask(&led_task_4);

        /* Show the value of the booleans on screen */
        // Message.Format("#%u ", _valid);
       	// m_Logger.Write(FromKernel, LogNotice, Message);

       	m_Logger.Write(FromKernel, LogNotice, "Hello there");

        /* Invert the first LED (right most in the video) forever. Meaning that the LED will keep blinking */
        while (1) {
                m_Event.Clear();
                m_OutputPin.Invert();
                m_Event.Wait();
        }
        
        return ShutdownHalt;
}