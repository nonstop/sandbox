package main

import (
    "log"; "flag"; "strconv"; "net"; "os";
)

func main() {
    var host *string = flag.String("host", "localhost", "hostname");
    var port *int = flag.Int("port", 9999, "port");
    flag.Parse();

    var ipAddr string = *host + ":" + strconv.Itoa(*port);
    log.Stdoutf("host=[%s] port=%d addr=[%s]", *host, *port, ipAddr);

    udpAddr, err := net.ResolveUDPAddr(ipAddr);
    if udpAddr == nil {
        log.Stdoutf("ResolveUDPAddr failed: %s", err.String());
        os.Exit(1);
    }
    udpConn, err := net.ListenUDP("udp", udpAddr);
    if udpConn == nil {
        log.Stdoutf("ListenUDP failed: %s", err.String());
        os.Exit(1);
    }
    udpConn.SetReadTimeout(10);
    stscall.SetNonblock(udpConn.fd, false);
    var buff [50]byte;
    sz, rUdpAddr, err := udpConn.ReadFromUDP(&buff);
    if err != nil {
        log.Stdoutf("Read failed: %s", err.String());
        os.Exit(1);
    }
    log.Stdoutf("read from remote addr: [%s] sz=%d buff=[%s]", rUdpAddr.String(), sz, buff);
//    var udpAddr *net.UDPAddr, err os.Error = net.ResolveUDPAddr(ipAddr);
}

