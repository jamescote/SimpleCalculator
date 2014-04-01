// Name: ioutil.cpp
// Description:  Contains the functions for the two other I/O utility
//               functions required: readBool and readString
// Written By:  James Coté
/////////////////////////////////////////////////////////////////////////////

// INCLUDES
#include <iostream>
#include <stdlib.h>
#include <climits>
#include <vector>
#include "ioutil.h"

// NAMESPACES
using namespace std;

// CONSTANTS
const char cNEWLINE = '\n'; 
const int iCHAR_MAX_LENGTH = 2;
const char cWHITESPACE = ' ';
const char cNULL_CHAR = '\0';

// Name: clearFailBuffer
// Description: Clears any fail state on cin then ignores what's left in the 
//              input buffer.
// Written by:  James Coté
/////////////////////////////////////////////////////////////////////////////
void clearFailBuffer()
{
    if( cin.fail() )
    {
	// Clear the fail state
	cin.clear();	
	cin.ignore( INT_MAX, '\n' );
    }    
}

// Name: clearString
// Description: Sets every value of the c-string to the null character.
// Parameters: char str[] - a pointer to the first element of the c-string
//                          that we wish to clear.
//             int maxlen - the maximum length of the c-string that we want 
//                          to clear (NOTE: may
//                          not be the full size of the character array).
// Written by: James Coté
/////////////////////////////////////////////////////////////////////////////
void clearString( char str[], int maxlen )
{
    // Go through the string, up to max length specified and set the
    // characters to null.
    for( int i = 0; i < maxlen; ++i )
    {
	str[i] = '\0';
    }    
}

// Description: reads in a long integer as required by our readInt function
// Method: Get a line from the user, determine if we triggered an end of file,
//         convert to a long int via strtol and finally set a boolean to see
//         if the long integer can be properly converted to a regular integer.
// Parameters: cInput - reference to the input array that is used to read in
//                      an integer.
//             bEOF - end of file flag, set if we get and eof.
//             bWrongInput - boolean to determine whether the integer entered
//                           was wrong or not.  Passed as reference to use
//                           for loop conditional.
// Return Value: returns the integer read in.  Return value will be different
//               if the user enters an integer outside the bounds of an int,
//               however, in that case, we ask them for a new input.
/////////////////////////////////////////////////////////////////////////////
int Get_int( char cInput[], bool &bWrongInput, bool &bEOF )
{
    // Local Variables
    long int liVar = 0;
    char *cpEndPtr = NULL;

    // Get a line of input from user to parse
    cin.getline( cInput, CHAR_MAX, cNEWLINE );
    bEOF = cin.eof(); 

    // Attempt to convert the input to a long int
    liVar = strtol( cInput, &cpEndPtr, 0 );

    // Set our wrong input flag to determine if the integer read in is correct.
    bWrongInput = ( ( cin.fail() || 
		      ( (*cpEndPtr) != '\0' ) || 
		      ( ( cInput[ 0 ] == cWHITESPACE ) ||
			( cInput[ 0 ] == (*cpEndPtr) ) ) || 
		      ( ( ( liVar > INT_MAX ) ||
			  ( liVar < INT_MIN ) ) ) ) && 
		    !bEOF );

    // return our int value
    return (int)liVar;
}

// Name: readInt( const char prompt[], bool &eof )
// Description: Successfully reads a valid integer.  uses error checking to
//              ensure only a proper integer is kept.
// Method: Prompt the user with a passed in prompt message then verify their
//		   input until the input is a proper integer value.
// Parameters: const char prompt[] - A message passed in to prompt the user 
//                                   to enter an integer.
//             bool &eof - A pointer to the program's end of file flag.  Set 
//                         to true if we reach the end of file, otherwise, 
//                         set to false if we get a valid integer.
// Returns: The integer that was input from the user.
/////////////////////////////////////////////////////////////////////////////
int readInt( const char prompt[], bool &eof )
{
    // Internal Variable Declarations:
    char cInputString[ CHAR_MAX ] = {};
    bool bWrongInput = true;
    int iReturnValue;

    // Output our prompt message to prompt the user to enter an integer.
    cout << prompt << endl;

    // read in the next int value
    iReturnValue = Get_int( cInputString, bWrongInput, eof );
    
    // While we don't have the input we want, re-prompt the user.
    while( bWrongInput )
    {
	// Output an error message:
	cout << "I'm sorry, '" << cInputString;
	cout << ( cin.fail() ? "..." : "" ) << "' isn't what I'm ";
	cout << "looking for.  Please try again.  " << endl << endl;
	cout << prompt << endl;

	// If we're in the fail state, clear it
	if( cin.fail() )
	{
	    // clear fail state
	    cin.clear();
	    
            // ignore anything left in the input buffer.
	    cin.ignore( INT_MAX, cNEWLINE );
	}
	
	// read in another int value.
	iReturnValue = Get_int( cInputString, bWrongInput, eof );
    }
    
    // If we're leaving because of end of file, clear fail flags.
    if( eof )
    {
	cin.clear();
    }

    // Return the integer we grabbed.
     return iReturnValue;
}

