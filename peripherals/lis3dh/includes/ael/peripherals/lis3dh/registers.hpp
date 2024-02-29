/**
 * @note Adjusted from: https://github.com/RavenSystem/esp-homekit-devices
 * Added unions for easier conversion
 */
#ifndef __AEL_PERIPHERALS_LIS3DH_REGISTERS_HPP
#define __AEL_PERIPHERALS_LIS3DH_REGISTERS_HPP
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"

#include "ael/types.hpp"

#define ANY_DATA_READY 0x0f  // REG_STATUS<3:0>

namespace ael::peripherals::lis3dh {
using namespace types;

/**
 * @brief register addresses
 */
struct reg_addr {
    static constexpr u8 OUT_ADC1_L = 0x08;
    static constexpr u8 OUT_ADC1_H = 0x09;
    static constexpr u8 OUT_ADC2_L = 0x0a;
    static constexpr u8 OUT_ADC2_H = 0x0b;
    static constexpr u8 OUT_ADC3_L = 0x0c;
    static constexpr u8 OUT_ADC3_H = 0x0d;
    static constexpr u8 INT_COUNTER = 0x0e;
    static constexpr u8 WHO_AM_I = 0x0f;
    static constexpr u8 REFERENCE = 0x26;
    static constexpr u8 OUT_X_L = 0x28;
    static constexpr u8 OUT_X_H = 0x29;
    static constexpr u8 OUT_Y_L = 0x2a;
    static constexpr u8 OUT_Y_H = 0x2b;
    static constexpr u8 OUT_Z_L = 0x2c;
    static constexpr u8 OUT_Z_H = 0x2d;
    static constexpr u8 INT1_THS = 0x32;
    static constexpr u8 INT1_DUR = 0x33;
    static constexpr u8 INT2_THS = 0x36;
    static constexpr u8 INT2_DUR = 0x37;
    static constexpr u8 CLICK_SRC = 0x39;
    static constexpr u8 CLICK_THS = 0x3a;
    static constexpr u8 TIME_LIMIT = 0x3b;
    static constexpr u8 TIME_LATENCY = 0x3c;
    static constexpr u8 TIME_WINDOW = 0x3d;
};

union reg_status {
    static constexpr u8 ADDR = 0x27;
    struct {
        u8 XDA : 1;    // STATUS<0>   X axis new data available
        u8 YDA : 1;    // STATUS<1>   Y axis new data available
        u8 ZDA : 1;    // STATUS<2>   Z axis new data available
        u8 ZYXDA : 1;  // STATUS<3>   X, Y and Z axis new data available
        u8 XOR : 1;    // STATUS<4>   X axis data overrun
        u8 YOR : 1;    // STATUS<5>   Y axis data overrun
        u8 ZOR : 1;    // STATUS<6>   Z axis data overrun
        u8 ZYXOR : 1;  // STATUS<7>   X, Y and Z axis data overrun
    };
    u8 reg;
};

union reg_status_aux {
    static constexpr u8 ADDR = 0x07;
    struct {
        u8 DA1 : 1;    // STATUS_AUX<0>   1 axis data available
        u8 DA2 : 1;    // STATUS_AUX<1>   2 axis data available
        u8 DA3 : 1;    // STATUS_AUX<2>   3 axis data available
        u8 DA321 : 1;  // STATUS_AUX<3>   1, 2 and 3 axis data available
        u8 OR1 : 1;    // STATUS_AUX<4>   1 axis data overrun
        u8 OR2 : 1;    // STATUS_AUX<5>   2 axis data overrun
        u8 OR3 : 1;    // STATUS_AUX<1>   3 axis data overrun
        u8 OR321 : 1;  // STATUS_AUX<7>   1, 2 and 3 axis data overrun
    };
    u8 reg;
};

union reg_ctrl1 {
    static constexpr u8 ADDR = 0x20;

    static constexpr u8 RATE_1_HZ = 0x10;
    static constexpr u8 RATE_10_HZ = 0x20;
    static constexpr u8 RATE_25_HZ = 0x30;
    static constexpr u8 RATE_50_HZ = 0x40;
    static constexpr u8 RATE_100_HZ = 0x50;
    static constexpr u8 RATE_200_HZ = 0x60;
    static constexpr u8 RATE_400_HZ = 0x70;

