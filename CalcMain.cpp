// Name: CalcMain.cpp
// Description: Main driver for calculator program
// Written by: James Coté
//////////////////////////////////////////////////////////////////////////////

//////////////
// Includes //
//////////////
#include "Calculator/Calculator.h"
#include "IO/ioutil.h"
#include <cstring>
#include <iostream>

////////////////
// Namespaces //
////////////////

using namespace std;

/////////////
// Defines //
/////////////
#define MAX_STR_INPUT 20
#define MIN_STR_INPUT 3
#define MEM_TRIGGER "mem"
#define MEM_CHECK_SIZE 4
#define POSSIBLE_INPUT_COUNT 8

///////////////////////////
// Function Declarations //
///////////////////////////
bool process_Calculation( const char sInput[], 
						  char& cOperand, double& dValue, 
						  Calculator* const m_Calculator );
bool run_menu( Calculator* const m_Calculator );
bool parse_Calculation( Calculator* const m_Calculator );



//////////
// Main //
//////////
int main( )
{
	Calculator m_Calculator = Calculator( );
	bool bFinished			= false;

	while( !bFinished )
		bFinished = run_menu( &m_Calculator );

	return 0;
}

// runs a menu for the user, returns the result
// to the caller
//	Returns:
//		Returns a boolean value to tell the caller if the user has
//		ended the program or not.
/////////////////////////////////////////////////////////////////////
bool run_menu( Calculator* const m_Calculator )
{
	bool bFinished = false;
	char cSelection = ' ';

	cout << "Calculator Menu: \n"
		 << "Current Working Value:\t" << m_Calculator->read_Value( ) << "\n"
		 << "\nPlease select an option:\n"
		 << "\tc). Perform Calculation.\n"
		 << "\ts). Store Current Working Value.\n" 
		 << "\tr). Reset Current Working Value.\n"
		 << "\tq). Quit Program.\n\n";

	cSelection = readChar( "Enter a Value: ", bFinished, POSSIBLE_INPUT_COUNT, 'c','C','s','S','r','R','q','Q' );

	switch( cSelection )
	{
	case 'C':
	case 'c':
		bFinished = parse_Calculation( m_Calculator );
		break;
	case 'S':
	case 's':
		m_Calculator->store_Mem( );
		break;
	case 'R':
	case 'r':
		m_Calculator->clear_Value( );
		break;
	case 'Q':
	case 'q':
	default:
		bFinished = true;
		break;
	}

	return bFinished;
}

// Prompts the user for a string input for calculation,
//	parses the input and performs the calculation.
//
//	Parameters:
//		m_Calculator : Calculator - Calculator object for
//			referencing operands and calling the process_calculation function.
//	Returns:
//		Returns whether an end of file was hit or not after prompting the user.
//////////////////////////////////////////////////////////////////////////////////
bool parse_Calculation( Calculator* const m_Calculator )
{
	char sInputString[ MAX_STR_INPUT ] = { '\0' };
	const char* cpAvailableOperations = m_Calculator->get_Available_Ops( );
	bool bFinished = false;
	bool bValid = true;
	char cOperand = 0;
	double dValue = 0.0;

	cout << "\n\nSyntax: (operator) (value*)\n"
		 << "Available Operations:\n";

	for( int i = 0; i < MAXIMUM_OPERATIONS; ++i )
		cout << "\t" << cpAvailableOperations[ i ] << "\n";

	cout << "*Value can be \"mem\" to use the stored value in memory.\n";

	readString( "Please enter a calculation: ",
				sInputString,
				MAX_STR_INPUT - 1,
				MIN_STR_INPUT,
				bFinished );

	if( !bFinished )
	{
		if( !process_Calculation( sInputString, cOperand, dValue, m_Calculator ) )
			cout << "Sorry, but the calculation entered could not be properly parsed. \n\n";
		else
			m_Calculator->process_Calculation( cOperand, dValue );

	}

	return bFinished;
}

// Parses the string input and pulls the desired values to return to the caller.
//	Parameters:
//		sInput : String - The input to parse
//		cOperand : Char - Operand character to return to the caller
//		dValue : double - The value read in to return to the caller
//		m_Calculator : Calculator - Calculator object for referencing memory and operands
//	Returns: 
//		True if input is valid, False otherwise
//		Operand read in : char
//		Value read in : double
//////////////////////////////////////////////////////////////////////////////////////////////
bool process_Calculation( const char sInput[],
						  char& cOperand, 
						  double& dValue, 
						  Calculator* const m_Calculator )
{
	// Local variables
	bool bValid = true;
	char sMemChk[ MEM_CHECK_SIZE ] =
	{
		sInput[2],
		sInput[3],
		sInput[4]
	};

	// Check Operand
	cOperand = sInput[0];
	bValid &= m_Calculator->isValidOperand( cOperand );

	// Ensure space between operand and value.
	bValid &= sInput[1] == ' ';

	// Check value
	if( !strcmp( sMemChk, MEM_TRIGGER ) )
		dValue = m_Calculator->pull_Mem( );
	else
		dValue = atof( &(sInput[2]) );

	return bValid;
}