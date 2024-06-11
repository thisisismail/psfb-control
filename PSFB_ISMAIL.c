#include "driverlib.h"
#include "device.h"
#include "board.h"
#define EPWM_TIMER_TBPRD    350 //71 kHz

void initEPWM(uint32_t epwm_base, uint16_t phaseCount);
void initDeadBand(uint32_t epwm_base, uint16_t count);
void initPhaseShift(uint32_t epwm_basee, uint16_t phaseCount);
void setPinConfig3(void);
void initSDFM();
void configureSDFMPins();

__interrupt void epwm1ISR(void);

int deadtime = 100;
int i;

float inputVoltage = 300;
float targetVoltage = 35.0;
float targetVoltageGraph;
float voltage;
float dVoltage;
float errVoltage;
float integralErr;
float oldIntegralErr = 0;
float controlSignalP;
float controlSignalI;
float control;

int16_t  rawVoltage;
int16_t rawCurrent;

//// 80V operation for 8V operation (scaling per 100)
//int16_t kp = 1000; //1100 and 200 ki
//int16_t ki = 50; //120 //180

//// 150V operation for 15V and 20V operation (scaling per 100)
//int16_t kp = 100;
//int16_t ki = 10;

//// 200V operation for 20V operation (scaling per 100)
//int16_t kp = 100;
//int16_t ki = 10;

//// 200V-300V operation for 20V-27V operation (scaling per 100)
//int16_t kp = 100;
//int16_t ki = 50;

// 200V-300V operation for 20V-27V operation (scaling per 10)
int16_t kp = 10;
int16_t ki = 5;

float current;
float dCurrent;

// //Shifting List Reference
// Range of phase count is determined by (0 to (EPWM_TIMER_TBPRD - (RED + FED)/2)),
// it means (EPWM_TIMER_TBPRD - (RED + FED)/2) is 180 degree of shifting
//int16_t shift = 320; //~100% duty cycle
//int16_t shift = 250; //50% duty cycle
//int16_t shift = 220;
//int16_t shift = 180;
//int16_t shift = 170; //28.8V => 36V
//int16_t shift = 165; //27.2V
//int16_t shift = 164;
//int16_t shift = 160; //25.6V => 33V
//int16_t shift = 150; //27V for 300V
//int16_t shift = 140; //28V
//int16_t shift = 120; //20v
int16_t shift = 0;

int16_t tshift = 0;

//int16_t shiftLimit = 250; // max 65V
//int16_t shiftLimit = 300; // max 68V
int16_t shiftLimit = 350;

uint32_t counter = 0;

void main(main){
    Device_init();
    Device_initGPIO();
    Board_init();

    Interrupt_initModule();
    Interrupt_initVectorTable();
    initSDFM();

    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    targetVoltage = targetVoltage;

    // Interrupt initialization
    Interrupt_register(INT_EPWM1, &epwm1ISR);
    GPIO_setPadConfig(0, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_0_EPWM1A);
    GPIO_setPadConfig(1, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_1_EPWM1B);

    GPIO_setPadConfig(2, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_4_EPWM3A);
    GPIO_setPadConfig(3, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_5_EPWM3B);

    // Left Legs
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_GTBCLKSYNC);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
    initEPWM(EPWM1_BASE, 0U); // initiate EPMW1_BASE
    initDeadBand(EPWM1_BASE, deadtime); // execute deadband EPWM1_BASE
    EPWM_setInterruptSource(EPWM1_BASE, EPWM_INT_TBCTR_ZERO);


    // Right Legs
    initEPWM(EPWM3_BASE, 0U); // initiate EPMW2_BASE

    // set phase shift to Right Legs
    initPhaseShift(EPWM3_BASE, shift);

    initDeadBand(EPWM3_BASE, deadtime); // execute deadband EPWM2_BASE

    EPWM_enablePhaseShiftLoad(EPWM3_BASE); // execute phase shift

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
    Interrupt_enable(INT_EPWM1);
    EPWM_setInterruptEventCount(EPWM1_BASE, 1U);

    EINT;
    ERTM;
    for(;;){

    }
}

