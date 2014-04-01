//////////////
// Includes //
//////////////
#include "Calculator.h"

// Constant, uneditable array of available operations that can
// be done by this calculator.
const char Calculator::m_sAvailableOps[ MAXIMUM_OPERATIONS ] = { '+','-','*','/' };

/*********************************************************************\
 *	Constructor/Desctructor											 *
\*********************************************************************/

// Main Constructor for Calculator Objects
Calculator::Calculator(void)
{
	m_dValue = 0.0f;
	m_dMemory = 0.0f;
}


// Main Destructor for Calculator Objects
Calculator::~Calculator(void)
{
	// Empty
}

/*********************************************************************\
 *	Public Use Functions											 *
\*********************************************************************/

// Takes in an operator and 2 values and returns the calculation.
//	Parameters:
//		cOperator : Char - The User-selected operation to perform
//		dValue : Double - The User-selected value to operate with on
//						  the calculator's internal value.
//////////////////////////////////////////////////////////////////////
void Calculator::process_Calculation( char cOperator, double dValue )
{
	switch( cOperator )
	{
	case '+':	
		m_dValue += dValue;
		break;
	case '-':
		m_dValue -= dValue;
		break;
	case '*':
		m_dValue *= dValue;
		break;
	case '/':
		m_dValue /= dValue;
		break;
	default:
		break;
	};
}

// Runs through the list of available operands to determine
// if the passed in operand is valid.
//	Returns
//		true if the operand is valid.
///////////////////////////////////////////////////////////////////////
bool Calculator::isValidOperand( char cOperand )
{
	bool bValid = false;

	for( int i = 0; i < MAXIMUM_OPERATIONS; ++i )
		bValid |= m_sAvailableOps[ i ] == cOperand;

	return bValid;
}

/*********************************************************************\
 *	Getters and Setters  											 *
\*********************************************************************/

// Stores a value into the calculator's internal "memory"
void Calculator::store_Mem( )
{
	m_dMemory = m_dValue;
}

// Grabs the value from the calculator's internal "memory"
double Calculator::pull_Mem( )
{
	return m_dMemory;
}

// Reads the current value being displayed on the calculator
double Calculator::read_Value( )
{
	return m_dValue;
}

// Clears the current working value of the calculator
void Calculator::clear_Value( )
{
	m_dValue = 0.0f;
}

// Returns the list of available operands.
const char* Calculator::get_Available_Ops( )
{
	return m_sAvailableOps;
}
