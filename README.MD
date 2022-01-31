This is my basic kernel : 

# Example

https://www.youtube.com/watch?v=Rj0L3bI1cR4

# Download the sources

    git clone https://github.com/AlexandreArduino/mykernel.git
    cd mykernel/
    python setup.py
or
    chmod +x setup.sh
    ./setup.sh

Now, your folder mykernel/ has been replaced by the folder myos/

# Install depencies

    cd myos/
    make depencies

# Compile and run the kernel

    cd myos/
    make