#include "W7500x.h"

/** @defgroup I2C_Private_Functions
  * @{
  */

GPIO_InitTypeDef GPIO_InitDef;
void i2c_loop_us(int us);

#define SCL GPIO_Pin_9
#define SDA GPIO_Pin_10
uint16_t buf[] ={0x00,0x01};

/**
  * @brief  Initializes the I2Cx peripheral according to the specified 
  *   parameters in the I2C_InitStruct.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  I2C_InitStruct: pointer to a I2C_InitTypeDef structure that
  *   contains the configuration information for the specified I2C peripheral.
  * @retval None
  */

uint32_t I2C_Init(I2C_TypeDef* I2Cx, I2C_ConfigStruct conf)
{
    uint32_t mode;
    uint8_t  prescale;
    uint16_t timeout;
    uint16_t slave_address;
    
    
    mode = conf.mode;
    slave_address = conf.slave_address;
    if(mode == I2C_Master)
    {
        prescale = conf.master.prescale;
        timeout = conf.master.timeout;

        I2C_CoreEn(I2Cx,ENABLE);
        I2C_MasterSlave(I2Cx,ENABLE);
    
        I2C_Prescale(I2Cx,prescale);           // 0x61         //When PLL clk is 20MHz and Prescale value set 0x61, SCL is 100KHz
      	I2C_TimeoutSet(I2Cx,timeout);          // 0xFFFF        
  	 
        I2C_CoreEn(I2Cx,DISABLE);
    }
    else if(conf.mode == I2C_Slave)
    {
        I2C_AcknowledgeConfig(I2Cx,ENABLE);
        I2C_SetSlavAddress(I2Cx,slave_address);
    }
    else
        return ERROR; 


    I2C_AcknowledgeConfig(I2Cx,ENABLE);

    return SUCCESS;
}


void I2C_DeInit(I2C_TypeDef* I2Cx)
{
    I2C_InterRst(I2Cx,ENABLE);
    I2C_CoreEn(I2Cx, ENABLE);
    I2C_InterRst(I2Cx,DISABLE);
    I2C_CoreEn(I2Cx, DISABLE);
}


ErrorStatus I2C_Start(I2C_TypeDef* I2Cx, uint16_t slave_address, I2C_CTR ctr)
{
    ErrorStatus ret;
          
    I2C_GenerateSTART(I2Cx,ENABLE);
    I2C_SendSlaveAddress(I2Cx,slave_address,(I2C_CTR)ctr);
    I2C_GenerateSTART(I2Cx,DISABLE);
  
    ret=I2C_CheckEvent(I2Cx,I2C_ACKR);

    return ret;
}

void I2C_Stop(I2C_TypeDef* I2Cx)
{
    I2C_GenerateSTOP(I2Cx,ENABLE);
    I2C_GenerateSTOP(I2Cx,DISABLE);
    GPIO_InitDef.GPIO_Pin = GPIO_Pin_9; // Set to Pin_9 (SCL0))
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT; // Set to Mode Output
    HAL_GPIO_Init(GPIOA, &GPIO_InitDef);
    HAL_PAD_AFConfig(PAD_PA,GPIO_Pin_9, PAD_AF0); // PAD Config - LED used 2nd Function
}

void I2C_Reset(I2C_TypeDef* I2Cx)
{
    I2C_CoreEn(I2Cx,ENABLE);
    // Maybe, it needs a little delay
    I2C_CoreEn(I2Cx,DISABLE);
}

void I2C_SendData(I2C_TypeDef* I2Cx,uint16_t Data)
{
    I2Cx -> TXR = (uint16_t)Data;
}

int8_t I2C_SendDataAck(I2C_TypeDef* I2Cx,uint16_t Data)
{
    buf[0] = Data;
    if(buf[0] == buf[1])
    {
        I2C_GPIO();
        WriteByte(Data);     
        i2c_loop_us(1);
        GPIO_I2C();
    }
    else
    {
        I2Cx -> TXR = (uint16_t)Data;
        if(I2C_CheckEvent(I2Cx,I2C_ACKR) == ERROR)
        {
            return ERROR;
        }           
    }
    buf[1] = buf[0];
    return SUCCESS;
}

int I2C_ReceiveData(I2C_TypeDef* I2Cx, int last)    
{
    if(last)
    {   
        I2C_AcknowledgeConfig(I2Cx,DISABLE);
        if( I2C_CheckEvent(I2Cx,I2C_ACKT) == ERROR ) {
            return -1; 
        }
    }
    else if( I2C_CheckEvent(I2Cx,I2C_ACKT) == ERROR ) {
            return -1;    
    }
     
    return (uint8_t)I2Cx -> RXR;    
}