    struct {
        u8 Xen : 1;   // CTRL1<0>    X axis enable
        u8 Yen : 1;   // CTRL1<1>    Y axis enable
        u8 Zen : 1;   // CTRL1<2>    Z axis enable
        u8 LPen : 1;  // CTRL1<3>    Low power mode enable
        u8 ODR : 4;   // CTRL1<7:4>  Data rate selection
    };
    u8 reg;
};

union reg_ctrl2 {
    static constexpr u8 ADDR = 0x21;
    struct {
        u8 HPIS1 : 1;    // CTRL2<0>    HPF enabled for AOI on INT2
        u8 HPIS2 : 1;    // CTRL2<1>    HPF enabled for AOI on INT2
        u8 HPCLICK : 1;  // CTRL2<2>    HPF enabled for CLICK
        u8 FDS : 1;      // CTRL2<3>    Filter data selection
        u8 HPCF : 2;     // CTRL2<5:4>  HPF cutoff frequency
        u8 HPM : 2;      // CTRL2<7:6>  HPF mode
    };
    u8 reg;
};

union reg_ctrl3 {
    static constexpr u8 ADDR = 0x22;
    struct {
        u8 unused : 1;      // CTRL3<0>  unused
        u8 I1_OVERRUN : 1;  // CTRL3<1>  FIFO Overrun interrupt on INT1
        u8 I1_WTM1 : 1;     // CTRL3<2>  FIFO Watermark interrupt on INT1
        u8 IT_DRDY2 : 1;    // CTRL3<3>  DRDY2 (ZYXDA) interrupt on INT1
        u8 IT_DRDY1 : 1;    // CTRL3<4>  DRDY1 (321DA) interrupt on INT1
        u8 I1_AOI2 : 1;     // CTRL3<5>  AOI2 interrupt on INT1
        u8 I1_AOI1 : 1;     // CTRL3<6>  AOI1 interrupt on INT1
        u8 I1_CLICK : 1;    // CTRL3<7>  CLICK interrupt on INT1
    };
    u8 reg;
};

union reg_ctrl4 {
    static constexpr u8 ADDR = 0x23;
    struct {
        u8 SIM : 1;  // CTRL4<0>   SPI serial interface selection
        u8 ST : 2;   // CTRL4<2:1> Self test enable
        u8 HR : 1;   // CTRL4<3>   High resolution output mode
        u8 FS : 2;   // CTRL4<5:4> Full scale selection
        u8 BLE : 1;  // CTRL4<6>   Big/litle endian data selection
        u8 BDU : 1;  // CTRL4<7>   Block data update
    };
    u8 reg;
};

union reg_ctrl5 {
    static constexpr u8 ADDR = 0x24;
    struct {
        u8 D4D_INT2 : 1;  // CTRL5<0>   4D detection enabled on INT1
        u8 LIR_INT2 : 1;  // CTRL5<1>   Latch interrupt request on INT1
        u8 D4D_INT1 : 1;  // CTRL5<2>   4D detection enabled on INT2
        u8 LIR_INT1 : 1;  // CTRL5<3>   Latch interrupt request on INT1
        u8 unused : 2;    // CTRL5<5:4> unused
        u8 FIFO_EN : 1;   // CTRL5<6>   FIFO enabled
        u8 BOOT : 1;      // CTRL5<7>   Reboot memory content
    };
    u8 reg;
};

union reg_ctrl6 {
    static constexpr u8 ADDR = 0x25;
    struct {
        u8 unused1 : 1;    // CTRL6<0>   unused
        u8 H_LACTIVE : 1;  // CTRL6<1>   Interrupt polarity
        u8 unused2 : 1;    // CTRL6<2>   unused
        u8 I2_ACT : 1;     // CTRL6<3>   ?
        u8 I2_BOOT : 1;    // CTRL6<4>   ?
        u8 I2_AOI2 : 1;    // CTRL6<5>   AOI2 interrupt on INT1
        u8 I2_AOI1 : 1;    // CTRL6<6>   AOI1 interrupt on INT1
        u8 I2_CLICK : 1;   // CTRL6<7>   CLICK interrupt on INT2
    };
    u8 reg;
};

union reg_temp_cfg {
    static constexpr u8 ADDR = 0x1F;
    struct {
        u8 __reserved : 6;
        u8 TEMP_EN : 1;  // ADC enable, Default = 0
        u8 ADC_EN : 1;   // Temperature Sensor, Default = 0: enable=1, disable=0
    };
    u8 reg;
};

union reg_fifo_ctrl {
    static constexpr u8 ADDR = 0x2e;
    static constexpr u8 BYPASS = 0x00;
    static constexpr u8 FIFO = 0x40;
    static constexpr u8 STREAM = 0x80;
    static constexpr u8 STREAM_TO_FIFO = 0xc0;
    struct {
        u8 FTH : 5;  // FIFO_CTRL<4:0>  FIFO threshold
        u8 TR : 1;   // FIFO_CTRL<5>    Trigger selection INT1 / INT2
        u8 FM : 2;   // FIFO_CTRL<7:6>  FIFO mode
    };
    u8 reg;
};

union reg_fifo_src {
    static constexpr u8 ADDR = 0x2f;
    struct {
        u8 FFS : 5;        // FIFO_SRC<4:0>  FIFO samples stored
        u8 EMPTY : 1;      // FIFO_SRC<5>    FIFO is empty
        u8 OVRN_FIFO : 1;  // FIFO_SRC<6>    FIFO buffer full
        u8 WTM : 1;        // FIFO_SRC<7>    FIFO content exceeds watermark
    };
    u8 reg;
};

union reg_intx_cfg {
    static constexpr u8 INT1_ADDR = 0x30;
    static constexpr u8 INT2_ADDR = 0x34;
    struct {
        u8 XLIE : 1;  // INTx_CFG<0>    X axis below threshold enabled
        u8 XHIE : 1;  // INTx_CFG<1>    X axis above threshold enabled
        u8 YLIE : 1;  // INTx_CFG<2>    Y axis below threshold enabled
        u8 YHIE : 1;  // INTx_CFG<3>    Y axis above threshold enabled
        u8 ZLIE : 1;  // INTx_CFG<4>    Z axis below threshold enabled
        u8 ZHIE : 1;  // INTx_CFG<5>    Z axis above threshold enabled
        u8 SIXD : 1;  // INTx_CFG<6>    6D/4D orientation detecetion enabled
        u8 AOI : 1;   // INTx_CFG<7>    AND/OR combination of interrupt events
    };
    u8 reg;
};

union reg_intx_src {
    static constexpr u8 INT1_ADDR = 0x31;
    static constexpr u8 INT2_ADDR = 0x35;
    struct {
        u8 XL : 1;      // INTx_SRC<0>    X axis below threshold enabled
        u8 XH : 1;      // INTx_SRC<1>    X axis above threshold enabled
        u8 YL : 1;      // INTx_SRC<2>    Y axis below threshold enabled
        u8 YH : 1;      // INTx_SRC<3>    Y axis above threshold enabled
        u8 ZL : 1;      // INTx_SRC<4>    Z axis below threshold enabled
        u8 ZH : 1;      // INTx_SRC<5>    Z axis above threshold enabled
        u8 IA : 1;      // INTx_SRC<6>    Interrupt active
        u8 unused : 1;  // INTx_SRC<7>    unused}
    };
    u8 reg;
};

union reg_click_cfg {
    static constexpr u8 ADDR = 0x38;
    struct {
        u8 XS : 1;      // CLICK_CFG<0>    X axis single click enabled
        u8 XD : 1;      // CLICK_CFG<1>    X axis double click enabled
        u8 YS : 1;      // CLICK_CFG<2>    Y axis single click enabled
        u8 YD : 1;      // CLICK_CFG<3>    Y axis double click enabled
        u8 ZS : 1;      // CLICK_CFG<4>    Z axis single click enabled
        u8 ZD : 1;      // CLICK_CFG<5>    Z axis double click enabled
        u8 unused : 2;  // CLICK_CFG<7:6>  unused
    };
    u8 reg;
};

}  // namespace ael::peripherals::lis3dh
#pragma GCC diagnostic pop
#endif  // !__AEL_PERIPHERALS_LIS3DH_REGISTERS_HPP
