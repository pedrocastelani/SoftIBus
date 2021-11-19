#include <inttypes.h>
#include <SoftwareSerial.h>
class SoftwareSerial;
class Stream;

class SIBus
{
public:
  void begin(SoftwareSerial& serial);
  void begin(Stream& stream);
  void loop(void);
  uint16_t readChannel(uint8_t channelNr);

private:
  enum State
  {
    GET_LENGTH,
    GET_DATA,
    GET_CHKSUML,
    GET_CHKSUMH,
    DISCARD,
  };

  static const uint8_t PROTOCOL_LENGTH = 0x20;
  static const uint8_t PROTOCOL_OVERHEAD = 3; // <len><cmd><data....><chkl><chkh>
  static const uint8_t PROTOCOL_TIMEGAP = 3; // Packets are received very ~7ms so use ~half that for the gap
  static const uint8_t PROTOCOL_CHANNELS = 14;
  static const uint8_t PROTOCOL_COMMAND40 = 0x40; // Command is always 0x40

  uint8_t state;
  Stream* stream;
  uint32_t last;
  uint8_t buffer[PROTOCOL_LENGTH];
  uint8_t ptr;
  uint8_t len;
  uint16_t channel[PROTOCOL_CHANNELS];
  uint16_t chksum;
  uint8_t lchksum;
};

extern SIBus IBus;