// Name: readBool( const char prompt[], bool &eof )
// Description: Prompts the user to enter in either a 'y' or 'n' character
//              followed by a newline. If we receive the wrong input, 
//              we will notify the user of an error then reprompt the user 
//              until we get the input we're looking for.
// Method: Using readChar( ), continue to prompt the user until the character
//		   'y' or 'n' is read in.
// Parameters: const char prompt - This is a string passed into the function
//                                 and is used to prompt the user for input.
//             bool &eof - This is a reference to a boolean variable used
//                         by the main program to determine when the end of
//                         file is reached.
// Return value: returns a requested boolean value from the user:
//               'y' = true, 'n' = false.
// Written by: James Coté
/////////////////////////////////////////////////////////////////////////////
bool readBool( const char prompt[], bool &eof )
{
    // Create variables
    bool bReturn;
    char cInput = '\0';

    // grab a character from the user, ensure it's a y or an n
    cInput = readChar( prompt, eof, 2, 'y', 'n' );
    
    if( !eof )
    {
	// Parse the first character
	switch( cInput )
	{
	case 'n':            
	    bReturn = false; 
	    break;
	case 'y':            
	    bReturn = true;  
	    break;
	default:      
	    // Prompt error message and request new input.
	    cerr << "I'm sorry, '" << cInput;
	    cerr << "' was not the answer we were looking for.";
	    cerr << "  Please try again." << endl << endl;
	    cerr << prompt << endl;
	    cInput = readChar( prompt, eof, 2, 'y', 'n' );
	    break;
	}
    }

    // Return our boolean value.
    return bReturn;
}

// Name: readChar
// Description: Reliably reads a character from the user, compares it with
//              any additional comparative arguments passed into the
//              function and ensures it's a character that the caller is
//              looking for.
// Method: Prompts the user with a message prompt and returns the character 
//		   read in.  If iVarArgCount is greater than 0, then the method
//		   will repeatedly prompt the user until the character passed in
//		   is one of the valid arguments requested.
// Parameters: prompt - Message to prompt the user to enter a character.
//             eof - EoF flag passed by reference to determine if the user
//                   triggers an end of file.
//             iVarArgCount - Integer that indicates how many variable
//                            arguments are passed into the function.
//             ... - variable character arguments that are used when the
//                   caller is looking for a specific character(s).
///////////////////////////////////////////////////////////////////////////
char readChar( const char prompt[], bool &eof, int iVarArgCount, ... )
{
    // Variable Declarations
    char cInput[ iCHAR_MAX_LENGTH ] = { };
    vector< char > cCompareList;
    bool bSuccess = false;

    // if there's variable arguments, store them in a character array
    if( iVarArgCount > 0 )
    {
		// Get our Variable Arguments
		va_list va_Character_List;
		va_start( va_Character_List, iVarArgCount );

		for( int i = 0; i < iVarArgCount; ++i )
		{
			cCompareList.push_back( ( char ) va_arg( va_Character_List, int ) );
		}

		va_end( va_Character_List );
    }

    // Prompt the user to enter a character
    cout << prompt << endl;
    
    // read in input
    cin.getline( cInput, ( iCHAR_MAX_LENGTH + 1 ), cNEWLINE );
    eof = cin.eof();

    // Error Checking
    while( !bSuccess & !eof )
    {
		if( cInput[ iCHAR_MAX_LENGTH - 1 ] != cNULL_CHAR )
		{
			// Error, output a message and re-prompt
			cerr << "I'm sorry, the format needs to contain a character ";
			cerr << "followed by a newline.  Please try again." << endl;
			cerr << endl << prompt << endl;

			// Clear the fail state and input buffer
			clearFailBuffer();
		}
		else if( !cCompareList.empty() )
		{
			// We have arguments to compare our input against
			for( vector< char >::iterator it = cCompareList.begin(); it != cCompareList.end(); ++it )
			{
				// If it is a character we're looking for, we succeeded.
				if( cInput[ 0 ] == (*it) )
				{
					bSuccess = true;
				}
			}
	    
			// If not successful, let the user know.
			if( !bSuccess )
			{
				cerr << "I'm sorry, I'm looking for one of the following";
				cerr << " characters: ";
		
				for( vector< char >::iterator it = cCompareList.begin(); it != cCompareList.end(); ++it )
				{
					cerr << "'" << (*it) << "'";
		    
					if( (it + 1) != cCompareList.end( )  )
					{
						if( (it + 2) == cCompareList.end() )
							cerr << ", or ";
						else
							cerr << ", ";
					}
				}

				cerr << "." << endl << endl;
				cerr << prompt << endl;
			}
		}
		else
			bSuccess = true;

		// "If at first you don't succeed, try, try again."
		if( !bSuccess )
		{
			// Clear the Input String
			clearString( cInput, iCHAR_MAX_LENGTH );

			// get more input from the user.
			cin.getline( cInput, ( iCHAR_MAX_LENGTH + 1 ), cNEWLINE );
			eof = cin.eof();
		}
    }
    
    // Clear fail state if we are leaving because of an end of file.
    if( eof )
    {
		cin.clear();	
    }

    // return the character
    return cInput[ 0 ];
}