int I2C_Burst_Read(I2C_TypeDef* I2Cx, uint16_t address, uint8_t *data, int length, int stop)
{
    int recv_cnt;

    if( I2C_Start(I2Cx,address,I2C_READ_SA7) == ERROR){
        return -1;
    }

    for(recv_cnt=0;recv_cnt<length;recv_cnt++)
    {
    }

    return recv_cnt;
}


int I2C_Burst_Write(I2C_TypeDef* I2Cx, uint16_t address, uint8_t *data, int length, int stop)
{
    int cnt;

    if( I2C_Start(I2Cx,address,I2C_WRITE_SA7) == ERROR)
    {
        return -1;
    }

    for(cnt=0;cnt<length;cnt++)
    {
        if( I2C_SendDataAck(I2Cx,data[cnt]) == ERROR )
        {
            I2C_Stop(I2Cx);
            return -1;
        }
    }

    // If not repeated start, send stop
    if(stop)
    {
        I2C_Stop(I2Cx);
    }

    return length;
}


/**
  * @brief  Generates I2Cx communication START condition.
  * @param  I2Cx: where x can be 0 or 1 to select the I2C peripheral.
  * @param  NewState: NewState of the I2C START condition generation.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_GenerateSTART(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
    if(NewState != DISABLE)     
    {    
        I2Cx->CMDR = I2C_CMDR_STA;  
    }
    else                        
    {
        I2Cx->CMDR = I2C_CMDR_STA;
    }
 }
/**
  * @brief  Generates I2Cx communication STOP condition.
  * @param  I2Cx: where x can be 0 or 1 to select the I2C peripheral.
  * @param  NewState: NewState of the I2C STOP condition generation.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_GenerateSTOP(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
    if(NewState != DISABLE)     
    {   

        I2Cx->CMDR = I2C_CMDR_STO;

    }
    else               
    {
        I2Cx->CMDR = I2C_CMDR_STO;
    }
}

/**
  * @brief  Enables or disables the specified I2C acknowledge feature.
  * @param  I2Cx: where x can be 0 or 1 to select the I2C peripheral.
  * @param  NewState: NewState of the I2C Acknowledgement.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
    if(NewState != DISABLE)             I2Cx -> CMDR = I2C_CMDR_ACK;
    else                                I2Cx -> CMDR = I2C_CMDR_ACK;
}

/**
  * @brief  Generates I2Cx communication REGenerateSTART condition
  * @param  I2Cx: where x can be 0 or 1 to select the I2C peripheral.
  * @param  NewState: NewState of the I2C Acknowledgement.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_RESTART(I2C_TypeDef * I2Cx, FunctionalState NewState)
{
    if(NewState != DISABLE)              I2Cx->CMDR = I2C_CMDR_RESTA;
    else                                 I2Cx->CMDR = I2C_CMDR_RESTA;
}

/**
  * @brief  Enable or disable the specified I2C Core_en feature
  * @param  I2Cx: where x can be 0 or 1 to select the I2C peripheral.
  * @param  NewState: NewState of the I2C Acknowledgement.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_CoreEn(I2C_TypeDef* I2Cx,FunctionalState NewState)
{
    /*Control*/
   if(NewState != DISABLE)              I2Cx -> CTR = I2C_CTR_COREEN;
   else                                 I2Cx -> CTR = I2C_CTR_COREEN;
}


void I2C_InterEn(I2C_TypeDef* I2Cx,FunctionalState NewState)
{
    /*Control Interrupt Enable*/
    if(NewState != DISABLE)             I2Cx -> CTR = I2C_CTR_INTEREN;
    else                                I2Cx -> CTR = I2C_CTR_INTEREN;
}


void I2C_MasterSlave(I2C_TypeDef* I2Cx,FunctionalState NewState)
{
    /*Control MasterSlave select*/
    if(NewState == ENABLE)
    {
        if( (I2Cx->CTR & I2C_CTR_MODE) != I2C_CTR_MODE )
        {
            I2Cx->CTR = I2C_CTR_MODE;
        }
    }
    else    // DISABLE
    {
        if( (I2Cx->CTR & I2C_CTR_MODE) == I2C_CTR_MODE )
        {
            I2Cx->CTR = I2C_CTR_MODE;
        }
    }
}


void I2C_ControlRW(I2C_TypeDef* I2Cx,FunctionalState NewState)
{
    /*Control Read(receive)*/
    if(NewState == ENABLE)
    {
        if( (I2Cx->CTR & I2C_CTR_CTRRWN) != I2C_CTR_CTRRWN )
        {
            I2Cx->CTR = I2C_CTR_CTRRWN;
        }
    }
    else    // DISABLE
    {
        if( (I2Cx->CTR & I2C_CTR_CTRRWN) == I2C_CTR_CTRRWN )
        {
            I2Cx->CTR = I2C_CTR_CTRRWN;
        }
    }
}


