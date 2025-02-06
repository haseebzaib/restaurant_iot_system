/*
 *  ======== ti_radio_config.c ========
 *  Configured RadioConfig module definitions
 *
 *  DO NOT EDIT - This file is generated for the CC1314R10RSK
 *  by the SysConfig tool.
 *
 *  Radio Config module version : 1.18.0
 *  SmartRF Studio data version : 2.31.0
 */

#include "ti_radio_config.h"
#include DeviceFamily_constructPath(rf_patches/rf_patch_cpe_multi_protocol.h)

// Custom overrides
#include <ti/ti154stack/common/boards/ti_154stack_overrides.h>


// *********************************************************************************
//   RF Frontend configuration
// *********************************************************************************
// RF design based on: LP_EM_CC1314R10

// TX Power tables
// The RF_TxPowerTable_DEFAULT_PA_ENTRY and RF_TxPowerTable_HIGH_PA_ENTRY macros are defined in RF.h.
// The following arguments are required:
// RF_TxPowerTable_DEFAULT_PA_ENTRY(bias, gain, boost, coefficient)
// RF_TxPowerTable_HIGH_PA_ENTRY(bias, ibboost, boost, coefficient, ldoTrim)
// See the Technical Reference Manual for further details about the "txPower" Command field.
// The PA settings require the CCFG_FORCE_VDDR_HH = 0 unless stated otherwise.

// 868 MHz, 13 dBm
RF_TxPowerTable_Entry txPowerTable_868_pa13[TXPOWERTABLE_868_PA13_SIZE] =
{
    {-20, RF_TxPowerTable_CC13x4Sub1GHz_DEFAULT_PA_ENTRY(22, 3, 0, 0, 3) }, // 0x0300D6
    {-19, RF_TxPowerTable_CC13x4Sub1GHz_DEFAULT_PA_ENTRY(25, 3, 0, 0, 3) }, // 0x0300D9
    {-18, RF_TxPowerTable_CC13x4Sub1GHz_DEFAULT_PA_ENTRY(28, 3, 0, 0, 3) }, // 0x0300DC
    {-17, RF_TxPowerTable_CC13x4Sub1GHz_DEFAULT_PA_ENTRY(32, 3, 0, 0, 3) }, // 0x0300E0
    {-16, RF_TxPowerTable_CC13x4Sub1GHz_DEFAULT_PA_ENTRY(37, 3, 0, 0, 3) }, // 0x0300E5
    {-15, RF_TxPowerTable_CC13x4Sub1GHz_DEFAULT_PA_ENTRY(42, 3, 0, 4, 3) }, // 0x0308EA
    {-14, RF_TxPowerTable_CC13x4Sub1GHz_DEFAULT_PA_ENTRY(48, 3, 0, 4, 3) }, // 0x0308F0
    {-13, RF_TxPowerTable_CC13x4Sub1GHz_DEFAULT_PA_ENTRY(56, 3, 0, 0, 3) }, // 0x0300F8
    {-12, RF_TxPowerTable_CC13x4Sub1GHz_DEFAULT_PA_ENTRY(63, 3, 0, 0, 3) }, // 0x0300FF
    {-11, RF_TxPowerTable_CC13x4Sub1GHz_DEFAULT_PA_ENTRY(38, 2, 0, 0, 3) }, // 0x0300A6
    {-10, RF_TxPowerTable_CC13x4Sub1GHz_DEFAULT_PA_ENTRY(35, 3, 0, 4, 2) }, // 0x0208E3
    {-9, RF_TxPowerTable_CC13x4Sub1GHz_DEFAULT_PA_ENTRY(50, 2, 0, 4, 3) }, // 0x0308B2
    {-8, RF_TxPowerTable_CC13x4Sub1GHz_DEFAULT_PA_ENTRY(58, 2, 0, 0, 3) }, // 0x0300BA
    {-7, RF_TxPowerTable_CC13x4Sub1GHz_DEFAULT_PA_ENTRY(55, 3, 0, 7, 2) }, // 0x020EF7
    {-6, RF_TxPowerTable_CC13x4Sub1GHz_DEFAULT_PA_ENTRY(63, 3, 0, 2, 2) }, // 0x0204FF
    {-5, RF_TxPowerTable_CC13x4Sub1GHz_DEFAULT_PA_ENTRY(26, 3, 0, 14, 1) }, // 0x011CDA
    {-4, RF_TxPowerTable_CC13x4Sub1GHz_DEFAULT_PA_ENTRY(40, 2, 0, 14, 2) }, // 0x021CA8
    {-3, RF_TxPowerTable_CC13x4Sub1GHz_DEFAULT_PA_ENTRY(47, 2, 0, 14, 2) }, // 0x021CAF
    {-2, RF_TxPowerTable_CC13x4Sub1GHz_DEFAULT_PA_ENTRY(42, 3, 0, 25, 1) }, // 0x0132EA
    {-1, RF_TxPowerTable_CC13x4Sub1GHz_DEFAULT_PA_ENTRY(50, 3, 0, 28, 1) }, // 0x0138F2
    {0, RF_TxPowerTable_CC13x4Sub1GHz_DEFAULT_PA_ENTRY(61, 3, 0, 19, 1) }, // 0x0126FD
    {1, RF_TxPowerTable_CC13x4Sub1GHz_DEFAULT_PA_ENTRY(32, 1, 0, 25, 2) }, // 0x023260
    {2, RF_TxPowerTable_CC13x4Sub1GHz_DEFAULT_PA_ENTRY(33, 2, 0, 32, 1) }, // 0x0140A1
    {3, RF_TxPowerTable_CC13x4Sub1GHz_DEFAULT_PA_ENTRY(40, 2, 0, 39, 1) }, // 0x014EA8
    {4, RF_TxPowerTable_CC13x4Sub1GHz_DEFAULT_PA_ENTRY(49, 2, 0, 49, 1) }, // 0x0162B1
    {5, RF_TxPowerTable_CC13x4Sub1GHz_DEFAULT_PA_ENTRY(35, 3, 0, 46, 0) }, // 0x005CE3
    {6, RF_TxPowerTable_CC13x4Sub1GHz_DEFAULT_PA_ENTRY(43, 3, 0, 56, 0) }, // 0x0070EB
    {7, RF_TxPowerTable_CC13x4Sub1GHz_DEFAULT_PA_ENTRY(27, 1, 0, 39, 1) }, // 0x014E5B
    {8, RF_TxPowerTable_CC13x4Sub1GHz_DEFAULT_PA_ENTRY(35, 1, 0, 53, 1) }, // 0x016A63
    {9, RF_TxPowerTable_CC13x4Sub1GHz_DEFAULT_PA_ENTRY(47, 1, 0, 64, 1) }, // 0x01806F
    {10, RF_TxPowerTable_CC13x4Sub1GHz_DEFAULT_PA_ENTRY(47, 2, 0, 71, 0) }, // 0x008EAF
    {11, RF_TxPowerTable_CC13x4Sub1GHz_DEFAULT_PA_ENTRY(23, 1, 0, 53, 0) }, // 0x006A57
    {12, RF_TxPowerTable_CC13x4Sub1GHz_DEFAULT_PA_ENTRY(25, 0, 0, 71, 0) }, // 0x008E19
    // This setting requires CCFG_FORCE_VDDR_HH = 1.
    {14, RF_TxPowerTable_CC13x4Sub1GHz_DEFAULT_PA_ENTRY(63, 0, 1, 0, 0) }, // 0x00013F
    RF_TxPowerTable_TERMINATION_ENTRY
};



