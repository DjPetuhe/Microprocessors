#include "Terminals.h"
#include "App.h"

extern "C" void USART2_IRQHandler()
{
    App::instance()->onCharRecieve(USART2->DR);
    USART2->SR &= ~USART_SR_RXNE;
}

void Terminals::setup()
{
    //USART for printing ADC 
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    USART1->BRR = 8000000 / 9600;
    USART1->CR1 |= USART_CR1_TE | USART_CR1_UE;

    //USART for writing commands
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    USART2->BRR = 8000000 / 9600;
    USART2->CR1 |= USART_CR1_RE | USART_CR1_UE | USART_CR1_RXNEIE;
    NVIC_EnableIRQ(USART2_IRQn);
}

bool Terminals::hasNewCommand()
{
    return m_receiveCmd;
}

std::string Terminals::newCommand()
{
    m_receiveCmd = false;
    return m_cmd;
}

void Terminals::receiveChar(char s)
{
    if (s == '\r')
    {
        m_cmd = m_tempCmd;
        m_receiveCmd = true;
        m_tempCmd = "";
    }
    else
    {
        m_tempCmd.push_back(s);
    }
}

void Terminals::sendMsg(std::string msg)
{
    for (char c : msg)
    {
        while (!(USART1->SR & USART_SR_TXE)) {}
        USART1->DR = c;
    }
}