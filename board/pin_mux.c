/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v15.0
processor: MCXA153
package_id: MCXA153VLH
mcu_data: ksdk2_0
processor_version: 15.0.0
pin_labels:
- {pin_num: '16', pin_signal: P2_2/TRIG_IN6/LPUART0_RTS_B/LPUART2_TXD/CT_INP12/CT2_MAT2/ADC0_A4/CMP0_IN0, label: ADC0, identifier: ADC0}
- {pin_num: '5', pin_signal: P1_11/WUU0_IN11/TRIG_OUT2/LPUART1_CTS_B/LPI2C0_SCLS/CT2_MAT1/I3C0_PUR/ADC0_A9, label: I3C0_PUR}
- {pin_num: '55', pin_signal: P0_17/LPI2C0_SCL/LPSPI0_PCS3/CT0_MAT1/UTICK_CAP3/I3C0_SCL, label: I3C0_SCL}
- {pin_num: '2', pin_signal: P1_8/WUU0_IN10/LPUART1_RXD/LPI2C0_SDA/CT_INP8/CT0_MAT2/I3C0_SDA, label: ARD_D18, identifier: ARD_D18}
- {pin_num: '38', pin_signal: P3_12/LPUART2_RTS_B/CT1_MAT2/PWM0_X0, label: ARD_D5, identifier: ARD_D5}
- {pin_num: '37', pin_signal: P3_13/LPUART2_CTS_B/CT1_MAT3/PWM0_X1, label: ARD_D6, identifier: ARD_D6}
- {pin_num: '46', pin_signal: P3_0/WUU0_IN22/TRIG_IN0/CT_INP16/PWM0_A0, label: ARD_D3, identifier: ARD_D3}
- {pin_num: '35', pin_signal: P3_15/LPUART2_TXD/CT_INP7, label: ARD_D8, identifier: ARD_D8}
- {pin_num: '36', pin_signal: P3_14/WUU0_IN25/LPUART2_RXD/CT_INP6/PWM0_X2, label: ARD_D9, identifier: ARD_D9}
- {pin_num: '45', pin_signal: P3_1/TRIG_IN1/CT_INP17/PWM0_B0/FREQME_CLK_OUT0, label: ARD_D7, identifier: ARD_D7}
- {pin_num: '30', pin_signal: P3_31/LPTMR0_ALT2/TRIG_IN10/CT0_MAT3/ADC0_A12, label: ARD_A4, identifier: ARD_A4}
- {pin_num: '31', pin_signal: P3_30/TRIG_OUT6/CT0_MAT2/ADC0_A13, label: ARD_A5, identifier: ARD_A5}
- {pin_num: '62', pin_signal: P1_4/WUU0_IN8/FREQME_CLK_IN0/LPSPI0_PCS3/LPUART2_RXD/CT1_MAT2/ADC0_A20/CMP0_IN2, label: ARD_D0, identifier: ARD_D0}
- {pin_num: '63', pin_signal: P1_5/FREQME_CLK_IN1/LPSPI0_PCS2/LPUART2_TXD/CT1_MAT3/ADC0_A21/CMP1_IN2, label: ARD_D1, identifier: ARD_D1}
- {pin_num: '18', pin_signal: P2_4/CT_INP14/CT1_MAT0, label: ARD_D2, identifier: ARD_D2}
- {pin_num: '19', pin_signal: P2_5/CT_INP15/CT1_MAT1, label: ARD_D4, identifier: ARD_D4}
- {pin_num: '20', pin_signal: P2_6/TRIG_OUT4/LPSPI1_PCS1/CT_INP18/CT1_MAT2/ADC0_A3, label: ARD_D10, identifier: ARD_D10}
- {pin_num: '23', pin_signal: P2_13/TRIG_IN8/LPSPI1_SDO/LPUART1_TXD/CT0_MAT1, label: ARD_D11, identifier: ARD_D11}
- {pin_num: '24', pin_signal: P2_16/LPSPI1_SDI/LPUART1_RTS_B/CT0_MAT2/ADC0_A6, label: ARD_D12, identifier: ARD_D12}
- {pin_num: '22', pin_signal: P2_12/WUU0_IN20/USB0_VBUS_DET/LPSPI1_SCK/LPUART1_RXD/CT0_MAT0/ADC0_A5, label: ARD_D13, identifier: ARD_D13}
- {pin_num: '3', pin_signal: P1_9/LPUART1_TXD/LPI2C0_SCL/CT_INP9/CT0_MAT3/I3C0_SCL, label: ARD_D19, identifier: ARD_D19}
- {pin_num: '4', pin_signal: P1_10/LPUART1_RTS_B/LPI2C0_SDAS/CT2_MAT0/ADC0_A8, label: ARD_A0, identifier: ARD_A0}
- {pin_num: '6', pin_signal: P1_12/WUU0_IN12/LPUART2_RXD/CT2_MAT2/ADC0_A10, label: ARD_A1, identifier: ARD_A1}
- {pin_num: '7', pin_signal: P1_13/TRIG_IN3/LPUART2_TXD/CT2_MAT3/ADC0_A11, label: ARD_A2, identifier: ARD_A2}
- {pin_num: '14', pin_signal: P2_0/WUU0_IN18/TRIG_IN6/LPUART0_RXD/CT_INP16/CT2_MAT0/ADC0_A0, label: ARD_A3, identifier: ARD_A3}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void)
{
    BOARD_InitPins();
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: cm33_core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '52', peripheral: LPUART0, signal: TX, pin_signal: P0_3/TDI/LPUART0_TXD/LPSPI0_SDO/CT0_MAT1/UTICK_CAP1/CMP0_OUT/CMP1_IN1, slew_rate: fast, open_drain: disable,
    drive_strength: low, pull_select: up, pull_enable: enable, input_buffer: enable, invert_input: normal}
  - {pin_num: '51', peripheral: LPUART0, signal: RX, pin_signal: P0_2/TDO/SWO/LPUART0_RXD/LPSPI0_SCK/CT0_MAT0/UTICK_CAP0/I3C0_PUR, slew_rate: fast, open_drain: disable,
    drive_strength: low, pull_select: up, pull_enable: enable, input_buffer: enable, invert_input: normal}
  - {pin_num: '5', peripheral: I3C0, signal: PUR, pin_signal: P1_11/WUU0_IN11/TRIG_OUT2/LPUART1_CTS_B/LPI2C0_SCLS/CT2_MAT1/I3C0_PUR/ADC0_A9, slew_rate: fast, open_drain: disable,
    drive_strength: low, pull_select: down, pull_enable: disable, input_buffer: enable, invert_input: normal}
  - {pin_num: '38', peripheral: GPIO3, signal: 'GPIO, 12', pin_signal: P3_12/LPUART2_RTS_B/CT1_MAT2/PWM0_X0}
  - {pin_num: '37', peripheral: GPIO3, signal: 'GPIO, 13', pin_signal: P3_13/LPUART2_CTS_B/CT1_MAT3/PWM0_X1}
  - {pin_num: '53', peripheral: GPIO0, signal: 'GPIO, 6', pin_signal: P0_6/LPI2C0_HREQ/LPSPI0_PCS1/CT_INP2/CMP1_OUT/CLKOUT/ADC0_A15}
  - {pin_num: '30', peripheral: GPIO3, signal: 'GPIO, 31', pin_signal: P3_31/LPTMR0_ALT2/TRIG_IN10/CT0_MAT3/ADC0_A12}
  - {pin_num: '31', peripheral: GPIO3, signal: 'GPIO, 30', pin_signal: P3_30/TRIG_OUT6/CT0_MAT2/ADC0_A13}
  - {pin_num: '6', peripheral: GPIO1, signal: 'GPIO, 12', pin_signal: P1_12/WUU0_IN12/LPUART2_RXD/CT2_MAT2/ADC0_A10}
  - {pin_num: '7', peripheral: GPIO1, signal: 'GPIO, 13', pin_signal: P1_13/TRIG_IN3/LPUART2_TXD/CT2_MAT3/ADC0_A11}
  - {pin_num: '14', peripheral: GPIO2, signal: 'GPIO, 0', pin_signal: P2_0/WUU0_IN18/TRIG_IN6/LPUART0_RXD/CT_INP16/CT2_MAT0/ADC0_A0}
  - {pin_num: '18', peripheral: GPIO2, signal: 'GPIO, 4', pin_signal: P2_4/CT_INP14/CT1_MAT0}
  - {pin_num: '19', peripheral: GPIO2, signal: 'GPIO, 5', pin_signal: P2_5/CT_INP15/CT1_MAT1}
  - {pin_num: '35', peripheral: GPIO3, signal: 'GPIO, 15', pin_signal: P3_15/LPUART2_TXD/CT_INP7}
  - {pin_num: '36', peripheral: GPIO3, signal: 'GPIO, 14', pin_signal: P3_14/WUU0_IN25/LPUART2_RXD/CT_INP6/PWM0_X2}
  - {pin_num: '22', peripheral: GPIO2, signal: 'GPIO, 12', pin_signal: P2_12/WUU0_IN20/USB0_VBUS_DET/LPSPI1_SCK/LPUART1_RXD/CT0_MAT0/ADC0_A5}
  - {pin_num: '23', peripheral: GPIO2, signal: 'GPIO, 13', pin_signal: P2_13/TRIG_IN8/LPSPI1_SDO/LPUART1_TXD/CT0_MAT1}
  - {pin_num: '24', peripheral: GPIO2, signal: 'GPIO, 16', pin_signal: P2_16/LPSPI1_SDI/LPUART1_RTS_B/CT0_MAT2/ADC0_A6}
  - {pin_num: '20', peripheral: GPIO2, signal: 'GPIO, 6', pin_signal: P2_6/TRIG_OUT4/LPSPI1_PCS1/CT_INP18/CT1_MAT2/ADC0_A3}
  - {pin_num: '45', peripheral: GPIO3, signal: 'GPIO, 1', pin_signal: P3_1/TRIG_IN1/CT_INP17/PWM0_B0/FREQME_CLK_OUT0}
  - {pin_num: '62', peripheral: GPIO1, signal: 'GPIO, 4', pin_signal: P1_4/WUU0_IN8/FREQME_CLK_IN0/LPSPI0_PCS3/LPUART2_RXD/CT1_MAT2/ADC0_A20/CMP0_IN2}
  - {pin_num: '63', peripheral: GPIO1, signal: 'GPIO, 5', pin_signal: P1_5/FREQME_CLK_IN1/LPSPI0_PCS2/LPUART2_TXD/CT1_MAT3/ADC0_A21/CMP1_IN2}
  - {pin_num: '43', peripheral: FlexPWM0, signal: 'B, 0', pin_signal: P3_7/TRIG_IN2/LPSPI1_PCS2/PWM0_B0}
  - {pin_num: '42', peripheral: FlexPWM0, signal: 'A, 1', pin_signal: P3_8/WUU0_IN23/TRIG_IN3/LPSPI1_SDO/LPUART1_RXD/CT_INP4/PWM0_A1/CLKOUT}
  - {pin_num: '40', peripheral: FlexPWM0, signal: 'A, 2', pin_signal: P3_10/TRIG_IN5/LPSPI1_SCK/LPUART1_RTS_B/CT1_MAT0/PWM0_A2}
  - {pin_num: '46', peripheral: FlexPWM0, signal: 'A, 0', pin_signal: P3_0/WUU0_IN22/TRIG_IN0/CT_INP16/PWM0_A0}
  - {pin_num: '4', peripheral: GPIO1, signal: 'GPIO, 10', pin_signal: P1_10/LPUART1_RTS_B/LPI2C0_SDAS/CT2_MAT0/ADC0_A8}
  - {pin_num: '55', peripheral: I3C0, signal: SCL, pin_signal: P0_17/LPI2C0_SCL/LPSPI0_PCS3/CT0_MAT1/UTICK_CAP3/I3C0_SCL}
  - {pin_num: '54', peripheral: I3C0, signal: SDA, pin_signal: P0_16/WUU0_IN2/LPI2C0_SDA/LPSPI0_PCS2/CT0_MAT0/UTICK_CAP2/I3C0_SDA}
  - {pin_num: '3', peripheral: GPIO1, signal: 'GPIO, 9', pin_signal: P1_9/LPUART1_TXD/LPI2C0_SCL/CT_INP9/CT0_MAT3/I3C0_SCL}
  - {pin_num: '2', peripheral: GPIO1, signal: 'GPIO, 8', pin_signal: P1_8/WUU0_IN10/LPUART1_RXD/LPI2C0_SDA/CT_INP8/CT0_MAT2/I3C0_SDA}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void)
{
    /* Write to PORT0: Peripheral clock is enabled */
    CLOCK_EnableClock(kCLOCK_GatePORT0);
    /* Write to PORT1: Peripheral clock is enabled */
    CLOCK_EnableClock(kCLOCK_GatePORT1);
    /* Write to PORT2: Peripheral clock is enabled */
    CLOCK_EnableClock(kCLOCK_GatePORT2);
    /* Write to PORT3: Peripheral clock is enabled */
    CLOCK_EnableClock(kCLOCK_GatePORT3);
    /* I3C0 peripheral is released from reset */
    RESET_ReleasePeripheralReset(kI3C0_RST_SHIFT_RSTn);
    /* PORT0 peripheral is released from reset */
    RESET_ReleasePeripheralReset(kPORT0_RST_SHIFT_RSTn);
    /* LPUART0 peripheral is released from reset */
    RESET_ReleasePeripheralReset(kLPUART0_RST_SHIFT_RSTn);
    /* GPIO0 peripheral is released from reset */
    RESET_ReleasePeripheralReset(kGPIO0_RST_SHIFT_RSTn);
    /* GPIO1 peripheral is released from reset */
    RESET_ReleasePeripheralReset(kGPIO1_RST_SHIFT_RSTn);
    /* PORT1 peripheral is released from reset */
    RESET_ReleasePeripheralReset(kPORT1_RST_SHIFT_RSTn);
    /* GPIO2 peripheral is released from reset */
    RESET_ReleasePeripheralReset(kGPIO2_RST_SHIFT_RSTn);
    /* PORT2 peripheral is released from reset */
    RESET_ReleasePeripheralReset(kPORT2_RST_SHIFT_RSTn);
    /* FLEXPWM0 peripheral is released from reset */
    RESET_ReleasePeripheralReset(kFLEXPWM0_RST_SHIFT_RSTn);
    /* PORT3 peripheral is released from reset */
    RESET_ReleasePeripheralReset(kPORT3_RST_SHIFT_RSTn);
    /* GPIO3 peripheral is released from reset */
    RESET_ReleasePeripheralReset(kGPIO3_RST_SHIFT_RSTn);

    /* PORT0_16 (pin 54) is configured as I3C0_SDA */
    PORT_SetPinMux(PORT0, 16U, kPORT_MuxAlt10);

    PORT0->PCR[16] = ((PORT0->PCR[16] &
                       /* Mask bits to zero which are setting */
                       (~(PORT_PCR_IBE_MASK)))

                      /* Input Buffer Enable: Enables. */
                      | PORT_PCR_IBE(PCR_IBE_ibe1));

    /* PORT0_17 (pin 55) is configured as I3C0_SCL */
    PORT_SetPinMux(PORT0, 17U, kPORT_MuxAlt10);

    PORT0->PCR[17] = ((PORT0->PCR[17] &
                       /* Mask bits to zero which are setting */
                       (~(PORT_PCR_IBE_MASK)))

                      /* Input Buffer Enable: Enables. */
                      | PORT_PCR_IBE(PCR_IBE_ibe1));

    const port_pin_config_t port0_2_pin51_config = {/* Internal pull-up resistor is enabled */
                                                    kPORT_PullUp,
                                                    /* Low internal pull resistor value is selected. */
                                                    kPORT_LowPullResistor,
                                                    /* Fast slew rate is configured */
                                                    kPORT_FastSlewRate,
                                                    /* Passive input filter is disabled */
                                                    kPORT_PassiveFilterDisable,
                                                    /* Open drain output is disabled */
                                                    kPORT_OpenDrainDisable,
                                                    /* Low drive strength is configured */
                                                    kPORT_LowDriveStrength,
                                                    /* Normal drive strength is configured */
                                                    kPORT_NormalDriveStrength,
                                                    /* Pin is configured as LPUART0_RXD */
                                                    kPORT_MuxAlt2,
                                                    /* Digital input enabled */
                                                    kPORT_InputBufferEnable,
                                                    /* Digital input is not inverted */
                                                    kPORT_InputNormal,
                                                    /* Pin Control Register fields [15:0] are not locked */
                                                    kPORT_UnlockRegister};
    /* PORT0_2 (pin 51) is configured as LPUART0_RXD */
    PORT_SetPinConfig(PORT0, 2U, &port0_2_pin51_config);

    const port_pin_config_t port0_3_pin52_config = {/* Internal pull-up resistor is enabled */
                                                    kPORT_PullUp,
                                                    /* Low internal pull resistor value is selected. */
                                                    kPORT_LowPullResistor,
                                                    /* Fast slew rate is configured */
                                                    kPORT_FastSlewRate,
                                                    /* Passive input filter is disabled */
                                                    kPORT_PassiveFilterDisable,
                                                    /* Open drain output is disabled */
                                                    kPORT_OpenDrainDisable,
                                                    /* Low drive strength is configured */
                                                    kPORT_LowDriveStrength,
                                                    /* Normal drive strength is configured */
                                                    kPORT_NormalDriveStrength,
                                                    /* Pin is configured as LPUART0_TXD */
                                                    kPORT_MuxAlt2,
                                                    /* Digital input enabled */
                                                    kPORT_InputBufferEnable,
                                                    /* Digital input is not inverted */
                                                    kPORT_InputNormal,
                                                    /* Pin Control Register fields [15:0] are not locked */
                                                    kPORT_UnlockRegister};
    /* PORT0_3 (pin 52) is configured as LPUART0_TXD */
    PORT_SetPinConfig(PORT0, 3U, &port0_3_pin52_config);

    /* PORT0_6 (pin 53) is configured as P0_6 */
    PORT_SetPinMux(PORT0, 6U, kPORT_MuxAlt0);

    PORT0->PCR[6] = ((PORT0->PCR[6] &
                      /* Mask bits to zero which are setting */
                      (~(PORT_PCR_IBE_MASK)))

                     /* Input Buffer Enable: Enables. */
                     | PORT_PCR_IBE(PCR_IBE_ibe1));

    /* PORT1_10 (pin 4) is configured as P1_10 */
    PORT_SetPinMux(BOARD_INITPINS_ARD_A0_PORT, BOARD_INITPINS_ARD_A0_PIN, kPORT_MuxAlt0);

    PORT1->PCR[10] = ((PORT1->PCR[10] &
                       /* Mask bits to zero which are setting */
                       (~(PORT_PCR_IBE_MASK)))

                      /* Input Buffer Enable: Enables. */
                      | PORT_PCR_IBE(PCR_IBE_ibe1));

    const port_pin_config_t port1_11_pin5_config = {/* Internal pull-up/down resistor is disabled */
                                                    kPORT_PullDisable,
                                                    /* Low internal pull resistor value is selected. */
                                                    kPORT_LowPullResistor,
                                                    /* Fast slew rate is configured */
                                                    kPORT_FastSlewRate,
                                                    /* Passive input filter is disabled */
                                                    kPORT_PassiveFilterDisable,
                                                    /* Open drain output is disabled */
                                                    kPORT_OpenDrainDisable,
                                                    /* Low drive strength is configured */
                                                    kPORT_LowDriveStrength,
                                                    /* Normal drive strength is configured */
                                                    kPORT_NormalDriveStrength,
                                                    /* Pin is configured as I3C0_PUR */
                                                    kPORT_MuxAlt10,
                                                    /* Digital input enabled */
                                                    kPORT_InputBufferEnable,
                                                    /* Digital input is not inverted */
                                                    kPORT_InputNormal,
                                                    /* Pin Control Register fields [15:0] are not locked */
                                                    kPORT_UnlockRegister};
    /* PORT1_11 (pin 5) is configured as I3C0_PUR */
    PORT_SetPinConfig(PORT1, 11U, &port1_11_pin5_config);

    /* PORT1_12 (pin 6) is configured as P1_12 */
    PORT_SetPinMux(BOARD_INITPINS_ARD_A1_PORT, BOARD_INITPINS_ARD_A1_PIN, kPORT_MuxAlt0);

    PORT1->PCR[12] = ((PORT1->PCR[12] &
                       /* Mask bits to zero which are setting */
                       (~(PORT_PCR_IBE_MASK)))

                      /* Input Buffer Enable: Enables. */
                      | PORT_PCR_IBE(PCR_IBE_ibe1));

    /* PORT1_13 (pin 7) is configured as P1_13 */
    PORT_SetPinMux(BOARD_INITPINS_ARD_A2_PORT, BOARD_INITPINS_ARD_A2_PIN, kPORT_MuxAlt0);

    PORT1->PCR[13] = ((PORT1->PCR[13] &
                       /* Mask bits to zero which are setting */
                       (~(PORT_PCR_IBE_MASK)))

                      /* Input Buffer Enable: Enables. */
                      | PORT_PCR_IBE(PCR_IBE_ibe1));

    /* PORT1_4 (pin 62) is configured as P1_4 */
    PORT_SetPinMux(BOARD_INITPINS_ARD_D0_PORT, BOARD_INITPINS_ARD_D0_PIN, kPORT_MuxAlt0);

    PORT1->PCR[4] = ((PORT1->PCR[4] &
                      /* Mask bits to zero which are setting */
                      (~(PORT_PCR_IBE_MASK)))

                     /* Input Buffer Enable: Enables. */
                     | PORT_PCR_IBE(PCR_IBE_ibe1));

    /* PORT1_5 (pin 63) is configured as P1_5 */
    PORT_SetPinMux(BOARD_INITPINS_ARD_D1_PORT, BOARD_INITPINS_ARD_D1_PIN, kPORT_MuxAlt0);

    PORT1->PCR[5] = ((PORT1->PCR[5] &
                      /* Mask bits to zero which are setting */
                      (~(PORT_PCR_IBE_MASK)))

                     /* Input Buffer Enable: Enables. */
                     | PORT_PCR_IBE(PCR_IBE_ibe1));

    /* PORT1_8 (pin 2) is configured as P1_8 */
    PORT_SetPinMux(BOARD_INITPINS_ARD_D18_PORT, BOARD_INITPINS_ARD_D18_PIN, kPORT_MuxAlt0);

    PORT1->PCR[8] = ((PORT1->PCR[8] &
                      /* Mask bits to zero which are setting */
                      (~(PORT_PCR_IBE_MASK)))

                     /* Input Buffer Enable: Enables. */
                     | PORT_PCR_IBE(PCR_IBE_ibe1));

    /* PORT1_9 (pin 3) is configured as P1_9 */
    PORT_SetPinMux(BOARD_INITPINS_ARD_D19_PORT, BOARD_INITPINS_ARD_D19_PIN, kPORT_MuxAlt0);

    PORT1->PCR[9] = ((PORT1->PCR[9] &
                      /* Mask bits to zero which are setting */
                      (~(PORT_PCR_IBE_MASK)))

                     /* Input Buffer Enable: Enables. */
                     | PORT_PCR_IBE(PCR_IBE_ibe1));

    PORT2->PCR[0] = ((PORT2->PCR[0] &
                      /* Mask bits to zero which are setting */
                      (~(PORT_PCR_MUX_MASK | PORT_PCR_IBE_MASK)))

                     /* Pin Multiplex Control: PORT2_0 (pin 14) is configured as P2_0. */
                     | PORT_PCR_MUX(PORT2_PCR0_MUX_mux00)

                     /* Input Buffer Enable: Enables. */
                     | PORT_PCR_IBE(PCR_IBE_ibe1));

    PORT2->PCR[12] = ((PORT2->PCR[12] &
                       /* Mask bits to zero which are setting */
                       (~(PORT_PCR_MUX_MASK | PORT_PCR_IBE_MASK)))

                      /* Pin Multiplex Control: PORT2_12 (pin 22) is configured as P2_12. */
                      | PORT_PCR_MUX(PORT2_PCR12_MUX_mux00)

                      /* Input Buffer Enable: Enables. */
                      | PORT_PCR_IBE(PCR_IBE_ibe1));

    PORT2->PCR[13] = ((PORT2->PCR[13] &
                       /* Mask bits to zero which are setting */
                       (~(PORT_PCR_MUX_MASK | PORT_PCR_IBE_MASK)))

                      /* Pin Multiplex Control: PORT2_13 (pin 23) is configured as P2_13. */
                      | PORT_PCR_MUX(PORT2_PCR13_MUX_mux00)

                      /* Input Buffer Enable: Enables. */
                      | PORT_PCR_IBE(PCR_IBE_ibe1));

    PORT2->PCR[16] = ((PORT2->PCR[16] &
                       /* Mask bits to zero which are setting */
                       (~(PORT_PCR_MUX_MASK | PORT_PCR_IBE_MASK)))

                      /* Pin Multiplex Control: PORT2_16 (pin 24) is configured as P2_16. */
                      | PORT_PCR_MUX(PORT2_PCR16_MUX_mux00)

                      /* Input Buffer Enable: Enables. */
                      | PORT_PCR_IBE(PCR_IBE_ibe1));

    PORT2->PCR[4] = ((PORT2->PCR[4] &
                      /* Mask bits to zero which are setting */
                      (~(PORT_PCR_MUX_MASK | PORT_PCR_IBE_MASK)))

                     /* Pin Multiplex Control: PORT2_4 (pin 18) is configured as P2_4. */
                     | PORT_PCR_MUX(PORT2_PCR4_MUX_mux00)

                     /* Input Buffer Enable: Enables. */
                     | PORT_PCR_IBE(PCR_IBE_ibe1));

    PORT2->PCR[5] = ((PORT2->PCR[5] &
                      /* Mask bits to zero which are setting */
                      (~(PORT_PCR_MUX_MASK | PORT_PCR_IBE_MASK)))

                     /* Pin Multiplex Control: PORT2_5 (pin 19) is configured as P2_5. */
                     | PORT_PCR_MUX(PORT2_PCR5_MUX_mux00)

                     /* Input Buffer Enable: Enables. */
                     | PORT_PCR_IBE(PCR_IBE_ibe1));

    PORT2->PCR[6] = ((PORT2->PCR[6] &
                      /* Mask bits to zero which are setting */
                      (~(PORT_PCR_MUX_MASK | PORT_PCR_IBE_MASK)))

                     /* Pin Multiplex Control: PORT2_6 (pin 20) is configured as P2_6. */
                     | PORT_PCR_MUX(PORT2_PCR6_MUX_mux00)

                     /* Input Buffer Enable: Enables. */
                     | PORT_PCR_IBE(PCR_IBE_ibe1));

    /* PORT3_0 (pin 46) is configured as PWM0_A0 */
    PORT_SetPinMux(BOARD_INITPINS_ARD_D3_PORT, BOARD_INITPINS_ARD_D3_PIN, kPORT_MuxAlt5);

    PORT3->PCR[0] = ((PORT3->PCR[0] &
                      /* Mask bits to zero which are setting */
                      (~(PORT_PCR_IBE_MASK)))

                     /* Input Buffer Enable: Enables. */
                     | PORT_PCR_IBE(PCR_IBE_ibe1));

    /* PORT3_1 (pin 45) is configured as P3_1 */
    PORT_SetPinMux(BOARD_INITPINS_ARD_D7_PORT, BOARD_INITPINS_ARD_D7_PIN, kPORT_MuxAlt0);

    PORT3->PCR[1] = ((PORT3->PCR[1] &
                      /* Mask bits to zero which are setting */
                      (~(PORT_PCR_IBE_MASK)))

                     /* Input Buffer Enable: Enables. */
                     | PORT_PCR_IBE(PCR_IBE_ibe1));

    /* PORT3_10 (pin 40) is configured as PWM0_A2 */
    PORT_SetPinMux(PORT3, 10U, kPORT_MuxAlt5);

    PORT3->PCR[10] = ((PORT3->PCR[10] &
                       /* Mask bits to zero which are setting */
                       (~(PORT_PCR_IBE_MASK)))

                      /* Input Buffer Enable: Enables. */
                      | PORT_PCR_IBE(PCR_IBE_ibe1));

    /* PORT3_12 (pin 38) is configured as P3_12 */
    PORT_SetPinMux(BOARD_INITPINS_ARD_D5_PORT, BOARD_INITPINS_ARD_D5_PIN, kPORT_MuxAlt0);

    PORT3->PCR[12] = ((PORT3->PCR[12] &
                       /* Mask bits to zero which are setting */
                       (~(PORT_PCR_IBE_MASK)))

                      /* Input Buffer Enable: Enables. */
                      | PORT_PCR_IBE(PCR_IBE_ibe1));

    /* PORT3_13 (pin 37) is configured as P3_13 */
    PORT_SetPinMux(BOARD_INITPINS_ARD_D6_PORT, BOARD_INITPINS_ARD_D6_PIN, kPORT_MuxAlt0);

    PORT3->PCR[13] = ((PORT3->PCR[13] &
                       /* Mask bits to zero which are setting */
                       (~(PORT_PCR_IBE_MASK)))

                      /* Input Buffer Enable: Enables. */
                      | PORT_PCR_IBE(PCR_IBE_ibe1));

    /* PORT3_14 (pin 36) is configured as P3_14 */
    PORT_SetPinMux(BOARD_INITPINS_ARD_D9_PORT, BOARD_INITPINS_ARD_D9_PIN, kPORT_MuxAlt0);

    PORT3->PCR[14] = ((PORT3->PCR[14] &
                       /* Mask bits to zero which are setting */
                       (~(PORT_PCR_IBE_MASK)))

                      /* Input Buffer Enable: Enables. */
                      | PORT_PCR_IBE(PCR_IBE_ibe1));

    /* PORT3_15 (pin 35) is configured as P3_15 */
    PORT_SetPinMux(BOARD_INITPINS_ARD_D8_PORT, BOARD_INITPINS_ARD_D8_PIN, kPORT_MuxAlt0);

    PORT3->PCR[15] = ((PORT3->PCR[15] &
                       /* Mask bits to zero which are setting */
                       (~(PORT_PCR_IBE_MASK)))

                      /* Input Buffer Enable: Enables. */
                      | PORT_PCR_IBE(PCR_IBE_ibe1));

    PORT3->PCR[30] = ((PORT3->PCR[30] &
                       /* Mask bits to zero which are setting */
                       (~(PORT_PCR_MUX_MASK | PORT_PCR_IBE_MASK)))

                      /* Pin Multiplex Control: PORT3_30 (pin 31) is configured as P3_30. */
                      | PORT_PCR_MUX(PORT3_PCR30_MUX_mux00)

                      /* Input Buffer Enable: Enables. */
                      | PORT_PCR_IBE(PCR_IBE_ibe1));

    PORT3->PCR[31] = ((PORT3->PCR[31] &
                       /* Mask bits to zero which are setting */
                       (~(PORT_PCR_MUX_MASK | PORT_PCR_IBE_MASK)))

                      /* Pin Multiplex Control: PORT3_31 (pin 30) is configured as P3_31. */
                      | PORT_PCR_MUX(PORT3_PCR31_MUX_mux00)

                      /* Input Buffer Enable: Enables. */
                      | PORT_PCR_IBE(PCR_IBE_ibe1));

    PORT3->PCR[7] = ((PORT3->PCR[7] &
                      /* Mask bits to zero which are setting */
                      (~(PORT_PCR_MUX_MASK | PORT_PCR_IBE_MASK)))

                     /* Pin Multiplex Control: PORT3_7 (pin 43) is configured as PWM0_B0. */
                     | PORT_PCR_MUX(PORT3_PCR7_MUX_mux101)

                     /* Input Buffer Enable: Enables. */
                     | PORT_PCR_IBE(PCR_IBE_ibe1));

    /* PORT3_8 (pin 42) is configured as PWM0_A1 */
    PORT_SetPinMux(PORT3, 8U, kPORT_MuxAlt5);

    PORT3->PCR[8] = ((PORT3->PCR[8] &
                      /* Mask bits to zero which are setting */
                      (~(PORT_PCR_IBE_MASK)))

                     /* Input Buffer Enable: Enables. */
                     | PORT_PCR_IBE(PCR_IBE_ibe1));
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
