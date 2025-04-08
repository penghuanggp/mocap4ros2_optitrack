#include <iostream>
#include <NatNetClient.h>
#include <NatNetTypes.h>
#include <NatNetCAPI.h>

int main() {
    NatNetClient client;

    // Connection parameters
    sNatNetClientConnectParams clientParams;
    clientParams.connectionType = ConnectionType_Multicast; // Or ConnectionType_Unicast
    clientParams.serverAddress = "192.168.0.125"; // Replace with your server address
    clientParams.localAddress = "192.168.0.48";   // Replace with your local address
    clientParams.serverCommandPort = 1510;
    clientParams.serverDataPort = 1511;

    // Connect to the server
    std::cout << "Connecting to server..." << std::endl;
    int result = client.Connect(clientParams);
    if (result != ErrorCode_OK) {
        std::cerr << "Error connecting to server: " << result << std::endl;
        return 1;
    }

    // Get server description
    sServerDescription serverDescription;
    memset(&serverDescription, 0, sizeof(serverDescription));
    client.GetServerDescription(&serverDescription);

    if (!serverDescription.HostPresent) {
        std::cerr << "Unable to connect to server. Host not present." << std::endl;
        return 1;
    }

    std::cout << "Connected to server" << std::endl;
    std::cout << "  Application: " << serverDescription.szHostApp << std::endl;
    std::cout << "  NatNet Version: " << serverDescription.NatNetVersion[0] << "."
              << serverDescription.NatNetVersion[1] << "."
              << serverDescription.NatNetVersion[2] << "."
              << serverDescription.NatNetVersion[3] << std::endl;
    std::cout << "  Server Name: " << serverDescription.szHostComputerName << std::endl;

    // Disconnect from the server
    client.Disconnect();

    return 0;
}