//*********************************************************************************
//  RF Setting:   IEEE 802.15.4, 50 kbps, 25 kHz Deviation, 2-GFSK, 100 kHz RX Bandwidth
//
//  PHY:          2gfsk50kbps154g
//  Setting file: setting_tc106_154g.json
//*********************************************************************************

// PARAMETER SUMMARY
// Frequency (MHz): 915.0000
// Deviation (kHz): 25.0
// Max Packet Length: 2047
// Preamble Count: 7 Bytes
// Preamble Mode: Send 0 as the first preamble bit
// RX Filter BW (kHz): 98.0
// Symbol Rate (kBaud): 50.000
// Sync Word: 0x55904E
// Sync Word Length: 24 Bits
// TX Power (dBm): 5
// Whitening: Dynamically IEEE 802.15.4g compatible whitener and 16/32-bit CRC

// TI-RTOS RF Mode Object
RF_Mode RF_prop_2gfsk50kbps154g =
{
    .rfMode = RF_MODE_AUTO,
    .cpePatchFxn = &rf_patch_cpe_multi_protocol,
    .mcePatchFxn = 0,
    .rfePatchFxn = 0
};

// Overrides for CMD_PROP_RADIO_DIV_SETUP
uint32_t pOverrides_2gfsk50kbps154g[] =
{
    // override_txsub1_placeholder.json
    // TX sub-1GHz power override
    TXSUB1_POWER_OVERRIDE(0x005CE3),
    // override_prop_common.json
    // Tx: Set DCDC settings IPEAK=7, dither = off
    (uint32_t)0x004388D3,
    // override_prop_common_sub1g.json
    // TX: Set FSCA divider bias to 1
    HW32_ARRAY_OVERRIDE(0x405C,0x0001),
    // TX: Set FSCA divider bias to 1
    (uint32_t)0x08141131,
    // override_tc106.json
    // Tx: Configure PA ramp time, PACTL2.RC=0x1 (in ADI0, set PACTL2[4:3]=0x1)
    ADI_2HALFREG_OVERRIDE(0,16,0x8,0x8,17,0x1,0x1),
    // Rx: Set AGC reference level to 0x1A (default: 0x2E)
    HW_REG_OVERRIDE(0x609C,0x001A),
    // Rx: Set RSSI offset to adjust reported RSSI by -1 dB at 779-930 MHz
    (uint32_t)0x000188A3,
    // Rx: Set anti-aliasing filter bandwidth to 0xD (in ADI0, set IFAMPCTL3[7:4]=0xD)
    ADI_HALFREG_OVERRIDE(0,61,0xF,0xD),
    // Tx: Configure PA ramping, set wait time before turning off (0x1A ticks of 16/24 us = 17.3 us).
    HW_REG_OVERRIDE(0x6028,0x001A),
    // ti/ti154stack/common/boards/ti_154stack_overrides.h
    TI_154_STACK_OVERRIDES(),
    (uint32_t)0xFFFFFFFF
};



