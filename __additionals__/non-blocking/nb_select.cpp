#include <sys/select.h>

void serverLoop(int serverFd) {
    fd_set readfds;
    int maxFd;
    struct timeval tv;
    int activity;

    while (true) {
        FD_ZERO(&readfds);
        FD_SET(serverFd, &readfds);
        maxFd = serverFd;

        // İstemci dosya tanımlayıcılarını ekleyin
        for (const auto& client : clients) {
            int cliFd = client.cliFd;
            FD_SET(cliFd, &readfds);
            if (cliFd > maxFd) {
                maxFd = cliFd;
            }
        }

        tv.tv_sec = 1;  // 1 saniye zaman aşımı
        tv.tv_usec = 0;

        activity = select(maxFd + 1, &readfds, NULL, NULL, &tv);

        if ((activity < 0) && (errno != EINTR)) {
            std::cerr << "select error" << std::endl;
        }

        // Yeni bir bağlantı varsa
        if (FD_ISSET(serverFd, &readfds)) {
            int newSocket;
            sockaddr_in addr;
            socklen_t addrlen = sizeof(addr);
            if ((newSocket = accept(serverFd, (sockaddr *)&addr, &addrlen)) < 0) {
                std::cerr << "accept error" << std::endl;
                continue;
            }

            setNonBlocking(newSocket);  // Yeni soketi non-blocking moda geçirin
            clients.push_back({newSocket, inet_ntoa(addr.sin_addr), ntohs(addr.sin_port)});
            std::cout << "New connection, socket fd: " << newSocket << std::endl;
        }

        // İstemcilerden gelen verileri işleyin
        for (auto& client : clients) {
            int cliFd = client.cliFd;
            if (FD_ISSET(cliFd, &readfds)) {
                char buffer[1024];
                int bytesRead = read(cliFd, buffer, sizeof(buffer));
                if (bytesRead == 0) {
                    // Bağlantı kapandı
                    std::cout << "Client disconnected, socket fd: " << cliFd << std::endl;
                    close(cliFd);
                    clients.erase(std::remove(clients.begin(), clients.end(), client), clients.end());
                } else if (bytesRead > 0) {
                    buffer[bytesRead] = '\0';
                    std::cout << "Received message: " << buffer << std::endl;
                }
            }
        }
    }
}



/*

Non-blocking I/O, bir işlem tamamlanmasa bile çağıran iş parçacığının beklemeden devam etmesine olanak tanır.
*/