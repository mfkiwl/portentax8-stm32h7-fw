/* mbed Microcontroller Library
 * Copyright (c) 2006-2017 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "can.h"
#include "stm32h7xx_hal.h"
#include "stm32h7xx_ll_hsem.h"
#include "debug.h"
#include "system.h"
#include "opcodes.h"
#include "peripherals.h"
#include "error_handler.h"

/**************************************************************************************
 * DEFINE
 **************************************************************************************/

#define TARGET_STM32H7      1
#define CFG_HW_RCC_SEMID    3
#undef DUAL_CORE

/**************************************************************************************
 * GLOBAL VARIABLES
 **************************************************************************************/

FDCAN_HandleTypeDef fdcan_1;
FDCAN_HandleTypeDef fdcan_2;

static uint32_t HAL_RCC_FDCAN_CLK_ENABLED = 0;

/**************************************************************************************
 * FUNCTION DEFINITION
 **************************************************************************************/

void HAL_FDCAN_MspInit(FDCAN_HandleTypeDef *hfdcan)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_FDCAN_CLK_ENABLE();
  HAL_RCC_FDCAN_CLK_ENABLED++;

  if (hfdcan->Instance == FDCAN1)
  {
    __HAL_RCC_GPIOD_CLK_ENABLE();
    /*
     * FDCAN1 GPIO Configuration
     * PD1     ------> FDCAN1_TX
     * PD0     ------> FDCAN1_RX
     */
    GPIO_InitStruct.Pin = GPIO_PIN_1 | GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_FDCAN1;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(FDCAN1_IT0_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(FDCAN1_IT0_IRQn);
  }
  else if (hfdcan->Instance == FDCAN2)
  {
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /*
     * FDCAN2 GPIO Configuration
     * PB5     ------> FDCAN2_RX
     * PB6     ------> FDCAN2_TX
     */
    GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_FDCAN2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(FDCAN2_IT0_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(FDCAN2_IT0_IRQn);
  }
}

void HAL_FDCAN_MspDeInit(FDCAN_HandleTypeDef *hfdcan)
{
  HAL_RCC_FDCAN_CLK_ENABLED--;
  if (HAL_RCC_FDCAN_CLK_ENABLED == 0) {
    __HAL_RCC_FDCAN_CLK_DISABLE();
  }

  if (hfdcan->Instance == FDCAN1)
  {
    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_1 | GPIO_PIN_0);
    HAL_NVIC_DisableIRQ(FDCAN1_IT0_IRQn);
  }
  else if (hfdcan->Instance == FDCAN2)
  {
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_5 | GPIO_PIN_6);
    HAL_NVIC_DisableIRQ(FDCAN2_IT0_IRQn);
  }
}

int can_internal_init(FDCAN_HandleTypeDef * handle)
{
  if (HAL_FDCAN_Init(handle) != HAL_OK)
    Error_Handler("HAL_FDCAN_Init Error_Handler\n");

  if (can_filter(handle, 0, 0, 0, false) == 0)
    Error_Handler("can_filter Error_Handler\n");

  if (can_filter(handle, 0, 0, 0, true) == 0)
    Error_Handler("can_filter Error_Handler\n");

  if (HAL_FDCAN_ConfigGlobalFilter(handle, FDCAN_REJECT, FDCAN_REJECT, FDCAN_FILTER_REMOTE, FDCAN_FILTER_REMOTE) != HAL_OK)
    Error_Handler("HAL_FDCAN_ConfigGlobalFilter Error_Handler\n");

  if (HAL_FDCAN_Start(handle) != HAL_OK)
    Error_Handler("HAL_FDCAN_Start Error_Handler\n");

  return 1;
}

