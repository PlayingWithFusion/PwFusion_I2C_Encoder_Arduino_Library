/***************************************************************************
* File Name: PwFusion_Encoder.h
* Processor/Platform: PwFusion R3aktor M0 (tested)
* Development Environment: Arduino 2.1.1
*
* Designed to simplify the integration of the PwFusion I2C Encoder board
* Device (IFB-40001)
*   ---> <Insert Link to product page>
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

#ifndef PwFusion_Encoder_h
#define PwFusion_Encoder_h

#include "Arduino.h"
//#include "DataTransfer.h"
#include <PwFusion_Data_Transfer.h>

class Encoder {
  private:
    uint8_t _adr;

    DataTransfer* transfer;

    uint8_t _reg_btnState                       = 0x00;
    uint8_t _reg_count                          = 0x01;
    uint8_t _reg_millisBetweenRotations         = 0x02;
    uint8_t _reg_rpm                            = 0x03;
    uint8_t _reg_direction                      = 0x04;
    int _numData = 5;

  public:
    Encoder(/*uint8_t adr*/);
    int getCount();
    int getBtnState();
    int getMillisBetweenRotations();
    int getRPM();
    int getDirection();
    void begin(uint8_t adr);

};

#endif