void I2C_ControlEn(I2C_TypeDef* I2Cx,FunctionalState NewState)
{
    /*Control*/
    if(NewState == ENABLE)
    {
        if( (I2Cx->CTR & I2C_CTR_CTEN) != I2C_CTR_CTEN )
        {
            I2Cx->CTR = I2C_CTR_CTEN;
        }
    }
    else    // DISABLE
    {
        if( (I2Cx->CTR & I2C_CTR_CTEN) == I2C_CTR_CTEN )
        {
            I2Cx->CTR = I2C_CTR_CTEN;
        }
    }
}


void I2C_InterRst(I2C_TypeDef* I2Cx,FunctionalState NewState)
{
     /*Control*/
    if(NewState == ENABLE)
    {
        if( (I2Cx->ISCR & I2C_ISCR_RST) != I2C_ISCR_RST )
        {
            I2Cx->ISCR = I2C_ISCR_RST;
        }
    }
    else    // DISABLE
    {
        if( (I2Cx->ISCR & I2C_ISCR_RST) == I2C_ISCR_RST )
        {
            I2Cx->ISCR = I2C_ISCR_RST;
        }
    }
}

void I2C_Prescale(I2C_TypeDef* I2Cx,uint16_t Data)
{
    I2Cx -> PRER = (uint16_t)Data;
}

void I2C_TimeoutSet(I2C_TypeDef* I2Cx,uint16_t Data)
{
    I2Cx -> TSR = (uint16_t)Data;
}
void I2C_SetSlavAddress(I2C_TypeDef* I2Cx,uint16_t Data)
{
    I2Cx -> SADDR = (uint16_t)Data;
}


uint8_t I2C_StatusRead(I2C_TypeDef* I2Cx)
{
    return (uint8_t)I2Cx -> SR;
}


ErrorStatus WaitEvent(I2C_TypeDef* I2Cx, uint32_t flag, FlagStatus status)
{
    int Timeout=0,loopcnt=0;
    
    Timeout = I2Cx->TSR;
    if(status == SET)
    {
        for(loopcnt=Timeout; loopcnt>0; loopcnt--)
        {
            if( ((I2Cx->SR) & flag) == flag )
                return SUCCESS;
        }
    }
    else
    {
        for(loopcnt=Timeout; loopcnt>0; loopcnt--)
        {
            if( ((I2Cx->SR) & flag) != flag )
                return SUCCESS;
        }
    }


    return ERROR;
}


/**
 *  @brief Checks whether the specified I2C flag is set or not.
 *  @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
 *  @param  I2C_EVENT: specifies the event to be checked. 
 */
ErrorStatus I2C_CheckEvent(I2C_TypeDef* I2Cx,I2C_SR sr)
{
    switch(sr)
    {
        case(I2C_ACKR):
            if( WaitEvent(I2Cx, I2C_SR_ACKR, SET)   == ERROR)   return ERROR;
            if( WaitEvent(I2Cx, I2C_SR_ACKR, RESET) == ERROR)   return ERROR;            
            break;

        case(I2C_ACKT ):
            if( WaitEvent(I2Cx, I2C_SR_ACKT, SET)   == ERROR)   return ERROR;
            if( WaitEvent(I2Cx, I2C_SR_ACKT, RESET) == ERROR)   return ERROR;
            break;
  
        case(I2C_OACKR):
            if( WaitEvent(I2Cx, I2C_SR_ACKR, SET)   == ERROR)   return ERROR;
            break;
  
        case(I2C_SACKR  ):
            if( WaitEvent(I2Cx, I2C_SR_ACKR, RESET) == ERROR)   return ERROR;
            break;
 
        case(I2C_BT  ):
            if( WaitEvent(I2Cx, I2C_SR_BT, RESET) == ERROR)     return ERROR;
            break; 
     
        default:
            return ERROR;
        }

    return SUCCESS;
}


void I2C_SendSlaveAddress(I2C_TypeDef* I2Cx, uint8_t SlaveAddress,I2C_CTR Ctr)
{
    switch(Ctr)
    {
        case(I2C_READ_SA7):
             I2C_SendData(I2Cx,SlaveAddress|I2C_READ);
        break;
        
        
        case(I2C_WRITE_SA7):
            I2C_SendData(I2Cx,SlaveAddress|I2C_WRITE);
        break;
 
        case(I2C_CTRWRITE_SA7):
        case(I2C_CTRREAD_SA7):
             I2C_SendData(I2Cx,SlaveAddress);
        break;
        
        default:
            return;
        
    }
}

 int8_t I2C_Restart_Structure(I2C_TypeDef * I2Cx,uint32_t SlaveAddress,I2C_CTR Ctr)
{

    I2C_RESTART(I2Cx,ENABLE);
    I2C_SendSlaveAddress(I2Cx,SlaveAddress,Ctr);
    if((I2C_CheckEvent(I2Cx,I2C_OACKR)) == ERROR )
    {
        return 0;
    }
    I2C_RESTART(I2Cx,DISABLE);
    if((I2C_CheckEvent(I2Cx,I2C_SACKR)) == ERROR)
    {
        return 0;
    }
    return 1;
}
    