void can_init(FDCAN_HandleTypeDef * handle, CANName peripheral, uint32_t const baud_rate_prescaler, uint32_t const time_segment_1, uint32_t const time_segment_2, uint32_t const sync_jump_width)
{
    // Default values
    handle->Instance = (FDCAN_GlobalTypeDef *)peripheral;

    handle->Init.FrameFormat = FDCAN_FRAME_CLASSIC;
    handle->Init.Mode = FDCAN_MODE_NORMAL;
    handle->Init.AutoRetransmission = ENABLE;
    handle->Init.TransmitPause = DISABLE;
    handle->Init.ProtocolException = ENABLE;
    handle->Init.NominalPrescaler = baud_rate_prescaler;
    handle->Init.NominalTimeSeg1 = time_segment_1;
    handle->Init.NominalTimeSeg2 = time_segment_2;
    handle->Init.NominalSyncJumpWidth = sync_jump_width;
    handle->Init.DataPrescaler = 0x1;       // Not used - only in FDCAN
    handle->Init.DataSyncJumpWidth = 0x1;   // Not used - only in FDCAN
    handle->Init.DataTimeSeg1 = 0x1;        // Not used - only in FDCAN
    handle->Init.DataTimeSeg2 = 0x1;        // Not used - only in FDCAN

    /* Message RAM offset is only supported in STM32H7 platforms of supported FDCAN platforms */
    handle->Init.MessageRAMOffset = 0;

    /* The number of Standard and Extended ID filters are initialized to the maximum possible extent
     * for STM32H7 platforms
     */
    handle->Init.StdFiltersNbr = 128; // to be aligned with the handle parameter in can_filter
    handle->Init.ExtFiltersNbr = 64; // to be aligned with the handle parameter in can_filter

    handle->Init.RxFifo0ElmtsNbr = 64;
    handle->Init.RxFifo0ElmtSize = FDCAN_DATA_BYTES_8;
    handle->Init.RxFifo1ElmtsNbr =  0;
    handle->Init.RxFifo1ElmtSize = FDCAN_DATA_BYTES_8;
    handle->Init.RxBuffersNbr    =  0;
    handle->Init.RxBufferSize    = FDCAN_DATA_BYTES_8;

    handle->Init.TxEventsNbr         = 32;
    handle->Init.TxBuffersNbr        =  0;
    handle->Init.TxFifoQueueElmtsNbr = 32;
    handle->Init.TxFifoQueueMode     = FDCAN_TX_FIFO_OPERATION;
    handle->Init.TxElmtSize          = FDCAN_DATA_BYTES_8;

    can_internal_init(handle);
}

void can_deinit(FDCAN_HandleTypeDef * handle)
{
  HAL_FDCAN_Stop(handle);
  HAL_FDCAN_DeInit(handle);
}

int can_set_bittiming(FDCAN_HandleTypeDef * handle, uint32_t const baud_rate_prescaler, uint32_t const time_segment_1, uint32_t const time_segment_2, uint32_t const sync_jump_width)
{
  if (HAL_FDCAN_Stop(handle) != HAL_OK)
    Error_Handler("HAL_FDCAN_Stop Error_Handler\n");

  handle->Init.NominalPrescaler     = baud_rate_prescaler;
  handle->Init.NominalTimeSeg1      = time_segment_1;
  handle->Init.NominalTimeSeg2      = time_segment_2;
  handle->Init.NominalSyncJumpWidth = sync_jump_width;

  return can_internal_init(handle);
}

int can_filter(FDCAN_HandleTypeDef * handle, uint32_t const filter_index, uint32_t const id, uint32_t const mask, bool const is_extended_id)
{
  FDCAN_FilterTypeDef sFilterConfig = {0};

  sFilterConfig.IdType = is_extended_id ? FDCAN_EXTENDED_ID : FDCAN_STANDARD_ID;
  sFilterConfig.FilterIndex = filter_index;
  sFilterConfig.FilterType = FDCAN_FILTER_MASK;
  sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
  sFilterConfig.FilterID1 = is_extended_id ? (id & CAN_EFF_MASK) : (id & CAN_SFF_MASK);
  sFilterConfig.FilterID2 = is_extended_id ? (mask & CAN_EFF_MASK) : (mask & CAN_SFF_MASK);

  if (HAL_FDCAN_ConfigFilter(handle, &sFilterConfig) != HAL_OK) {
    return 0;
  }

  return 1;
}

uint32_t can_tx_fifo_available(FDCAN_HandleTypeDef * handle)
{
  return HAL_FDCAN_GetTxFifoFreeLevel(handle);
}

