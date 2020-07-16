The command format:
keygen:
	hw3 keygen -p=pphrase -t=period
crypt or decrpt:
	hw3 crypt -k=keyfile [file]
invkey:
	hw3 invkey keyfile
histo:
	hw3 histo -t=period -i=which [file]
solve:
	hw3 solve -l=max_t file


Known Bug:
None.


Citations:
In keygen.c, the code in the random_integer function refers to the code on the homework webpage and refers to my hw2. In function keygen, the key generation algorithm refers to the hw3 webpage.