/**
  * @brief  Reads the specified I2C register and returns its value.
  * @param  I2C_Register: specifies the register to read.
  *   This parameter can be one of the following values:
  *     @arg I2C_Register_CR1:  CR1 register.
  *     @arg I2C_Register_CR2:   CR2 register.
  *     @arg I2C_Register_OAR1:  OAR1 register.
  *     @arg I2C_Register_OAR2:  OAR2 register.
  *     @arg I2C_Register_DR:    DR register.
  *     @arg I2C_Register_SR1:   SR1 register.
  *     @arg I2C_Register_SR2:   SR2 register.
  *     @arg I2C_Register_CCR:   CCR register.
  *     @arg I2C_Register_TRISE: TRISE register.
  * @retval The value of the read register.
  */
uint16_t I2C_ReadRegister(I2C_TypeDef* I2Cx, uint8_t I2C_Register)
{
  __IO uint32_t tmp = 0;

  
  tmp = (uint32_t) I2Cx;
  tmp += I2C_Register;

  /* Return the selected register value */
  return (*(__IO uint16_t *) tmp);
}

    
void I2C_GPIO(void )
{
        GPIO_InitDef.GPIO_Pin = GPIO_Pin_9; // Set to Pin_9 (SCL0))
        GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT; // Set to Mode Output
        HAL_GPIO_Init(GPIOA, &GPIO_InitDef);
        HAL_PAD_AFConfig(PAD_PA,GPIO_Pin_9, PAD_AF1); // PAD Config - LED used 2nd Function
        
        GPIO_InitDef.GPIO_Pin = GPIO_Pin_10; // Set to Pin_9 (SCL0))
        GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT; // Set to Mode Output
        HAL_GPIO_Init(GPIOA, &GPIO_InitDef);
        HAL_PAD_AFConfig(PAD_PA,GPIO_Pin_10, PAD_AF1); // PAD Config - LED used 2nd Function
 
}
void GPIO_I2C(void )
{
       GPIO_InitDef.GPIO_Pin = GPIO_Pin_9; // Set to Pin_9 (SCL0))
       GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT; // Set to Mode Output
       HAL_GPIO_Init(GPIOA, &GPIO_InitDef);
       HAL_PAD_AFConfig(PAD_PA,GPIO_Pin_9, PAD_AF0); // PAD Config - LED used 2nd Function
        
       GPIO_InitDef.GPIO_Pin = GPIO_Pin_10; // Set to Pin_10 (SDA0))
       GPIO_InitDef.GPIO_Mode = GPIO_Mode_IN; // Set to Mode Output
       HAL_GPIO_Init(GPIOA, &GPIO_InitDef);
       HAL_PAD_AFConfig(PAD_PA,GPIO_Pin_10, PAD_AF0); // PAD Config - LED used 2nd Functio

}


void WriteByte(uint8_t val)
{
    int  i;
    GPIO_TypeDef* GPIOx;
    GPIOx = GPIOA;

	for(i=0;i<8;i++)
	{
		if((val << i) & 0x80){
			digitalWrite(GPIOx,SDA, Bit_SET);
		}else{
			digitalWrite(GPIOx,SDA, Bit_RESET);
		}
        i2c_loop_us(1);
		digitalWrite(GPIOx,SCL, Bit_SET);
        i2c_loop_us(2);
		digitalWrite(GPIOx,SCL, Bit_RESET);
	}
	digitalWrite(GPIOx,SDA, Bit_SET);
    i2c_loop_us(1);
	digitalWrite(GPIOx,SCL, Bit_SET);
	i2c_loop_us(2);
    digitalWrite(GPIOx,SCL, Bit_RESET);
}


void digitalWrite(GPIO_TypeDef* GPIOx,uint16_t pin, uint16_t val)
{
    
    if(val == Bit_SET)
    {
        GPIOx -> OUTENCLR = pin;
    }
    else
    {
        GPIOx -> OUTENSET |= pin;
        
    }
}


void i2c_loop_us(int us)
{
    volatile uint32_t delay = us; // approximate loops per ms at 24 MHz, Debug config
    for(; delay != 0; delay--)
        __NOP();
}
void i2c_loop_ms(int count) {
    i2c_loop_us(count*1000);
}

