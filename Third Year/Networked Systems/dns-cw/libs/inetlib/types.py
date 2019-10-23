""" Data types useful for Internet programming. """

from libs.util import *
import logging
from socket import inet_ntoa, inet_aton
import struct

class InetAddr:
  """ Internet address type. """

  def __init__(self, s):
    """ Initialize from a user-supplied dotted quad string. """
    self._a = s

  def toNetwork(self):
    """ Convert to network data format (four packed binary bytes). """
    return inet_aton(self._a)

  def __str__(self):
    return self._a

  def __repr__(self):
    return "<InetAddr %s>" % (self._a,)

  def __hash__(self):
    """ Returns a hash of this object based on its string rep. """
    return hash(self._a)

  def __cmp__(self, other):
    return cmp(self._a, other._a)

  def __eq__(self, other):
    return self._a == other._a

  @staticmethod
  def fromNetwork(n):
    return InetAddr(inet_ntoa(n))

class DomainName:
  """ Representation of a DNS domain name. """

  def __init__(self, s = ""):
    """ Initialize from a user-supplied string (optionally empty). """
    self._namelist = s.lstrip(".").split(".") # XXX this is subtle

  @staticmethod
  def fromData(data, offset = 0):
    """ Return a DomainName object from user-supplied packed binary
    data, with an optional offset modifier.  """

    dn = DomainName()
    dn._namelist = [ ]
    dn._length = 0
    followedPointer = False
    while offset < len(data): # loop over label sequence
      (labellen,) = struct.unpack_from("B", data, offset)
      if not labellen:
        dn._namelist.append('')
        if not followedPointer:
          dn._length += 1
        break
      elif (labellen >> 6) == 3:
        # this is a pointer label (see RFC 1035, Section 4.1.4)
        (pointer,) = struct.unpack_from(">H", data, offset)
        pointer &= 0x3FFF
        offset = pointer
        if not followedPointer:
          dn._length += 2
        followedPointer = True
      else:
        # else, this is a normal label (see RFC 1035, Section 4.1.2)
        offset = offset + 1
        (labeldata,) = struct.unpack_from("%ds" % (labellen,), data, offset)
        offset = offset + labellen
        if not followedPointer:
          dn._length += 1 + labellen
        dn._namelist.append(labeldata)
    return dn

  def parent(self):
    """ Return a DomainName object that represents the parent domain. """
    if self != DomainName("."):
      res = DomainName()
      res._namelist = self._namelist[1:]
      return res
    return None

  def __copy__(self):
    """  Return a copy of this DomainName object that loses any
    pointer information that may exist in this object's rep.  """

    res = DomainName(str(self))
    return res

  def __len__(self):
    """ Returns the length of the RFC 1035-compliant binary
    representation, taking into account pointers.  """

    if not hasattr(self, '_length'):
      l = 0
      for name in self._namelist:
        l += len(name) + 1
      return l
    return self._length

  def __str__(self):
    """ Returns a '.'-terminated string representation of this
    object. """
    self._namelist
    res = []
    for n in self._namelist:
        if type(n) == str:
            res.append(n.lower())
        else:
            res.append(n.decode('utf-8','backslashreplace').lower())
    # XXX subtle again, same reason
    return ".".join(res).rstrip(".") + "." 

  def __hash__(self):
    """ Returns a hash of this object based on its string rep. """
    return hash(str(self))

  def __cmp__(self, other):
    return cmp(str(self).lower(), str(other).lower())

  def __eq__(self, other):
    return str(self).lower() == str(other).lower()

  def __repr__(self):
    return str(self)

  def pack(self):
    """ Packs this object into RFC 1035-compliant data and returns the
    resulting binary-packed string. """

    l = []
    for name in self._namelist:
      l.append(struct.pack("B", len(name)).decode('unicode-escape'))
      if type(name) == str:
          l.append(name)
      else:
          l.append(name.decode('unicode-escape'))
    res = ("".join(l)).encode('ISO-8859-1')
    return res

