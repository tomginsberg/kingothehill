if [ $# -ne 1 ]
then 
    echo "Please provide a single argument, the name of the state to be constructed."
else
    sed "s/{1}/$1/" misc/SampleState.h > src/states/$1.h
fi
