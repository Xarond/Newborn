#pragma once

#include "NewbornTcp.hpp"
#include "NewbornAtomicSharedPtr.hpp"
#include "NewbornP2PNetworkingService.hpp"
#include "NewbornNetPackets.hpp"
#include "NewbornZSTDCompression.hpp"
#include "NewbornNetCompatibility.hpp"

namespace Newborn {

NEWBORN_CLASS(PacketSocket);
NEWBORN_CLASS(LocalPacketSocket);
NEWBORN_CLASS(TcpPacketSocket);
NEWBORN_CLASS(P2PPacketSocket);

struct PacketStats {
  HashMap<PacketType, float> packetBytesPerSecond;
  float bytesPerSecond;
  PacketType worstPacketType;
  size_t worstPacketSize;
};

// Collects PacketStats over a given window of time.
class PacketStatCollector {
public:
  PacketStatCollector(float calculationWindow = 1.0f);

  void mix(size_t size);
  void mix(PacketType type, size_t size, bool addToTotal = true);
  void mix(HashMap<PacketType, size_t> const& sizes, bool addToTotal = true);

  // Should always return packet statistics for the most recent completed
  // window of time
  PacketStats stats() const;

private:
  void calculate();

  float m_calculationWindow;
  PacketStats m_stats;
  Map<PacketType, float> m_unmixed;
  size_t m_totalBytes;
  int64_t m_lastMixTime;
};

// Interface for bidirectional communication using NetPackets, based around a
// simple non-blocking polling interface.  Communication is assumed to be done
// via writeData() and readData(), and any delay in calling writeData or
// readData may translate directly into increased latency.
class PacketSocket {
public:
  virtual ~PacketSocket() = default;

  virtual bool isOpen() const = 0;
  virtual void close() = 0;

  // Takes all packets from the given list and queues them for sending.
  virtual void sendPackets(List<PacketPtr> packets) = 0;
  // Receives any packets from the incoming queue, if available
  virtual List<PacketPtr> receivePackets() = 0;

  // Returns true if any sent packets on the queue are still not completely
  // written.
  virtual bool sentPacketsPending() const = 0;

  // Write all data possible without blocking, returns true if any data was
  // actually written.
  virtual bool writeData() = 0;
  // Read all data available without blocking, returns true if any data was
  // actually received.
  virtual bool readData() = 0;

  // Should return incoming / outgoing packet stats, if they are tracked.
  // Default implementations return nothing.
  virtual Maybe<PacketStats> incomingStats() const;
  virtual Maybe<PacketStats> outgoingStats() const;

  virtual void setNetRules(NetCompatibilityRules netRules);
  virtual NetCompatibilityRules netRules() const;

private:
  NetCompatibilityRules m_netRules;
};

class CompressedPacketSocket : public PacketSocket {
public:
  virtual ~CompressedPacketSocket() = default;

  virtual void setCompressionStreamEnabled(bool enabled);
  virtual bool compressionStreamEnabled() const;
private:
  bool m_useCompressionStream = false;
protected:
  CompressionStream m_compressionStream;
  DecompressionStream m_decompressionStream;
};

// PacketSocket for local communication.
class LocalPacketSocket : public PacketSocket {
public:
  static pair<LocalPacketSocketUPtr, LocalPacketSocketUPtr> openPair();

  bool isOpen() const override;
  void close() override;

  void sendPackets(List<PacketPtr> packets) override;
  List<PacketPtr> receivePackets() override;

  bool sentPacketsPending() const override;

  // write / read for local sockets is actually a no-op, sendPackets places
  // packets directly in the incoming queue of the paired local socket.
  bool writeData() override;
  bool readData() override;

private:
  struct Pipe {
    Mutex mutex;
    Deque<PacketPtr> queue;
  };

  LocalPacketSocket(shared_ptr<Pipe> incomingPipe, weak_ptr<Pipe> outgoingPipe);

  AtomicSharedPtr<Pipe> m_incomingPipe;
  weak_ptr<Pipe> m_outgoingPipe;
};

// Wraps a TCP socket into a PacketSocket.
class TcpPacketSocket : public CompressedPacketSocket {
public:
  static TcpPacketSocketUPtr open(TcpSocketPtr socket);

  bool isOpen() const override;
  void close() override;

  void sendPackets(List<PacketPtr> packets) override;
  List<PacketPtr> receivePackets() override;

  bool sentPacketsPending() const override;

  bool writeData() override;
  bool readData() override;

  Maybe<PacketStats> incomingStats() const override;
  Maybe<PacketStats> outgoingStats() const override;
private:
  TcpPacketSocket(TcpSocketPtr socket);

  TcpSocketPtr m_socket;

  PacketStatCollector m_incomingStats;
  PacketStatCollector m_outgoingStats;
  ByteArray m_outputBuffer;
  ByteArray m_inputBuffer;
};

// Wraps a P2PSocket into a PacketSocket
class P2PPacketSocket : public CompressedPacketSocket {
public:
  static P2PPacketSocketUPtr open(P2PSocketUPtr socket);

  bool isOpen() const override;
  void close() override;

  void sendPackets(List<PacketPtr> packets) override;
  List<PacketPtr> receivePackets() override;

  bool sentPacketsPending() const override;

  bool writeData() override;
  bool readData() override;

  Maybe<PacketStats> incomingStats() const override;
  Maybe<PacketStats> outgoingStats() const override;

private:
  P2PPacketSocket(P2PSocketPtr socket);

  P2PSocketPtr m_socket;

  PacketStatCollector m_incomingStats;
  PacketStatCollector m_outgoingStats;
  Deque<ByteArray> m_outputMessages;
  Deque<ByteArray> m_inputMessages;
};

}
