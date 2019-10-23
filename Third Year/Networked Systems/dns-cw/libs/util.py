""" Utility functions for gz01. """

import logging, logging.handlers
import signal, sys

DEBUG1 = 9
DEBUG2 = 8
logfile = "./ncsdns.log"

logging.addLevelName(DEBUG1, "DEBUG1")
logging.addLevelName(DEBUG2, "DEBUG2")

logger = logging.getLogger()
logger.setLevel(DEBUG2) # do not alter

# Create console handler and set level.  You may configure the
# following call to ch.setLevel in order to alter the verbosity of
# messages output to the console.
ch = logging.StreamHandler()
ch.setLevel(logging.INFO)
chformatter = logging.Formatter("%(levelname)-7s: %(message)s")
ch.setFormatter(chformatter)

# Create file handler and set verbosity level.  You may configure the
# following call to fh.setLevel in order to alter the verbosity of
# messages output to the log file.
fh = logging.handlers.RotatingFileHandler(logfile, 'a', 2000000, 5)
fh.setLevel(DEBUG2)
fhformatter = logging.Formatter("%(message)s")
fh.setFormatter(fhformatter)

logger.addHandler(ch)
logger.addHandler(fh)

def signal_handler(signal, frame):
  fh.doRollover()
  sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)


def hexdump(src, length=16):
  """ 
  Dump combined hex/ascii rep of a packed binary string to stdout.

  [Credit: stackoverflow] 

  src -- packed binary data to hex dump.
  length -- number of octets per line to display.
  """
  result = []
  digits = 4 if isinstance(src, str) else 2
  for i in range(0, len(src), length):
    s = src[i:i+length]
    hexa = " ".join(map("{0:0>2X}".format,s))
    text = "".join([chr(x) if 0x20 <= x < 0x7F else "." for x in s])
    result.append("%04X   %-*s   %s" % (i, length*(digits + 1), hexa, text))
  return "\n".join(result)


# TODO: remove the following

#FILTER=''.join([(len(repr(chr(x)))==3) and chr(x) or '.' for x in range(256)])

#def old_hexdump(src, length=16):
#  """ 
#  Dump combined hex/ascii rep of a packed binary string to stdout.
#
#  [Credit: code.activestate.com] 
#
#  src -- packed binary data to hex dump.
#  length -- number of octets per line to display.
#  """
#  result=[]
#  for i in range(0, len(src), length):
#    s = src[i:i+length]
#    hexa = ' '.join(["%02X"%x for x in s])
#    printable = s.translate(FILTER)
#    result.append("%04X   %-*s   %s\n" % (i, length*3, hexa, printable))
#  return (''.join(result)).strip()

