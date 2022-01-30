This is my basic kernel : 


# Download the sources

    git clone https://github.com/AlexandreArduino/mykernel.git
    cd mykernel/
    python setup.py

Now, your folder mykernel/ has been replaced by the folder myos/

# Install depencies

    cd myos/
    make depencies

# Compile and run the kernel

    cd myos/
    make