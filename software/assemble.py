import sys, getopt, os, re

def main( argv ):
    opts, args = getopt.getopt( argv, 's:' )
    for opt, arg in opts:
        if opt == '-s':
            if arg == '':
                print "Please provide the name of the state to be loaded."
            elif os.path.isfile( 'src/states/{0}.h'.format( arg ) ):
                f = open( 'src/master.h', 'w' )
                f.write( """#include <Arduino.h>
#include "states/{0}.h"

#include "Pins.h"

State* singleState = new S_{0}();

void setup() {{
    initializePins();
    singleState -> onStart();
}}

void loop() {{
    singleState -> onLoop();
}}""".format( arg ) )
                f.close()
            else:
                print "\"src/states/{0}.h\" was not found...".format( arg )
            sys.exit()

    if len( args ) == 0:
        print "Please enter the name of the starting state as an argument."
        sys.exit()
    elif not os.path.isfile( 'src/states/{0}.h'.format( args[0] ) ):
        print "Please enter a valid starting state."
        sys.exit()
    else:
        state_names = [ "Null" ] 
        states = [ { "name": "Null", "primary": "Null", "alternate": "Null", "error": "Null" } ]
        stack = [ args[0] ]
        while len( stack ) > 0:
            state = stack.pop()
            if state not in state_names:
                state_names.append( state )
                stateDict = getInfo( state )
                states.append( stateDict )
                stack.append( stateDict['primary'] )
                stack.append( stateDict['alternate'] )
                stack.append( stateDict['error'] )
        f = open( 'src/master.h', 'w' )
        assemble( f, states, state_names )
        f.close()
        sys.exit()

def getInfo( stateName ):
    stateDict = { "name": stateName, "primary": "Null", "alternate": "Null", "error": "Null" }
    try:
        f = open( 'src/states/{0}.h'.format( stateName ), 'r' ) 
        lines = f.readlines()
        f.close()           
        patt = re.compile( "<tt>.*<tt>" )
        for i in range( len( lines ) ):
            if " transitionCondition() " in lines[i]:
                match = patt.search( lines[i+1] )
                if match:
                    matchStr = match.group( 0 )
                    stateDict['primary'] = matchStr.replace( '<tt>', '' )
                else: 
                    print "Expected transistion target for transistionCondition() in {0}".format( stateName )
                    sys.exit()
            if " alternateCondition() " in lines[i]:
                match = patt.search( lines[i+1] )
                if match:
                    matchStr = match.group( 0 )
                    stateDict['alternate'] = matchStr.replace( '<tt>', '' )
                else: 
                    print "Expected transistion target for alternateCondition() in {0}".format( stateName )
                    sys.exit()
            if " errorCondition() " in lines[i]:
                match = patt.search( lines[i+1] )
                if match:
                    matchStr = match.group( 0 )
                    stateDict['error'] = matchStr.replace( '<tt>', '' )
                else: 
                    print "Expected transistion target for errorCondition() in {0}".format( stateName )
                    sys.exit()
        return stateDict
    except IOError:
        print 'Could not open \"src/states/{0}.h\". Does it exist?'.format( stateName )
        sys.exit()

def array2str( arr ): 
    if len( arr ) == 0:
        return "{{ }}"
    string = "{{ {0}".format( arr[0] )
    for i in range( 1, len( arr ) ):
        string +=  ", {0}".format( arr[i] )
    string += " }"
    return string

def assemble( f, dicts, names ):
    for name in names:
        f.write( "#include \"states/{0}.h\"\n".format( name ) )
    f.write( "\n#define STARTING_STATE 1\n\n" )
    classNames = map( lambda x : "new S_{0}()".format( x ), names )
    transitionIndices = map( lambda x : names.index( x['primary'] ), dicts )
    alternateIndices = map( lambda x : names.index( x['alternate'] ), dicts )
    errorIndices = map( lambda x : names.index( x['error'] ), dicts )
    f.write( "State * states[] = {0};\n\n".format( array2str( classNames ) ) )
    f.write( "uint8_t defaultTransitions[] = {0};\n".format( array2str( transitionIndices ) ) )
    f.write( "uint8_t alternateTransitions[] = {0};\n".format( array2str( alternateIndices ) ) )
    f.write( "uint8_t errorTransitions[] = {0};\n".format( array2str( errorIndices ) ) )
    f.write( """
#include "Pins.h"

void setup() {
    initializePins();
    states[STARTING_STATE] -> onStart();
}

void loop() {
    static uint8_t currentStateID = STARTING_STATE;
    State * currentState = states[currentStateID];

    currentState -> onLoop();
    if( currentState -> transitionCondition() ) {
        currentState -> onEnd();
        currentStateID = defaultTransitions[currentStateID];
        states[currentStateID] -> onStart();
    } else if( currentState -> alternateCondition() ) {
        currentState -> onEnd();
        currentStateID = alternateTransitions[currentStateID];
        states[currentStateID] -> onStart();   
    } else if( currentState -> errorCondition() ) {
        currentState -> onEnd();
        currentStateID = errorTransitions[currentStateID];
        states[currentStateID] -> onStart();         
    }
}""")



if __name__ == "__main__":
    main( sys.argv[1:] )

