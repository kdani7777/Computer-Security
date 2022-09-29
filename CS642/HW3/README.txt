How to run our code: Our code is run from the command line by entering "python scanner.py filename.pcap"
where Filename is substituted with the name of a pcap file.

ARP Spoofing: We created a dictionary of valid MAC to IP mappings and then checked each packet to see that the source IP and the source hardware matched according to the dictionary. If they did not match, we printed out a warning of spoofing.

Port scan: We check to see if the packet is a TCP SYN packet and if it is, we search for port scanning attempts. We record the destination IP of every server hit as well as what port within the server was hit by which packet. If the number of ports hit on an IP is at least 100, we print a message warning of a port scan.

TCP SYN flood: For a given IP, we check the number of times each port is hit. If a port is hit over 100 times within one second we print a warning of a SYN Flood.
