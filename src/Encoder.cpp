/***************************************************************************
* File Name: Encoder.cpp
* Processor/Platform: PwFusion R3aktor M0 (tested)
* Development Environment: Arduino 2.1.1
*
* Designed to simplify the integration of the PwFusion I2C Encoder board
* Device (IFB-40001)
*   ---> <Insert Link>
*
* Copyright � 2023 Playing With Fusion, Inc.
* SOFTWARE LICENSE AGREEMENT: This code is released under the MIT License.
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
* **************************************************************************
* REVISION HISTORY:
* Author		    Date		    Comments
* N. Johnson    2023Aug29   Original version
*
* Playing With Fusion, Inc. invests time and resources developing open-source
* code. Please support Playing With Fusion and continued open-source
* development by buying products from Playing With Fusion!
***************************************************************************/

#include "Arduino.h"
#include "Encoder.h"
#include "DataTransfer.h"

Encoder::Encoder(uint8_t adr) {
  _adr = adr;
  transfer = new DataTransfer(_adr, _numData);
}

int Encoder::getCount() {
  return transfer->getData(_reg_count);
}

int Encoder::getBtnState() {
  return transfer->getData(_reg_btnState);
}

int Encoder::getMillisBetweenRotations() {
  return transfer->getData(_reg_millisBetweenRotations);
}

int Encoder::getRPM() {
  return transfer->getData(_reg_rpm);
}

int Encoder::getDirection() {
  return transfer->getData(_reg_direction);
}