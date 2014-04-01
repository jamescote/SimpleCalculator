#ifndef _CALCULATOR_H
#define _CALCULATOR_H

// Name: Calculator.h
// Description: Calculator class that performs different functions 
// Written By: James Coté
//////////////////////////////////////////////////////////////////////

/////////////
// Defines //
/////////////
#define MAXIMUM_OPERATIONS 4

////////////////////////////
// Calculator Declaration //
////////////////////////////
class Calculator
{
public:
	Calculator(void);
	~Calculator(void);

	// public use functions
	void process_Calculation( char cOperator, double dValue );
	bool isValidOperand( char cOperand );

	// Getters and setters
	const char* get_Available_Ops( );
	void store_Mem( );
	double pull_Mem( );
	void clear_Value( );
	double read_Value( );

private:
	double m_dMemory;
	double m_dValue;
	static const char m_sAvailableOps[ MAXIMUM_OPERATIONS ];

};

#endif