void initEPWM(uint32_t epwm_base, uint16_t phaseCount)
{
    //
    // Configuring time period of output signal as 10us
    //
    EPWM_setTimeBasePeriod(epwm_base, EPWM_TIMER_TBPRD);
    EPWM_setPhaseShift(epwm_base, phaseCount);
    EPWM_setTimeBaseCounter(epwm_base, 0U);
    EPWM_setTimeBaseCounterMode(epwm_base, EPWM_COUNTER_MODE_UP_DOWN);

    EPWM_setClockPrescaler(epwm_base,
                           EPWM_CLOCK_DIVIDER_1,
                           EPWM_HSCLOCK_DIVIDER_1);

    EPWM_disablePhaseShiftLoad(epwm_base);

    EPWM_setCounterCompareValue(epwm_base, EPWM_COUNTER_COMPARE_A, EPWM_TIMER_TBPRD/2);

    EPWM_setActionQualifierAction(epwm_base,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(epwm_base,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    EPWM_setActionQualifierAction(epwm_base,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    EPWM_setActionQualifierAction(epwm_base,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);

    EPWM_enableInterrupt(epwm_base);
    EPWM_setInterruptEventCount(epwm_base, 1U);
}

void initDeadBand(uint32_t epwm_base, uint16_t count){
    EPWM_setRisingEdgeDeadBandDelayInput(epwm_base, EPWM_DB_INPUT_EPWMA);
    EPWM_setRisingEdgeDeadBandDelayInput(epwm_base, EPWM_DB_INPUT_EPWMB);
    EPWM_setFallingEdgeDeadBandDelayInput(epwm_base, EPWM_DB_INPUT_EPWMB);
    EPWM_setFallingEdgeDeadBandDelayInput(epwm_base, EPWM_DB_INPUT_EPWMB);
    EPWM_setRisingEdgeDelayCount(epwm_base, count);
    EPWM_setFallingEdgeDelayCount(epwm_base, count);
    EPWM_setDeadBandDelayPolarity(epwm_base, EPWM_DB_RED, EPWM_DB_POLARITY_ACTIVE_HIGH);
    EPWM_setDeadBandDelayPolarity(epwm_base, EPWM_DB_FED, EPWM_DB_POLARITY_ACTIVE_LOW);
    EPWM_setDeadBandDelayMode(epwm_base, EPWM_DB_RED, true);
    EPWM_setDeadBandDelayMode(epwm_base, EPWM_DB_FED, true);
    EPWM_setDeadBandOutputSwapMode(epwm_base, EPWM_DB_OUTPUT_A, false);
    EPWM_setDeadBandOutputSwapMode(epwm_base, EPWM_DB_OUTPUT_B, false);
}

// Range of phase count is determined by (0 to (EPWM_TIMER_TBPRD - (RED + FED)/2)),
// it means (EPWM_TIMER_TBPRD - (RED + FED)/2) is 180 degree of shifting
void initPhaseShift(uint32_t epwm_base, uint16_t phaseCount){
    EPWM_selectPeriodLoadEvent(epwm_base, EPWM_SHADOW_LOAD_MODE_SYNC);
    EPWM_setPhaseShift(epwm_base, phaseCount); // set amount of phase shift
    EPWM_setTimeBaseCounter(epwm_base, phaseCount); // set amount of phase shift
    EPWM_setSyncOutPulseMode(EPWM1_BASE, EPWM_SYNC_OUT_PULSE_ON_COUNTER_ZERO);
    EPWM_setSyncOutPulseMode(epwm_base, EPWM_SYNC_OUT_PULSE_ON_EPWMxSYNCIN);
}

__interrupt void epwm1ISR(void)
{
    // plot set point to graph
    targetVoltageGraph = targetVoltage;

    // read current sensor
    rawCurrent = SDFM_getFilterData(SDFM1_BASE, SDFM_FILTER_2)>>16;

    // current calibration
    current = (float) (rawCurrent*0.0208319-0.15);

    // read voltage sensor
    rawVoltage = SDFM_getFilterData(SDFM1_BASE, SDFM_FILTER_1)>>16;

    // voltage calibration
    voltage = (float)(rawVoltage - 4) / 8;

    // execute control loop for 1 kHz
    if((counter % 7000) == 0){
        // reset counter
        counter = 0;

        // control signal computation
        errVoltage = (float)targetVoltage - voltage;
        controlSignalP = (float)kp*errVoltage;
        integralErr = (float)(oldIntegralErr + errVoltage);
        controlSignalI = (float)ki*integralErr;
        control = (float)(controlSignalI + controlSignalP);

        // control signal to phase shift signal scaling
          tshift = (float)control/10;
          if(tshift > shiftLimit){
              shift = shiftLimit;
          }else if(tshift <= 0){
              shift = 5;
          }else{
              shift = tshift;
          }

        // execute phase shift
        initPhaseShift(EPWM3_BASE, 300);
        EPWM_enablePhaseShiftLoad(EPWM3_BASE);

        oldIntegralErr = integralErr;
    }
    counter ++;
//    rawCurrent = SDFM_getFilterData(SDFM1_BASE, SDFM_FILTER_2)>>16;
    //
    // Clear INT flag for this timer
    //
    EPWM_clearEventTriggerInterruptFlag(EPWM1_BASE);

    //
    // Acknowledge interrupt group
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
}

void configureSDFMPins()
{
    uint16_t pin;
            for(pin = 122; pin <= 125; pin++)
            {
                GPIO_setMasterCore(pin, GPIO_CORE_CPU1);
                GPIO_setDirectionMode(pin, GPIO_DIR_MODE_IN);
                GPIO_setPadConfig(pin, GPIO_PIN_TYPE_STD);
                GPIO_setQualificationMode(pin, GPIO_QUAL_ASYNC);
            }
            for(pin = 130; pin <= 131; pin++)
            {
                GPIO_setMasterCore(pin, GPIO_CORE_CPU1);
                GPIO_setDirectionMode(pin, GPIO_DIR_MODE_IN);
                GPIO_setPadConfig(pin, GPIO_PIN_TYPE_STD);
                GPIO_setQualificationMode(pin, GPIO_QUAL_ASYNC);
            }
            GPIO_setMasterCore(26, GPIO_CORE_CPU1);
            GPIO_setDirectionMode(26, GPIO_DIR_MODE_IN);
            GPIO_setPadConfig(26, GPIO_PIN_TYPE_STD);
            GPIO_setQualificationMode(26, GPIO_QUAL_ASYNC);

            GPIO_setMasterCore(27, GPIO_CORE_CPU1);
            GPIO_setDirectionMode(27, GPIO_DIR_MODE_IN);
            GPIO_setPadConfig(27, GPIO_PIN_TYPE_STD);
            GPIO_setQualificationMode(27, GPIO_QUAL_ASYNC);
            setPinConfig3();


}

void setPinConfig3()
{
    GPIO_setPinConfig(GPIO_122_SD1_D1);
    GPIO_setPinConfig(GPIO_123_SD1_C1);
    GPIO_setPinConfig(GPIO_124_SD1_D2);
    GPIO_setPinConfig(GPIO_125_SD1_C2);
/*    GPIO_setPinConfig(GPIO_126_SD1_D3);
    GPIO_setPinConfig(GPIO_127_SD1_C3);
    GPIO_setPinConfig(GPIO_128_SD1_D4);
    GPIO_setPinConfig(GPIO_129_SD1_C4);*/
    GPIO_setPinConfig(GPIO_130_SD2_D1);
    GPIO_setPinConfig(GPIO_131_SD2_C1);
    GPIO_setPinConfig(GPIO_26_SD2_D2);
    GPIO_setPinConfig(GPIO_27_SD2_C2);
/*    GPIO_setPinConfig(GPIO_134_SD2_D3);
    GPIO_setPinConfig(GPIO_135_SD2_C3);
    GPIO_setPinConfig(GPIO_136_SD2_D4);
    GPIO_setPinConfig(GPIO_137_SD2_C4);*/
}


void initSDFM()
{

#ifdef CPU1

    //
    // Configure GPIO pins as SDFM pins
    //
    configureSDFMPins();
#endif

    //
    // Input Control Unit
    //
    // Configure Input Control Unit: Modulator Clock rate = Modulator data rate
    //
    SDFM_setupModulatorClock(SDFM1_BASE, SDFM_FILTER_1,
                             SDFM_MODULATOR_CLK_EQUAL_DATA_RATE);

    SDFM_setupModulatorClock(SDFM1_BASE, SDFM_FILTER_2,
                             SDFM_MODULATOR_CLK_EQUAL_DATA_RATE);

    SDFM_setupModulatorClock(SDFM2_BASE, SDFM_FILTER_1,
                             SDFM_MODULATOR_CLK_EQUAL_DATA_RATE);

    SDFM_setupModulatorClock(SDFM2_BASE, SDFM_FILTER_2,
                             SDFM_MODULATOR_CLK_EQUAL_DATA_RATE);


    //
    // Comparator Unit - over and under value threshold settings
    //

    //
    // Configure Comparator Unit's comparator filter type and comparator's
    // OSR value, higher threshold, lower threshold
    //


    //
    // Data Filter Unit
    //
    // Configure Data Filter Unit - filter type, OSR value and
    // enable / disable data filter
    //
    SDFM_configDataFilter(SDFM1_BASE, (SDFM_FILTER_1 | SDFM_FILTER_SINC_3 |
           SDFM_SET_OSR(128)), (SDFM_DATA_FORMAT_16_BIT | SDFM_FILTER_ENABLE |
           SDFM_SHIFT_VALUE(0x0008)));

    SDFM_configDataFilter(SDFM1_BASE, (SDFM_FILTER_2 | SDFM_FILTER_SINC_3 |
           SDFM_SET_OSR(128)), (SDFM_DATA_FORMAT_16_BIT | SDFM_FILTER_ENABLE |
           SDFM_SHIFT_VALUE(0x0008)));

    SDFM_configDataFilter(SDFM2_BASE, (SDFM_FILTER_1 | SDFM_FILTER_SINC_3 |
           SDFM_SET_OSR(128)), (SDFM_DATA_FORMAT_16_BIT | SDFM_FILTER_ENABLE |
           SDFM_SHIFT_VALUE(0x0008)));

    SDFM_configDataFilter(SDFM2_BASE, (SDFM_FILTER_2 | SDFM_FILTER_SINC_3 |
           SDFM_SET_OSR(128)), (SDFM_DATA_FORMAT_16_BIT | SDFM_FILTER_ENABLE |
           SDFM_SHIFT_VALUE(0x0008)));

    //
    // Enable Master filter bit: Unless this bit is set none of the filter modules
    // can be enabled. All the filter modules are synchronized when master filter
    // bit is enabled after individual filter modules are enabled.
    //
    SDFM_enableMasterFilter(SDFM1_BASE);
    SDFM_enableMasterFilter(SDFM2_BASE);

    //
    // PWM11.CMPC, PWM11.CMPD, PWM12.CMPC and PWM12.CMPD signals cannot synchronize
    // the filters. This option is not being used in this example.
    //
    SDFM_disableExternalReset(SDFM1_BASE, SDFM_FILTER_1);
    SDFM_disableExternalReset(SDFM1_BASE, SDFM_FILTER_2);
    SDFM_disableExternalReset(SDFM1_BASE, SDFM_FILTER_3);
    SDFM_disableExternalReset(SDFM1_BASE, SDFM_FILTER_4);
/*
    //
    // Enable interrupts
    //
    // Following SDFM interrupts can be enabled / disabled using this function.
    // Enable / disable comparator high threshold
    // Enable / disable comparator low threshold
    // Enable / disable modulator clock failure
    // Enable / disable data filter acknowledge
    //
    SDFM_enableInterrupt(SDFM1_BASE, SDFM_FILTER_1,
            (SDFM_MODULATOR_FAILURE_INTERRUPT |
             SDFM_DATA_FILTER_ACKNOWLEDGE_INTERRUPT));

    SDFM_enableInterrupt(SDFM1_BASE, SDFM_FILTER_2,
            (SDFM_MODULATOR_FAILURE_INTERRUPT |
             SDFM_DATA_FILTER_ACKNOWLEDGE_INTERRUPT));

    SDFM_enableInterrupt(SDFM1_BASE, SDFM_FILTER_3,
            (SDFM_MODULATOR_FAILURE_INTERRUPT |
             SDFM_DATA_FILTER_ACKNOWLEDGE_INTERRUPT));

    SDFM_enableInterrupt(SDFM1_BASE, SDFM_FILTER_4,
            (SDFM_MODULATOR_FAILURE_INTERRUPT |
             SDFM_DATA_FILTER_ACKNOWLEDGE_INTERRUPT));

    SDFM_disableInterrupt(SDFM1_BASE, SDFM_FILTER_1,
            (SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT |
             SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT));

    SDFM_disableInterrupt(SDFM1_BASE, SDFM_FILTER_2,
            (SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT |
             SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT));

    SDFM_disableInterrupt(SDFM1_BASE, SDFM_FILTER_3,
            (SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT |
             SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT));

    SDFM_disableInterrupt(SDFM1_BASE, SDFM_FILTER_4,
            (SDFM_HIGH_LEVEL_THRESHOLD_INTERRUPT |
             SDFM_LOW_LEVEL_THRESHOLD_INTERRUPT));

    //
    // Enable master interrupt so that any of the filter interrupts can trigger
    // by SDFM interrupt to CPU
    //
    SDFM_enableMasterInterrupt(SDFM1_BASE);
*/
}