// CMD_PROP_RADIO_DIV_SETUP
// Proprietary Mode Radio Setup Command for All Frequency Bands
const rfc_CMD_PROP_RADIO_DIV_SETUP_t RF_cmdPropRadioDivSetup_2gfsk50kbps154g =
{
    .commandNo = 0x3807,
    .status = 0x0000,
    .pNextOp = 0,
    .startTime = 0x00000000,
    .startTrigger.triggerType = 0x0,
    .startTrigger.bEnaCmd = 0x0,
    .startTrigger.triggerNo = 0x0,
    .startTrigger.pastTrig = 0x0,
    .condition.rule = 0x1,
    .condition.nSkip = 0x0,
    .modulation.modType = 0x1,
    .modulation.deviation = 0x64,
    .modulation.deviationStepSz = 0x0,
    .symbolRate.preScale = 0xF,
    .symbolRate.rateWord = 0x8000,
    .symbolRate.decimMode = 0x0,
    .rxBw = 0x52,
    .preamConf.nPreamBytes = 0x7,
    .preamConf.preamMode = 0x0,
    .formatConf.nSwBits = 0x18,
    .formatConf.bBitReversal = 0x0,
    .formatConf.bMsbFirst = 0x1,
    .formatConf.fecMode = 0x0,
    .formatConf.whitenMode = 0x7,
    .config.frontEndMode = 0x0,
    .config.biasMode = 0x1,
    .config.analogCfgMode = 0x0,
    .config.bNoFsPowerUp = 0x0,
    .config.bSynthNarrowBand = 0x0,
    .txPower = 0xFFFE,
    .pRegOverride = pOverrides_2gfsk50kbps154g,
    .centerFreq = 0x0393,
    .intFreq = 0x8000,
    .loDivider = 0x05
};

// CMD_FS
// Frequency Synthesizer Programming Command
const rfc_CMD_FS_t RF_cmdFs_2gfsk50kbps154g =
{
    .commandNo = 0x0803,
    .status = 0x0000,
    .pNextOp = 0,
    .startTime = 0x00000000,
    .startTrigger.triggerType = 0x0,
    .startTrigger.bEnaCmd = 0x0,
    .startTrigger.triggerNo = 0x0,
    .startTrigger.pastTrig = 0x0,
    .condition.rule = 0x1,
    .condition.nSkip = 0x0,
    .frequency = 0x0393,
    .fractFreq = 0x0000,
    .synthConf.bTxMode = 0x0,
    .synthConf.refFreq = 0x0,
    .__dummy0 = 0x00,
    .__dummy1 = 0x00,
    .__dummy2 = 0x00,
    .__dummy3 = 0x0000
};

