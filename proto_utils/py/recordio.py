import six
from google.protobuf.internal import encoder


# I had to implement this because the tools in google.protobuf.internal.decoder
# read from a buffer, not from a file-like objcet
def readRawVarint32(stream):
    mask = 0x80  # (1 << 7)
    raw_varint32 = []
    while 1:
        b = stream.read(1)
        # eof
        if b == "":
            break
        raw_varint32.append(b)
        if not (ord(b) & mask):
            # we found a byte starting with a 0, which means
            # it's the last byte of this varint
            break
    return raw_varint32


def getSize(raw_varint32):
    result = 0
    shift = 0
    b = six.indexbytes(raw_varint32, 0)
    result |= ((ord(b) & 0x7f) << shift)
    return result


def writeDelimitedTo(message, stream):
    message_str = message.SerializeToString()
    delimiter = encoder._VarintBytes(len(message_str))
    stream.write(delimiter + message_str)


def readDelimitedFrom(MessageType, stream):
    raw_varint32 = readRawVarint32(stream)
    message = None
    if raw_varint32:
        size = getSize(raw_varint32)
        data = stream.read(size)
        if len(data) < size:
            return
        try:
            message = MessageType()
            message.ParseFromString(data)
            return message
        except Exception as e:
            return


def loadManyFromFile(MessageType, filename):
    out = []
    with open(filename, "rb") as fp:
        while True:
            msg = readDelimitedFrom(MessageType, fp)
            if msg:
                out.append(msg)
            else:
                break

    return out