int can_write(FDCAN_HandleTypeDef * handle, uint32_t const id, uint8_t const len, uint8_t const * data)
{
  FDCAN_TxHeaderTypeDef TxHeader = {0};

  if (id & CAN_EFF_FLAG)
  {
    TxHeader.IdType     = FDCAN_EXTENDED_ID;
    TxHeader.Identifier = id & CAN_EFF_MASK;
  }
  else
  {
    TxHeader.IdType     = FDCAN_STANDARD_ID;
    TxHeader.Identifier = id & CAN_SFF_MASK;
  }

    TxHeader.TxFrameType = FDCAN_DATA_FRAME;
    switch (len)
    {
      default:
      case 0:  TxHeader.DataLength = FDCAN_DLC_BYTES_0;  break;
      case 1:  TxHeader.DataLength = FDCAN_DLC_BYTES_1;  break;
      case 2:  TxHeader.DataLength = FDCAN_DLC_BYTES_2;  break;
      case 3:  TxHeader.DataLength = FDCAN_DLC_BYTES_3;  break;
      case 4:  TxHeader.DataLength = FDCAN_DLC_BYTES_4;  break;
      case 5:  TxHeader.DataLength = FDCAN_DLC_BYTES_5;  break;
      case 6:  TxHeader.DataLength = FDCAN_DLC_BYTES_6;  break;
      case 7:  TxHeader.DataLength = FDCAN_DLC_BYTES_7;  break;
      case 8:  TxHeader.DataLength = FDCAN_DLC_BYTES_8;  break;
      case 12: TxHeader.DataLength = FDCAN_DLC_BYTES_12; break;
      case 16: TxHeader.DataLength = FDCAN_DLC_BYTES_16; break;
      case 20: TxHeader.DataLength = FDCAN_DLC_BYTES_20; break;
      case 24: TxHeader.DataLength = FDCAN_DLC_BYTES_24; break;
      case 32: TxHeader.DataLength = FDCAN_DLC_BYTES_32; break;
      case 48: TxHeader.DataLength = FDCAN_DLC_BYTES_48; break;
      case 64: TxHeader.DataLength = FDCAN_DLC_BYTES_64; break;
    }
    TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
    TxHeader.BitRateSwitch = FDCAN_BRS_OFF;
    TxHeader.FDFormat = FDCAN_CLASSIC_CAN;
    TxHeader.TxEventFifoControl = FDCAN_STORE_TX_EVENTS;
    TxHeader.MessageMarker = 0;

    if (HAL_FDCAN_AddMessageToTxFifoQ(handle, &TxHeader, (uint8_t *)data) != HAL_OK)
    {
      uint32_t const err_code = HAL_FDCAN_GetError(handle);
      printf("HAL_FDCAN_AddMessageToTxFifoQ failed with %ld\n", err_code);
      return -err_code;
    }
    return 0;
}

int can_read(FDCAN_HandleTypeDef * handle, uint32_t * id, uint8_t * len, uint8_t * data)
{
  static const uint8_t DLCtoBytes[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64};

  if (HAL_FDCAN_GetRxFifoFillLevel(handle, FDCAN_RX_FIFO0) == 0)
    return 0; // No message arrived

  FDCAN_RxHeaderTypeDef RxHeader = {0};
  uint8_t RxData[64] = {0};
  if (HAL_FDCAN_GetRxMessage(handle, FDCAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
  {
    Error_Handler("HAL_FDCAN_GetRxMessage Error_Handler\n"); // Should not occur as previous HAL_FDCAN_GetRxFifoFillLevel call reported some data
    return 0;
  }

  if (RxHeader.IdType == FDCAN_EXTENDED_ID)
    *id = CAN_EFF_FLAG | (RxHeader.Identifier & CAN_EFF_MASK);
  else
    *id =                (RxHeader.Identifier & CAN_SFF_MASK);

  if (RxHeader.RxFrameType == FDCAN_REMOTE_FRAME)
    *id |= CAN_RTR_FLAG;

  *len = DLCtoBytes[RxHeader.DataLength >> 16];
  if (*len > X8H7_CAN_FRAME_MAX_DATA_LEN)
    *len = X8H7_CAN_FRAME_MAX_DATA_LEN;

  memcpy(data, RxData, *len);

  return 1;
}

unsigned char can_rdError_Handler(FDCAN_HandleTypeDef * handle)
{
  FDCAN_ErrorCountersTypeDef ErrorCounters;
  HAL_FDCAN_GetErrorCounters(handle, &ErrorCounters);
  return (unsigned char)ErrorCounters.RxErrorCnt;
}

unsigned char can_tdError_Handler(FDCAN_HandleTypeDef * handle)
{
  FDCAN_ErrorCountersTypeDef ErrorCounters;
  HAL_FDCAN_GetErrorCounters(handle, &ErrorCounters);
  return (unsigned char)ErrorCounters.TxErrorCnt;
}
