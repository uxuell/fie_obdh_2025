/*
 * emu_tc_programming.cpp
 *
 *  Created on: Jan 13, 2017
 *
 *  Created on: Oct 26, 2024
 *      Author: Oscar Rodriguez Polo
 */

/****************************************************************************
 *
 *   This program is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU General Public License
 *   as published by the Free Software Foundation; either version 2
 *   of the License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,USA.
 *
 *
 ****************************************************************************/

#include <public/emu_hw_timecode_drv_v1.h>
#include <public/emu_sc_channel_drv_v1.h>
#include <public/emu_gss_v1.h>

#define FT_UAH_ASW_ICU_SERV_20_PARAM_10_ACCESS_0070

#define FT_UAH_ASW_ICU_SERV_20_ERROR_WRITE_PID_0080


#ifdef FT_UAH_ASW_ICU_SERV_20_PARAM_10_ACCESS_0070

//DONE 07
// Use EmuGSS_TCProgram20_3_uint8 to Set PID 20 value to 99 (0x63)
EmuGSS_TCProgram20_3_uint8  prog_FT_0070_step_0(OBT_AFTER_POWER_ON +1,
"FT_UAH_ASW_ICU_SERV_20_3_0040 step 0, Set PID 20 Value to 99",20,99);

//use EmuGSS_TCProgram20_1 to read PID 20
EmuGSS_TCProgram20_1 prog_FT_0070_step_1(OBT_AFTER_POWER_ON +1,
"FT_SOLO_EPD_ICU_SERV_20_0080_Step0, Report PID 20 Value ", 20 );

#endif

#ifdef FT_UAH_ASW_ICU_SERV_20_ERROR_WRITE_PID_0080

//DONE 08
//Use EmuGSS_TCProgram20_3_uint32 to write PID 10 to 55 (0x37)
EmuGSS_TCProgram20_3_uint32 prog_FT_0080_step_0(OBT_AFTER_POWER_ON +3,
"FT_SOLO_ASW_SERV_20_0080_Step0, Set PID 10 Value to 55",10,55);

//Use EmuGSS_TCProgram20_1 to read PID 10
EmuGSS_TCProgram20_1 prog_FT_0080_step_1(OBT_AFTER_POWER_ON +2,
"FT_SOLO_EPD_ICU_SERV_20_0080_Step0, Report PID 10 Value ", 10);

//Use EmuGSS_TCProgram20_3_uint32 to write the value 33 to a read only PID 3
//Check TM[1.4] is received
EmuGSS_TCProgram20_3_uint32 prog_FT_0080_step_2(OBT_AFTER_POWER_ON +3,
"FT_SOLO_ASW_SERV_20_0080_Step0, Set PID 10 Value to 55",3,33);

#endif
