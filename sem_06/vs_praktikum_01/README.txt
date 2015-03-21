# Info
        All 'ant' commands need to be executed inside the directory
        where the 'build.xml' file is located. 'javac' and 'java' need
        to be run where the '.java' and '.class' files are (src or build
        directory)

        target 'bank' will start up a rmi server with to interfaces, one
        for the Customer, the other for the taxOffice. target 'customer'
        will then create some customers and print out information.
        target taxOffice will request some data about the existing
        customers, so it should be run after the 'customer' target, else
        there wont be much to see.

# Build

        either:
                'ant build'
        or:
                'javac *.java'

# Run
## Bank
        'ant bank' or
        'java Bank'

## Customer
        'ant customer' or
        'java CustomerClient'

## TaxOffice
        'ant taxOffice' or
        'java TaxOfficeClient'