// CMD_PROP_TX_ADV
// Proprietary Mode Advanced Transmit Command
const rfc_CMD_PROP_TX_ADV_t RF_cmdPropTxAdv_2gfsk50kbps154g =
{
    .commandNo = 0x3803,
    .status = 0x0000,
    .pNextOp = 0,
    .startTime = 0x00000000,
    .startTrigger.triggerType = 0x2,
    .startTrigger.bEnaCmd = 0x0,
    .startTrigger.triggerNo = 0x0,
    .startTrigger.pastTrig = 0x1,
    .condition.rule = 0x1,
    .condition.nSkip = 0x0,
    .pktConf.bFsOff = 0x0,
    .pktConf.bUseCrc = 0x1,
    .pktConf.bCrcIncSw = 0x0,
    .pktConf.bCrcIncHdr = 0x0,
    .numHdrBits = 0x10,
    .pktLen = 0x0014,
    .startConf.bExtTxTrig = 0x0,
    .startConf.inputMode = 0x0,
    .startConf.source = 0x0,
    .preTrigger.triggerType = 0x4,
    .preTrigger.bEnaCmd = 0x0,
    .preTrigger.triggerNo = 0x0,
    .preTrigger.pastTrig = 0x1,
    .preTime = 0x00000000,
    .syncWord = 0x0055904E,
    .pPkt = 0
};

// CMD_PROP_RX_ADV
// Proprietary Mode Advanced Receive Command
const rfc_CMD_PROP_RX_ADV_t RF_cmdPropRxAdv_2gfsk50kbps154g =
{
    .commandNo = 0x3804,
    .status = 0x0000,
    .pNextOp = 0,
    .startTime = 0x00000000,
    .startTrigger.triggerType = 0x0,
    .startTrigger.bEnaCmd = 0x0,
    .startTrigger.triggerNo = 0x0,
    .startTrigger.pastTrig = 0x0,
    .condition.rule = 0x1,
    .condition.nSkip = 0x0,
    .pktConf.bFsOff = 0x0,
    .pktConf.bRepeatOk = 0x0,
    .pktConf.bRepeatNok = 0x0,
    .pktConf.bUseCrc = 0x1,
    .pktConf.bCrcIncSw = 0x0,
    .pktConf.bCrcIncHdr = 0x0,
    .pktConf.endType = 0x0,
    .pktConf.filterOp = 0x1,
    .rxConf.bAutoFlushIgnored = 0x1,
    .rxConf.bAutoFlushCrcErr = 0x0,
    .rxConf.bIncludeHdr = 0x1,
    .rxConf.bIncludeCrc = 0x1,
    .rxConf.bAppendRssi = 0x1,
    .rxConf.bAppendTimestamp = 0x1,
    .rxConf.bAppendStatus = 0x1,
    .syncWord0 = 0x0055904E,
    .syncWord1 = 0x00000000,
    .maxPktLen = 0x07FF,
    .hdrConf.numHdrBits = 0x10,
    .hdrConf.lenPos = 0x0,
    .hdrConf.numLenBits = 0xB,
    .addrConf.addrType = 0x0,
    .addrConf.addrSize = 0x0,
    .addrConf.addrPos = 0x0,
    .addrConf.numAddr = 0x0,
    .lenOffset = 0xFC,
    .endTrigger.triggerType = 0x1,
    .endTrigger.bEnaCmd = 0x0,
    .endTrigger.triggerNo = 0x0,
    .endTrigger.pastTrig = 0x0,
    .endTime = 0x00000000,
    .pAddr = 0,
    .pQueue = 0,
    .pOutput = 0
};

// CMD_PROP_CS
// Carrier Sense Command
const rfc_CMD_PROP_CS_t RF_cmdPropCs_2gfsk50kbps154g =
{
    .commandNo = 0x3805,
    .status = 0x0000,
    .pNextOp = 0,
    .startTime = 0x00000000,
    .startTrigger.triggerType = 0x0,
    .startTrigger.bEnaCmd = 0x0,
    .startTrigger.triggerNo = 0x0,
    .startTrigger.pastTrig = 0x0,
    .condition.rule = 0x0,
    .condition.nSkip = 0x0,
    .csFsConf.bFsOffIdle = 0x0,
    .csFsConf.bFsOffBusy = 0x0,
    .__dummy0 = 0x00,
    .csConf.bEnaRssi = 0x0,
    .csConf.bEnaCorr = 0x0,
    .csConf.operation = 0x0,
    .csConf.busyOp = 0x0,
    .csConf.idleOp = 0x0,
    .csConf.timeoutRes = 0x0,
    .rssiThr = 0x00,
    .numRssiIdle = 0x00,
    .numRssiBusy = 0x00,
    .corrPeriod = 0x0000,
    .corrConfig.numCorrInv = 0x0,
    .corrConfig.numCorrBusy = 0x0,
    .csEndTrigger.triggerType = 0x0,
    .csEndTrigger.bEnaCmd = 0x0,
    .csEndTrigger.triggerNo = 0x0,
    .csEndTrigger.pastTrig = 0x0,
    .csEndTime = 0x00000000
};