// Function Name: readString
// Description: Prompts the user for a string between a minimum and maximum
//              length as specified by the variables passed in.  
//              Upon reading the string, it will parse the string to make 
//              sure it's within the specified bounds.  Once it receives 
//              a string from the user that is valid, it will exit the 
//              function.
// Method: Prompt the user until the input read in is within the min and
//		   max lengths as specified by the caller.
// Parameters: const char prompt[] - a c-string that contains a message for
//                                   the user prompting them to enter a
//                                   string.
//             char str[] - a pointer to the first element of the c-string
//                          that the user's string will be stored in.
//             int maxlen - an integer value that specifies the maximum
//                          length of the string to be read.
//             int minlen - an integer value that specifies the minimum
//                          length of the string to be read.
//             bool &eof - a reference to the program's end of file boolean
//                         to determine if the user enters an end of file
//                         ( ctrl+D ).
// Written by:  James Coté
/////////////////////////////////////////////////////////////////////
void readString( const char prompt[], char str[], int maxlen, int minlen, bool &eof )
{
    // Initialize our success flag
    bool bSuccess = false;

    // Ensure our str c-string is nullified.  Don't assume it is.
    clearString( str, maxlen );

    // Prompt the user for input
    cout << prompt << endl;

    // Get input from the user then ensure we haven't reached the 
    // end of file.
    cin.getline( str, ( maxlen + 1 ), '\n' );
    eof = cin.eof();

    //check to make sure it's valid.
    while( !bSuccess && !eof )
    {
	// Check to make sure minlen isn't set to 0 so we don't go out 
	// of bounds in the array.  Also, make sure that the string is
	// at least the minimum length.
	if( ( minlen != 0 ) && ( str[ minlen - 1 ] == '\0' ) )
	{
	    // Output an error message to let the user know that what they
	    // entered was too short of a string.
	    cerr << "I'm sorry, the minimum length of the string must be ";
	    cerr << minlen << " long.  Please try again." << endl << endl;
	    cerr << prompt << endl;
	    clearString( str, maxlen );
	}
	else if( cin.fail() )  // Entered fail state (input > maxlength)
	{
	    cerr << "I'm sorry, but the string you entered was too long.";
	    cerr << "  Please keep it at a maximum length of " << maxlen;
	    cerr << ".  Thank you." << endl << endl << prompt << endl;
	    clearFailBuffer();
	}
	else                   // We succeeded, trigger our success flag.
	{
	    bSuccess = true;
	}

	// If we didn't succeed, read in another string from the user.
	if( !bSuccess )
	{
	    cin.getline( str, ( maxlen + 1 ), '\n' );
	    eof = cin.eof();
	}
    }

    // If we're leaving because of end of file, clear fail flags.
    if( eof )
    {
	cin.clear();
    }

    // Exit function
    return;
}
